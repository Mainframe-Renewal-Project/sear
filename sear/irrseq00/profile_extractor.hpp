#ifndef __SEAR_PROFILE_EXTRACTOR_H_
#define __SEAR_PROFILE_EXTRACTOR_H_

#include <cstdint>
#include <cstdlib>
#include <string>

#include "extractor.hpp"
#include "irrseq00.hpp"
#include "logger.hpp"
#include "sear_result.h"
#include "security_request.hpp"

namespace SEAR {
class ProfileExtractor : public Extractor {
 private:
  static void buildGenericExtractRequest(
      generic_extract_underbar_arg_area_t *arg_area, std::string profile_name,
      std::string class_name, uint8_t function_code);
  static void buildRACFOptionsExtractRequest(
      racf_options_extract_underbar_arg_area_t *arg_area);
  static void buildRACFRRSFExtractRequest(
      racf_rrsf_extract_underbar_arg_area_t *arg_area);
  static char *cloneBuffer(const char *p_buffer, const int &length);

 public:
  void extract(SecurityRequest &request) override;
};

struct DefaultDeleter {
  void operator()(void *ptr) const {
    Logger::getInstance().debugFree(ptr);
    std::free(ptr);
    Logger::getInstance().debug("Done");
  }
};

template <typename T, typename Deleter = DefaultDeleter, typename... Targs>
auto make_unique31(Targs &&...args) -> std::unique_ptr<T, Deleter> {
  T *p = static_cast<T *>(__malloc31(sizeof(T)));
  if (p == nullptr) {
    throw std::bad_alloc();
  }
  Logger::getInstance().debugAllocate(p, 31, sizeof(T));
  new (p) T(std::forward(args)...);
  return std::unique_ptr<T, Deleter>(p);
}
}  // namespace SEAR

#endif
