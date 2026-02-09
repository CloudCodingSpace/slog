#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  SLOG_SEVERITY_CUSTOM,
  SLOG_SEVERITY_INFO,
  SLOG_SEVERITY_DEBUG,
  SLOG_SEVERITY_WARN,
  SLOG_SEVERITY_ERROR,
  SLOG_SEVERITY_FATAL
} SLSeverity;

typedef enum {
  SLCOLOR_RED = (3 << 8) | 1,
  SLCOLOR_WHITE = (3 << 8) | 7,
  SLCOLOR_GREEN = (3 << 8) | 2,
  SLCOLOR_BLACK = (3 << 8) | 0,
  SLCOLOR_YELLOW = (3 << 8) | 3,
  SLCOLOR_MAGENTA = (3 << 8) | 5,
  SLCOLOR_BLUE = (3 << 8) | 4,
  SLCOLOR_CYAN = (3 << 8) | 6,
  SLCOLOR_DEFAULT = 0,
  SLCOLOR_TOTAL_COUNT = 10
} SLColor;


typedef struct {
  char* name;
  SLColor crntColor;
} SLogger;

void slogLoggerSetName(SLogger* logger, const char* name);
void slogLoggerSetColor(SLogger* logger, SLColor color);
void slogLoggerReset(SLogger* logger);

void slogLogConsole(SLogger* logger, SLSeverity severity, const char* msg, ...);

#ifdef __cplusplus
}
#endif
