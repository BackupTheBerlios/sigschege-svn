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
#include "TimCmdRmListItem.h"
#include <iostream>

using namespace std;

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


  TimLayoutData *layoutd;
  layoutd = m_scene->getLayoutData();


  Range<double> timeRange(layoutd->get_start_time(), layoutd->get_end_time());

  Range<double> layoutRange(layoutd->get_col_0_width(), layoutd->get_col_0_width()+layoutd->get_col_1_width());

  double timeDist = timeRange.distance();
  double normFactor = pow(10, floor(log10(timeDist))); 
  double timeDistNorm = timeDist/normFactor; // (1<=timeDistNorm<10)
  double labelDistNorm;
  if (timeDistNorm>8.0) {
    labelDistNorm = 2.0;
  } else if (timeDistNorm>5.0) {
    labelDistNorm = 1.0;
  } else if (timeDistNorm>2.5) {
    labelDistNorm = 0.5;
  } else if (timeDistNorm>1.5) {
    labelDistNorm = 0.2;
  } else {
    labelDistNorm = 0.1;
  }
  
  int labelCnt = static_cast<int>(floor(timeDistNorm/labelDistNorm));
//   cout << "DEBUG: starttime=" << timeRange.cStart << " endtime=" << timeRange.cEnd << endl;
//   cout << "DEBUG: timeDist=" << timeDist << " normFactor=" << normFactor << endl;
//   cout << "DEBUG: timeDistNorm=" << timeDistNorm << " labelDistNorm=" << labelDistNorm << endl;

  double labelDistance = labelDistNorm*normFactor;
  double tickDistance;
  if (labelCnt>5) {
    tickDistance = labelDistance/5.0;
  } else {
    tickDistance = labelDistance/10.0;
  }
  double tickTime;

  for (tickTime = timeRange.cStart; tickTime<timeRange.cEnd; tickTime += tickDistance) {
    int place = layoutRange.cStart+static_cast<int>(static_cast<double>(layoutRange.distance())*(tickTime-timeRange.cStart)/timeRange.distance());
    cout << "T-PLACE:" << place << endl;
    painter->drawLine(place, 5, place, 15);
  }

  int tdistcoord = layoutRange.cStart+static_cast<int>(static_cast<double>(layoutRange.distance())*labelDistance/timeRange.distance());
  for (tickTime = timeRange.cStart; tickTime<timeRange.cEnd; tickTime += labelDistance) {
    QRect textBox;
    int place = layoutRange.cStart+static_cast<int>(static_cast<double>(layoutRange.distance())*(tickTime-timeRange.cStart)/timeRange.distance());
    painter->drawLine(place, 5, place, 25);
    painter->drawText(QRect(place-tdistcoord/2, 27, tdistcoord, 20), Qt::AlignHCenter|Qt::AlignTop, QString("%1").arg(tickTime, 0, 'g', -1), &textBox);
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
  return new TimCmdRmListItem(getScene(), this);
}
