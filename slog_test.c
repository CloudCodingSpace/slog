#include <slog/slog.h>

int main(int argc, const char** argv) {
  SLogger logger = {0};

  slogLoggerReset(&logger);
  slogLoggerSetName(&logger, "main");
  
  slogLogConsole(&logger, SLOG_SEVERITY_WARN, "Hello %d", 5); 
  slogLogConsole(&logger, SLOG_SEVERITY_INFO, "Hello %d", 5); 
  slogLogConsole(&logger, SLOG_SEVERITY_DEBUG, "Hello %d", 5); 

  slogLoggerReset(&logger);

  return 0;
}
