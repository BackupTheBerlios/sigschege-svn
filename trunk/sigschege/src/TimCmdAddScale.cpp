// TimCmdAddScale.cpp
// Copyright 2009 by ingo & ulf
//
// This file is part of Sigschege - Scale Schedule Generator
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

#include "TimCmdAddScale.h"

TimCmdAddScale::TimCmdAddScale(TimingScene *tscene) {
  m_timingScene = tscene;
  m_timScale   = NULL;
  m_owned       = false;
}

TimCmdAddScale::~TimCmdAddScale() {
  if(m_owned && m_timScale) {
    delete m_timScale;
  }
}

void TimCmdAddScale::undo() {
  m_timingScene->removeTimScale(m_timScale);
  m_owned = true;
}

void TimCmdAddScale::redo() {
  if(m_timScale) {
    m_timingScene->addTimScale(m_timScale);
  } else {
    m_timScale = m_timingScene->addTimScale();
  }
  m_owned = true;
}
