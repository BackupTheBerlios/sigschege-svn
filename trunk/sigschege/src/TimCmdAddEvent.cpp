// -*- c++ -*-
// TimCmdAddEvent.cpp
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

#include "TimCmdAddEvent.h"
#include "TimWave.h"
#include "TimEventHigh.h"

TimCmdAddEvent::TimCmdAddEvent(TimingScene *tscene, TimEvent *event, TimEventType *type, double time) {
  m_timingScene = tscene;
  m_event       = event;
  m_eventType   = type;
  m_newEvent    = NULL;
  m_time        = time;
}

TimCmdAddEvent::~TimCmdAddEvent() {
  if(m_newEvent) {
    delete m_newEvent;
  }
}

void TimCmdAddEvent::undo() {
  m_newEvent = m_event->removeEvent(); // we gain ownership again
}

void TimCmdAddEvent::redo() {

  if(m_newEvent == NULL) {
    m_newEvent = new TimEvent(m_event->getWave(), m_timingScene, m_eventType, m_time);
  }
  m_event->insertEvent(m_newEvent);
  m_newEvent = NULL; // ownership was transfered
}

