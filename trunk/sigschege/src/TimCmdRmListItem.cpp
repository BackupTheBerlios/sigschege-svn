// -*- c++ -*-
// TimCmdRmListItem.cpp
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

#include "TimCmdRmListItem.h"

TimCmdRmListItem::TimCmdRmListItem(TimingScene *scene, TimMember *item) {
  m_timingScene = scene;
  m_item = item;
  m_index = -1;
  m_owning = false;
}

TimCmdRmListItem::~TimCmdRmListItem() {
  if (m_owning) {
    delete m_item;
  }
}

void TimCmdRmListItem::undo() {
  // add items again
  m_timingScene->addTimListItem(m_index, m_item);
  m_owning = false;
}

void TimCmdRmListItem::redo() {
  m_index = m_timingScene->removeTimListItem(m_item);
  m_owning = true;
}



