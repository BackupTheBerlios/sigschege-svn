// -*- c++ -*-
// TimWave.cpp
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

#include "TimWave.h"
#include "TimSignal.h"
#include "TimEventHigh.h"
#include "TimEventLow.h"
#include "TimCmdAddEvent.h"
#include <iostream>
using namespace std;

TimWave::TimWave(TimMember *parent, TimingScene *scene)  :
    TimMember(parent, scene) {

  m_scene = scene;

  m_TimEvent = new TimEvent(this, getScene(), getScene()->getSignalManager()->getDefault());

}

TimWave::~TimWave() {
  delete m_TimEvent;
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

void TimWave::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  qreal xpos = mouseEvent->pos().x();
  cout << "POS=" << xpos << endl;
  //QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void TimWave::setGeometry(const QRectF & rect) {
  setPos(rect.topLeft());
}

QRectF TimWave::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(0 - penWidth / 2, 0 - penWidth / 2, getLayoutData()->get_col_1_width()
      + penWidth, 50 + penWidth);
}

void TimWave::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  //painter->drawRoundedRect(0, 0, m_LayoutData->get_col_1_width(), 50, 5, 5);
  // painter->drawLine(0, 30, 250, 30);

  if(isSelected()) {

    QBrush old = painter->brush();

    painter->setBrush(QBrush(QColor(255,100,100,100)));
    painter->drawRect(boundingRect());
    qDebug("Event is selected");

    painter->setBrush(old);
  }

}

TimLayoutData* TimWave::getLayoutData() const {
  return m_scene->getLayoutData();
}

TimingScene* TimWave::getScene() const {
  return m_scene;
}

void TimWave::timeRangeChange() { 
  TimEvent *timEvent;
  timEvent = m_TimEvent;
  while (timEvent != 0) {
    timEvent->setStdPos();
    timEvent = timEvent->getNext();
  }

}

EventLevel TimWave::getLevel(qreal time) {
  EventLevel result = Low;  
  TimEvent *timEvent;
  timEvent = m_TimEvent;
  while (timEvent != 0) {
    if (timEvent->getTime()>time) break;
    result = timEvent->getEventType()->getLevel();
    timEvent->setStdPos();
    timEvent = timEvent->getNext();
  }
  return result;
}
