/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 13:15:10
 * @FilePath: /railbot-v2/Src/Common/Math/Angle.h
 * @Description: https://en.cppreference.com/w/cpp/language/user_literal
 * 
 */
#pragma once

#include "Constants.h"

constexpr float operator""_deg(unsigned long long deg) {
  return static_cast<float>(deg * pi / 180);
}

constexpr float operator""_deg(long double deg) {
  return static_cast<float>(deg * pi / 180);
}

constexpr float operator""_rad(unsigned long long rad) {
  return static_cast<float>(rad);
}

constexpr float operator""_rad(long double rad) {
  return static_cast<float>(rad);
}