/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 13:07:26
 * @FilePath: /railbot-v2/Src/Common/Blackboard/Blackboard.h
 * @Description:
 *
 */
#pragma once

#include <memory>

#include "Representations/Infrastructure/BatterySensorData.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Infrastructure/JointSensorData.h"

#define _USE(R) const R &get##R = *(Bb::instance().get##R.get())
#define _MODIFY(R) R &get##R = *(Bb::instance().get##R.get())

#define _DECLARE(R) std::unique_ptr<R> get##R;
#define _MAKE(R) get##R = std::make_unique<R>();

class Bb {
 public:
  Bb();
  ~Bb();
  static Bb &instance();

 public:
  _DECLARE(FrameInfo);
  _DECLARE(JointSensorData);
  _DECLARE(BatterySensorData);

 private:
  void makeR();
};
