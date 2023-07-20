/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-20 10:26:22
 * @FilePath: /railbot-v2/Src/Common/Threads/Lower.h
 * @Description: 
 * 
 */
#pragma once

#include "ThreadBase.h"

class Lower : public ThreadBase {
 public:
  Lower(BlackboardThread *bbt) : ThreadBase(bbt) {}
  void tick();
};
