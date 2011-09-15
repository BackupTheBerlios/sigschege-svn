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

#include <utility>

#include "TimWave.h"
#include "TimEventTool.h"
#include "TimCmdAddEvent.h"

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

    double scale_factor = getLayoutData()->get_scale_factor();

    unsigned int ev_abs_setup;
    unsigned int ev_abs_event;
    unsigned int ev_abs_hold;
    unsigned int ev_abs_end;

    TimEventPainter::EventLevel prev_level = TimEventPainter::None;
    TimEventPainter *ev_painter;

    // Process the first event

    TimEventSet_t::const_iterator ev = m_event_set.lower_bound(TimEvent(start_time));

    // check if we have to draw something before this event.
    if(ev->getAbsSetupTime() > start_time && ev != m_event_set.begin()) {

      // save for later
      ev_abs_end = (unsigned int) ((ev->getAbsSetupTime() - start_time) * scale_factor);

      // move to the prev event and get all data that we need
      --ev;

      double es = (ev->getAbsSetupTime() - start_time);
      if(es < 0.0)
        es = 0.0;

      double ee = (ev->getEventTime() - start_time);
      if(ee < 0.0)
        ee = 0.0;

      double eh = (ev->getAbsHoldTime() - start_time);
      if(eh < 0.0)
        eh = 0.0;

      ev_abs_setup = (unsigned int) (es * scale_factor);
      ev_abs_event = (unsigned int) (ee * scale_factor);
      ev_abs_hold  = (unsigned int) (eh * scale_factor);

      ev->getEventPainter()->paint(painter, option, widget, prev_level, ev_abs_event, ev_abs_setup, ev_abs_hold, ev_abs_end);

      // set values for next event
      ++ev;
      prev_level = ev_painter->getEventLevel();
    }

    while (ev != m_event_set.end() && ev->getAbsSetupTime() < end_time) {

      ev_abs_setup = (unsigned int) ((ev->getAbsSetupTime() - start_time) * scale_factor);
      ev_abs_event = (unsigned int) ((ev->getEventTime() - start_time) * scale_factor);
      ev_abs_hold  = (unsigned int) ((ev->getAbsHoldTime() - start_time) * scale_factor);
      ev_painter = ev->getEventPainter();

      ++ev;

      // check if we handel the last event. If so, then use the end of the diagram as end of event.
      if(ev == m_event_set.end() || (ev->getAbsSetupTime() - start_time) >= end_time) {
        ev_abs_end = end_pos;
      } else {
        ev_abs_end = (unsigned int) ((ev->getAbsSetupTime() - start_time) * scale_factor);
      }

      // Let's paint
      ev_painter->paint(painter, option, widget, prev_level, ev_abs_event, ev_abs_setup, ev_abs_hold, ev_abs_end);

      // save for next round
      prev_level = ev_painter->getEventLevel();
    }
  }
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

bool TimWave::addTimEvent(double time, TimEventPainter *painter, double setup, double hold) {
  std::pair<TimEventSet_t::iterator, bool> ret = m_event_set.insert(TimEvent(time, painter, setup, hold));
  update();
  return ret.second;
}

bool TimWave::rmTimEvent(double time) {
  size_t ret = m_event_set.erase(TimEvent(time));
  update();
  return ret;
}

#include "TimEventPainterLow.h"
#include "TimEventPainterHigh.h"

void TimWave::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {

  if (event->button() == Qt::LeftButton) {

    // get time of the event
    double time = event->pos().x() / getLayoutData()->get_scale_factor();
    time += getLayoutData()->get_start_time();

    // snap to the next snap time (if enabled)
    qreal snap_time = calcSnapTime(event->pos().x(),true);

    TimEventTool* et = getScene()->getSignalManager()->getCurrent();

    if(et) {
      TimEventPainter *current_painter = 0;

      TimEventSet_t::const_iterator ev;
      if (!m_event_set.empty()) {
        ev = m_event_set.upper_bound(TimEvent(time));
        if(ev != m_event_set.begin())
          ev--;
        current_painter = ev->getEventPainter();
      }

      getScene()->pushCmd(new TimCmdAddEvent(this, time, et->getEventPainter(current_painter), 0.0, 0.0));

    }

  } else {
    TimMember::mousePressEvent(event);
  }
}

void TimWave::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event) {

}
