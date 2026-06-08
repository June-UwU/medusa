#include "medusa.hpp"

using namespace medusa;
int main() {
  initialize({});

  write_log(log_level::log, "1. this is a log\n");
  write_log(log_level::paranoid, "%d. this is a paranoid log\n", 2);
  write_log(log_level::debug, "3. this is a debug log\n");
  write_log(log_level::warning, "4. this is warning log\n");
  write_log(log_level::fatal, "5. this is a fatal log\n");

  deinitialize();
}
