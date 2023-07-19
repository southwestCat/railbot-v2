/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:31:05
 * @FilePath: /railbot-v2/Src/Common/Threads/ThreadManager.cpp
 * @Description:
 *
 */
#include "ThreadManager.h"

ThreadManager::ThreadManager(std::string name, int cycleTime) {
  this->name = name;
  this->cycleTime = cycleTime;
  running = false;
}

void ThreadManager::join() {
  if (running) {
    pthread_join(pthread, NULL);
  }
  running = false;
}

bool ThreadManager::setCPU(pthread_t &a, int i) {
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(i, &mask);
  if (0 != pthread_setaffinity_np(a, sizeof(mask), &mask)) {
    std::cerr << "[ERROR] Cannot set CPU affinity, aborting..." << std::endl;
    return false;
  }
  return true;
}