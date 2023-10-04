#pragma once

#include "Common/Blackboard/Blackboard.h"

class HeadMotionEngine {
 private:
  _USE(RobotStates);
  _USE(JointAngles);
  _USE(FrameInfo);

 private:
  _MODIFY(HeadMotionEngineOutput);

 private:
  bool shouldActive();
  void standing();
  void reset();

 public:
  void exec();

 private:
  static constexpr float StandingInterpolationTime = 1500.0;
  static constexpr float panTarget = 0.0;
  static constexpr float tiltTarget = 0.0;
  unsigned startTime;
  float initialPan;
  float initialTilt;
};