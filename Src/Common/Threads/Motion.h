/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:09:51
 * @FilePath: /railbot-v2/Src/Common/Threads/Motion.h
 * @Description:
 *
 */
#pragma once

#include <memory>

#include "Modules/Infrastructure/NaoProvider/NaoProvider.h"
#include "ThreadBase.h"

class Motion : public ThreadBase {
 public:
  Motion(BlackboardThread *bbt) : ThreadBase(bbt) {
    naoProvider = std::make_unique<NaoProvider>();
  }
  void tick();

 private:
  std::unique_ptr<NaoProvider> naoProvider;
};