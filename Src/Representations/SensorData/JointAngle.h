/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 13:22:47
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/JointAngle.h
 * @Description:
 *
 */
#pragma once

#include <array>

#include "Common/Motion/SensorData.h"
#include "Common/RobotParts/Joints.h"

struct JointAngle {
  static constexpr float off = SensorData::off;
  static constexpr float ignore = SensorData::ignore;

  JointAngle();
  std::array<float, Joints::numOfJoints> angle;
  unsigned timestamp = 0;
};
