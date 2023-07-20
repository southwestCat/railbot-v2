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

// Got from this.
// https://blog.csdn.net/m0_74282605/article/details/129845278
int pthread_attr_init_with_sched_policy(pthread_attr_t *attr,
                                        struct sched_param *param,
                                        int sch_algorithm, int rt_priority) {
  int ret;
  ret = pthread_attr_init(attr);
  if (ret) {
    printf("attr_init error is %s.\n", strerror(errno));
    return ret;
  }

  param->sched_priority = rt_priority;
  ret = pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
  if (ret) {
    printf("setinheritsched error is %s.\n", strerror(errno));
    return ret;
  }
  ret = pthread_attr_setschedpolicy(attr, sch_algorithm);
  if (ret) {
    printf("setschedpolicy error is %s.\n", strerror(errno));
    return ret;
  }
  ret = pthread_attr_setschedparam(attr, param);
  if (ret) {
    printf("setschedpolicy error is %s.\n", strerror(errno));
    return ret;
  }
  return 0;
}