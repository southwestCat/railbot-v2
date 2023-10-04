/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-20 10:26:58
 * @FilePath: /railbot-v2/Src/Common/Threads/Cognition.cpp
 * @Description:
 *
 */
#include "Cognition.h"

Cognition::Cognition(BlackboardThread *bbt) : ThreadBase(bbt) {
  ledHandler = std::make_unique<LEDHandler>();
  robotStateHandler = std::make_unique<RobotStateHandler>();
}

void Cognition::tick() {
  beforeFrame();
  beforeModules();
  updateModules();
  afterModules();
  afterFrame();
}

void Cognition::beforeFrame() {
  // FrameInfo
  *bb->getFrameInfo.get() = bbt->MWCR->theFrameInfo.read();
  // TouchSensorData
  *bb->getTouchSensorData.get() = bbt->MWCR->theTouchSensorData.read();
  // MotionInfo
  *bb->getMotionInfo.get() = bbt->MWCR->theMotionInfo.read();
}
void Cognition::beforeModules() {}

void Cognition::updateModules() {
  // LEDRequest
  ledHandler->exec();
  // RobotState
  robotStateHandler->exec();
}

void Cognition::afterModules() {}

void Cognition::afterFrame() {
  // LEDRequest
  bbt->CWMR->theLEDRequest.write(*bb->getLEDRequest.get());
  // RobotState
  bbt->CWMR->theRobotStates.write(*bb->getRobotStates.get());
}