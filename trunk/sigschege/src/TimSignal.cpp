// -*- c++ -*-
// TimSignal.cpp
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

#include "TimSignal.h"
#include "TimWave.h"
#include "TimLabel.h"

TimSignal::TimSignal(TimLayoutData *layout, QGraphicsItem *parent) :
  QGraphicsItem(parent), QGraphicsLayoutItem(0, false) {

  m_LayoutData = layout;

  m_label = new TimLabel(m_LayoutData, "Test", this);
  m_label->setGeometry(QRectF(0, 0, m_LayoutData->get_col_0_width(), 50));
  m_wave = new TimWave(m_LayoutData, this);
  m_wave->setGeometry(QRectF(m_LayoutData->get_col_0_width(), 0, m_LayoutData->get_col_1_width(), 50));
}

TimSignal::~TimSignal() {
  delete m_wave;
  delete m_label;
}

QSizeF TimSignal::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const {
  switch (which) {
  case Qt::MinimumSize:
    return QSizeF(50, 50);
  case Qt::PreferredSize:
    return QSizeF(100, 50);
  case Qt::MaximumSize:
    return QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
  default:
    qWarning("r::TimSignal::sizeHint(): Don't know how to handle the value of 'which'");
    break;
  }
  return constraint;
}

void TimSignal::setGeometry(const QRectF & rect) {
  setPos(rect.topLeft());
}

QRectF TimSignal::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(0 - penWidth / 2, 0 - penWidth / 2, m_LayoutData->get_col_0_width()
      + m_LayoutData->get_col_1_width() + penWidth, 50 + penWidth);
}

void TimSignal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->drawRoundedRect(0, 0, m_LayoutData->get_col_0_width()
      + m_LayoutData->get_col_1_width(), 50, 5, 5);
}
