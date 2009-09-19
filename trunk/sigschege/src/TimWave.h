// -*- c++ -*-
// TimWave.h
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


#ifndef TIMWAVE_H_
#define TIMWAVE_H_

#include <QtGui>
#include "TimLayoutData.h"
#include "TimEvent.h"

class TimSignal;

class TimWave: public QGraphicsItem, public QGraphicsLayoutItem {

public:
  TimWave(TimLayoutData *layoutdata, QGraphicsItem *parent = 0);
  ~TimWave();

  virtual QRectF boundingRect() const;

  virtual void
      paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  virtual void setGeometry(const QRectF & rect);

  TimLayoutData* getLayoutData();

protected:
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

private:
  TimEvent *m_TimEvent;
  TimLayoutData *m_LayoutData;

};

#endif /* TIMWAVE_H_ */
