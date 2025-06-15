#define _UNIX03_SOURCE

#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *raw_request;
  int raw_request_length;
  char *raw_result;
  int raw_result_length;
  char *result_json;
} sear_result_t;

typedef sear_result_t *(*sear_t)(const char *, int, bool);

int main(int argc, char **argv) {
  // Parameter Validation
  if (argc != 2) {
    printf("Usage: %s <request json>\n", argv[0]);
    return 1;
  }

  // DLL Processing
  void *lib_handle;
  sear_t sear;

  lib_handle = dlopen("libsear.so", RTLD_NOW);
  if (lib_handle == NULL) {
    perror("Unable to load 'libsear.so'.");
    return 2;
  }

  sear = (sear_t)dlsym(lib_handle, "sear");
  if (sear == NULL) {
    perror("Unable to resolve symbol 'sear()'.");
    return 3;
  }

  // Open Request JSON File
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("");
    printf("Unable to open '%s' for reading.\n", argv[1]);
    return 4;
  }
  fseek(fp, 0, SEEK_END);
  long int size = ftell(fp);
  char request_json[size];
  fseek(fp, 0, SEEK_SET);
  fread(request_json, size, 1, fp);
  fclose(fp);

  // Make Request;
  sear_result_t *sear_result = sear(request_json, size, true);
  dlclose(lib_handle);

  // Write Raw Request
  char raw_request_file[] = "request.bin";
  fp                      = fopen(raw_request_file, "wb");
  if (fp == NULL) {
    perror("");
    printf("Unable to open '%s' for writing.\n", raw_request_file);
    return 5;
  }
  fwrite(sear_result->raw_request, sear_result->raw_request_length, 1, fp);
  fclose(fp);

  // Write Raw Result
  char raw_result_file[] = "result.bin";
  fp                     = fopen(raw_result_file, "wb");
  if (fp == NULL) {
    perror("");
    printf("Unable to open '%s' for writing.\n", raw_result_file);
    return 6;
  }
  fwrite(sear_result->raw_result, sear_result->raw_result_length, 1, fp);
  fclose(fp);

  // Write Result JSON
  char result_json_file[] = "result.json";
  fp                      = fopen(result_json_file, "wb");
  if (fp == NULL) {
    perror("");
    printf("Unable to open '%s' for writing.\n", "result_json_file");
    return 7;
  }
  fwrite(sear_result->result_json, strlen(sear_result->result_json), 1, fp);
  fclose(fp);

  return 0;
}
