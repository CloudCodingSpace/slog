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
  SLOG_COLOR_GREEN,
  SLOG_COLOR_BLUE,
  SLOG_COLOR_YELLOW,
  SLOG_COLOR_RED,
  SLOG_COLOR_RED
};

void slogLoggerCreate(SLogger* logger, const char* name, const char* fileName, SLoggerFeatures features) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }

  memset(logger, 0, sizeof(SLogger));
  slogLoggerSetName(logger, name);

  memcpy((SLoggerFeatures*)&logger->features, &features, sizeof(SLoggerFeatures));

  if(logger->fileName)
    slogLoggerSetOutFileName(logger, fileName);
}

void slogLoggerDestroy(SLogger* logger) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }

  if(logger->name) {
    free((void*) logger->name);
    logger->name = NULL;
  }

  if(logger->fileName) {
    free((void*) logger->fileName);
    logger->fileName = NULL;
  }

  if(logger->file) {
    fclose(logger->file);
  }

  memset(logger, 0, sizeof(SLogger));
}

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

  size_t size = strlen(name);

  logger->name = (char*) malloc(sizeof(char) * (size + 1));
  memcpy((void*)logger->name, name, size * sizeof(char));
  logger->name[size] = '\0';
}

void slogLoggerSetOutFileName(SLogger* logger, const char* fileName) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }
  if(!fileName) {
    SLERROR("[SLOG]: The output file name shouldn't be NULL!");
    return;
  }

  if(logger->fileName) {
    free((void*) logger->fileName);
  }

  if(logger->file) {
    fclose(logger->file);
  }

  size_t size = strlen(fileName);

  logger->fileName = (char*) malloc(sizeof(char) * (size + 1));
  memcpy((void*)logger->fileName, fileName, size * sizeof(char));
  logger->fileName[size] = '\0';

  if(logger->features & SLOG_LOGGER_FEATURE_LOG2FILE) {
    logger->file = fopen(fileName, "w+");
    if(!logger->file) {
      SLERROR("[SLOG]: Failed to open the output file! File path :- %s", fileName);
      logger->file = NULL;
    }
  }
}

void slogConsoleSetColor(SLogger* logger, SLColor color) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }

  switch(color) {
    case SLOG_COLOR_RED:
      printf("\033[0;%d%dm", (SLOG_COLOR_RED >> 8) & 0xff, SLOG_COLOR_RED & 0xff);
      break;
    case SLOG_COLOR_YELLOW:
      printf("\033[0;%d%dm", (SLOG_COLOR_YELLOW >> 8) & 0xff, SLOG_COLOR_YELLOW & 0xff);
      break;
    case SLOG_COLOR_WHITE:
      printf("\033[0;%d%dm", (SLOG_COLOR_WHITE >> 8) & 0xff, SLOG_COLOR_WHITE & 0xff);
      break;
    case SLOG_COLOR_BLACK:
      printf("\033[0;%d%dm", (SLOG_COLOR_BLACK >> 8) & 0xff, SLOG_COLOR_BLACK & 0xff);
      break;
    case SLOG_COLOR_GREEN:
      printf("\033[0;%d%dm", (SLOG_COLOR_GREEN >> 8) & 0xff, SLOG_COLOR_GREEN & 0xff);
      break;
    case SLOG_COLOR_BLUE:
      printf("\033[0;%d%dm", (SLOG_COLOR_BLUE >> 8) & 0xff, SLOG_COLOR_BLUE & 0xff);
      break;
    case SLOG_COLOR_CYAN:
      printf("\033[0;%d%dm", (SLOG_COLOR_CYAN >> 8) & 0xff, SLOG_COLOR_CYAN & 0xff);
      break;
    case SLOG_COLOR_MAGENTA:
      printf("\033[0;%d%dm", (SLOG_COLOR_MAGENTA >> 8) & 0xff, SLOG_COLOR_MAGENTA & 0xff);
      break;
    case SLOG_COLOR_DEFAULT: 
      printf("\033[0;%dm", SLOG_COLOR_DEFAULT & 0xff);
      break;
    case SLOG_COLOR_TOTAL_COUNT: break;
    default:
      SLERROR("[SLOG]: The color provided must be a valid color! The color provided is %d!", color);
  }
}

void slogLoggerSetCustomOutCallback(SLogger* logger, void* userState, SLCustomOutCallback callback) {
  if(!logger) {
    SLERROR("[SLOG]: The logger can't be NULL!");
    return;
  }

  logger->userState = userState;
  logger->callback = callback;
}

void slogLogMsg(SLogger* logger, SLSeverity severity, const char* msg, ...) {
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

  if(logger->features & SLOG_LOGGER_FEATURE_LOG2CUSTOM_OUT && logger->callback) {
    char* msg1;
    char* msg2;

    if(severity == SLOG_SEVERITY_CUSTOM) {
      size_t len = snprintf(NULL, 0, "[%s]: ", logger->name);
      msg1 = (char*)calloc(len+1, sizeof(char));
      snprintf(msg1, len + 1, "[%s]: ", logger->name);
    }
    else {
      size_t len = snprintf(NULL, 0, "[%s] %s: ", logger->name, severityStrTable[severity]);
      msg1 = (char*)calloc(len+1, sizeof(char));
      snprintf(msg1, len + 1, "[%s] %s: ", logger->name, severityStrTable[severity]);
    }

    va_list args;
    va_start(args, msg);
    size_t len = vsnprintf(NULL, 0, msg, args);
    msg2 = (char*)calloc(len + 2, sizeof(char));
    vsnprintf(msg2, len + 1, msg, args);
    msg2[len] = '\n';
    msg2[len+1] = '\0';

    va_end(args);

    len = strlen(msg1) + strlen(msg2);
    char* msg3 = (char*)calloc(len + 1, sizeof(char));

    int i = 0;
    for(int j = 0; j < strlen(msg1); j++) {
      msg3[i] = msg1[j];
      i++;
    }
    for(int j = 0; j < strlen(msg2); j++) {
      msg3[i] = msg2[j];
      i++;
    }

    msg3[len] = '\0';

    free((void*)msg1);
    free((void*)msg2);

    logger->callback(logger->userState, len+1, msg3);
    free((void*)msg3);
  }
  
  if(logger->features & SLOG_LOGGER_FEATURE_LOG2CONSOLE) {
    if(severity == SLOG_SEVERITY_CUSTOM) {
      printf("[%s]: ", logger->name);
      
      va_list args;
      va_start(args, msg);
      vprintf(msg, args);
      va_end(args);

      printf("\n");
    }
    else {
      slogConsoleSetColor(logger, severityColorTable[severity]);
      printf("[%s] %s: ", logger->name, severityStrTable[severity]);
      
      va_list args;
      va_start(args, msg);
      vprintf(msg, args);
      va_end(args);

      printf("\n");

      slogConsoleSetColor(logger, SLOG_COLOR_DEFAULT);
    }
  }
  
  if(logger->features & SLOG_LOGGER_FEATURE_LOG2FILE) {
    if(logger->file == NULL) {
      SLERROR("[SLOG]: Can't log to file even though the feature is enabled, because the output file isn't set!");
      return;
    }

    if(severity == SLOG_SEVERITY_CUSTOM) {
      fprintf(logger->file, "[%s]: ", logger->name);
    }
    else {
      fprintf(logger->file, "[%s] %s: ", logger->name, severityStrTable[severity]);
    }

    va_list args;
    va_start(args, msg);
    vfprintf(logger->file, msg, args);
    va_end(args);

    fprintf(logger->file, "\n");
  }
}

#ifdef __cplusplus
}
#endif
