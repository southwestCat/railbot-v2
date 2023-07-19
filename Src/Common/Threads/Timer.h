/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 17:34:24
 * @FilePath: /railbot-v2/Src/Common/Threads/Timer.h
 * @Description: (=^o^=)
 *
 */
#pragma once

#include <ctime>

class Timer {
 public:
  Timer() { clock_gettime(CLOCK_MONOTONIC, &timestamp); }
  void reset() { clock_gettime(CLOCK_MONOTONIC, &timestamp); }
  unsigned int msec(const timespec &ts) {
    return (unsigned int)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000l);
  }
  unsigned long long usec(const timespec &ts) {
    return ts.tv_sec * 1000000ll + ts.tv_nsec / 1000;
  }
  unsigned int getMsec() {
    return (unsigned int)(timestamp.tv_sec * 1000 +
                          timestamp.tv_nsec / 1000000l);
  }

  /* return elapsed time */
  unsigned int elapsed_ms() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return msec(ts) - msec(timestamp);
  }

  unsigned long long elapsed_us() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return usec(ts) - usec(timestamp);
  }

 private:
  timespec timestamp;
};