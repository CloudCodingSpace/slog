cmake_minimum_required(VERSION 3.5.0)
#slog
project(slog C)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    add_compile_options(/arch:AVX2)
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

add_library(${PROJECT_NAME} slog/slog.c)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Test
project(slog_test)

set(SLOG_BUILD_TEST TRUE)

if(SLOG_BUILD_TEST)
  add_executable(${PROJECT_NAME} slog_test.c)
  target_link_libraries(${PROJECT_NAME} PRIVATE slog)
endif(SLOG_BUILD_TEST)
