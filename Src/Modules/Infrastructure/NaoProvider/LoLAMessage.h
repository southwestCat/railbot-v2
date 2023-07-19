/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 12:53:33
 * @FilePath: /railbot-v2/Src/Modules/Infrastructure/NaoProvider/LoLAMessage.h
 * @Description: 
 * 
 */
#pragma once

#include <array>
#include <nlohmann/json.hpp>

struct LoLAMessage {
  std::array<float, 3> Accelerometer;
  std::array<float, 2> Angles;
  std::array<float, 4> Battery;
  std::array<float, 25> Current;
  std::array<float, 8> FSR;
  std::array<float, 3> Gyroscope;
  std::array<float, 25> Position;
  std::array<std::string, 4> RobotConfig;
  std::array<float, 2> Sonar;
  std::array<float, 25> Status;
  std::array<float, 25> Stiffness;
  std::array<float, 25> Temperature;
  std::array<float, 14> Touch;
  void info();
};


void to_json(nlohmann::json &j, const LoLAMessage &l);
void from_json(const nlohmann::json& j, LoLAMessage& l);
