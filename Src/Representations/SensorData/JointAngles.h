/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 13:22:47
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/JointAngles.h
 * @Description:
 *
 */
#pragma once

#include <array>

#include "Common/Motion/SensorData.h"
#include "Common/RobotParts/Joints.h"
#include "Common/Math/Angle.h"

struct JointAngles {
  static constexpr float off = SensorData::off;
  static constexpr float ignore = SensorData::ignore;

  JointAngles();
  std::array<Angle, Joints::numOfJoints> angles;
  unsigned timestamp = 0;
};
