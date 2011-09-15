#ifndef TIMEVENTPAINTER_H_
#define TIMEVENTPAINTER_H_

#include <QtGui>

class TimEventPainter {
public:

  enum EventLevel {
    None, Low, High
  };


  TimEventPainter();
  virtual ~TimEventPainter();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, TimEventPainter::EventLevel prev_level,
      double ev_abs_event, double ev_abs_setup, double ev_abs_hold, double ev_abs_end) = 0;

  TimEventPainter::EventLevel getEventLevel() { return m_event_level;}

protected:
  TimEventPainter::EventLevel m_event_level;
};

#endif /* TIMEVENTPAINTER_H_ */
