// -*- c++ -*-
// TimEvent.cpp
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


#include "TimEvent.h"


TimEvent::TimEvent() {
  setSetupTime(0.0);
  setEventTime(0.0);
  setHoldTime(0.0);
  setEventLevel(TimEvent::Low);
}

TimEvent::TimEvent(double event, TimEvent::EventLevel level) {
  setEventTime(event);
  setEventLevel(level);

  setSetupTime(0.0);
  setHoldTime(0.0);
}

TimEvent::TimEvent(double event, TimEvent::EventLevel level, double setup, double hold) {
  setEventTime(event);
  setEventLevel(level);

  setSetupTime(setup);
  setHoldTime(hold);
}

TimEvent::~TimEvent() {

}

double TimEvent::getSetupTime() const {
  return m_setup_time;
}

void TimEvent::setSetupTime(double time) {
  m_setup_time = time;
}

double TimEvent::getHoldTime() const {
  return m_hold_time;
}

void TimEvent::setHoldTime(double time) {
  m_hold_time = time;
}

double TimEvent::getEventTime() const {
  return m_event_time;
}

void TimEvent::setEventTime(double time) {
  m_event_time = time;
}

TimEvent::EventLevel TimEvent::getEventLevel() const {
  return m_event_level;
}

void TimEvent::setEventLevel(TimEvent::EventLevel level) {
  m_event_level = level;
}

bool TimEvent::operator < (const TimEvent & rhs) const {
  return getAbsSetupTime() < rhs.getAbsSetupTime();
}

double TimEvent::getAbsSetupTime() const {
  return getEventTime() - getSetupTime();
}

double TimEvent::getAbsHoldTime() const {
  return getEventTime() + getHoldTime();
}
