// -*- c++ -*-
// TimCmdAddEvent.h
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



#ifndef TIMCMDADDEVENT_H_
#define TIMCMDADDEVENT_H_

#include <QtGui>

#include "TimEvent.h"
#include "TimEventPainter.h"

class TimWave;


class TimCmdAddEvent : public QUndoCommand {

public:

  TimCmdAddEvent(TimWave *wave, double time, TimEventPainter *painter, double setup, double hold);
  virtual ~TimCmdAddEvent();

  virtual void undo();
  virtual void redo();

private:
  TimWave         *m_wave;
  double           m_time;
  double           m_setup;
  double           m_hold;
  TimEventPainter *m_painter;
};


#endif /* TIMCMDADDEVENT_H_ */
