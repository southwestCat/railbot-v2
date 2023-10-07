#pragma once

#include "Common/Blackboard/Blackboard.h"

class WalkingEngine {
 private:
  _USE(FrameInfo);
  _USE(RobotStates);
  _USE(RobotDimensions);
  _USE(LogJointRequest);
  _USE(JointAngles);

 private:
  _MODIFY(WalkingEngineOutput);

 public:
  void exec();

 private:
  bool shouldActive();
  void reset();
  void preWalk();
  void crouch();
  void standBy();
  void makeStep();
  void crouchStiffness(JointRequest &jr);

 private:
  static constexpr float HipHeight = 230.0;
  static constexpr float CrouchInterpTime = 1000.0;

  unsigned interpT;

  JointRequest startJR;
  JointRequest croushJR;
  float initialHipHeight = 0.0;
  enum class WalkProcess {
    start,
    crouch,
    end
  } walkP = WalkProcess::start;
};