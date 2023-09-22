/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:55:10
 * @FilePath: /railbot-v2/Src/Common/Threads/Motion.cpp
 * @Description:
 *
 */
#include "Motion.h"

void Motion::tick() {
  beforeFrame();
  beforeModules();
  updateModules();
  afterModules();
  afterFrame();
}

void Motion::updateModules() {
  naoProvider->exec();
  walkingEngine->exec();
}

void Motion::beforeFrame() {
}

void Motion::afterFrame() {
  bbt->MWCR->theFrameInfo.write(*bb->getFrameInfo.get());
}

void Motion::beforeModules() {}

void Motion::afterModules() {}