/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 09:22:40
 * @FilePath: /railbot-v2/Src/Modules/BehaviorControl/RobotStateHandler/RobotStateHandler.h
 * /railbot-v2/Src/Modules/BehaviorControl/RobotStateHandler/RobotStateHandler.h
 * @Description: Handle states such as initial, standing, stand, walk, etc.
 *
 */
#pragma once

#include "Common/Blackboard/Blackboard.h"

class RobotStateHandler {
 private:
  _USE(TouchSensorData);
  _USE(FrameInfo);
  _USE(MotionInfo);

 private:
  _MODIFY(RobotStates);

 public:
  void exec();

 private:
  void changeState();
  bool canChange();
  bool touchHeadALL();

 private:
  static constexpr int ChestButtonPressedThreshold = 150;
  static constexpr int HeadButtonPressedThreshold = 1000;
  unsigned chestPressed;
  unsigned headPressed;
};