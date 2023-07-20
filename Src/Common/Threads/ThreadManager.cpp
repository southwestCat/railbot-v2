/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:31:05
 * @FilePath: /railbot-v2/Src/Common/Threads/ThreadManager.cpp
 * @Description:
 *
 */
#include "ThreadManager.h"

#include <errno.h>

#include <cstring>

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

int pthread_attr_init_with_sched_policy(pthread_attr_t *attr,
                                        struct sched_param *param,
                                        int sch_algorithm, int rt_priority) {
  int s;
  s = pthread_attr_init(attr);
  if (s != 0) handle_error_en(s, "pthread_attr_init");

  param->sched_priority = rt_priority;
  s = pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
  if (s != 0) handle_error_en(s, "pthread_attr_setinheritsched");

  s = pthread_attr_setschedpolicy(attr, sch_algorithm);
  if (s != 0) handle_error_en(s, "pthread_attr_getschedpolicy");
  
  s = pthread_attr_setschedparam(attr, param);
  if (s != 0) handle_error_en(s, "pthread_attr_getschedparam");
  
  return 0;
}