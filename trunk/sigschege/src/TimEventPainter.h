#ifndef TIMEVENTPAINTER_H_
#define TIMEVENTPAINTER_H_

#include <QtGui>

class SSGWriter;

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

  /** @brief Write XML code for this class.
   *
   * This function writes the XML code for this object while saving a Sigschege XML file.
   * It is a pure virtual function which must be implemented by the derived classes (TimSignal,
   * TimScale, ...)
   *
   * @param writer Pointer to the SSGWriter object, needed for callback.
   */
  virtual void SSGWrite(SSGWriter *writer) = 0;

protected:
  TimEventPainter::EventLevel m_event_level;
};

#endif /* TIMEVENTPAINTER_H_ */
