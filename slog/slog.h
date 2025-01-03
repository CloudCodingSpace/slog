#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  SLOG_SEVERITY_CUSTOM, // Use it only to log the text!
  SLOG_SEVERITY_INFO,
  SLOG_SEVERITY_DEBUG,
  SLOG_SEVERITY_WARN,
  SLOG_SEVERITY_ERROR,
  SLOG_SEVERITY_FATAL
} SLSeverity;

typedef enum {
  SLCOLOR_RED,
  SLCOLOR_WHITE,
  SLCOLOR_GREEN,
  SLCOLOR_BLACK,
  SLCOLOR_YELLOW,
  SLCOLOR_MAGENTA,
  SLCOLOR_BLUE,
  SLCOLOR_CYAN,
  SLCOLOR_DEFAULT,
  SLCOLOR_TOTAL_COUNT
} SLColor;


typedef struct {
  char* name;
  SLColor crntColor;
} SLogger;

void slogLoggerSetName(SLogger* logger, const char* name);
void slogLoggerSetColor(SLogger* logger, SLColor color);
void slogLoggerReset(SLogger* logger);

void slogLogConsole(SLogger* logger, SLSeverity severity, const char* msg);

#ifdef __cplusplus
}
#endif
