#ifndef TIMEVENTPAINTERLOW_H_
#define TIMEVENTPAINTERLOW_H_

#include "TimEventPainter.h"

class TimEventPainterLow: public TimEventPainter {
public:
  TimEventPainterLow();
  virtual ~TimEventPainterLow();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, EventLevel prev_level,
      double ev_abs_event, double ev_abs_setup, double ev_abs_hold, double ev_abs_end);
};

#endif /* TIMEVENTPAINTERLOW_H_ */
