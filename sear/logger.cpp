#include "logger.hpp"

#include <cctype>
#include <csignal>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {
Logger::Logger() { debug_ = false; }

Logger& Logger::getInstance() {
  static Logger instance;
  return instance;
}

void Logger::setDebug(bool debug) { debug_ = debug; }

void Logger::debug(const std::string& message, const std::string& body) const {
  if (!debug_) {
    return;
  }
  std::string sear_header = "sear:";
  if (isatty(fileno(stdout))) {
    sear_header = ansi_bright_yellow_ + sear_header + ansi_reset_;
  }
  std::cout << sear_header << " " << message << std::endl;
  if (body != "") {
    char max_line_length = 80;
    std::cout << std::endl;
    for (size_t i = 0; i < body.length(); i += max_line_length) {
      std::cout << body.substr(i, max_line_length) << std::endl;
    }
    std::cout << std::endl;
  }
}

void Logger::debugAllocate(const void* ptr, int rmode, int byte_count) const {
  if (!debug_) {
    return;
  }
  std::ostringstream oss;
  oss << "Allocated " << byte_count << " bytes in " << rmode
      << "-bit memory at address " << ptr;
  Logger::debug(oss.str());
}

void Logger::debugFree(const void* ptr) const {
  if (!debug_) {
    return;
  }
  std::ostringstream oss;
  oss << "Freeing memory at address " << ptr << " ...";
  Logger::debug(oss.str());
}

void Logger::hexDump(const char* p_buffer, int length) const {
  if (!debug_) {
    return;
  }

  if (p_buffer == nullptr) {
    std::cout << std::endl << "N/A" << std::endl << std::endl;
    return;
  }

  auto decoded_unique_ptr = std::make_unique<char[]>(length);
  std::memcpy(decoded_unique_ptr.get(), p_buffer, length);
  __e2a_l(decoded_unique_ptr.get(), length);

  std::string hex_dump = "\n";
  std::ostringstream hex_stream;
  std::ostringstream decoded_stream;
  for (int i = 0; i < length; i++) {
    if (i % 16 == 0) {
      std::string hex_string = hex_stream.str();
      if (isatty(fileno(stdout))) {
        hex_string.resize(195, ' ');
      } else {
        hex_string.resize(51, ' ');
      }
      if (i != 0) {
        hex_dump += hex_string + decoded_stream.str() + "\n";
      }
      hex_stream.str("");
      hex_stream.clear();
      decoded_stream.str("");
      decoded_stream.clear();
      hex_stream << std::hex << std::setw(8) << std::setfill('0') << i << ":";
    }
    if (i % 2 == 0) {
      hex_stream << " ";
    }
    if (std::isprint(static_cast<unsigned char>(decoded_unique_ptr.get()[i]))) {
      if (isatty(fileno(stdout))) {
        hex_stream << ansi_bright_green_;
        decoded_stream << ansi_bright_green_ << decoded_unique_ptr.get()[i]
                       << ansi_reset_;
      } else {
        decoded_stream << decoded_unique_ptr.get()[i];
      }
    } else {
      if (isatty(fileno(stdout))) {
        if (decoded_unique_ptr.get()[i] == '\t' ||
            decoded_unique_ptr.get()[i] == '\r' ||
            decoded_unique_ptr.get()[i] == '\n') {
          hex_stream << ansi_bright_yellow_;
          decoded_stream << ansi_bright_yellow_ << '.' << ansi_reset_;
        } else {
          hex_stream << ansi_bright_red_;
          decoded_stream << ansi_bright_red_ << '.' << ansi_reset_;
        }
      } else {
        decoded_stream << '.';
      }
    }
    hex_stream << std::hex << std::setw(2) << std::setfill('0')
               << (static_cast<int>(p_buffer[i]) & 0xff);
    if (isatty(fileno(stdout))) {
      hex_stream << ansi_reset_;
    }
  }

  std::string hex_string = hex_stream.str();
  if (isatty(fileno(stdout))) {
    if (length % 16 == 0) {
      hex_string.resize(195, ' ');
    } else {
      hex_string.resize(51 + ((length % 16) * 5) + ((length % 16) * 4), ' ');
    }
  } else {
    hex_string.resize(51, ' ');
  }
  hex_dump += hex_string + decoded_stream.str() + "\n";

  std::cout << hex_dump << std::endl;
}
};  // namespace SEAR
