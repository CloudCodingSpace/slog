#pragma once


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

void slog_logger_set_name(SLogger* logger, char* name);
void slog_logger_set_color(SLogger* logger, SLColor color);
void slog_logger_reset(SLogger* logger);

void slog_log_console(SLogger* logger, SLSeverity severity, char* msg);

