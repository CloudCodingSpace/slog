# Slog

Slog is a simple logger written in C. It is mainly created for simplicity of use. slog doesn't use any 
platform dependent code. It only uses the C standard library (libc).

# Build instructions

To include and build it in your cmake project, then simply add this repo and then from your project's main 
**CMakeLists.txt** file, simply add this repo as a subdirectory using **add_subdirectory** function in cmake.
If you are not using cmake, then simply add **the slog/slog.h && slog/slog.c** file in your project and you are done! Just make sure the slog.c file compiles and that you can include slog.h in your project.

# Features

 - Can print coloured text
 - Can change the color of the console.
 - Has various severities
 - Has various features like can log to file, custom outputs by user callbacks and 

# Limitations

 - Doesn't have custom log patterns which can be customized by the client.
 - Can't do timestamping
 - Isn't suited for multithreaded use.
 - Can't filter severity. (like for eg., not to log any msg of severity higher than INFO, etc)

# API Guide

The information and various samples on using slog's api is given [here](API_GUIDE.md).

