# About slog
slog is a simple logger. It is mainly created for simplicity of use. slog doesn't use any 
platform dependent code. It only uses the C standard library (libc).

# Build instructions

To include and build it in your cmake project, then simply add this repo and then from your project's main 
**CMakeLists.txt** file, simply add this repo as a subdirectory using **add_subdirectory** function in cmake.
If you are not using cmake, then simply add **the slog/slog.h && slog/slog.c** file in your project and you are done!

# Features of slog
The features are :- 
 - Can print coloured text
 - Has various severities
 - Each severity has a color associated with it by default
 - If needed a custom color, change the logger's color manually, then while logging, use the severity **SLOG_SEVERITY_CUSTOM**.

# Usage samples

Creating and deleting the logger :-
```c
#include <slog/slog.h>

int main() {
    SLogger logger = {0};
    slogLoggerReset(&logger);
    slogLoggerSetName(&logger, "logger"); // Setting the name of the logger. It is mandatory to set a name before
                                          // Using the logger.
    
    ... // Using the logger to log stuff

    slogLoggerReset(&logger);
    return 0;
}
```

Using the default severities :-
```c

slogLogConsole(&logger, SLOG_SEVERITY_INFO, "Hello!! My age :- %d, my name :- ", 34, "CloudCodingSpace");
slogLogConsole(&logger, SLOG_SEVERITY_WARN, "Hello!! My age :- %d, my name :- ", 34, "CloudCodingSpace");
slogLogConsole(&logger, SLOG_SEVERITY_DEBUG, "Hello!! My age :- %d, my name :- ", 34, "CloudCodingSpace");
slogLogConsole(&logger, SLOG_SEVERITY_FATAL, "Hello!! My age :- %d, my name :- ", 34, "CloudCodingSpace");
slogLogConsole(&logger, SLOG_SEVERITY_ERROR, "Hello!! My age :- %d, my name :- ", 34, "CloudCodingSpace");

```

Using custom severity :- 
```c

slogLoggerSetColor(&logger, SLCOLOR_RED); // Can change color
slogLogConsole(&logger, SLOG_SEVERITY_CUSTOM, "Hello!!");
slogLoggerSetColor(&logger, SLCOLOR_DEFAULT); // Make sure to change the color back to default!

```

# TODO
 - Allow custom patterns for the log
 - Log time along with the message
 - Allow output of log patterns to a custom char* through a custom user callback.
