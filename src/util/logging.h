#ifndef UTIL_LOGGING_H_
#define UTIL_LOGGING_H_

#include <stdio.h>
#include <stdlib.h>

#define _LOG(level_char, ...)                                      \
  do {                                                             \
    fprintf(stderr, "%c:%s:%d: ", level_char, __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);                                  \
    fputc('\n', stderr);                                           \
  } while (0)

#define INFO(...) _LOG('I', __VA_ARGS__)
#define WARNING(...) _LOG('W', __VA_ARGS__)
#define ERROR(...)          \
  do {                      \
    _LOG('E', __VA_ARGS__); \
    exit(EXIT_FAILURE);     \
  } while (0)

#endif  // UTIL_LOGGING_H_
