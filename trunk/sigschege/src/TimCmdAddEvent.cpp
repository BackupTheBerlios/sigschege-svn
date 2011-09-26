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

TimCmdAddEvent::TimCmdAddEvent(TimWave *wave, double time, TimEventPainter *painter, double setup, double hold) :
  m_wave(wave), m_time(time), m_painter(painter), m_setup(setup), m_hold(hold)
{
}

TimCmdAddEvent::~TimCmdAddEvent() {
}

void TimCmdAddEvent::undo() {
  m_wave->rmTimEvent(m_time);
}

void TimCmdAddEvent::redo() {
    m_wave->addTimEvent(m_time, m_painter, m_setup, m_hold);
}

