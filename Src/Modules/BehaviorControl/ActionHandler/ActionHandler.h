/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-26 11:22:29
 * @FilePath: /railbot-v2/Src/Modules/BehaviorControl/ActionHandler/ActionHandler.h
 * /railbot-v2/Src/Modules/BehaviorControl/ActionHandler/ActionHandler.h
 * /railbot-v2/Src/Modules/BehaviorControl/ActionHandler/ActionHandler.h
 * /railbot-v2/Src/Modules/BehaviorControl/ActionHandler/ActionHandler.h
 * @Description:
 *
 */
#pragma once

#include "Common/Blackboard/Blackboard.h"

class ActionHandler {
 private:
  _USE(FrameInfo);
  _USE(TouchSensorData);

 public:
  void exec();

 private:
  static constexpr int ChestButtonPressedThreshold = 100;
  unsigned chestPressed;
};
