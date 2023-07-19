/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:11:19
 * @FilePath: /railbot-v2/Src/Common/Threads/ThreadBase.h
 * @Description:
 *
 */
#pragma once

#include <memory>
#include <cassert>
#include "Common/Blackboard/Blackboard.h"
#include "Common/Blackboard/BlackboardThread.h"

class ThreadBase {
 protected:
  BlackboardThread *bbt;  // blackboard thread
  std::unique_ptr<Bb> bb;  // blackboard self

  ThreadBase(BlackboardThread *bbthread) : bbt(bbthread) {
    assert(bbt != nullptr);
    bb = std::make_unique<Bb>();
  }
 public:
  virtual void tick() {}
  virtual void beforeFrame() {}
  virtual void beforeModules() {}
  virtual void updateModules() {}
  virtual void afterModules() {}
  virtual void afterFrame() {}
};