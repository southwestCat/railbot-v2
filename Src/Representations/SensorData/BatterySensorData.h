/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:18:37
 * @FilePath: /railbot-v2/Src/Representations/SensorData/BatterySensorData.h
 * @Description:
 *
 */
#pragma once

#include <nlohmann/json.hpp>

#include "Common/Motion/SensorData.h"

struct BatterySensorData {
  float charge = SensorData::off;  // [0, 1]
  float current = SensorData::off;
  float status = SensorData::off;
  float temperature = SensorData::off;
};

void to_json(nlohmann::json& j, const BatterySensorData& v);
void from_json(const nlohmann::json& j, BatterySensorData& v);