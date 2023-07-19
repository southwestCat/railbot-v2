/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 16:37:57
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/FrameInfo.h
 * @Description:
 *
 */
#pragma once

#include <nlohmann/json.hpp>

struct FrameInfo {
  unsigned time = 0;
  int getTimeSince(unsigned timestamp) const {
    return static_cast<int>(time - timestamp);
  }
};

void to_json(nlohmann::json &j, const FrameInfo &v);

void from_json(const nlohmann::json &j, FrameInfo &v);
