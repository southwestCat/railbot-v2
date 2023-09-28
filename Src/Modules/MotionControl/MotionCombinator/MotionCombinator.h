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
  _USE(FrameInfo);

 private:
  _MODIFY(JointRequest);

 public:
  void exec();
};