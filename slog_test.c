#include <slog/slog.h>

#include <stdio.h>

void callback(void* userState, size_t logLen, const char* log) {
  printf(log);
}

int main(int argc, const char** argv) {
  SLogger logger = {0};

  slogLoggerCreate(&logger, "main", NULL, SLOG_LOGGER_FEATURE_LOG2CONSOLE | SLOG_LOGGER_FEATURE_LOG2FILE | SLOG_LOGGER_FEATURE_LOG2CUSTOM_OUT);
  slogLoggerSetOutFileName(&logger, "main.txt");
  slogLoggerSetCustomOutCallback(&logger, NULL, callback);

  slogLogMsg(&logger, SLOG_SEVERITY_WARN, "Hello %d", 5); 
  slogLogMsg(&logger, SLOG_SEVERITY_INFO, "Hello %d", 5); 
  slogLogMsg(&logger, SLOG_SEVERITY_DEBUG, "Hello %d", 5); 
  slogLogMsg(&logger, SLOG_SEVERITY_ERROR, "Hello %d", 5); 
  slogLogMsg(&logger, SLOG_SEVERITY_FATAL, "Hello %d", 5); 
  slogLogMsg(&logger, SLOG_SEVERITY_CUSTOM, "Hello %d", 5); 

  slogLoggerDestroy(&logger);

  return 0;
}
