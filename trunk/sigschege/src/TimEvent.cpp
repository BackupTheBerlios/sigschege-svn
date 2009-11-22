// -*- c++ -*-
// TimEvent.cpp
// Copyright 2009 by ingo
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

#include "TimEvent.h"
#include "TimWave.h"
#include "TimEventLow.h"
#include "TimEventHigh.h"

TimEvent::TimEvent(TimWave *parent) :
  QGraphicsItem(parent), QGraphicsLayoutItem(0, false) {

  m_Wave = parent;

  m_prev = NULL;
  m_next = NULL;
  m_EventType = NULL;

  m_EventTime = 0.0;

  setEventType(new TimEventLow(this));

  setPos(calcXPos(m_EventTime), 0);

}

TimEvent::TimEvent(TimWave *parent, TimEventType *type) :
  QGraphicsItem(parent), QGraphicsLayoutItem(0, false) {
  m_Wave = parent;

  m_prev = NULL;
  m_next = NULL;
  m_EventType = NULL;

  m_EventTime = 0.0;

  setEventType(type);

  setPos(calcXPos(m_EventTime), 0);

}

TimEvent::TimEvent(TimWave *parent, TimEventType *type, double time) :
  QGraphicsItem(parent), QGraphicsLayoutItem(0, false) {
  m_Wave = parent;

  m_prev = NULL;
  m_next = NULL;
  m_EventType = NULL;

  m_EventTime = time;

  setEventType(type);

  setPos(calcXPos(m_EventTime), 0);

}

TimEvent::~TimEvent() {
  delete m_EventType;
}

void TimEvent::insertEvent(TimEvent *node) {

  /*
   +----+     +----+
   |    |-----|    |
   |    |-----|    |
   +----+     +----+
   */

  node->setNext(getNext());
  node->setPrev(this);

  if (getNext() != NULL) {
    getNext()->setPrev(node);
  }

  setNext(node);

}

void TimEvent::setNext(TimEvent *next) {
  m_next = next;
}

void TimEvent::setPrev(TimEvent *prev) {
  m_prev = prev;
}

TimEvent* TimEvent::getNext() {
  return m_next;
}

TimEvent* TimEvent::getPrev() {
  return m_prev;
}

unsigned int TimEvent::calcXPos(double time) {
  double start_time = m_Wave->getLayoutData()->get_start_time();
  double end_time = m_Wave->getLayoutData()->get_end_time();
  unsigned int width = m_Wave->getLayoutData()->get_col_1_width();

  double diff = end_time - start_time;

  double scale = diff / width;

  unsigned int x_pos = (unsigned int) ((time - start_time) / scale);

  return x_pos;

}

TimWave* TimEvent::getWave() {
  return m_Wave;
}

void TimEvent::setEventType(TimEventType *type) {
  if (m_EventType) {
    delete m_EventType;
  }
  m_EventType = type;
  m_EventType->setParent(this);
}

TimEventType* TimEvent::getEventType() {
  return m_EventType;
}

QSizeF TimEvent::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const {
  switch (which) {
  case Qt::MinimumSize:
    return QSizeF(200, 50);
  case Qt::PreferredSize:
    return QSizeF(200, 50);
  case Qt::MaximumSize:
    return QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
  default:
    qWarning("r::TimWave::sizeHint(): Don't know how to handle the value of 'which'");
    break;
  }
  return constraint;

}

void TimEvent::setGeometry(const QRectF & rect) {

  setPos(calcXPos(m_EventTime), 0);
}

QRectF TimEvent::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(0 - penWidth / 2, 0 - penWidth / 2, m_Wave->getLayoutData()->get_col_1_width()
      + penWidth, 50 + penWidth);
}

void TimEvent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  m_EventType->paint(this, painter, option, widget);
}

void TimEvent::mousePressEvent(QGraphicsSceneMouseEvent * event) {
  if (event->button() == Qt::LeftButton) {

    // get a pointer to the signal manager
    TimEventType * et = getWave()->getScene()->getSignalManager()->getCurrent();

    if( et == NULL) {
      QGraphicsItem::mousePressEvent(event);
    }
    qDebug("Mouse Event");
  }
}
