#include <slog/slog.h>

int main(int argc, const char** argv) {
  SLogger logger = {0};

  slogLoggerReset(&logger);
  slogLoggerSetName(&logger, "main");
  
  slogLogConsole(&logger, -1, "Hello %d\n", 5); 

  return 0;
}
