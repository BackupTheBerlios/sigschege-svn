// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs, Ulf Klaperski
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
    cout << " Time Start:  " << eventsIter->Object()->getTime(0) << endl;
    cout << " Time End:  " << eventsIter->Object()->getTime(100) << endl;
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
  EasyVecPolyline *sigline0 = 0;
  EasyVecPolyline *sigline1 = 0;
  EasyVecPolyline *sigline_tmp = 0;

  string currentState = initialState->getNewState();
  int xCoord,xMax = cOrigin.xpos()+cSize.xpos();
  vector< Handle<Event> >::iterator eventsIter;
  string newState;
  double eventStart, eventEnd;
  int where = 0;
  bool sigline0IsTop, sigline1IsTop;
  double compoundTimeDiff = compoundTimeEnd-compoundTimeStart;
  int startX, endX;
  int y0start, y0end, y1start, y1end;
  bool partialStart;

  int y0 = cOrigin.ypos()+cSize.ypos();
  int y1 = cOrigin.ypos();    
    
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {

    bool swapSiglines = false;
    Event *curEv = eventsIter->Object(); // unclean, but we don't manipulate events here...
    newState = eventsIter->Object()->getNewState();
    eventStart = eventsIter->Object()->getTime(0);
    eventEnd = eventsIter->Object()->getTime(100);

    startX = cOrigin.xpos()+static_cast<int>(static_cast<double>(cSize.xpos())
                                             * (eventStart-compoundTimeStart)/(compoundTimeDiff));
    endX = cOrigin.xpos()+static_cast<int>(static_cast<double>(cSize.xpos())
                                           * (eventEnd-compoundTimeStart)/(compoundTimeDiff));
    
    if (where==1 || (where==0 && eventEnd>compoundTimeStart)) {
      // we are in the visible area (2nd condition means we just entered)

      if (eventStart<compoundTimeStart) {
        // event crosses start of visible area
        startX = cOrigin.xpos();
        y1start = static_cast<int>(cOrigin.ypos()+cSize.ypos()*(1.0-(eventEnd-compoundTimeStart)/(eventEnd-eventStart)));
        y0start = static_cast<int>(cOrigin.ypos()+cSize.ypos()*(eventEnd-compoundTimeStart)/(eventEnd-eventStart));
        partialStart = true;
      } else {
        y0start=y0;
        y1start=y1;
        partialStart = false;
      }

      if (eventEnd>compoundTimeEnd) {
        // event crosses end of visible area
        endX = cOrigin.xpos()+cSize.xpos();
        y1end = static_cast<int>(cOrigin.ypos()+cSize.ypos()*(1.0-(compoundTimeEnd-eventStart)/(eventEnd-eventStart)));
        y0end = static_cast<int>(cOrigin.ypos()+cSize.ypos()*(compoundTimeEnd-eventStart)/(eventEnd-eventStart));
        where = 2;
      } else {
        y0end=y0;
        y1end=y1;
      }

      if ((currentState==string("1") && newState==string("X")) || (currentState==string("X") && newState==string("1"))) {
        // 1->X and X->1 need a top2top line
        if (sigline1==0) {
          sigline1 = evListCompound->polyline();
          if (where==0) {
            sigline1->add_point(EVPosInt(cOrigin.xpos(), y1));
          }
        }
        sigline1->add_point(EVPosInt(startX, y1));
        sigline1->add_point(EVPosInt(endX, y1));
        if (newState==string("X")) {
          // 1->X, make sure top2bottom works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
      }
      if ((currentState!=string("0") && newState!=string("1"))) {
        // 1->0, 1->X, X->X, X->0 need a top2bottom line
        if (sigline1==0) {
          sigline1 = evListCompound->polyline();
          if (where==0 && !partialStart) {
            sigline1->add_point(EVPosInt(cOrigin.xpos(), y1start));
          }
        }
        sigline1->add_point(EVPosInt(startX, y1start));
        sigline1->add_point(EVPosInt(endX, y0end));
        swapSiglines = true;
      }
      if ((currentState==string("0") && newState==string("X")) || (currentState==string("X") && newState==string("0"))) {
        // 0->X and X->0 need a bottom2bottom line
        if (sigline0==0) {
          sigline0 = evListCompound->polyline();
          if (where==0) {
            sigline0->add_point(EVPosInt(cOrigin.xpos(), y0));
          }
        }
        sigline0->add_point(EVPosInt(startX, y0));
        sigline0->add_point(EVPosInt(endX, y0));
        if (newState==string("X")) {
          // 0->X, make sure bottom2top works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
      }
      if (currentState!=string("1") && newState!=string("0")) {
        // 0->1, 0->X, X->X and X->1 need a bottom2top line
        if (sigline0==0) {
          sigline0 = evListCompound->polyline();
          if (where==0 && !partialStart) {
            sigline0->add_point(EVPosInt(cOrigin.xpos(), y0start));
          }
        }
        sigline0->add_point(EVPosInt(startX, y0start));
        sigline0->add_point(EVPosInt(endX, y1end));
        swapSiglines = true;
      }

      if (swapSiglines) {
        sigline_tmp = sigline1;
        sigline1 = sigline0;
        sigline0 = sigline_tmp;
      }
      if (currentState==string("X") && (newState==string("1") || newState==string("0"))) {
        if (newState==string("0")) sigline1 = 0;
        else sigline0 = 0;
      }      
      where = 1;
    }

    if (where == 0) { // before compound start
      if (eventEnd<compoundTimeStart) {
        // event before compound: just get its new state
        currentState = newState;
      } else if (eventStart<compoundTimeStart) {
        // event overlaps start of compound
        if ((currentState==string("1") && newState==string("X")) || (currentState==string("X") && newState==string("1"))) {
          sigline0 = evListCompound->polyline();
          sigline0->add_point(EVPosInt(cOrigin.xpos(), cSize.ypos()+cOrigin.ypos()));
          sigline0->add_point(EVPosInt(endX, cSize.ypos()+cOrigin.ypos()));
          sigline0IsTop = true;
        }
        where = 1;
      }
    }
    currentState = newState;
  }
  
  // Add the last point of the signal
  if (sigline0!=0) {
    sigline0->add_point(EVPosInt(xMax, y0end));
  }
  if (sigline1!=0) {
    sigline1->add_point(EVPosInt(xMax, y1end));
  }
}

