#ifndef TIMEVENTPAINTERHIGH_H_
#define TIMEVENTPAINTERHIGH_H_

#include "TimEventPainter.h"

class SSGWriter;

class TimEventPainterHigh: public TimEventPainter {
public:
  TimEventPainterHigh();
  virtual ~TimEventPainterHigh();

  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, EventLevel prev_level,
      double ev_abs_event, double ev_abs_setup, double ev_abs_hold, double ev_abs_end);

  /** @brief Write XML code for this class.
   *
   * This function writes the XML code for this object while saving a Sigschege XML file.
   * It is a pure virtual function which must be implemented by the derived classes (TimSignal,
   * TimScale, ...)
   *
   * @param writer Pointer to the SSGWriter object, needed for callback.
   */
  virtual void SSGWrite(SSGWriter *writer);
};

#endif /* TIMEVENTPAINTERHIGH_H_ */
