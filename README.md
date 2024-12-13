# About slog
slog is a simple logger. It is mainly created for the easiness for it to be used. slog doesn't uses any 
platform dependent code. It only uses the C standard library.

# Build instructions

To include and build it in your cmake project, then simply add this repo and then from your project's main 
**CMakeLists.txt** file, simply add this repo as a subdirectory using **add_subdirectory** function in cmake.
If you are not using cmake, then simply add **the slog/slog.h && slog/slog.c** file in your project and you are done!

# Featured of slog
The features are :- 
 - Can print coloured text
 - For logging, it needs a severity to better identify the use of the log. If you don't wanna provide any severity, then use **SLOG_SEVERITY_CUSTOM**

# TODO
 - Allow custom patterns for the log
 - Log time along with the message
 - Log to a file
