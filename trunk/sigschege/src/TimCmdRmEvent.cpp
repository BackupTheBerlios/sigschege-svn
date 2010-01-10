// -*- c++ -*-
// TimCmdRmEvent.cpp
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

#include "TimCmdRmEvent.h"
#include "TimWave.h"

TimCmdRmEvent::TimCmdRmEvent(TimEvent *event) :
  m_event(event) {
  m_owning = false;
  m_first = false;
  m_prev = m_event->getPrev();
}

TimCmdRmEvent::~TimCmdRmEvent() {
  if (m_owning) {
    delete m_event;
  }
}

void TimCmdRmEvent::redo() {
  if (m_prev) {
    m_owning = true;
    m_prev->removeEvent();
  } else {
    // Check if we have a next event
    qDebug() << "Try to delete last event in waveform. Ignore delete cmd.";
  }
}

void TimCmdRmEvent::undo() {
  if (m_owning) {
    m_owning = false;
    m_prev->insertEvent(m_event);
  }
}
