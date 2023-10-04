/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 16:17:25
 * @FilePath:
 * /railbot-v2/Src/Modules/MotionControl/MotionCombinator/MotionCombinator.cpp
 * /railbot-v2/Src/Modules/MotionControl/MotionCombinator/MotionCombinator.cpp
 * @Description:
 *
 */
#include "MotionCombinator.h"

#include <iostream>

#include "Common/Motion/ForwardKinematic.h"
#include "Common/Motion/InverseKinematic.h"

using std::cout;
using std::endl;

void MotionCombinator::exec() {
  if (getRobotStates.state == RobotStates::initial) {
    getLogJointRequest.angles = getJointAngles.angles;
    getLogJointRequest.stiffnessData.stiffnesses.fill(0.0);
    return;
  } else if (getRobotStates.state == RobotStates::standing) {
    getJointRequest.angles[Joints::headYaw] = getHeadMotionEngineOutput.j.angles[Joints::headYaw];
    getJointRequest.angles[Joints::headPitch] = getHeadMotionEngineOutput.j.angles[Joints::headPitch];
    getJointRequest.stiffnessData.stiffnesses[Joints::headYaw] = getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headYaw];
    getJointRequest.stiffnessData.stiffnesses[Joints::headPitch] = getHeadMotionEngineOutput.j.stiffnessData.stiffnesses[Joints::headPitch];
  }

  getLogJointRequest = getJointRequest;
}