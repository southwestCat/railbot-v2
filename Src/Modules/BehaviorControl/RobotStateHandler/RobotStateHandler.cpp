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
    if (getFrameInfo.getTimeSince(chestPressed) > ChestButtonPressedThreshold) {
      changeState();
      chestPressed = getFrameInfo.time;
    }
  } else {
    chestPressed = getFrameInfo.time;
  }
}

void RobotStateHandler::changeState() {
  cout << "In changeState().\n";
}