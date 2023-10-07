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

KeyFrameMotionEngine::KeyFrameMotionEngine() {
  MotionUtilities::stand(standTargetJR);
  MotionUtilities::sit(sittingTargetJR);
  standhighTargetJR.angles.fill(0_deg);
  for (int i = Joints::firstLegJoint; i < Joints::numOfJoints; i++) {
    standTargetJR.stiffnessData.stiffnesses[i] = 75;
    standhighTargetJR.stiffnessData.stiffnesses[i] = 75;
    sittingTargetJR.stiffnessData.stiffnesses[i] = 75;
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
    case RobotStates::standinghigh:
      standingHigh();
      break;
    case RobotStates::sitting:
      sitdown();
      break;
    default:
      break;
  }
}

void KeyFrameMotionEngine::reset() {
  getKeyFrameEngineOutput.activate = false;
  getKeyFrameEngineOutput.reset();
  standP = StandingProcess::start;
  standhighP = StandingHighProcess::start;
  sittingP = SittingProcess::start;
  interpolateStandTime = getFrameInfo.time;
  interpolateTime = getFrameInfo.time;
}

bool KeyFrameMotionEngine::shouldActive() {
  if (getRobotStates.state == RobotStates::standing) return true;
  if (getRobotStates.state == RobotStates::standinghigh) return true;
  if (getRobotStates.state == RobotStates::sitting) return true;
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
    MotionUtilities::interpolate(startJR, standTargetJR, t, jr, getJointAngles);
  };
  switch (standP) {
    case StandingProcess::start:
      interpolateStandTime = getFrameInfo.time;
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

void KeyFrameMotionEngine::standingHigh() {
  auto interp = [&](JointRequest &jr) {
    unsigned tms = getFrameInfo.getTimeSince(interpolateTime);
    float t = static_cast<float>(tms) / StandHighTime;
    if (t > 1.0) {
      standhighP = StandingHighProcess::end;
      return;
    }
    MotionUtilities::interpolate(startJR, standhighTargetJR, t, jr,
                                 getJointAngles);
  };

  switch (standhighP) {
    case StandingHighProcess::start:
      interpolateTime = getFrameInfo.time;
      startJR.angles = getLogJointRequest.angles;
      standhighP = StandingHighProcess::interpolation;
      break;
    case StandingHighProcess::interpolation:
      interp(getKeyFrameEngineOutput.j);
      break;
    case StandingHighProcess::end:
      getKeyFrameEngineOutput.standHighMotionDone = true;
      break;
    default:
      break;
  }
}

void KeyFrameMotionEngine::sitdown() {
  auto interp = [&](JointRequest &jr) {
    unsigned tms = getFrameInfo.getTimeSince(interpolateTime);
    float t = static_cast<float>(tms) / SitDownTime;
    if (t > 1.0) {
      sittingP = SittingProcess::end;
      return;
    }
    MotionUtilities::interpolate(startJR, sittingTargetJR, t, jr,
                                 getJointAngles);
  };

  switch (sittingP) {
    case SittingProcess::start:
      interpolateTime = getFrameInfo.time;
      startJR.angles = getLogJointRequest.angles;
      sittingP = SittingProcess::interpolation;
      break;
    case SittingProcess::interpolation:
      interp(getKeyFrameEngineOutput.j);
      break;
    case SittingProcess::end:
      getKeyFrameEngineOutput.sittingMotionDone = true;
      break;
    default:
      break;
  }
}
