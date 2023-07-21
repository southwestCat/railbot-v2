/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:19:41
 * @FilePath: /railbot-v2/Src/Representations/SensorData/FSRSensorData.cpp
 * @Description:
 *
 */
#include "FSRSensorData.h"

using json = nlohmann::json;

FSRSensorData::FSRSensorData() {
  pressure[Legs::left].fill(SensorData::off);
  pressure[Legs::right].fill(SensorData::off);
  total[Legs::left] = 0.f;
  total[Legs::right] = 0.f;
}

void to_json(nlohmann::json& j, const FSRSensorData& v) {
  j = json{{"pressure", v.pressure}, {"total", v.total}};
}
void from_json(const nlohmann::json& j, FSRSensorData& v) {
  j.at("pressure").get_to(v.pressure);
  j.at("total").get_to(v.total);
}