/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:18:49
 * @FilePath: /railbot-v2/Src/Representations/SensorData/BatterySensorData.cpp
 * @Description:
 *
 */
#include "BatterySensorData.h"

using json = nlohmann::json;

void to_json(nlohmann::json& j, const BatterySensorData& v) {
  j = json{{"charge", v.charge},
           {"current", v.current},
           {"status", v.status},
           {"temperature", v.temperature}};
}
void from_json(const nlohmann::json& j, BatterySensorData& v) {
  j.at("charge").get_to(v.charge);
  j.at("current").get_to(v.current);
  j.at("status").get_to(v.status);
  j.at("temperature").get_to(v.temperature);
}
