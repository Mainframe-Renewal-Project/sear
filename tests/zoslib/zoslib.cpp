#include "zoslib.h"

size_t __a2e_l(char *bufptr, size_t szLen) {
  for (int i = 0; i < szLen; i++) {
    *(bufptr + i) = ASCII_TO_EBCDIC[(unsigned char)*(bufptr + i)];
  }
  return szLen;
}

size_t __e2a_l(char *bufptr, size_t szLen) {
  for (int i = 0; i < szLen; i++) {
    *(bufptr + i) = EBCDIC_TO_ASCII[(unsigned char)*(bufptr + i)];
  }
  return szLen;
}

// Just allocate a normal pointer to enable unit testhing on non-z/OS platforms.
// Note: Technically __malloc31() is define in <stdlib.h>, but it being mocked
// here since 'extract.cpp' will pick it up from here.
void *__malloc31(size_t size) { return malloc(size); }

