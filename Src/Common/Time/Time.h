/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:40:54
 * @FilePath: /railbot-v2/Src/Common/Time/Time.h
 * @Description: 
 * 
 */
#pragma once

class Time {
  private:
  static unsigned base;
  public:
  static unsigned getSystemTime();
};