/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 09:26:37
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/RobotStates.cpp
 * @Description:
 *
 */
#include "RobotStates.h"

#include <cassert>

static std::string StateName[] = {
    "initial",   "standing", "standinghigh", "sitting", "stand",
    "standhigh", "walk",     "kick",         "sitdown"
};

std::string RobotStates::info() {
  assert(sizeof(StateName) / sizeof(std::string) == numOfStates);
  return StateName[state];
}
