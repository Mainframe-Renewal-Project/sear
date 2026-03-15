#include <sys/resource.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Project headers
#include "sear.h"
#include "tests/mock/irrsdl64.hpp"
#include "tests/mock/irrseq00.hpp"
#include "tests/mock/irrsmo64.hpp"
#include "unit_test_utilities.hpp"

using namespace std::chrono;

extern "C" {
void setUp(void) {}

void tearDown(void) {}
}

struct Metric {
  std::string name;
  double time_ms;
  double mem_growth_kb;
};

// Global vector to store all benchmark results
std::vector<Metric> all_results;

// Function to run benchmarks and store results
template <typename F>
// Benchmark Helper function
void run_bench(const std::string& name, int iterations, F func) {
  struct rusage usage_before, usage_after;

  // Get high-water mark BEFORE test
  getrusage(RUSAGE_SELF, &usage_before);
  long mem_before = usage_before.ru_maxrss;

  // Warm-up
  for (int i = 0; i < 5; ++i) func();

  auto start = high_resolution_clock::now();
  for (int i = 0; i < iterations; ++i) {
    func();
  }
  auto end = high_resolution_clock::now();

  // Get high-water mark AFTER test
  getrusage(RUSAGE_SELF, &usage_after);
  long mem_after                       = usage_after.ru_maxrss;

  duration<double, std::milli> elapsed = end - start;
  double avg_time_ms                   = elapsed.count() / iterations;

  // If mem_after > mem_before, this test forced the app to allocate more RAM.
  long mem_growth = mem_after - mem_before;
  all_results.push_back({name, avg_time_ms, static_cast<double>(mem_growth)});
}

int main() {
  const int N      = 1000;
  const bool debug = false;
  struct rusage startup_usage;

  auto suite_start_time = high_resolution_clock::now();
  getrusage(RUSAGE_SELF, &startup_usage);
  long baseline_mem = startup_usage.ru_maxrss;

  // Validation Logic Benchmark
  run_bench("Validation_Syntax_Error", N, [&]() {
    std::string json = "{\"invalid\": json...";
    sear(json.c_str(), json.length(), debug);
  });

  // IRRSMO00 Benchmarks (XML Generation)
  run_bench("IRRSMO_Generate_Add_User", N, [&]() {
    std::string json = get_json_sample(
        "tests/irrsmo00/request_samples/user/test_add_user_request.json");
    sear_result_t* res = sear(json.c_str(), json.length(), debug);
  });

  // IRRSMO00 Benchmarks (XML Parsing)
  run_bench("IRRSMO00_Parse_Add_User_Result", N, [&]() {
    std::string json = get_json_sample(
        "tests/irrsmo00/request_samples/user/test_add_user_request.json");
    // Mock the incoming XML from RACF
    int len;
    irrsmo64_result_mock = get_xml_sample(
        "tests/irrsmo00/request_samples/user/test_add_user_request.xml", &len);
    irrsmo64_result_size_mock = len;

    sear(json.c_str(), json.length(), debug);
    free(irrsmo64_result_mock);  // Prevent memory leak, as get_xml_sample
                                 // allocates memory for irrsmo64_result_mock
  });

  // IRRSEQ00 Benchmarks (Extraction)
  run_bench("IRRSEQ00_Generate_Extract_User", N, [&]() {
    std::string json = get_json_sample(
        "tests/irrseq00/request_samples/user/"
        "test_extract_next_user_request.json");
    sear(json.c_str(), json.length(), debug);
  });

  // IRRSDL00 Benchmarks (Keyrings)
  run_bench("IRRSDL00_Generate_Extract_Keyring", N, [&]() {
    std::string json = get_json_sample(
        "tests/irrsdl00/request_samples/keyring/"
        "test_extract_keyring_request.json");
    sear(json.c_str(), json.length(), debug);
  });

  // Total Suite Time
  auto suite_end_time = high_resolution_clock::now();
  duration<double, std::milli> total_duration =
      suite_end_time - suite_start_time;

  // Memory Metric
  struct rusage final_usage;
  getrusage(RUSAGE_SELF, &final_usage);

  std::cout << "[\n";
  for (size_t i = 0; i < all_results.size(); ++i) {
    // Time Entry
    std::cout << "  {\n";
    std::cout << "    \"name\": \"" << all_results[i].name << " (Time)\",\n";
    std::cout << "    \"unit\": \"ms\",\n";
    std::cout << "    \"value\": " << std::fixed << std::setprecision(4)
              << all_results[i].time_ms << "\n";
    std::cout << "  },\n";

    // Memory Entry
    std::cout << "  {\n";
    std::cout << "    \"name\": \"" << all_results[i].name << " (Memory)\",\n";
    std::cout << "    \"unit\": \"KB\",\n";
    std::cout << "    \"value\": " << std::fixed << std::setprecision(4)
              << all_results[i].mem_growth_kb << "\n";
    std::cout << "  }" << (i == all_results.size() - 1 ? "" : ",") << "\n";
  }
  std::cout << "]\n";

  return 0;
}
