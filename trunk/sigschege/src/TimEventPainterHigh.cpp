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
  unsigned int start_y;
  unsigned int event_y = 25;

  switch(prev_level) {
  case TimEventPainter::None:
    start_y = 15;
    event_y = 15;
    break;
  case TimEventPainter::Low:
    start_y = 35;
    break;
  case TimEventPainter::High:
    start_y = 15;
    break;
  }
  painter->drawLine(ev_abs_setup, start_y, ev_abs_event, event_y);

  // paint hold and level parts
  painter->drawLine(ev_abs_event, event_y, ev_abs_hold, 15);
  painter->drawLine(ev_abs_hold, 15, ev_abs_end, 15);
}

void TimEventPainterHigh::SSGWrite(SSGWriter *writer) {
  writer->writeStartElement("painter");
  writer->writeCharacters("high");
  writer->writeEndElement();
}
