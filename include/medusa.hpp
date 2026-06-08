#pragma once
#include <cstdint>
#include <string>

namespace medusa {

constexpr const uint32_t make_version(uint32_t major, uint32_t minor,
                                      uint32_t patch) {
  uint32_t version = 0;
  major = major & 0xff;
  minor = minor & 0xff;
  patch = patch & 0xffff;

  version |= (major << 24) | (minor << 16) | patch;
  return version;
}

constexpr const uint32_t get_major(uint32_t version) {
  return (version >> 24) & 0xff;
}

constexpr const uint32_t get_minor(uint32_t version) {
  return (version >> 16) & 0xff;
}

constexpr const uint32_t get_patch(uint32_t version) {
  return version & 0xffff;
}

constexpr const uint32_t medusa_version = make_version(0, 0, 1);

enum log_level { log = 0x0, paranoid, debug, warning, fatal };

struct config {
  std::string log_file = "medusa.log";
  log_level file_level = log_level::log;
  log_level console_level = log_level::log;
  bool write_intro = true;
  bool write_outro = true;
  bool force_flush = true;
  bool use_color = true;
  bool write_to_file = true;
};

void initialize(const medusa::config& conf);
void write_log(medusa::log_level level, const char* format, ...);
void deinitialize();
};  // namespace medusa
