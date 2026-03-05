#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

typedef enum {
  SLOG_SEVERITY_CUSTOM,
  SLOG_SEVERITY_INFO,
  SLOG_SEVERITY_DEBUG,
  SLOG_SEVERITY_WARN,
  SLOG_SEVERITY_ERROR,
  SLOG_SEVERITY_FATAL,
  SLOG_SEVERITY_COUNT
} SLSeverity;

typedef enum {
  SLOG_COLOR_DEFAULT = 0,
  SLOG_COLOR_RED = (3 << 8) | 1,
  SLOG_COLOR_WHITE = (3 << 8) | 7,
  SLOG_COLOR_GREEN = (3 << 8) | 2,
  SLOG_COLOR_BLACK = (3 << 8) | 0,
  SLOG_COLOR_YELLOW = (3 << 8) | 3,
  SLOG_COLOR_MAGENTA = (3 << 8) | 5,
  SLOG_COLOR_BLUE = (3 << 8) | 4,
  SLOG_COLOR_CYAN = (3 << 8) | 6,
  SLOG_COLOR_TOTAL_COUNT = 10
} SLColor;

typedef enum {
  SLOG_LOGGER_FEATURE_LOG2FILE = 1 << 0,
  SLOG_LOGGER_FEATURE_LOG2CONSOLE = 1 << 1,
  SLOG_LOGGER_FEATURE_LOG2CUSTOM_OUT = 1 << 2,
} SLoggerFeatures;

typedef void (*SLCustomOutCallback)(void* userState, uint64_t logLen, uint8_t* log);

typedef struct {
  char* name;
  char* fileName;
  FILE* file;

  void* userState;
  SLCustomOutCallback callback;
  SLoggerFeatures features;
} SLogger;

void slogLoggerCreate(SLogger* logger, const char* name, const char* fileName, SLoggerFeatures features);
void slogLoggerDestroy(SLogger* logger);

void slogLoggerSetName(SLogger* logger, const char* name);
void slogLoggerSetOutFileName(SLogger* logger, const char* fileName);
void slogConsoleSetColor(SLogger* logger, SLColor color);

void slogSetCustomOutCallback(SLogger* logger, void* userState, SLCustomOutCallback callback);
void slogLogMsg(SLogger* logger, SLSeverity severity, const char* msg, ...);

#ifdef __cplusplus
}
#endif
