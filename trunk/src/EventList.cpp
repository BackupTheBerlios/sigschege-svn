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

#include <EasyVecElmPolyline.h>
#include <EasyVecElmPolyline.h>
#include "EventList.h"
#include "Handle.t"
#include<algorithm>
#include<iostream>

EventList::EventList() : events(), initialState(new Event) {
}

EventList::~EventList() {
  clear(); // don't leave unused Events in memory...
}

void EventList::clear(void) {
    Handle<Event> last_elm;
  while (events.size()>0) {
    last_elm = events.back();
    //delete last_elm; // delete the Event the pointer points to
    events.pop_back(); // remove the pointer from the list
  }
}


Handle<Event> EventList::createEvent() {
  Event* new_event = new Event;
  Handle<Event> new_handle(new_event);
  events.push_back(new_handle);
  return new_handle;
}

Handle<Event> EventList::createEvent(const string &eventNewState, double eventDelay, const Handle<Event> *refEvent_p) {
  Handle<Event> new_event = createEvent();
  if (refEvent_p!=0) {
    new_event->setReference(*refEvent_p);
  }
  new_event->setDelay(eventDelay);
  new_event->setNewState(eventNewState);
  return new_event;
}


bool EventList::deleteEvent(Handle<Event> obsoleteEvent) {
  vector< Handle<Event> >::iterator eventsIter;
    for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
      if ( eventsIter->Object()==obsoleteEvent.Object()) {
        events.erase(eventsIter);
        return true;
      }
    }
    return false;
}

void EventList::sort() {
  ::sort(events.begin(), events.end(), EventList::evTimeCmp());
}

Handle<Event> EventList::getEventAfter(double evTime) {
  vector< Handle<Event> >::iterator eventsIter;
  sort(); // makes life easier... 
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
    if (eventsIter->Object()->getTime()>=evTime) {
      return *eventsIter;
    }
  }
  return Handle<Event>(0);
}

void EventList::debugEvents(void) {
  vector< Handle<Event> >::iterator eventsIter;
  cout << "===== EVENT LIST START" << endl;
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
    cout << "Event:  " << eventsIter->Object() << endl;
    cout << " Delay: " << eventsIter->Object()->getDelay() << endl;
    cout << " Time:  " << eventsIter->Object()->getTime() << endl;
    cout << " New State:  " << eventsIter->Object()->getNewState() << endl;
  }
  cout << "===== EVENT LIST STOP" << endl;
}

void EventList::setCompound(EasyVecElmCompound *newCompound, int xOffset, int yOffset,
                            int width, int height, double timeStart, double timeEnd) {
  evListCompound = newCompound;
  compoundXOffset = xOffset;
  compoundYOffset = yOffset;
  compoundWidth = width;
  compoundHeight = height;
  compoundTimeStart = timeStart;
  compoundTimeEnd = timeEnd;
}

void EventList::paint(void) {
  if (evListCompound==0) return;
  EasyVecElmPolyline *sigline = evListCompound->polyline();
  string currentState = initialState->getNewState();
  int xCoord;
  vector< Handle<Event> >::iterator eventsIter;

  sigline->add_point(EVPosInt(compoundXOffset, (currentState==string("1")) ? 0 : compoundHeight));
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
    xCoord = compoundXOffset +
      static_cast<int>(static_cast<double>(compoundWidth) * (eventsIter->Object()->getTime()-compoundTimeStart)
                       /(compoundTimeEnd-compoundTimeStart));
    sigline->add_point(EVPosInt(xCoord, (currentState==string("1")) ? 0 : compoundHeight));
    currentState = eventsIter->Object()->getNewState();
    sigline->add_point(EVPosInt(xCoord, (currentState==string("1")) ? 0 : compoundHeight));
  }
  sigline->add_point(EVPosInt(compoundXOffset+compoundWidth, (currentState==string("1")) ? 0 : compoundHeight));
}

