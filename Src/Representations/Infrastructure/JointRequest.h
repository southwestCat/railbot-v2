/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-20 17:42:12
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/JointRequest.h
 * @Description:
 *
 */
#pragma once

#include <cmath>

#include "Representations/Infrastructure/Stiffness.h"
#include "Representations/SensorData/JointAngles.h"

struct JointRequest : JointAngles {
  bool isValid(bool allowUseDefault = true) const {
    bool isValid = true;
    for (unsigned i = 0; i < Joints::numOfJoints; i++)
      if (!std::isfinite(angles[i])) {
        std::cerr << "Joint " << i << " is invalid.\n";
        isValid = false;
      }
    return stiffnessData.isValid(allowUseDefault) && isValid;
  }

  StiffnessData stiffnessData;
};

struct LogJointRequest : JointRequest {};