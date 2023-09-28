/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:19:18
 * @FilePath: /railbot-v2/Src/Representations/SensorData/FSRSensorData.h
 * @Description:
 *
 */
#pragma once

#include <array>
#include <nlohmann/json.hpp>

#include "Common/Motion/SensorData.h"
#include "Common/RobotParts/FsrSensors.h"
#include "Common/RobotParts/Legs.h"
struct FsrSensorData {
  std::array<std::array<float, FsrSensors::numOfFsrSensors>, Legs::numOfLegs> pressure;
  std::array<float, Legs::numOfLegs> total;

  FsrSensorData();
};

void to_json(nlohmann::json& j, const FsrSensorData& v);
void from_json(const nlohmann::json& j, FsrSensorData& v);