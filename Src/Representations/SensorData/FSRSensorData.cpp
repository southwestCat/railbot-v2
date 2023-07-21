/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 17:19:41
 * @FilePath: /railbot-v2/Src/Representations/SensorData/FSRSensorData.cpp
 * @Description:
 *
 */
#include "FSRSensorData.h"

FSRSensorData::FSRSensorData() {
  pressure[Legs::left].fill(SensorData::off);
  pressure[Legs::right].fill(SensorData::off);
  total[Legs::left] = 0.f;
  total[Legs::right] = 0.f;
}