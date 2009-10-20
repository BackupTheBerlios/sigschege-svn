// -*- c++ -*-
// TimCmdAddSignal.cpp
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

#include "TimCmdAddSignal.h"

TimCmdAddSignal::TimCmdAddSignal(TimingScene *tscene) {
  m_timingScene = tscene;
  m_timSignal   = NULL;
}

TimCmdAddSignal::~TimCmdAddSignal() {
  if(m_timSignal) {
    delete m_timSignal;
  }
}

void TimCmdAddSignal::undo() {
  m_timingScene->removeTimSignal(m_timSignal);
}

void TimCmdAddSignal::redo() {
  if(m_timSignal) {
    m_timingScene->addTimSignal(m_timSignal);
  } else {
    m_timSignal = m_timingScene->addTimSignal();
  }
}
