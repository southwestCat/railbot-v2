/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 17:37:45
 * @FilePath: /railbot-v2/Src/Common/Blackboard/BlackboardThread.h
 * @Description:
 *
 */
#pragma once

#include <memory>
#include "TrippleBuffer.h"
#include "Blackboard.h"

#define _DECLARE_TRIBUF(x) TrippleBuffer<x> the##x

struct CognitionWriteMotionRead {};

struct MotionWriteCognitionRead {
  _DECLARE_TRIBUF(FrameInfo);
};
struct MotionWriteUpperRead {};
struct MotionWriteLowerRead {};

struct UpperWriteCognitionRead {};

struct LowerWriteCognitionRead {};

struct BlackboardThread {
  BlackboardThread();
  // std::unique_ptr<CognitionWriteMotionRead> CWMR;
  // std::unique_ptr<MotionWriteCognitionRead> MWCR;
  // std::unique_ptr<MotionWriteUpperRead> MWUR;
  // std::unique_ptr<MotionWriteLowerRead> MWLR;
  // std::unique_ptr<UpperWriteCognitionRead> UWCR;
  // std::unique_ptr<LowerWriteCognitionRead> LWCR;

  std::unique_ptr<MotionWriteCognitionRead> MWCR;
};