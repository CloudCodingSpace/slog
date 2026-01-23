#include "slog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void slogLoggerSetName(SLogger* logger, const char* name) {
  assert(logger && "[SLOG]: The logger can't be NULL!");
  assert(name && "[SLOG]: The name shouldn't be NULL!");

  if(logger->name) {
    free((void*) logger->name);
  }

  size_t size = sizeof(char) * strlen(name);

  logger->name = (char*) malloc(size + 1);
  memcpy((void*)logger->name, name, size);
  logger->name[size] = '\0';
}

void slogLoggerSetColor(SLogger* logger, SLColor color) {
  assert(logger && "[SLOG]: Logger can't be NULL!");

  logger->crntColor = color;

  switch(color) {
    case SLCOLOR_RED:
      printf("\033[0;31m");
      break;
    case SLCOLOR_YELLOW:
      printf("\033[0;33m");
      break;
    case SLCOLOR_WHITE:
      printf("\033[0;37m");
      break;
    case SLCOLOR_BLACK:
      printf("\033[0;30m");
      break;
    case SLCOLOR_GREEN:
      printf("\033[0;32m");
      break;
    case SLCOLOR_BLUE:
      printf("\033[0;34m");
      break;
    case SLCOLOR_CYAN:
      printf("\033[0;36m");
      break;
    case SLCOLOR_MAGENTA:
      printf("\033[0;35m");
      break;
    case SLCOLOR_DEFAULT: 
      printf("\033[0;0m");
      break;
    case SLCOLOR_TOTAL_COUNT: break;
    default:
      printf("[SLOG]: The color provided must be a valid color! The color provided is %d\n", color);
      logger->crntColor = SLCOLOR_DEFAULT;
      break;
  }
}

void slogLoggerReset(SLogger* logger) {
  assert(logger && "[SLOG]: Logger can't be NULL!");

  if(logger->name) {
    free((void*) logger->name);
    logger->name = NULL;
  }
  logger->crntColor = SLCOLOR_DEFAULT;
}

void slogLogConsole(SLogger* logger, SLSeverity severity, const char* msg, ...) {
  assert(logger && "[SLOG]: Logger can't be NULL!");
  assert(logger->name && "[SLOG]: Logger must have a name!");
  assert(msg && "[SLOG]: Expected a valid message to log!");

  char* severityStr;

  switch(severity) {
    case SLOG_SEVERITY_INFO:
      slogLoggerSetColor(logger, SLCOLOR_GREEN);
      severityStr = "INFO";
      break;
    case SLOG_SEVERITY_WARN:
      slogLoggerSetColor(logger, SLCOLOR_YELLOW);
      severityStr = "WARN";
      break;
    case SLOG_SEVERITY_DEBUG:
      slogLoggerSetColor(logger, SLCOLOR_BLUE);
      severityStr = "DEBUG";
      break;
    case SLOG_SEVERITY_ERROR:
      slogLoggerSetColor(logger, SLCOLOR_RED);
      severityStr = "ERROR";
      break;
    case SLOG_SEVERITY_FATAL:
      slogLoggerSetColor(logger, SLCOLOR_RED);
      severityStr = "FATAL";
      break;
    case SLOG_SEVERITY_CUSTOM:
      printf("[%s]: %s", logger->name, msg);
      return;
    default:
      printf("[SLOG]: The severity parameter must be a valid severity. The severity provided was %d\n", severity);
      return; 
  }

  printf("[%s] %s: ", logger->name, severityStr);
  
  va_list args;
  va_start(args, msg);
  vprintf(msg, args);
  va_end(args);

  printf("\n");

  slogLoggerSetColor(logger, SLCOLOR_DEFAULT);
}

#ifdef __cplusplus
}
#endif
