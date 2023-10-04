/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 16:12:39
 * @FilePath:
 * /railbot-v2/Src/Modules/MotionControl/KeyFrameMotionEngine/KeyFrameMotionEngine.cpp
 * @Description:
 *
 */
#include "KeyFrameMotionEngine.h"

#include <iostream>

#include "Common/Motion/MotionUtilities.h"

using std::cout;
using std::endl;

JointRequest startJR;
JointRequest standTargetJR;

KeyFrameMotionEngine::KeyFrameMotionEngine() {
  MotionUtilities::stand(standTargetJR);
  for (int i = Joints::firstLegJoint; i < Joints::numOfJoints; i++) {
    standTargetJR.stiffnessData.stiffnesses[i] = 75;
  }
}

void KeyFrameMotionEngine::exec() {
  if (!shouldActive()) {
    reset();
    return;
  }

  getKeyFrameEngineOutput.activate = true;

  switch (getRobotStates.state) {
    case RobotStates::standing:
      standing();
      break;
    case RobotStates::sitdown:
      sitdown();
      break;
    default:
      break;
  }
}

void KeyFrameMotionEngine::reset() {
  getKeyFrameEngineOutput.reset();
  standP = StandingProcess::start;
  interpolateStandTime = getFrameInfo.time;
}

bool KeyFrameMotionEngine::shouldActive() {
  if (getRobotStates.state == RobotStates::standing) return true;
  if (getRobotStates.state == RobotStates::sitdown) return true;
  return false;
}

void KeyFrameMotionEngine::standing() {
  auto interp = [&](JointRequest &jr) {
    unsigned tms = getFrameInfo.getTimeSince(interpolateStandTime);
    float t = static_cast<float>(tms) / StandingTime;
    if (t > 1.0) {
      standP = StandingProcess::end;
      return;
    }
    MotionUtilities::interpolate(startJR, standTargetJR, t,
                                 getKeyFrameEngineOutput.j, getJointAngles);
  };
  switch (standP) {
    case StandingProcess::start:
      startJR.angles = getLogJointRequest.angles;
      standP = StandingProcess::interpolation;
      break;
    case StandingProcess::interpolation:
      interp(getKeyFrameEngineOutput.j);
      break;
    case StandingProcess::end:
      getKeyFrameEngineOutput.standMotionDone = true;
      break;
    default:
      break;
  }
}

void KeyFrameMotionEngine::sitdown() {}
