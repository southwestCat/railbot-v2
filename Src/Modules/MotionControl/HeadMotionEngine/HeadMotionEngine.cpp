#include "HeadMotionEngine.h"

#include <cstdio>

void HeadMotionEngine::exec() {
  if (!shouldActive()) {
    reset();
    return;
  }

  if (getRobotStates.state == RobotStates::standing) {
    unsigned tms = getFrameInfo.getTimeSince(startTime);
    float t = static_cast<float>(tms) / StandingInterpolationTime;
    if (t > 1.0) return;
    getHeadMotionEngineOutput.j.angles[Joints::headYaw] =
        initialPan + (panTarget - initialPan) * t;
    getHeadMotionEngineOutput.j.angles[Joints::headPitch] =
        initialTilt + (tiltTarget - initialTilt) * t;
    getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headYaw] = 20;
    getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headPitch] = 30;
  }
}

bool HeadMotionEngine::shouldActive() {
  if (getRobotStates.state == RobotStates::standing) return true;
  if (getRobotStates.state == RobotStates::stand) return true;
  return false;
}

void HeadMotionEngine::reset() {
  initialPan = getJointAngles.angles[Joints::headYaw];
  initialTilt = getJointAngles.angles[Joints::headPitch];
  startTime = getFrameInfo.time;
}
