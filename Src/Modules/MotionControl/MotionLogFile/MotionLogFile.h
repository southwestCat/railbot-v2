#pragma once

#include <fstream>

#include "Common/Blackboard/Blackboard.h"

class MotionLogFile {
 private:
  _USE(FrameInfo);
  _USE(JointRequest);
  _USE(JointAngles);
  _USE(HeadMotionEngineOutput);

 public:
  MotionLogFile();
  ~MotionLogFile();
  void exec();

  private:
  void log();

 private:
  std::ofstream fs;

  unsigned startT;
  enum class LogProcess {start, log} pStat = LogProcess::start;
};