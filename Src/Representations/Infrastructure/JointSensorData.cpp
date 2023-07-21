/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 13:29:04
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/JointSensorData.cpp
 * @Description:
 *
 */
#include "JointSensorData.h"

using json = nlohmann::json;

JointSensorData::JointSensorData() {
  current.fill(SensorData::off);
  temperature.fill(0);
  status.fill(regular);
}

void to_json(nlohmann::json &j, const JointSensorData &v) {
  j = json{{"angle", v.angle},
           {"current", v.current},
           {"temperature", v.temperature},
           {"status", v.status}};
}

void from_json(const nlohmann::json &j, JointSensorData &v) {
  j.at("angle").get_to(v.angle);
  j.at("current").get_to(v.current);
  j.at("temperature").get_to(v.temperature);
  j.at("status").get_to(v.status);
}
