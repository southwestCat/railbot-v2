/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-20 18:53:14
 * @FilePath: /railbot-v2/Src/Representations/SensorData/InertialSensorData.h
 * @Description: 
 * 
 */
#pragma once

#include <Eigen/Eigen>
#include <nlohmann/json.hpp>

struct InertialSensorData {
  Eigen::Vector3f gyro;
  Eigen::Vector3f acc;
  Eigen::Vector2f angle;
};

void to_json(nlohmann::json &j, const InertialSensorData &v);
void from_json(const nlohmann::json &j, InertialSensorData &v);
