#include "TimEventPainterHigh.h"
#include "SSGWriter.h"

TimEventPainterHigh::TimEventPainterHigh() {
  m_event_level = TimEventPainter::High;
}

TimEventPainterHigh::~TimEventPainterHigh() {
}

void TimEventPainterHigh::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, EventLevel prev_level,
    double ev_abs_event, double ev_abs_setup, double ev_abs_hold, double ev_abs_end)
{
  // paint setup part
  unsigned int sy;
  switch(prev_level) {
  case TimEventPainter::None:
    sy = 35;
    break;
  case TimEventPainter::Low:
    sy = 35;
    break;
  case TimEventPainter::High:
    sy = 15;
    break;
  }
  painter->drawLine(ev_abs_setup, sy, ev_abs_event, 25);

  // paint hold and level parts
  painter->drawLine(ev_abs_event, 25, ev_abs_hold, 15);
  painter->drawLine(ev_abs_hold, 15, ev_abs_end, 15);
}

void TimEventPainterHigh::SSGWrite(SSGWriter *writer) {
  writer->writeStartElement("painter");
  writer->writeCharacters("high");
  writer->writeEndElement();
}
