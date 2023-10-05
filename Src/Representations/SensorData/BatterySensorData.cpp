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
  j = json{{"level", v.level},
           {"current", v.current},
           {"temperature", v.temperature},
           {"status", v.status},
           {"charging", v.charging}};
}
void from_json(const nlohmann::json& j, BatterySensorData& v) {
  j.at("level").get_to(v.level);
  j.at("current").get_to(v.current);
  j.at("temperature").get_to(v.temperature);
  j.at("status").get_to(v.status);
  j.at("charging").get_to(v.charging);
}
