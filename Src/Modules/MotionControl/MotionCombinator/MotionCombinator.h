/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 16:17:14
 * @FilePath:
 * /railbot-v2/Src/Modules/MotionControl/MotionCombinator/MotionCombinator.h
 * /railbot-v2/Src/Modules/MotionControl/MotionCombinator/MotionCombinator.h
 * /railbot-v2/Src/Modules/MotionControl/MotionCombinator/MotionCombinator.h
 * @Description:
 *
 */
#pragma once

#include "Common/Blackboard/Blackboard.h"

class MotionCombinator {
 private:
  _USE(RobotStates);
  _USE(JointAngles);
  _USE(HeadMotionEngineOutput);
  _USE(KeyFrameEngineOutput);
  _USE(WalkingEngineOutput);

 private:
  _MODIFY(MotionInfo);
  _MODIFY(JointRequest);
  _MODIFY(LogJointRequest);

 public:
  void exec();

  private:
  bool activeEngineMoreThanOne();
};