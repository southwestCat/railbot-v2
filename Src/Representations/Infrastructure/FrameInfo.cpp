/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 16:39:59
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/FrameInfo.cpp
 * @Description:
 *
 */
#include "FrameInfo.h"

using json = nlohmann::json;

void to_json(json &j, const FrameInfo &v) { j = json{{"time", v.time}}; }

void from_json(const json &j, FrameInfo &v) { j.at("time").get_to(v.time); }