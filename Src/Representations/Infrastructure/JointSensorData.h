/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 13:28:54
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/JointSensorData.h
 * @Description:
 *
 */
#pragma once

#include "JointAngle.h"
#include <nlohmann/json.hpp>

struct JointSensorData : JointAngle {
  enum TemperatureStatus {
    regular,       /**< 0: means regular temperature. */
    hot,           /**< 1: means temperature has reached the max limit, start reducing the stiffness. */
    veryhot,       /**< 2: means the joint is very hot, stiffness reduced over 30%. */
    criticallyhot, /**< 3: means the joint is critically hot, stiffness value is set to 0. */
    unknown,
  };
  enum { NJoints = Joints::numOfJoints };

  std::array<float, NJoints> current;
  std::array<float, NJoints> temperature;
  std::array<TemperatureStatus, NJoints> status;

  JointSensorData();
};

void to_json(nlohmann::json &j, const JointSensorData &v);
void from_json(const nlohmann::json &j, JointSensorData &v);
