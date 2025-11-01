#include "xml_parser.hpp"

#include <cstring>
#include <memory>
#include <regex>
#include <string>

#include "../conversion.hpp"
#include "logger.hpp"
#include "sear_error.hpp"

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {
// Public Methods of XMLParser
nlohmann::json XMLParser::buildJSONString(SecurityRequest& request) {
  std::string xml_buffer;

  const char* p_raw_result = request.getRawResultPointer();
  int raw_result_length    = request.getRawResultLength();

  auto xml_ascii_result_unique_ptr =
      std::make_unique<char[]>(raw_result_length + 1);
  std::memset(xml_ascii_result_unique_ptr.get(), 0, raw_result_length + 1);

  // Build a JSON string from the XML result string, SMO return and Reason
  // Codes
  Logger::getInstance().debug("Raw EBCDIC encoded result XML:");
  Logger::getInstance().hexDump(p_raw_result, raw_result_length);

  std::memcpy(xml_ascii_result_unique_ptr.get(), p_raw_result,
              raw_result_length);

  std::string ebcdic_string = std::string(xml_ascii_result_unique_ptr.get());

  xml_buffer = toUTF8(ebcdic_string, "IBM-1047");

  Logger::getInstance().debug("Decoded result XML:", xml_buffer);

  // Regular expression designed to match the header attributes, generic body,
  // and closing tags of the xml
  std::regex full_xml_regex{
      R"~(<\?xml version="1\.0" encoding="IBM-1047"\?><securityresult xmlns="http:\/\/www\.ibm\.com\/systems\/zos\/saf\/IRRSMO00Result1"><([a-z]*) ([^>]*)>(<.+>)<returncode>.*<\/returncode><reasoncode>.*<\/reasoncode><\/securityresult>)~"};
  std::smatch useful_xml_substrings;

  nlohmann::json result_json;

  if (regex_match(xml_buffer, useful_xml_substrings, full_xml_regex)) {
    // Use sub-matches in the regular expression to pull out useful
    // information
    std::string admin_type     = useful_xml_substrings[1];
    std::string admin_xml_body = useful_xml_substrings[3];

    // Erase the profile close tag as it messes up later regex parsing
    std::string admin_close_tag = R"(</)" + admin_type + ">";
    admin_xml_body.erase(admin_xml_body.find(admin_close_tag),
                         admin_close_tag.length());

    XMLParser::parseXMLTags(result_json, admin_xml_body);

    request.setSEARReturnCode(0);
  } else {
    // If the XML does not match the main regular expression, then return
    // this string to indicate an error
    request.setSEARReturnCode(4);
    throw SEARError("unable to parse XML returned by IRRSMO00");
  }

  return result_json;
}

// Private Methods of XMLParser
void XMLParser::parseXMLTags(nlohmann::json& input_json,
                             std::string input_xml_string) {
  // Parse the outer layer of the XML (the tags) for attributes and tag names
  // with regex Ex:
  // <safreturncode>0</safreturncode><returncode>0</returncode><reasoncode>0</reasoncode><image>ADDUSER
  // SQUIDWRD </image><message>ICH01024I User SQUIDWRD is defined as
  // PROTECTED.</message>
  std::regex outermost_xml_tags_regex{R"(<([a-z]*)>.*</([a-z]*)>)"};
  std::smatch outermost_xml_tags, data_around_current_tag;

  // If we do not match our generic regular expression for an XML attribute
  if (!regex_match(input_xml_string, outermost_xml_tags,
                   outermost_xml_tags_regex)) {
    return;
  }
  // Use regex substrings to identify the name of the current xml tag
  // Ex: safreturncode
  std::string::size_type start_index = 0;
  std::string current_tag            = outermost_xml_tags[1];
  while (current_tag != "") {
    // Enter a loop iterating through xml looking for XML tags within the
    // "current" tag In a practical sense, from SMO this ends up parsing
    // "Command" entries, then looking At individual xml entries within
    // these "Command" entries like "image" or "message"
    std::regex current_tags_regex{"<" + current_tag + R"~(>(.*?)(<\/)~" +
                                  current_tag + ">)(<(.*?)>)?.*"};
    std::string remaining_string = input_xml_string.substr(start_index);
    if (regex_match(remaining_string, data_around_current_tag,
                    current_tags_regex)) {
      // Ex: 1) 0 2) </safreturncode> 3) <returncode>  4) returncode
      std::string data_within_current_tags = data_around_current_tag[1];
      XMLParser::parseXMLData(input_json, data_within_current_tags,
                              current_tag);
      start_index += current_tag.length() * 2 +
                     ((std::string) "<></>").length() +
                     data_within_current_tags.length();
      // Update current tag with the "next" tag found after the current
      // set
      current_tag = data_around_current_tag[4];
    }
  }
};

void XMLParser::parseXMLData(nlohmann::json& input_json,
                             const std::string& data_within_outer_tags,
                             const std::string& outer_tag) {
  // Parse data from within XML tags and add the values to the JSON
  if (data_within_outer_tags.find("<") == std::string::npos) {
    nlohmann::json data_as_json = data_within_outer_tags;
    XMLParser::updateJSON(input_json, data_as_json, outer_tag);
    return;
  }
  // If we did not return, there is another xml tag within this data (nested)
  nlohmann::json nested_json;
  std::string nested_xml = data_within_outer_tags;
  XMLParser::parseXMLTags(nested_json, nested_xml);
  XMLParser::updateJSON(input_json, nested_json, outer_tag);
}

void XMLParser::updateJSON(nlohmann::json& input_json,
                           nlohmann::json& inner_data, std::string outer_tag) {
  // Add specified information (inner_data) to the input_json_p JSON object
  // using the specified key (outer_tag)
  outer_tag = XMLParser::replaceXMLChars(outer_tag);
  if (inner_data.is_string()) {
    inner_data = XMLParser::replaceXMLChars(inner_data);
  }
  if (!input_json.contains(outer_tag)) {
    // If we do not already have this tag used in our object (at this
    // layer), just add data
    input_json[outer_tag] = inner_data;
  } else {
    // If we do already use this tag, add the data to the list (may have to make
    // the json attribute a list first)
    if (input_json[outer_tag].is_array()) {
      input_json[outer_tag].push_back(inner_data);
    } else {
      input_json[outer_tag] = {input_json[outer_tag], inner_data};
    }
  }
}

std::string XMLParser::replaceXMLChars(std::string xml_data) {
  std::string amp = "&amp;", gt = "&gt;", lt = "&lt;", quot = "&quot;",
              apos = "&apos;";
  std::size_t index;

  index = xml_data.find("&");
  if (index == std::string::npos) {
    return xml_data;
  }
  do {
    xml_data = XMLParser::replaceSubstring(xml_data, gt, ">", index);
    xml_data = XMLParser::replaceSubstring(xml_data, lt, "<", index);
    xml_data = XMLParser::replaceSubstring(xml_data, apos, "'", index);
    xml_data = XMLParser::replaceSubstring(xml_data, quot, "\"", index);
    xml_data = XMLParser::replaceSubstring(xml_data, amp, "&", index);
    index    = xml_data.find("&", index + 1);
  } while (index != std::string::npos);
  return xml_data;
}

std::string XMLParser::replaceSubstring(std::string data,
                                        std::string& substring,
                                        std::string replacement,
                                        std::size_t start) {
  std::size_t match;
  if ((data.length() - start) < substring.length()) {
    return data;
  }
  match = data.find(substring, start);
  if (match == std::string::npos) {
    return data;
  }
  data.replace(match, substring.length(), replacement);
  return data;
}
}  // namespace SEAR
