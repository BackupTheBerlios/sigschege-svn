// -*- c++ -*-
// TimWave.cpp
// Copyright 2011 by Ingo Hinrichs
//
// This file is part of Sigschege - Signal Schedule Generator
//
// #############################################################################
//
// Sigschege is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// Sigschege is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with the Sigschege sources; see the file COPYING.
//
// #############################################################################
//

#include "TimWave.h"

#include "TimEventType.h"

TimWave::TimWave(TimMember *parent, TimingScene *scene) : TimMember(parent, scene) {

}

TimWave::~TimWave() {
}

QRectF TimWave::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(0 - penWidth / 2, 0 - penWidth / 2, getLayoutData()->get_col_1_width() + penWidth, 50 + penWidth);
}

void TimWave::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

  if(!m_event_set.empty()) {

    // Get information about the timing diagram.
    double       start_time   = getLayoutData()->get_start_time();
    double       end_time     = getLayoutData()->get_end_time();
    unsigned int end_pos      = getLayoutData()->get_col_1_width();

    double diff               = end_time - start_time;
    double       scale_factor = (diff != 0.0) ? end_pos / diff : 0;

    unsigned int ev_abs_setup;
    unsigned int ev_abs_event;
    unsigned int ev_abs_hold;
    unsigned int ev_abs_end;

    TimEvent::EventLevel prev_level = TimEvent::None;
    TimEvent::EventLevel ev_level;

    // Process the first event

    TimEventSet_t::const_iterator ev = m_event_set.begin();

    while (ev != m_event_set.end()) {
      qDebug() << ev->getAbsSetupTime();
      qDebug() << ev->getEventTime();
      qDebug() << ev->getAbsHoldTime();

      ev_abs_setup = (unsigned int) (ev->getAbsSetupTime() * scale_factor);
      ev_abs_event = (unsigned int) (ev->getEventTime() * scale_factor);
      ev_abs_hold  = (unsigned int) (ev->getAbsHoldTime() * scale_factor);
      ev_level     = ev->getEventLevel();

      ++ev;

      // check if we handel the last event. If so, then use the end of the diagram as end of event.
      if(ev == m_event_set.end()) {
        ev_abs_end = end_pos;
      } else {
        ev_abs_end = (unsigned int) (ev->getAbsSetupTime() * scale_factor);
      }

      // Let's paint

      // paint setup part
      unsigned int sy;
      switch(prev_level) {
      case TimEvent::None:
        switch(ev_level) {
        case TimEvent::Low:
          sy = 35;
          break;
        case TimEvent::High:
          sy = 15;
          break;
        }
        break;
      case TimEvent::Low:
        sy = 35;
        break;
      case TimEvent::High:
        sy = 15;
        break;
      }
      painter->drawLine(ev_abs_setup, sy, ev_abs_event, 25);

      // paint hold and level parts
      switch(ev_level) {
      case TimEvent::Low:
        painter->drawLine(ev_abs_event, 25, ev_abs_hold, 35);
        painter->drawLine(ev_abs_hold, 35, ev_abs_end, 35);
        break;

      case TimEvent::High:
        painter->drawLine(ev_abs_event, 25, ev_abs_hold, 15);
        painter->drawLine(ev_abs_hold, 15, ev_abs_end, 15);
        break;
      }

      // save for next round
      prev_level = ev_level;

    }

  }

    //  if(isSelected()) {

//        QBrush old = painter->brush();

//        painter->setBrush(QBrush(QColor(255,255,100,100)));
//        painter->drawRect(boundingRect());

//        painter->setBrush(old);
    //  }

}

TimLayoutData* TimWave::getLayoutData() const {
  return m_scene->getLayoutData();
}

QSizeF TimWave::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const {
  switch (which) {
  case Qt::MinimumSize:
    return QSizeF(getLayoutData()->get_col_1_width(), 50);
  case Qt::PreferredSize:
    return QSizeF(getLayoutData()->get_col_1_width(), 50);
  case Qt::MaximumSize:
    return QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
  default:
    qWarning("r::TimWave::sizeHint(): Don't know how to handle the value of 'which'");
    break;
  }
  return constraint;

}

void TimWave::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {

  if (event->button() == Qt::LeftButton) {

    double time = event->pos().x() / getScene()->getLayoutData()->get_scale_factor();

    TimEventType* et = getScene()->getSignalManager()->getCurrent();

    if(et) {
      m_event_set.insert(TimEvent(time, (TimEvent::EventLevel)et->getLevel()));
      // TODO : Implement tool classes to select the event level.
    }

    update();

  } else {
    TimMember::mousePressEvent(event);
  }
}

void TimWave::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event) {

}
