/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-22 10:00:01
 * @FilePath: /railbot-v2/Src/Modules/BehaviorControl/LEDHandler/LEDHandler.h
 * @Description:
 *
 */
#pragma once

#include "Common/Blackboard/Blackboard.h"

class LEDHandler {
 private:
  _USE(FrameInfo);
  _USE(TouchSensorData);

 private:
  _MODIFY(LEDRequest);

 public:
  void exec();
};
