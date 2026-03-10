# API Guide

> NOTE: You are not supposed to change any parameter's in the SLogger struct, any parameter or setting change must be done by 
the provided API function!

## Creating and destroying the logger

For creating, use the function `slogLoggerCreate` and for deleting use `slogLoggerDestroy`.

Sample :-

```c
#include <slog/slog.h>

int main() {
    SLogger logger;
    slogLoggerCreate(&logger, "test", NULL, SLOG_LOGGER_FEATURE_LOG2CONSOLE);

    ... // Do or log whatever you want! 

    slogLoggerDestroy(&logger);

    return 0;
}
```

In the above sample, in the function call of `slogLoggerCreate`, the first parameter is the 
pointer to the logger handle. The second paramter is the name of the logger, the third parameter 
is the path of the output log file, and the last parameter are the features.

In the function call of `slogLoggerDestroy`, the only parameter is the pointer to the 
logger handle.

## Changing the name of the logger

You can later change the name of the logger by using `slogLoggerSetName`.

Sample :- 
```c
slogLoggerSetName(&logger, "new_name");
```

## Features of a logger

SLogger has the option to specify one or multiple features (Use `|` with the feature's bitmask for using multiple of them)
while creating the logger.
The different features are :- 

- `SLOG_LOGGER_FEATURE_LOG2CONSOLE`: This feature enables the logger to log messages to the console
- `SLOG_LOGGER_FEATURE_LOG2CUSTOM_OUT`: This feature enables the logger to log messages to the custom callback. (More info down)
- `SLOG_LOGGER_FEATURE_LOG2FILE`: This feature enables the logger to log messages to the specified file

> NOTE: If no features are provided (feature is 0), then the logger technically won't log anything! So make sure at least any one 
feature is enabled!

## Custom callback

The api has a functionality where if the client wants, slog can give them the formatted message and they can use or do whatever 
it wants with it. As mentioned above, for this to work, the `SLOG_LOGGER_FEATURE_LOG2CUSTOM_OUT` feature must be enabled!
If either the callback isn't set, or the feature isn't enabled, no log will be done by the `custom out` but other outs like 
file and console will work provided the corresponding features are enabled.

Setting the callback :-

```c
slogLoggerSetCustomOutCallback(&logger, userState, callbackFunPtr);
```

Callback function signature :- 
```c
void callback(void* userState, uint64_t logLen, const char* log) {
    ...
}
```

> NOTE: The last char of the `log` parameter in the callback is "\0"

## Setting the output file path :-

Suppose you passed `NULL` in the output file path parameter in `slogLoggerCreate(...)`, you can use the function, 
`slogLoggerSetOutFileName`. Even if you have provided the path in `slogLoggerCreate`, you can change, the output file, 
but explicitly changing the output path. But if the new path provided explicitly is the same path as the previous 
output path, then the previous logs on that file, will disappear!

Setting the output file path :-

```c
slogLoggerSetOutFileName(&logger, "path/to/log_file.txt");
```

## Logging messages

The logging API function isn't complicated. Just use `slogLogMsg`.

Sample :- 

```c
slogLogMsg(&logger, SLOG_SEVERITY_INFO, "hello! my age is %d", 4);
```

## Changing the color of the console

You can change the color of the console by using `slogConsoleSetColor`.
Also, this function changes the console through which the executable has been launched from.
>NOTE: This function uses ANSII codes for changing the colors, but if the console doesn't support, 
ANSII color codes, then it won't do the color change!

Sample :- 

```c
slogConsoleSetColor(SLOG_COLOR_BLUE);

... // Custom logs

slogConsoleSetColor(SLOG_COLOR_DEFAULT);
```

> NOTE: Even if you change the color of the console, it won't be visible unless the feature to `LOG2CONSOLE` is enabled and 
the severity is `SLOG_SEVERITY_CUSTOM`. It is because when logging to console, every severity has a fixed color associated with it, 
except for `SLOG_SEVERITY_CUSTOM`.

## Additional sample

If you want a sample with context, you can take a look at `slog_test.c` file which is at the root of this project.
