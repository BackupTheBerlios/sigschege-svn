// -*- c++ -*-
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

#include "TimScale.h"
#include "TimLabel.h"
#include "TimUtil.h"
#include "SSGWriter.h"
#include "TimCmdRmSignal.h"

TimScale::TimScale(TimMember *parent, TimingScene *scene) : TimMember(parent, scene) {

  setFlag(ItemIsSelectable);

  m_label = new TimLabel(this, getScene(), "Time");
  m_label->setGeometry(QRectF(0, 0, getLayoutData()->get_col_0_width(), 50));
  m_label->setParentItem(this);

}

TimScale::~TimScale() {
}

QSizeF TimScale::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const {
  switch (which) {
  case Qt::MinimumSize:
    return QSizeF(50, 50);
  case Qt::PreferredSize:
    return QSizeF(100, 50);
  case Qt::MaximumSize:
    return QSizeF(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
  default:
    qWarning("r::TimScale::sizeHint(): Don't know how to handle the value of 'which'");
    break;
  }
  return constraint;
}

void TimScale::setGeometry(const QRectF & rect) {
  setPos(rect.topLeft());
}

QRectF TimScale::boundingRect() const {
  qreal penWidth = 1;
  return QRectF(0 - penWidth / 2, 0 - penWidth / 2, m_scene->getLayoutData()->get_col_0_width()
      + m_scene->getLayoutData()->get_col_1_width() + penWidth, 50 + penWidth);
}

void TimScale::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

  if (isSelected()) {
    painter->setBrush(QBrush(QColor(100,100,255,100)));
  }

  painter->drawRoundedRect(0, 0, m_scene->getLayoutData()->get_col_0_width()
      + m_scene->getLayoutData()->get_col_1_width(), 50, 5, 5);

  Range<double> timeRange(0.0, 100.0);
  Range<double> layoutRange(0, m_scene->getLayoutData()->get_col_1_width());

  double tickTime;
  double tickDistance = 10.0;

  for (tickTime = timeRange.cStart; tickTime<timeRange.cEnd; tickTime+=tickDistance) {
    int place = static_cast<int>(static_cast<double>(layoutRange.distance())*(tickTime-timeRange.cStart)/timeRange.distance());
    painter->drawLine(place, 10, place, 40);
  }

}

void TimScale::setText ( const QString & text ) {
  m_label->setText(text);
}

void TimScale::SSGWrite(SSGWriter *writer) {
  writer->writeStartElement("timescale");
  writer->writeStartElement("primarytext");
  writer->writeCDATA("TODO");
  writer->writeEndElement();
  writer->writeEndElement();

}

QUndoCommand* TimScale::createDeleteCmd() {
  return new TimCmdRmSignal(getScene(), this);
}
