/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 09:25:30
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/RobotStates.h
 * @Description:
 *
 */
#pragma once

#include <string>

struct RobotStates {
  enum State {
    initial,
    standing,
    standinghigh,
    sitting,
    stand,
    standhigh,
    walk,
    kick,
    numOfStates
  };
  State state = initial;
  std::string info();
};