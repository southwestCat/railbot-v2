/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-20 17:33:26
 * @FilePath:
 * /railbot-v2/Src/Modules/MotionControl/WalkingEngine/WalkingEngine.cpp
 * @Description:
 *
 */
#include "WalkingEngine.h"

#include <iostream>

#include "Common/Motion/InverseKinematic.h"
#include "Common/Motion/MotionUtilities.h"

using std::cout;
using std::endl;

void WalkingEngine::exec() {
  if (!shouldActive()) {
    reset();
    return;
  }
  getWalkingEngineOutput.active = true;

  switch (walkP) {
    case WalkProcess::start:
      preWalk();
      walkP = WalkProcess::crouch;
      break;
    case WalkProcess::crouch:
      crouch();
      break;
    case WalkProcess::end:
      standBy();
      break;
    default:
      break;
  }

  if (getRobotStates.state == RobotStates::walk) {
    makeStep();
  }
}

void WalkingEngine::reset() {
  getWalkingEngineOutput.reset();
  walkP = WalkProcess::start;
}

bool WalkingEngine::shouldActive() {
  if (getRobotStates.state == RobotStates::prewalk) return true;
  if (getRobotStates.state == RobotStates::walk) return true;
  return false;
}

void WalkingEngine::preWalk() {
  interpT = getFrameInfo.time;
  startJR = getLogJointRequest;

  float yoffset = getRobotDimensions.yHipOffset;
  Pose3f targetL(0.0, yoffset, -HipHeight);
  Pose3f targetR(0.0, -yoffset, -HipHeight);
  bool isPossible = InverseKinematic::calcLegJoints(targetL, targetR, Vector2f::Zero(), croushJR, getRobotDimensions);
  assert(isPossible);
}

void WalkingEngine::crouch() {
  float tms = getFrameInfo.getTimeSince(interpT);
  float t = static_cast<float>(tms) / CrouchInterpTime;
  if (t > 1.0) {
    walkP = WalkProcess::end;
    return;
  }

  MotionUtilities::interpolate(startJR, croushJR, t, getWalkingEngineOutput.j, getJointAngles);
  crouchStiffness(getWalkingEngineOutput.j);
}

void WalkingEngine::standBy() {
  getWalkingEngineOutput.inWalking = true;
}

void WalkingEngine::crouchStiffness(JointRequest &jr) {
  for (int i = Joints::firstLegJoint; i <= Joints::rAnkleRoll; i++) {
    jr.stiffnessData.stiffnesses[i] = 75;
  }
}

void WalkingEngine::makeStep() {
}
