/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:18:00
 * @FilePath: /railbot-v2/Src/Representations/SensorData/TouchSensorData.h
 * @Description:
 *
 */
#pragma once

#include <array>
#include <nlohmann/json.hpp>

struct TouchSensorData {
  enum Touch {
    chest,
    headFront,
    headMiddle,
    headRear,
    lFootLeft,
    lFootRight,
    lHandBack,
    lHandLeft,
    lHandRight,
    rFootLeft,
    rFootRight,
    rHandBack,
    rHandLeft,
    rHandRight,
    numOfTouchs
  };

  std::array<bool, numOfTouchs> pressed;

  TouchSensorData();
};

void to_json(nlohmann::json& j, const TouchSensorData& v);
void from_json(const nlohmann::json& j, TouchSensorData& v);