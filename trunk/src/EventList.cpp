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

#include <EasyVecPolyline.h>
#include <EasyVecPolyline.h>
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

/*!
 * Set the compound
 * \param newCompound The new Compound
 */
void EventList::setCompound(EasyVecCompound *newCompound) {
  evListCompound = newCompound;
}

/*!
 * Set the Origin
 * \param newOrigin The new Origin
 */
void EventList::setOrigin(EVPosInt newOrigin) {
  cOrigin = newOrigin;
}

/*!
 * Set the Origin
 * \param xOffset The xOffset of the new Origin
 * \param yOffset The yOffset of the new Origin
 */
void EventList::setOrigin(int xOffset, int yOffset) {
  cOrigin.set(xOffset, yOffset);
}

//! Set the Size
/*!
 * Set the Size
 * \param newSize The new Size
 */
void EventList::setSize(EVPosInt newSize) {
  cSize = newSize;
}

//! Set the Size
/*!
 * Set the Size
 * \param width The new width
 * \param height The new height
 */
void EventList::setSize(int width, int height) {
  cSize.set(width,height);
}

/*!
 * Set the compound to which the signal is drawn.
 * \param newCompound  A pointer to the new compound.
 * \param xOffset The horizontal offset of the compound in the figure. 
 * \param yOffset The vertical offset of the compound in the figure. 
 * \param width  The width of the signal compound in figure units
 * \param height  The height of the signal compound in figure units
 * \param timeStart The start time of the signal 
 * \param timeEnd   The end time of the signal 
 */
void EventList::setCompound(EasyVecCompound *newCompound, int xOffset, int yOffset,
                            int width, int height, double timeStart, double timeEnd) {
  evListCompound = newCompound;
  cOrigin.set(xOffset,yOffset);

  cSize.set(width,height);

  compoundTimeStart = timeStart;
  compoundTimeEnd = timeEnd;
}

/*!
 * Set the compound to which the signal is drawn.
 * \param newCompound  A pointer to the new compound.
 * \param xOffset The horizontal offset of the compound in the figure. 
 * \param yOffset The vertical offset of the compound in the figure. 
 * \param width  The width of the signal compound in figure units
 * \param height  The height of the signal compound in figure units
 * \param timeStart The start time of the signal 
 * \param timeEnd   The end time of the signal 
 */
void EventList::setCompound(EasyVecCompound *newCompound, EVPosInt newOrigin, EVPosInt newSize, double timeStart, double timeEnd) {
  evListCompound = newCompound;
  cOrigin = newOrigin;

  cSize = newSize;

  compoundTimeStart = timeStart;
  compoundTimeEnd = timeEnd;
}

void EventList::paint(void) {
  if (evListCompound==0) return;
  sort(); // makes life easier... 
  EasyVecPolyline *sigline = evListCompound->polyline();
  string currentState = initialState->getNewState();
  int xCoord,xMax = cOrigin.xpos()+cSize.xpos();
  vector< Handle<Event> >::iterator eventsIter;

  // we want to draw lines without arrows
  sigline->forward_arrow(false);
  sigline->backward_arrow(false);

  // Set the first point of the signal
  sigline->add_point(EVPosInt(cOrigin.xpos(), (currentState==string("1")) ? cOrigin.ypos() : cSize.ypos()+cOrigin.ypos()));

  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
   
    xCoord = cOrigin.xpos() +  static_cast<int>(static_cast<double>(cSize.xpos()) * (eventsIter->Object()->getTime(0)-compoundTimeStart) /(compoundTimeEnd-compoundTimeStart));
    sigline->add_point(EVPosInt(xCoord, (currentState==string("1")) ? cOrigin.ypos() : cSize.ypos()+cOrigin.ypos()));
    currentState = eventsIter->Object()->getNewState();
    if (eventsIter->Object()->getSlope()!=0.0) { // get time for end of slope, if we have a slope!
      xCoord = cOrigin.xpos() +  static_cast<int>(static_cast<double>(cSize.xpos()) * (eventsIter->Object()->getTime(100)-compoundTimeStart) /(compoundTimeEnd-compoundTimeStart));
    }
    sigline->add_point(EVPosInt(xCoord, (currentState==string("1")) ? cOrigin.ypos() : cSize.ypos()+cOrigin.ypos()));
  }

  // Add the last point of the signal
  sigline->add_point(EVPosInt(xMax, (currentState==string("1")) ? cOrigin.ypos() : cSize.ypos()+cOrigin.ypos()));
}

