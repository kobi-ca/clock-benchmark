######## CMakeLists.txt ############

cmake_minimum_required(VERSION 3.12.1)
project(xsdk_bench)

find_package(benchmark REQUIRED)

set(SRC timestamp_bench.cpp)

add_executable(xsdk_bench ${SRC})

target_compile_options(xsdk_bench PRIVATE -O3 -Wall -Werror)

target_link_libraries(xsdk_bench PRIVATE
  benchmark
  benchmark_main
  pthread
  ${CMAKE_THREAD_LIBS_INIT})
