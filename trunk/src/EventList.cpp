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
#include<iostream>

EventList::EventList() : events() {
}

EventList::~EventList() {
  clear(); // don't leave unused Events in memory...
}

void EventList::clear(void) {
    Event* last_elm;
  while (events.size()>0) {
    last_elm = events.back();
    delete last_elm; // delete the Event the pointer points to
    events.pop_back(); // remove the pointer from the list
  }

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

Event* EventList::getEventAfter(double evTime) {
  vector<Event*>::iterator eventsIter;
  sort(); // makes life easier... 
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
    if ((*eventsIter)->getTime()>=evTime) {
      return *eventsIter;
    }
  }
  return NULL;
}

void EventList::debugEvents(void) {
  vector<Event*>::iterator eventsIter;
  cout << "===== EVENT LIST START" << endl;
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
    cout << "Event:  " << *eventsIter << endl;
    cout << " Delay: " << (*eventsIter)->getDelay() << endl;
    cout << " Time:  " << (*eventsIter)->getTime() << endl;
  }
  cout << "===== EVENT LIST STOP" << endl;
}
