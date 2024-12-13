#include <slog/slog.h>

int main(int argc, const char** argv) {
  SLogger logger = {0};

  slog_logger_reset(&logger);
  slog_logger_set_name(&logger, "main");
  
  slog_log_console(&logger, SLOG_SEVERITY_INFO, "Hello"); 

  return 0;
}
