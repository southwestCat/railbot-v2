/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 09:22:57
 * @FilePath: /railbot-v2/Src/Modules/BehaviorControl/RobotStateHandler/RobotStateHandler.cpp
 * /railbot-v2/Src/Modules/BehaviorControl/RobotStateHandler/RobotStateHandler.cpp
 * @Description:
 *
 */
#include "RobotStateHandler.h"
#include <iostream>

using std::cout;
using std::endl;

void RobotStateHandler::exec() {
  if (getTouchSensorData.pressed[TouchSensorData::chest]) {
    if (getFrameInfo.getTimeSince(chestPressed) > ChestButtonPressedThreshold && canChange()) {
      changeState();
      chestPressed = getFrameInfo.time;
    }
  } else {
    chestPressed = getFrameInfo.time;
  }
}

bool RobotStateHandler::canChange() {
  return getRobotStates.state == RobotStates::initial || 
    getRobotStates.state == RobotStates::standhigh ||
    getRobotStates.state == RobotStates::stand ||
    getRobotStates.state == RobotStates::walk;
}

void RobotStateHandler::changeState() {
  if (getRobotStates.state == RobotStates::initial) {
    getRobotStates.state = RobotStates::standing;
  }
}