cmake_minimum_required(VERSION 3.5.0)
project(slog C)

add_library(slog "${CMAKE_CURRENT_SOURCE_DIR}/slog/slog.c")
target_include_directories(slog PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

option(SLOG_BUILD_TEST "Build slog test executable" ON) # Default ON

if(SLOG_BUILD_TEST)
  add_executable(slog_test slog_test.c)
  target_link_libraries(slog_test PRIVATE slog)
endif()
