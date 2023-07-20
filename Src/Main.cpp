/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 12:42:22
 * @FilePath: /railbot-v2/Src/Main.cpp
 * @Description:
 *
 */
#include <csignal>
#include <iostream>

#include "Common/Blackboard/BlackboardThread.h"
#include "Common/Threads/Cognition.h"
#include "Common/Threads/Lower.h"
#include "Common/Threads/Motion.h"
#include "Common/Threads/ThreadManager.h"
#include "Common/Threads/Upper.h"
#include "Modules/Infrastructure/NaoProvider/NaoProvider.h"

using namespace std;

static bool run = true;
bool attemptingShutdown = false;

static void sighandlerShutdown(int sig) {
  if (run) {
    printf("Caught signal %i\nShutting down...\n", sig);
  }
  run = false;
  attemptingShutdown = true;
}

int main() {
  signal(SIGTERM, sighandlerShutdown);
  signal(SIGINT, sighandlerShutdown);

  BlackboardThread *bbt = new BlackboardThread;

  ThreadManager motion("Motion", 0);
  motion.run<Motion>(bbt);

  ThreadManager upper("Upper", 33);
  upper.run<Upper>(bbt);
  usleep(15000);

  ThreadManager lower("Lower", 33);
  lower.run<Lower>(bbt);
  usleep(15000);

  ThreadManager cognition("Cognition", 15);
  cognition.run<Cognition>(bbt);  

  while (run) {
    pause();
  }

  delete bbt;

  return 0;
}