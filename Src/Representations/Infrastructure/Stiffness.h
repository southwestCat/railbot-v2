#pragma once

#include <array>
#include <iostream>

#include "Common/RobotParts/Joints.h"

struct StiffnessData {
  enum { useDefault = -1 };
  StiffnessData() { stiffnesses.fill(useDefault); }

  bool isValid(bool allowUseDefault = true) const {
    bool isValid = true;
    for (unsigned i = 0; i < Joints::numOfJoints; i++)
      if (stiffnesses[i] > 100 ||
          (stiffnesses[i] < 0 &&
           ((stiffnesses[i] != useDefault) || !allowUseDefault))) {
        std::cerr << "Joint " << i << " stiffness is invalid.\n";
        isValid = false;
      }
    return isValid;
  }

  std::array<int, Joints::numOfJoints> stiffnesses;
};

struct StiffnessSettings : StiffnessData {
  StiffnessSettings() {
    stiffnesses[Joints::headYaw] = 20;
    stiffnesses[Joints::headPitch] = 30;

    stiffnesses[Joints::lShoulderPitch] = 10;
    stiffnesses[Joints::lShoulderRoll] = 20;
    stiffnesses[Joints::lElbowYaw] = 10;
    stiffnesses[Joints::lElbowRoll] = 10;
    stiffnesses[Joints::lWristYaw] = 60;
    stiffnesses[Joints::lHand] = 40;

    stiffnesses[Joints::rShoulderPitch] = 10;
    stiffnesses[Joints::rShoulderRoll] = 20;
    stiffnesses[Joints::rElbowYaw] = 10;
    stiffnesses[Joints::rElbowRoll] = 10;
    stiffnesses[Joints::rWristYaw] = 60;
    stiffnesses[Joints::rHand] = 40;

    stiffnesses[Joints::lHipYawPitch] = 75;
    stiffnesses[Joints::lHipRoll] = 75;
    stiffnesses[Joints::lHipPitch] = 75;
    stiffnesses[Joints::lKneePitch] = 75;
    stiffnesses[Joints::lAnklePitch] = 75;
    stiffnesses[Joints::lAnkleRoll] = 75;

    stiffnesses[Joints::rHipYawPitch] = 75;
    stiffnesses[Joints::rHipRoll] = 75;
    stiffnesses[Joints::rHipPitch] = 75;
    stiffnesses[Joints::rKneePitch] = 75;
    stiffnesses[Joints::rAnklePitch] = 75;
    stiffnesses[Joints::rAnkleRoll] = 75;
  }
};