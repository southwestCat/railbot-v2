/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 17:38:24
 * @FilePath: /railbot-v2/Src/Common/Threads/ThreadManager.h
 * @Description:
 *
 */
#pragma once

#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "Common/Blackboard/BlackboardThread.h"
#include "Timer.h"

extern bool attemptingShutdown;

#define handle_error_en(en, msg) \
  do {                           \
    errno = en;                  \
    perror(msg);                 \
    exit(EXIT_FAILURE);          \
  } while (0)
/*
 * Set thread priority SCHED_FIFO or SCHED_RR
 * Get the min and max priority nby `chrt -m` in NAO.
 * rt_priority = 99 means rt.

 * https://man7.org/linux/man-pages/man3/pthread_setschedparam.3.html
*/
// SCHED_OTHER min/max priority	: 0/0
// SCHED_FIFO min/max priority	: 1/99
// SCHED_RR min/max priority	: 1/99
// SCHED_BATCH min/max priority	: 0/0
// SCHED_IDLE min/max priority	: 0/0
// SCHED_DEADLINE min/max priority	: 0/0
int pthread_attr_init_with_sched_policy(pthread_attr_t *attr,
                                        struct sched_param *param,
                                        int sch_algorithm, int rt_priority);

class ThreadManager;

struct SafelyRunArgs {
  ThreadManager *threadManager;
  BlackboardThread *blackboard;
};

template <class T, void (T::*mem_fn)(BlackboardThread *)>
void *thunk(void *args);

class ThreadManager {
 public:
  ThreadManager(std::string name, int cycleTime);
  ~ThreadManager() {
    std::cout << "~ThreadManager " << name << std::endl;
    join();
  }
  template <class T>
  void run(BlackboardThread *bb);

  void join();
  bool setCPU(pthread_t &a, int i);

  std::string name;  // thread name
  int cycleTime;     // microseconds
  pthread_t pthread;
  bool running;

 private:
  template <class T>
  void safelyRun(BlackboardThread *bb);
  SafelyRunArgs args;
};

template <class T, void (T::*mem_fn)(BlackboardThread *)>
void *thunk(void *args) {
  void *p = ((SafelyRunArgs *)args)->threadManager;
  BlackboardThread *b = ((SafelyRunArgs *)args)->blackboard;
  (static_cast<T *>(p)->*mem_fn)(b);
  return 0;
}

template <class T>
void ThreadManager::run(BlackboardThread *bb) {
  args.blackboard = bb;
  args.threadManager = this;

  if (name == "Upper") {
    const int cpuID = 0;
    if (0 != pthread_create(&pthread, NULL,
                            &thunk<ThreadManager, &ThreadManager::safelyRun<T>>,
                            &args)) {
      std::cerr << "[ERROR] Cannot create thread: " << name << std::endl;
      exit(-1);
    }
    if (!setCPU(pthread, cpuID)) {
      std::cerr << "[ERROR] Cannot set Logger thread to cpu" << cpuID
                << std::endl;
    }
    std::cout << "[INFO] Create thread: " << name << "     --> binding to cpu"
              << cpuID << std::endl;
  } else if (name == "Lower") {
    const int cpuID = 1;
    if (0 != pthread_create(&pthread, NULL,
                            &thunk<ThreadManager, &ThreadManager::safelyRun<T>>,
                            &args)) {
      std::cerr << "[ERROR] Cannot create thread: " << name << std::endl;
      exit(-1);
    }
    if (!setCPU(pthread, cpuID)) {
      std::cerr << "[ERROR] Cannot set Logger thread to cpu" << cpuID
                << std::endl;
    }
    std::cout << "[INFO] Create thread: " << name << "     --> binding to cpu"
              << cpuID << std::endl;
  } else if (name == "Cognition") {
    const int cpuID = 2;
    if (0 != pthread_create(&pthread, NULL,
                            &thunk<ThreadManager, &ThreadManager::safelyRun<T>>,
                            &args)) {
      std::cerr << "[ERROR] Cannot create thread: " << name << std::endl;
      exit(-1);
    }
    if (!setCPU(pthread, cpuID)) {
      std::cerr << "[ERROR] Cannot set Cognition thread to cpu1" << std::endl;
      exit(-1);
    }
    std::cout << "[INFO] Create thread: " << name << " --> binding to cpu"
              << cpuID << std::endl;
  } else if (name == "Motion") {
    const int cpuID = 3;
    pthread_attr_t attr;
    struct sched_param param;
    int ret =
        pthread_attr_init_with_sched_policy(&attr, &param, SCHED_FIFO, 99);
    if (ret) {
      std::cerr << "pthread_attr_init_with_sched_policy error.\n" << std::endl;
      exit(-1);
    }

    int s;
    s = pthread_create(&pthread, &attr,
                       &thunk<ThreadManager, &ThreadManager::safelyRun<T>>,
                       &args);
    if (s != 0) handle_error_en(s, "pthread_create");
    
    if (!setCPU(pthread, cpuID)) {
      std::cerr << "[ERROR] Cannot set Motion thread to cpu" << cpuID
                << std::endl;
      exit(-1);
    }
    std::cout << "[INFO] Create thread: " << name << "    --> binding to cpu"
              << cpuID << std::endl;
  } else {
    if (0 != pthread_create(&pthread, NULL,
                            &thunk<ThreadManager, &ThreadManager::safelyRun<T>>,
                            &args)) {
      std::cerr << "[ERROR] Cannot create thread: " << name << std::endl;
      exit(-1);
    }
    std::cout << "[INFO] Create thread: " << name << std::endl;
  }
  running = true;
}

template <class T>
void ThreadManager::safelyRun(BlackboardThread *bb) {
  T t(bb);
  Timer timer;
  unsigned int elapsed = 0;
  while (!attemptingShutdown) {
    try {
      timer.reset();
      if (cycleTime != -1) {
        t.tick();
        elapsed = timer.elapsed_us();
        if ((int)elapsed < cycleTime) {
          usleep(cycleTime - elapsed);
        }
      } else {
        sleep(1);
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
}
