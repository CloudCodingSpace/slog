#include "slog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SLERROR(msg, ...) do { printf("\033[0;31m"); printf(msg, ##__VA_ARGS__); printf("\n\033[0;0m"); } while(0);

static const char* severityStrTable[SLOG_SEVERITY_COUNT] = {
  "",
  "INFO",
  "DEBUG",
  "WARN",
  "ERROR",
  "FATAL"
};

static uint64_t severityColorTable[SLOG_SEVERITY_COUNT] = {
  0,
  SLCOLOR_GREEN,
  SLCOLOR_BLUE,
  SLCOLOR_YELLOW,
  SLCOLOR_RED,
  SLCOLOR_RED
};

void slogLoggerSetName(SLogger* logger, const char* name) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }
  if(!name) {
    SLERROR("[SLOG]: The name shouldn't be NULL!");
    return;
  }

  if(logger->name) {
    free((void*) logger->name);
  }

  size_t size = sizeof(char) * strlen(name);

  logger->name = (char*) malloc(size + 1);
  memcpy((void*)logger->name, name, size);
  logger->name[size] = '\0';
}

void slogLoggerSetColor(SLogger* logger, SLColor color) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }

  switch(color) {
    case SLCOLOR_RED:
      printf("\033[0;%d%dm", (SLCOLOR_RED >> 8) & 0xff, SLCOLOR_RED & 0xff);
      break;
    case SLCOLOR_YELLOW:
      printf("\033[0;%d%dm", (SLCOLOR_YELLOW >> 8) & 0xff, SLCOLOR_YELLOW & 0xff);
      break;
    case SLCOLOR_WHITE:
      printf("\033[0;%d%dm", (SLCOLOR_WHITE >> 8) & 0xff, SLCOLOR_WHITE & 0xff);
      break;
    case SLCOLOR_BLACK:
      printf("\033[0;%d%dm", (SLCOLOR_BLACK >> 8) & 0xff, SLCOLOR_BLACK & 0xff);
      break;
    case SLCOLOR_GREEN:
      printf("\033[0;%d%dm", (SLCOLOR_GREEN >> 8) & 0xff, SLCOLOR_GREEN & 0xff);
      break;
    case SLCOLOR_BLUE:
      printf("\033[0;%d%dm", (SLCOLOR_BLUE >> 8) & 0xff, SLCOLOR_BLUE & 0xff);
      break;
    case SLCOLOR_CYAN:
      printf("\033[0;%d%dm", (SLCOLOR_CYAN >> 8) & 0xff, SLCOLOR_CYAN & 0xff);
      break;
    case SLCOLOR_MAGENTA:
      printf("\033[0;%d%dm", (SLCOLOR_MAGENTA >> 8) & 0xff, SLCOLOR_MAGENTA & 0xff);
      break;
    case SLCOLOR_DEFAULT: 
      printf("\033[0;%dm", SLCOLOR_DEFAULT & 0xff);
      break;
    case SLCOLOR_TOTAL_COUNT: break;
    default:
      SLERROR("[SLOG]: The color provided must be a valid color! The color provided is %d!", color);
  }
}

void slogLoggerReset(SLogger* logger) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }

  if(logger->name) {
    free((void*) logger->name);
    logger->name = NULL;
  }
}

void slogSetCustomOutCallback(SLogger* logger, void* userState, 
                              void (callback)(void* state, uint64_t logLen, uint8_t* log, SLogger* logger)) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }

  logger->userState = userState;
  logger->callback = callback;
}

void slogLogConsole(SLogger* logger, SLSeverity severity, const char* msg, ...) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }
  if(!logger->name) {
    SLERROR("[SLOG]: The logger's name shouldn't be NULL!");
    return;
  }
  if(!msg) {
    SLERROR("[SLOG]: Expected a valid message to log!");
    return;
  }

  if((severity < 0) || (severity >= SLOG_SEVERITY_COUNT)) {
    SLERROR("[SLOG]: The severity parameter must be a valid severity. The severity provided was %d!", severity);
    return;
  }

  if(severity == SLOG_SEVERITY_CUSTOM) {
    printf("[%s]: %s", logger->name, msg);
    return;
  }

  slogLoggerSetColor(logger, severityColorTable[severity]);
  printf("[%s] %s: ", logger->name, severityStrTable[severity]);
  
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
