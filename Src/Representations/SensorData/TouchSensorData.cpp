/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:18:14
 * @FilePath: /railbot-v2/Src/Representations/SensorData/TouchSensorData.cpp
 * @Description:
 *
 */
#include "TouchSensorData.h"

using json = nlohmann::json;

TouchSensorData::TouchSensorData() { pressed.fill(false); }

void to_json(nlohmann::json& j, const TouchSensorData& v) {
  j = json{"pressed", v.pressed};
}
void from_json(const nlohmann::json& j, TouchSensorData& v) {
  j.at("pressed").get_to(v.pressed);
}