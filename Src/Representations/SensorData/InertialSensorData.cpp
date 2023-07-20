/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-20 18:57:34
 * @FilePath: /railbot-v2/Src/Representations/SensorData/InertialSensorData.cpp
 * @Description:
 *
 */
#include "InertialSensorData.h"
#include <array>

using namespace std;
using json = nlohmann::json;

void to_json(nlohmann::json &j, const InertialSensorData &v) {
  j = json{{"gyro", v.gyro}, {"acc", v.acc}, {"angle", v.angle}};
}

void from_json(const nlohmann::json &j, InertialSensorData &v) {
  array<float, 3> _gyro;
  array<float, 3> _acc;
  array<float, 2> _angle;
  j.at("gyro").get_to(_gyro);
  j.at("acc").get_to(_acc);
  j.at("angle").get_to(_angle);
  v.gyro << _gyro[0], _gyro[1], _gyro[2];
  v.acc << _acc[0], _acc[1], _acc[2];
  v.angle << _angle[0], _angle[1];
}
