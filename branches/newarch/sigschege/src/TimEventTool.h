#ifndef TIMEVENTTOOL_H_
#define TIMEVENTTOOL_H_

#include "TimEventPainter.h"

class TimEventTool {
public:
  virtual TimEventPainter* getEventPainter(TimEventPainter* prev) = 0 ;
};

#endif /* TIMEVENTTOOL_H_ */
