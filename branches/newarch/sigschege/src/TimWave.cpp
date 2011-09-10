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

    for(TimEventSet_t::iterator walk = m_event_set.begin(); walk != m_event_set.end(); ++walk)
    {
      switch(walk->getEventLevel()) {
      case TimEvent::Low:
        painter->drawLine(0, 35, 100, 35);
        break;

      case TimEvent::High:
        painter->drawLine(0, 15, 100, 15);
        break;
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

    double time = event->pos().x() * getScene()->getLayoutData()->get_scale_factor();

    TimEventType* et = getScene()->getSignalManager()->getCurrent();

    if(et) {
      m_event_set.insert(TimEvent(time, (TimEvent::EventLevel)et->getLevel()));
    }

    update();

  } else {
    TimMember::mousePressEvent(event);
  }
}

void TimWave::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event) {

}
