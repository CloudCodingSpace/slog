#include <slog/slog.h>

int main(int argc, const char** argv) {
  SLogger logger = {0};

  slogLoggerReset(&logger);
  slogLoggerSetName(&logger, "main");
  
  slogLogConsole(&logger, SLOG_SEVERITY_INFO, "Hello"); 

  return 0;
}
