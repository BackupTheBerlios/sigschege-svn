#ifndef TIMEVENTPAINTERHIGH_H_
#define TIMEVENTPAINTERHIGH_H_

#include "TimEventPainter.h"

class TimEventPainterHigh: public TimEventPainter {
public:
  TimEventPainterHigh();
  virtual ~TimEventPainterHigh();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, EventLevel prev_level,
      double ev_abs_event, double ev_abs_setup, double ev_abs_hold, double ev_abs_end);
};

#endif /* TIMEVENTPAINTERHIGH_H_ */
