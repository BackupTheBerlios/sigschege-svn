// -*- c++ -*-
// TimLabel.cpp
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

#include "TimLabel.h"
#include "SSGWriter.h"

TimLabel::TimLabel(TimMember *parent, TimingScene *scene) : TimMember(parent, scene) {
}

TimLabel::TimLabel(TimMember *parent, TimingScene *scene, const QString & text) : TimMember(parent, scene) {
  m_label = text;
}

QSizeF TimLabel::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const {

  QRectF prec = parentItem()->boundingRect();

  switch (which) {
  case Qt::MinimumSize:
    return QSizeF(m_LayoutData->get_col_0_width(), prec.width());
  case Qt::PreferredSize:
    return QSizeF(m_LayoutData->get_col_0_width(), prec.width());
  case Qt::MaximumSize:
    return QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
  default:
    qWarning("r::TimWave::sizeHint(): Don't know how to handle the value of 'which'");
    break;
  }
  return constraint;

}

void TimLabel::setGeometry(const QRectF & rect) {
  setPos(10, 0 );
}

QRectF TimLabel::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(0 - penWidth / 2, 0 - penWidth / 2, 30 + penWidth, 50
      + penWidth);
}

void TimLabel::SSGWrite(SSGWriter *writer) {

}

void TimLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  painter->drawText(boundingRect(), Qt::AlignCenter, m_label);
}

void TimLabel::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
  event->ignore();
}

void TimLabel::setText(const QString & text ) {
  m_label = text;
}

