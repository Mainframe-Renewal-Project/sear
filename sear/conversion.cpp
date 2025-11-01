#include "conversion.hpp"
#include <iconv.h>
#include <stdexcept>
#include <vector>

std::string convert(std::string input, std::string_view inputCodepage, std::string_view outputCodepage) {
    std::string fromCode{inputCodepage};
    std::string toCode{outputCodepage};
    iconv_t conv = ::iconv_open(toCode.c_str(), fromCode.c_str());

    if (conv == (iconv_t)-1) {
      if (errno == EINVAL)
        throw std::runtime_error(
            "not supported from " + fromCode + " to " + toCode);
      else
        throw std::runtime_error("unknown error");
    }

    char* src_ptr = &input[0];
    size_t src_size = input.size();

    std::vector<char> buf(1024);
    std::string dst;

    while (0 < src_size) {
      char* dst_ptr = &buf[0];
      size_t dst_size = buf.size();
      size_t res = ::iconv(conv, &src_ptr, &src_size, &dst_ptr, &dst_size);
      if (res == (size_t)-1) {
        if (errno == E2BIG)  {
          // ignore this error
        } else {
            switch (errno) {
            case EILSEQ:
            case EINVAL:
                throw std::runtime_error("invalid multibyte chars");
            default:
                throw std::runtime_error("unknown error");
            }
        }
      }
      dst.append(&buf[0], buf.size() - dst_size);
    }

    iconv_close(conv);

    return dst;
}

/** Converts string from specified codepage to UTF-8, defaults to IBM-1047 if nothing is specified */
std::string SEAR::toUTF8(const std::string& input, std::string_view codepage) {
  return convert(input,codepage,"UTF-8");
}

/** Converts string from UTF-8 to specified codepage, defaults to IBM-1047 if nothing is specified */
std::string SEAR::fromUTF8(const std::string& input, std::string_view codepage) {
  return convert(input,"UTF-8",codepage);
}