/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-26 11:22:38
 * @FilePath: /railbot-v2/Src/Modules/BehaviorControl/ActionHandler/ActionHandler.cpp
 * /railbot-v2/Src/Modules/BehaviorControl/ActionHandler/ActionHandler.cpp
 * @Description:
 *
 */
#include "ActionHandler.h"

#include <iostream>

using std::cout;
using std::endl;

void ActionHandler::exec() {
  if (getTouchSensorData.pressed[TouchSensorData::chest]) {
    if (getFrameInfo.getTimeSince(chestPressed) > ChestButtonPressedThreshold) {
      cout << "Chest pressed.\n";
      chestPressed = getFrameInfo.time;
    }
  } else {
    chestPressed = getFrameInfo.time;
  }
}