#include "medusa.hpp"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

namespace medusa {

config log_config;
FILE* log_file = nullptr;
bool initialized = false;

double get_elapsed_seconds() {
  if (false == initialized) {
    return 0.0f;
  }
  const std::chrono::time_point<std::chrono::high_resolution_clock> time_now =
      std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> time_elapsed =
      time_now - log_config.start_time;
  return time_elapsed.count();
}

void write_banner() {
  write_log(log_level::log, "Medusa Version %d.%d.%d\n",
            get_major(medusa_version), get_minor(medusa_version),
            get_patch(medusa_version));
}

void initialize(const medusa::config& conf) {
  log_config = conf;

  if (true == log_config.write_to_file) {
    log_file = fopen(log_config.log_file.c_str(), "w");
  }

  if (true == conf.write_intro) {
    write_banner();
  }

  if (true == log_config.write_to_file && nullptr == log_file) {
    write_log(log_level::log, "open log file : %s\n",
              log_config.log_file.c_str());
  } else {
    write_log(log_level::log, "log file : %s\n", log_config.log_file.c_str());
  }
  log_config.start_time = std::chrono::high_resolution_clock::now();
  initialized = true;
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

  if (nullptr == log_file || level < log_config.file_level) {
    goto log_exit;
  }

  fprintf(log_file, "%s", buffer);
log_exit:
  return;
}

void deinitialize() {
  if (true == log_config.write_outro) {
    double time = get_elapsed_seconds();
    write_log(log_level::log, "took %lf seconds.\n", time);
  }

  if (nullptr != log_file) {
    fclose(log_file);
  }
}
}  // namespace medusa
