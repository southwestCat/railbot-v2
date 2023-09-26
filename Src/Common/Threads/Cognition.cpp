/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-20 10:26:58
 * @FilePath: /railbot-v2/Src/Common/Threads/Cognition.cpp
 * @Description:
 *
 */
#include "Cognition.h"

void Cognition::tick() {
  beforeFrame();
  beforeModules();
  updateModules();
  afterModules();
  afterFrame();
}

void Cognition::updateModules() {
  ledHandler.exec();
}
void Cognition::beforeFrame() {
  *bb->getFrameInfo.get() = bbt->MWCR->theFrameInfo.read();
  *bb->getTouchSensorData.get() = bbt->MWCR->theTouchSensorData.read();
}
void Cognition::beforeModules() {}
void Cognition::afterModules() {}
void Cognition::afterFrame() {}