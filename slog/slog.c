#include "slog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

void slog_logger_set_name(SLogger* logger, char* name) {
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

void slog_logger_set_color(SLogger* logger, SLColor color) {
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
      printf("[SLOG]: The color provided must be a valid color! The color provided is %d", color);
      logger->crntColor = SLCOLOR_DEFAULT;
      break;
  }
}

void slog_logger_reset(SLogger* logger) {
  assert(logger && "[SLOG]: Logger can't be NULL!");

  if(logger->name) {
    free((void*) logger->name);
    logger->name = NULL;
  }
  logger->crntColor = SLCOLOR_DEFAULT;
}

void slog_log_console(SLogger* logger, SLSeverity severity, char* msg) {
  assert(logger && "[SLOG]: Logger can't be NULL!");
  assert(logger->name && "[SLOG]: Logger must have a name!");
  assert(msg && "[SLOG]: Expected a valid message to log!");

  char* severityStr;

  switch(severity) {
    case SLOG_SEVERITY_INFO:
      slog_logger_set_color(logger, SLCOLOR_GREEN);
      severityStr = "INFO";
      break;
    case SLOG_SEVERITY_WARN:
      slog_logger_set_color(logger, SLCOLOR_YELLOW);
      severityStr = "WARN";
      break;
    case SLOG_SEVERITY_DEBUG:
      slog_logger_set_color(logger, SLCOLOR_BLUE);
      severityStr = "DEBUG";
      break;
    case SLOG_SEVERITY_ERROR:
      slog_logger_set_color(logger, SLCOLOR_RED);
      severityStr = "ERROR";
      break;
    case SLOG_SEVERITY_FATAL:
      slog_logger_set_color(logger, SLCOLOR_RED);
      severityStr = "FATAL";
      break;
    case SLOG_SEVERITY_CUSTOM:
      printf("[%s]: %s", logger->name, msg);
      return;
    default:
      printf("[SLOG]: The severity parameter must be a valid severity. The severity provided was %d", severity);
      break; 
  }

  printf("[%s] %s: %s", logger->name, severityStr, msg);

  slog_logger_set_color(logger, SLCOLOR_DEFAULT);
}
