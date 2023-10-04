/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 16:12:27
 * @FilePath:
 * /railbot-v2/Src/Modules/MotionControl/KeyFrameMotionEngine/KeyFrameMotionEngine.h
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
  _USE(LogJointRequest);
  _USE(JointAngles);

 private:
  _MODIFY(KeyFrameEngineOutput);

 private:
  bool shouldActive();
  void standing();
  void sitdown();
  void reset();

 public:
  KeyFrameMotionEngine();
  void exec();

 private:
  static constexpr float StandingTime = 1500.f;
  static constexpr float SitDownTime = 1500.f;

  enum class StandingProcess { start, interpolation, end } standP = StandingProcess::start;
  unsigned interpolateStandTime;
};
