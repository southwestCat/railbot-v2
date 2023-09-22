/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-20 10:26:53
 * @FilePath: /railbot-v2/Src/Common/Threads/Cognition.h
 * @Description:
 *
 */
#pragma once

#include "ThreadBase.h"

#include "Modules/BehaviorControl/LEDHandler/LEDHandler.h"

class Cognition : public ThreadBase {
 public:
  Cognition(BlackboardThread *bbt) : ThreadBase(bbt) {}
  void tick();
  void updateModules();
  void beforeFrame();
  void beforeModules();
  void afterModules();
  void afterFrame();

 private:
  LEDHandler ledHandler;
};