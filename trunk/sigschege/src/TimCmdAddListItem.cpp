// -*- c++ -*-
// TimCmdAddListItem.cpp
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

#include "TimCmdAddListItem.h"
#include <iostream>
using namespace std;

TimCmdAddListItem::TimCmdAddListItem(TimingScene *tscene, int index, TimMember *item) {
  m_timingScene = tscene;
  m_item        = item;
  m_index       = index;
  m_owning      = true;
}

TimCmdAddListItem::~TimCmdAddListItem() {
  if(m_owning) {
    cout << "TimCmdAddListItem: delete " << m_item << endl;
    //delete m_item; TODO: why does this create a crash in TimScene?
  }
}

void TimCmdAddListItem::undo() {
  m_timingScene->rmTimListItem(m_item);
  m_owning = true;
}

void TimCmdAddListItem::redo() {
  m_timingScene->addTimListItem(m_index , m_item);
  m_owning = false;
}


