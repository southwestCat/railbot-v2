/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:41:05
 * @FilePath: /railbot-v2/Src/Common/Time/Time.cpp
 * @Description:
 *
 */
#include "Time.h"

#include <ctime>

unsigned Time::base = 0;

unsigned Time::getSystemTime() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  const unsigned int time =
      (unsigned int)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000l);
  if (!base) base = time - 100000;
  return time - base;
}