/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:55:10
 * @FilePath: /railbot-v2/Src/Common/Threads/Motion.cpp
 * @Description:
 *
 */
#include "Motion.h"

void Motion::tick() { 
  naoProvider->exec();
  walkingEngine->exec();
}