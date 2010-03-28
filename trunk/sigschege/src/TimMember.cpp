// -*- c++ -*-
// TimSignal.cpp
// Copyright 2009 by ingo & ulf
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

#include "TimMember.h"
#include "TimLabel.h"
#include "TimUtil.h"


TimMember::TimMember(TimMember *parent, TimingScene *scene) :
  QGraphicsItem(parent), QGraphicsLayoutItem(0, false) {

  m_scene = scene;
}

TimMember::~TimMember() {
}

QSizeF TimMember::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const {
  switch (which) {
  case Qt::MinimumSize:
    return QSizeF(50, 50);
  case Qt::PreferredSize:
    return QSizeF(100, 50);
  case Qt::MaximumSize:
    return QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
  default:
    qWarning("r::TimMember::sizeHint(): Don't know how to handle the value of 'which'");
    break;
  }
  return constraint;
}

void TimMember::setGeometry(const QRectF & rect) {
  setPos(rect.topLeft());
}

QRectF TimMember::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(0 - penWidth / 2, 0 - penWidth / 2, getLayoutData()->get_col_0_width()
      + getLayoutData()->get_col_1_width() + penWidth, 50 + penWidth);
}

TimLayoutData* TimMember::getLayoutData() const {
  return getScene()->getLayoutData();
}


TimingScene* TimMember::getScene() const {
  return m_scene;
}

qreal TimMember::calcSnapTime(qreal xpos, bool isWave) {

  TimLayoutData *ld = getLayoutData();

  if (!isWave) xpos -= ld->get_col_0_width();

  int width = ld->get_col_1_width();
  double start = ld->get_start_time();
  double end = ld->get_end_time();

  double time = ((((end - start) / width) * xpos));
  double lower = ld->get_snap_delta_time()*floor(time/ld->get_snap_delta_time());

  if ((time-lower)<(ld->get_snap_delta_time()/2.0))	time = lower;
  else time = lower + ld->get_snap_delta_time();

  return time;
}
