#ifndef _LOG_H_
#define _LOG_H_

#include <string>

#include "stdio.h"

enum loglevel_e {
  logERROR,
  logWARNING,
  logINFO,
  logDEBUG,
  logDEBUG1,
  logDEBUG2,
  logDEBUG3,
  logDEBUG4
};

class Log {
 public:
  Log() = default;

  ~Log() = default;

  static void Info(const std::string &input) {
    printf("Info: %s\n", input.c_str());
  }

  static void Info(const std::string &input, const int value) {
    printf("Info: %s - %d\n", input.c_str(), value);
  }

  static void Error(const std::string &input) {
    printf("Error: %s\n", input.c_str());
  }

  static void Error(const std::string &input, const int value) {
    printf("Error: %s - %d\n", input.c_str(), value);
  }

  // Log &operator<<(const std::string &s)
  // {
  //     logging(s)
  //     return *this;
  // }

  // template <class T>
  // Log &operator<<(const T &v)
  // {
  //     std::ostringstream s;
  //     s << v;
  //     return operator<<(logging(ss.str()));
  // };
};

#endif  // _LOG_H_
