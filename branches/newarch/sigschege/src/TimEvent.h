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

class TimEvent {

public:
  enum EventLevel {
    None, Low, High, Invert
  };

  TimEvent();

  TimEvent(double event, EventLevel level = Low);

  TimEvent(double event, EventLevel level, double setup, double hold);

  ~TimEvent();

  double getAbsSetupTime() const;
  double getAbsHoldTime() const;

  double getSetupTime() const;
  void   setSetupTime(double time);

  double getHoldTime() const;
  void   setHoldTime(double time);

  double getEventTime() const;
  void   setEventTime(double time);

  EventLevel getEventLevel() const;
  void setEventLevel(EventLevel level);

  bool operator < (const TimEvent & rhs) const;

private:
  double m_setup_time;

  double m_hold_time;

  double m_event_time;

  EventLevel m_event_level;

};

#include <set>

typedef std::set<TimEvent> TimEventSet_t;

#endif /* TIMEVENT_H_ */
