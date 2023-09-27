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

void Cognition::updateModules() {
  ledHandler->exec();
  robotStateHandler->exec();
}
void Cognition::beforeFrame() {
  *bb->getFrameInfo.get() = bbt->MWCR->theFrameInfo.read();
  *bb->getTouchSensorData.get() = bbt->MWCR->theTouchSensorData.read();
}
void Cognition::beforeModules() {}
void Cognition::afterModules() {}
void Cognition::afterFrame() {
  bbt->CWMR->theLEDRequest.write(*bb->getLEDRequest.get());
  bbt->CWMR->theRobotStates.write(*bb->getRobotStates.get());
}