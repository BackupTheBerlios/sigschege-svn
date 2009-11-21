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

TimMember::TimMember(TimingScene *scene) :
  QGraphicsItem(0), QGraphicsLayoutItem(0, false) {

  setFlag(ItemIsSelectable);

  m_scene = scene;
  m_label = 0;
}

TimMember::~TimMember() {
  if (m_label) delete m_label;
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

void TimMember::setText ( const QString & text ) {
  m_label->setText(text);
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


