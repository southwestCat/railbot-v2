/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-20 10:25:54
 * @FilePath: /railbot-v2/Src/Common/Threads/Upper.h
 * @Description:
 *
 */
#pragma once

#include "ThreadBase.h"

class Upper : public ThreadBase {
 public:
  Upper(BlackboardThread *bbt) : ThreadBase(bbt) {}
  void tick();
};
