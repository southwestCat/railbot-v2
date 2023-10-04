/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-26 14:31:21
 * @FilePath: /railbot-v2/Src/Representations/MotionControl/MotionInfo.h
 * @Description:
 *
 */
#pragma once

struct MotionInfo {
  enum Type { initial, standing, stand, standhigh, walk, kick, keyframe };
  bool isMotionDone = false;
  Type motion = initial;
};