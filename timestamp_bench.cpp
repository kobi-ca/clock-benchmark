#ifdef __linux__
#include <sys/time.h>
#endif

#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>

#include <benchmark/benchmark.h>

namespace {
class timestamp : public benchmark::Fixture {};

BENCHMARK_F(timestamp, rdtsc)(benchmark::State &state) {
  uint64_t ts;
  uint32_t lo, hi;
  for (auto _ : state) {
    // RDTSC copies contents of 64-bit TSC into EDX:EAX
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    ts = static_cast<uint64_t>(hi) << 32 | lo;
  }
  (void)ts;
}

BENCHMARK_F(timestamp, chrono_system)(benchmark::State &state) {
  std::chrono::system_clock::time_point stamp;
  for (auto _ : state) {
    stamp = std::chrono::system_clock::now();
  }
  (void)stamp;
}

BENCHMARK_F(timestamp, chrono_steady)(benchmark::State &state) {
  std::chrono::steady_clock::time_point stamp;
  for (auto _ : state) {
    stamp = std::chrono::steady_clock::now();
  }
  (void)stamp;
}

BENCHMARK_F(timestamp, chrono_high_res)(benchmark::State &state) {
  std::chrono::high_resolution_clock::time_point stamp;
  for (auto _ : state) {
    stamp = std::chrono::high_resolution_clock::now();
  }
  (void)stamp;
}

BENCHMARK_F(timestamp, clock_get_time_monotonic)(benchmark::State &state) {
  timespec tp;
  for (auto _ : state) {
    clock_gettime(CLOCK_MONOTONIC, &tp);
  }
  (void)tp;
}

BENCHMARK_F(timestamp, clock_get_time_cpu)(benchmark::State &state) {
  timespec tp;
  for (auto _ : state) {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp);
  }
  (void)tp;
}

BENCHMARK_F(timestamp, clock_realtime)(benchmark::State &state) {
timespec tp;
  for (auto _ : state) {
    clock_gettime(CLOCK_REALTIME, &tp);
  }
(void)tp;
}


#ifdef __linux__
BENCHMARK_F(timestamp, get_time_of_day)(benchmark::State &state) {
  timeval tv;
  for (auto _ : state) {
    gettimeofday(&tv, 0);
  }
  (void)tv;
}
#endif

} // namespace
