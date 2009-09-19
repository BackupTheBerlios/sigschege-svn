// -*- c++ -*-
// TimingScene.h
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


#ifndef TIMINGSCENE_H_
#define TIMINGSCENE_H_

#include <QtGui>
#include "TimLayoutData.h"

class TimSignal;

class TimingScene: public QGraphicsScene {
Q_OBJECT

public:
  TimingScene(QObject *parent = 0);

  TimSignal* addTimSignal();

  TimLayoutData* getLayoutData();

  void setStartTime(double stime);
  void setEndTime(double etime);
  void setLabelWidth(unsigned int width);
  void setSceneWidth(unsigned int width);

private:
  QGraphicsLinearLayout *m_layout;
  TimLayoutData m_LayoutData;

};

#endif /* TIMINGSCENE_H_ */
