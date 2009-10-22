// -*- c++ -*-
// TimCmdRmSignal.cpp
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

#include "TimCmdRmSignal.h"

TimCmdRmSignal::TimCmdRmSignal(TimingScene *tscene) {
  m_timingScene = tscene;
}

TimCmdRmSignal::~TimCmdRmSignal() {

  for (int it = 0; it < m_items.size(); ++it) {
    delete m_items[it];
  }

}

void TimCmdRmSignal::undo() {
  // add items again
  for (int it = m_items.size() - 1; it >= 0; --it) {
    m_timingScene->addTimSignal(m_index[it], (TimSignal*) m_items[it]);
  }
  m_index.clear();
  m_items.clear();
}

void TimCmdRmSignal::redo() {
  // get selected items
  m_items = m_timingScene->selectedItems();
  // remove the and store the index for undo operations
  for (int it = 0; it < m_items.size(); ++it) {
    m_index.push_back(m_timingScene->removeTimSignal((TimSignal*) m_items[it]));
  }
}

