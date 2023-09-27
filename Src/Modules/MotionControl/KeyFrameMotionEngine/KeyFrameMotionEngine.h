/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 16:12:27
 * @FilePath: /railbot-v2/Src/Modules/MotionControl/KeyFrameMotionEngine/KeyFrameMotionEngine.h
 * @Description:
 *
 */
#pragma once

#include "Common/Blackboard/Blackboard.h"

class KeyFrameMotionEngine {
 private:
  _USE(FrameInfo);
  _USE(JointSensorData);
  _USE(RobotStates);

 private:
  _MODIFY(JointRequest);

 public:
  void exec();
};
