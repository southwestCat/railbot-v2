/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:18:37
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/BatterySensorData.h
 * @Description:
 *
 */
#pragma once

#include "Common/Motion/SensorData.h"

struct BatterySensorData {
  float charge = SensorData::off;  // [0, 1]
  float current = SensorData::off;
  float status = SensorData::off;
  float temperature = SensorData::off;
};