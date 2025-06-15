#include "irrseq00.hpp"

#include <stdlib.h>

#include <cstring>

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

// Use htonl() to convert 32-bit values from little endian to big endian.
// On z/OS this macro does nothing since "network order" and z/Architecture are
// both big endian. This is only necessary for unit testing off platform.
#include <arpa/inet.h>

// These globals need to be defined differently depending
// on where they are compiled since BINDER on z/OS
// and off platform link editors (i.e., Mac/Linux)
// resolve symbols differently.
#ifndef __TOS_390__
char *r_admin_result_mock         = NULL;
uint32_t r_admin_result_size_mock = 0;
uint32_t r_admin_rc_mock          = 0;
uint32_t r_admin_saf_rc_mock      = 0;
uint32_t r_admin_racf_rc_mock     = 0;
uint32_t r_admin_racf_reason_mock = 0;
#endif

extern uint32_t callRadmin(char *__ptr32 arg_pointers) {
  // Copy mock result to 31 bit memory.
  if (r_admin_result_mock != NULL) {
    char *__ptr32 result_buffer =
        (char *__ptr32)__malloc31(r_admin_result_size_mock);
    if (result_buffer == NULL) {
      perror(
          "Fatal - Unable to allocate space in 31-bit storage "
          "for R_Admin result buffer mock.\n");
      exit(1);
    }
    // Set result buffer pointer in the R_Admin arg area.
    char *__ptr32 *__ptr32 result_buffer_pointer =
        ((char *__ptr32 *__ptr32)arg_pointers) - 1;
    memcpy(result_buffer, r_admin_result_mock, r_admin_result_size_mock);
    *result_buffer_pointer = result_buffer;
    (((char *__ptr32 *__ptr32)arg_pointers)[12]) =
        reinterpret_cast<char *>(result_buffer_pointer);
  }
  // Set mock return and reason codes.
  // Use 'htonl()' to ensure return and reason codes are
  // big endian when tests are run off platform.
  if (*(((uint32_t *__ptr32 *__ptr32)arg_pointers)[7]) == 0x1a ||
      *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[7]) == 0x1c ||
      *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[7]) == 0x20 ||
      *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[7]) == 0x23) {
    *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[2]) = htonl(4);
    *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[4]) = htonl(4);
    *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[6]) = htonl(4);
  } else {
    *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[2]) =
        htonl(r_admin_saf_rc_mock);
    *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[4]) =
        htonl(r_admin_racf_rc_mock);
    *(((uint32_t *__ptr32 *__ptr32)arg_pointers)[6]) =
        htonl(r_admin_racf_reason_mock);
  }
  return r_admin_rc_mock;
}
