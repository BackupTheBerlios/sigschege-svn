#ifndef TIMEVENTTOOL_H_
#define TIMEVENTTOOL_H_

#include "TimEventPainter.h"

class TimEventTool {
public:
  virtual TimEventPainter* getEventPainter() = 0 ;

};

#endif /* TIMEVENTTOOL_H_ */
