/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:09:51
 * @FilePath: /railbot-v2/Src/Common/Threads/Motion.h
 * @Description:
 *
 */
#pragma once

#include <memory>

#include "Modules/Infrastructure/JointAnglesProvider/JointAnglesProvider.h"
#include "Modules/Infrastructure/NaoProvider/NaoProvider.h"
#include "Modules/MotionControl/KeyFrameMotionEngine/KeyFrameMotionEngine.h"
#include "Modules/MotionControl/MotionCombinator/MotionCombinator.h"
#include "Modules/MotionControl/WalkingEngine/WalkingEngine.h"
#include "Modules/Sensing/RobotModelProvider/RobotModelProvider.h"
#include "ThreadBase.h"

class Motion : public ThreadBase {
 public:
  Motion(BlackboardThread *bbt);

  void tick();
  void updateModules();
  void beforeFrame();
  void beforeModules();
  void afterModules();
  void afterFrame();

 private:
  std::unique_ptr<NaoProvider> naoProvider;
  std::unique_ptr<MotionCombinator> motionCombinator;
  std::unique_ptr<KeyFrameMotionEngine> keyFrameMotionEngine;
  std::unique_ptr<JointAnglesProvider> jointAnglesProvider;
  std::unique_ptr<RobotModelProvider> robotModelProvider;
};