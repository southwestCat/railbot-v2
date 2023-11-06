#include "HeadMotionEngine.h"

#include <cstdio>

void HeadMotionEngine::exec() {
  if (!shouldActive()) {
    reset();
    return;
  }

  getHeadMotionEngineOutput.active = true;

  if (getRobotStates.state == RobotStates::standing) {
    unsigned tms = getFrameInfo.getTimeSince(startTime);
    float t = static_cast<float>(tms) / StandingInterpolationTime;
    if (t > 1.0) return;
    getHeadMotionEngineOutput.j.angles[Joints::headYaw] =
        initialPan + (panTarget - initialPan) * t;
    getHeadMotionEngineOutput.j.angles[Joints::headPitch] =
        initialTilt + (tiltTarget - initialTilt) * t;
    getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headYaw] = 20;
    getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headPitch] =
        30;
  } else if (getRobotStates.state == RobotStates::standinghigh) {
    unsigned tms = getFrameInfo.getTimeSince(startTime);
    float t = static_cast<float>(tms) / StandingInterpolationTime;
    if (t > 1.0) return;
    getHeadMotionEngineOutput.j.angles[Joints::headYaw] =
        initialPan + (panTarget - initialPan) * t;
    getHeadMotionEngineOutput.j.angles[Joints::headPitch] =
        initialTilt + (tiltTarget - initialTilt) * t;
    getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headYaw] = 20;
    getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headPitch] =
        30;
  } else if (getRobotStates.state == RobotStates::standhigh) {
    // auto interpfunc = [&](JointRequest &jr){
    //   const float T = 4.0;
    //   int tms = getFrameInfo.getTimeSince(startTime);
    //   float t = static_cast<float>(tms) / 1000.0;
    //   jr.angles[Joints::headYaw] = t / T * 90_deg;
    //   jr.stiffnessData.stiffnesses[Joints::headYaw] = 100;
    // };
    // switch (standhighP) {
    //   case StandHighProcess::start:
    //     startTime = getFrameInfo.time;
    //     initialPan = getJointAngles.angles[Joints::headYaw];
    //     standhighP = StandHighProcess::interp;
    //   case StandHighProcess::interp:
    //     interpfunc(getHeadMotionEngineOutput.j);
    //     break;
    //   case StandHighProcess::end:
    //     break;
    //   default:
    //     break;
    // }
  }
}

bool HeadMotionEngine::shouldActive() {
  if (getRobotStates.state == RobotStates::standing) return true;
  if (getRobotStates.state == RobotStates::standinghigh) return true;
  if (getRobotStates.state == RobotStates::stand) return true;
  if (getRobotStates.state == RobotStates::standhigh) return true;
  return false;
}

void HeadMotionEngine::reset() {
  getHeadMotionEngineOutput.reset();
  initialPan = getJointAngles.angles[Joints::headYaw];
  initialTilt = getJointAngles.angles[Joints::headPitch];
  startTime = getFrameInfo.time;
  standhighP = StandHighProcess::start;
}
