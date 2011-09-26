#include "TimEventPainterLow.h"
#include "SSGWriter.h"

TimEventPainterLow::TimEventPainterLow() {
  m_event_level = TimEventPainter::Low;
}

TimEventPainterLow::~TimEventPainterLow() {
}

void TimEventPainterLow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, EventLevel prev_level,
    double ev_abs_event, double ev_abs_setup, double ev_abs_hold, double ev_abs_end)
{
  // paint setup part
  unsigned int start_y;
  unsigned int event_y = 25;

  switch(prev_level) {
  case TimEventPainter::None:
    start_y = 35;
    event_y = 35;
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
  painter->drawLine(ev_abs_event, event_y, ev_abs_hold, 35);
  painter->drawLine(ev_abs_hold, 35, ev_abs_end, 35);
}

void TimEventPainterLow::SSGWrite(SSGWriter *writer) {
  writer->writeStartElement("painter");
  writer->writeCharacters("low");
  writer->writeEndElement();
}
