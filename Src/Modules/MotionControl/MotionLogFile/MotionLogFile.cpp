#include "MotionLogFile.h"

using std::endl;

MotionLogFile::MotionLogFile() { fs.open("log.txt"); }

MotionLogFile::~MotionLogFile() { fs.close(); }

void MotionLogFile::exec() {
  return; ///// 

  switch (pStat) {
    case LogProcess::start:
      startT = getFrameInfo.time;
      pStat = LogProcess::log;
    case LogProcess::log:
      log();
      break;
  }
}

void MotionLogFile::log() {
  if (!getHeadMotionEngineOutput.active) return;
  int tms = getFrameInfo.getTimeSince(startT);
  float t = static_cast<float>(tms) / 1000.0;
  float rJ = toDegrees(getJointRequest.angles[Joints::headYaw]);
  float mJ = toDegrees(getJointAngles.angles[Joints::headYaw]);
  fs << t << " " << rJ << " " << mJ << endl;
}

