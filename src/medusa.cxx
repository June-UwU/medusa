#include "medusa.hpp"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

namespace medusa {

config log_config;

void write_banner() {
  write_log(log_level::log,
            "Medusa Version %d.%d.%d\nWritten By: William Reji\n",
            get_major(medusa_version), get_minor(medusa_version),
            get_patch(medusa_version));
}

void initialize(const medusa::config& conf) {
  log_config = conf;

  if (true == conf.write_intro) {
    write_banner();
  }
}

void write_log(medusa::log_level level, const char* format, ...) {
  char buffer[512];
  uint64_t offset = 0;

  const char* color_code = nullptr;
  switch (level) {
    case log_level::log:
      color_code = "\x1b[37m";
      break;
    case log_level::paranoid:
      color_code = "\x1b[2;37m";
      break;
    case log_level::debug:
      color_code = "\x1b[1;37m";
      break;
    case log_level::warning:
      color_code = "\x1b[33m";
      break;
    case log_level::fatal:
      color_code = "\x1b[1;31m";
      break;
    default:
      color_code = "\x1b[0m";
      break;
  }

  if (level < log_config.console_level) {
    goto file_log;
  }
  va_list args;
  va_start(args, format);
  offset = vsnprintf(buffer, 512, format, args);
  va_end(args);

  printf("%s%s\x1b[0m", color_code, buffer);

file_log:
  return;
}

void deinitialize() {}
}  // namespace medusa
