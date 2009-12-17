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

class TimEvent;
class TimEventType;
class TimEventLow;
class TimEventHigh;

class TimSignalManager : public QObject {

  Q_OBJECT

public:
  TimSignalManager(QObject * parent = 0);
  ~TimSignalManager();

  TimEventType* getCurrent();

  TimEventType* getDefault();

private:
  TimEventType *m_current;

  TimEvent *m_event;

  TimEventHigh *m_high;
  TimEventLow  *m_low;

public slots:
  void selectNone(bool checked);
  void selectHigh(bool checked);
  void selectLow(bool checked);
};

#endif /* TIMSIGNALMANGER_H_ */
