// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs
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
// $Id$

using namespace std;

#include "EventList.h"
#include<algorithm>

EventList::EventList() {

}

EventList::~EventList() {
}

Event* EventList::createEvent() {
  Event* new_event = new Event;
  events.push_back(new_event);
  return new_event;
}

bool EventList::deleteEvent(Event* obsoleteEvent) {
  vector<Event*>::iterator eventsIter;
    for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
      if (*eventsIter==obsoleteEvent) {
        events.erase(eventsIter);
        return true;
      }
    }
    return false;
}

void EventList::sort() {
  ::sort(events.begin(), events.end(), EventList::evTimeCmp());
}

