// -*- c++ -*-
// TimSignalManger.h
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



#ifndef TIMSIGNALMANGER_H_
#define TIMSIGNALMANGER_H_

#include <QtGui>

#include "TimEventTool.h"
#include "TimEventPainterLow.h"
#include "TimEventPainterHigh.h"

class TimEventType;
class TimEventLow;
class TimEventHigh;
class TimEventInvert;

class TimSignalManager : public QObject {

  Q_OBJECT

public:
  TimSignalManager(QObject * parent = 0);
  ~TimSignalManager();

  TimEventTool* getCurrent();

private:
  TimEventTool *m_current;

  TimEventHigh    *m_high;
  TimEventLow     *m_low;
  TimEventInvert  *m_invert;

public slots:
  void selectNone(bool checked);
  void selectHigh(bool checked);
  void selectLow(bool checked);
  void selectInvert(bool checked);

  // FIXME : make real tools
public:
  TimEventPainterHigh *p_high;
  TimEventPainterLow  *p_low;
};

#endif /* TIMSIGNALMANGER_H_ */
