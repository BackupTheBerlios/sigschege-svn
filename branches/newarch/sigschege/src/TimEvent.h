// -*- c++ -*-
// TimEvent.h
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


#ifndef TIMEVENT_H_
#define TIMEVENT_H_

#include "TimEventPainter.h"

class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

class TimEvent {

public:

  TimEvent(double event, TimEventPainter *painter = 0);

  TimEvent(double event, TimEventPainter *painter, double setup, double hold);

  virtual ~TimEvent();

  double getAbsSetupTime() const;
  double getAbsHoldTime() const;

  double getSetupTime() const;
  void   setSetupTime(double time);

  double getHoldTime() const;
  void   setHoldTime(double time);

  double getEventTime() const;
  void   setEventTime(double time);

  TimEventPainter* getEventPainter() const;
  void setEventPainter(TimEventPainter * painter);

  bool operator < (const TimEvent & rhs) const;

private:
  double m_setup_time;
  double m_hold_time;
  double m_event_time;

  TimEventPainter  *m_event_painter;

};

#include <set>

typedef std::set<TimEvent> TimEventSet_t;

#endif /* TIMEVENT_H_ */
