/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 09:25:30
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/RobotStates.h
 * @Description:
 *
 */
#pragma once

struct RobotStates {
  enum State {
    initial,
    standing,
    standhigh,
    stand,
    walk,
    kick,
    numOfStates
  };
  State state = initial;
};