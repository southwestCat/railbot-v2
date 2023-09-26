/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 17:37:58
 * @FilePath: /railbot-v2/Src/Common/Blackboard/BlackboardThread.cpp
 * @Description:
 *
 */
#include "BlackboardThread.h"

using namespace std;

BlackboardThread::BlackboardThread() {
  // CWMR = make_unique<CognitionWriteMotionRead>();
  // MWCR = make_unique<MotionWriteCognitionRead>();
  // MWUR = make_unique<MotionWriteUpperRead>();
  // MWLR = make_unique<MotionWriteLowerRead>();
  // UWCR = make_unique<UpperWriteCognitionRead>();
  // LWCR = make_unique<LowerWriteCognitionRead>();

  MWCR = make_unique<MotionWriteCognitionRead>();
  CWMR = make_unique<CognitionWriteMotionRead>();
}