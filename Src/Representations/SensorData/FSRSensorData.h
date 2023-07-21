/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:19:18
 * @FilePath: /railbot-v2/Src/Representations/SensorData/FSRSensorData.h
 * @Description:
 *
 */
#pragma once

#include <array>

#include "Common/Motion/SensorData.h"
#include "Common/RobotParts/FSRSensors.h"
#include "Common/RobotParts/Legs.h"

struct FSRSensorData {
  std::array<std::array<float, FSRSensors::numOfFSRSensors>, Legs::numOfLegs>
      pressure;
  std::array<float, Legs::numOfLegs> total;

  FSRSensorData();
};