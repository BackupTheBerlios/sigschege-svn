// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ingo Hinrichs, Ulf Klaperski
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


#include <YaVecPolyline.h>
#include <YaVecText.h>
#include "EventList.h"
#include "Handle.t"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace YaVec;

EventList::EventList(double defaultSlope)
  : events(), initialState(new Event), cDefaultSlope(defaultSlope)
{
  namedEvents = false;
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

Handle<Event> EventList::createEvent(const State &eventNewState, double eventDelay, Handle<Event> *refEvent_p) {
  Handle<Event> new_event = createEvent();
  if (refEvent_p!=0) {
    new_event->setReference(*refEvent_p);
  }
  new_event->setDelay(eventDelay);
  new_event->setNewState(eventNewState);
  new_event->setSlope(cDefaultSlope);
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

Handle<Event> EventList::getEventAfter(double evTime, int percentageLevel, State newState) {
  vector< Handle<Event> >::iterator eventsIter;
  sort(); // makes life easier... 
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {
    if (eventsIter->Object()->getTime(percentageLevel)>=evTime &&
        (newState==State(State::Illegal) || newState==eventsIter->Object()->getNewState())) {
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
    cout << " Refcount:  " << eventsIter->Object()->objRefCount() << endl;
  }
  cout << "===== EVENT LIST STOP" << endl;
}

/*!
 * Set the compound
 * \param newCompound The new Compound
 */
void EventList::setCompound(FCompound *newCompound) {
  evListCompound = newCompound;
}

/*!
 * Set the Origin
 * \param newOrigin The new Origin
 */
void EventList::setOrigin(PosInt newOrigin) {
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
void EventList::setSize(PosInt newSize) {
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
void EventList::setCompound(FCompound *newCompound, int xOffset, int yOffset,
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
void EventList::setCompound(FCompound *newCompound, PosInt newOrigin, PosInt newSize, double timeStart, double timeEnd) {
  evListCompound = newCompound;
  cOrigin = newOrigin;

  cSize = newSize;

  compoundTimeStart = timeStart;
  compoundTimeEnd = timeEnd;
}

int EventList::vertPosFromState(State::drawStateType state, State::drawStateType newState, double percentageNew) {
  int pos = cOrigin.ypos();
  int height = cSize.ypos();
  if (state==State::Zero) {
    pos += height;
    if (newState==State::One) {
      pos -= static_cast<int>(percentageNew*height);
    } else if (newState==State::Z) {
      pos -= static_cast<int>(0.5*percentageNew*height);
    }
  } else if  (state==State::One) {
    if (newState==State::Zero) {
      pos += static_cast<int>(percentageNew*height);
    } else if (newState==State::Z) {
      pos += static_cast<int>(0.5*percentageNew*height);
    }
  } else {
    pos += static_cast<int>(0.5*height);
    if (newState==State::Zero) {
      pos += static_cast<int>(0.5*percentageNew*height);
    } else if (newState==State::One) {
      pos -= static_cast<int>(0.5*percentageNew*height);
    }
  }
  return pos;
}

void EventList::paint(void) {
  if (evListCompound==0) return;
  sort(); // makes life easier... 
  FPolyline *sigline0 = 0;
  FPolyline *sigline1 = 0;
  FPolyline *sigline_tmp = 0;

  State currentState = initialState->getNewState();
  State newState;
  int xMax = cOrigin.xpos()+cSize.xpos();
  vector< Handle<Event> >::iterator eventsIter;
  double eventStart, eventEnd;
  enum { before_visible, in_visible, after_visible } where;
  double compoundTimeDiff = compoundTimeEnd-compoundTimeStart;
  int startX, endX;
  bool partialStart;

  int y0 = vertPosFromState(State::Zero);
  int y1 = vertPosFromState(State::One);    
  int y0start, y0end, y1start, y1end; // variations of y0/y1 in case an event crosses start/end

  where = before_visible;
  y0end = y0;
  y1end = y1;
  double percentageNewStart;
  double percentageNewEnd; 
  
  double oldEndX = cOrigin.xpos();

  // make sure the starting points are set if the event list is empty
  if (events.size()==0) {
    if (currentState==State::Zero || currentState==State::X || currentState==State::Named) {
      sigline0 = evListCompound->polyline();
      sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::Zero)));
    } else if (currentState==State::Z) {
      sigline0 = evListCompound->polyline();
      sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::Z)));
    }
    if (currentState==State::One || currentState==State::X || currentState==State::Named) {
      sigline1 = evListCompound->polyline();
      sigline1->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::One)));
    }
  }
  
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {

    bool swapSiglines = false;
    newState = eventsIter->Object()->getNewState();
    eventStart = eventsIter->Object()->getTime(0);
    eventEnd = eventsIter->Object()->getTime(100);

    startX = cOrigin.xpos()+static_cast<int>(static_cast<double>(cSize.xpos())
                                             * (eventStart-compoundTimeStart)/(compoundTimeDiff));
    endX = cOrigin.xpos()+static_cast<int>(static_cast<double>(cSize.xpos())
                                           * (eventEnd-compoundTimeStart)/(compoundTimeDiff));
    
    if (where==in_visible || (where==before_visible && eventEnd>compoundTimeStart)) {
      // we are in the visible area (2nd condition means we just entered)

      if (eventStart<compoundTimeStart) {
        // event crosses start of visible area
        startX = cOrigin.xpos();
        percentageNewStart = (compoundTimeStart-eventStart)/(eventEnd-eventStart);
        y1start = vertPosFromState(State::One, State::Zero, percentageNewStart);
        y0start = vertPosFromState(State::Zero, State::One, percentageNewStart);
        partialStart = true;
      } else {
        percentageNewStart = 0.0;
        y0start=y0;
        y1start=y1;
        partialStart = false;
      }

      if (eventEnd>compoundTimeEnd) {
        // event crosses end of visible area
        endX = cOrigin.xpos()+cSize.xpos();
        percentageNewEnd = (compoundTimeEnd-eventStart)/(eventEnd-eventStart);
        y1end = static_cast<int>(cOrigin.ypos()+cSize.ypos()*(1.0-percentageNewEnd));
        y0end = static_cast<int>(cOrigin.ypos()+cSize.ypos()*percentageNewEnd);
        where = after_visible;
      } else {
        percentageNewEnd = 1.0;
        y0end=y0;
        y1end=y1;
      }

      if ((currentState.isRealDrawState('1') && newState.isRealDrawState('X')) ||
          (currentState.isRealDrawState('X') && newState.isRealDrawState('1'))) {
        // 1->X and X->1 need a top2top line
        if (sigline1==0) {
          sigline1 = evListCompound->polyline();
          if (where==before_visible) {
            sigline1->addPoint(PosInt(cOrigin.xpos(), y1));
          }
        }
        sigline1->addPoint(PosInt(startX, y1));
        sigline1->addPoint(PosInt(endX, y1));
        if (newState.isRealDrawState('X')) {
          // 1->X, make sure top2bottom works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
      }
      
      if ((currentState.isRealDrawState('1') || currentState.isRealDrawState('X')) &&
          (newState.isRealDrawState('0') || newState.isRealDrawState('X'))) {
        // 1->0, 1->X, X->X, X->0 need a top2bottom line
        if (sigline1==0) {
          sigline1 = evListCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline1->addPoint(PosInt(cOrigin.xpos(), y1start));
          }
        }
        sigline1->addPoint(PosInt(startX, y1start));
        sigline1->addPoint(PosInt(endX, y0end));
        swapSiglines = true;
      }
      
      if ((currentState.isRealDrawState('0') && newState.isRealDrawState('X')) || (currentState.isRealDrawState('X') && newState.isRealDrawState('0'))) {
        // 0->X and X->0 need a bottom2bottom line
        if (sigline0==0) {
          sigline0 = evListCompound->polyline();
          if (where==before_visible) {
            sigline0->addPoint(PosInt(cOrigin.xpos(), y0));
          }
        }
        sigline0->addPoint(PosInt(startX, y0));
        sigline0->addPoint(PosInt(endX, y0));
      }
      
      if ((currentState.isRealDrawState('0') || currentState.isRealDrawState('X'))
          && (newState.isRealDrawState('1') || newState.isRealDrawState('X'))) {
        // 0->1, 0->X, X->X and X->1 need a bottom2top line
        if (currentState.isRealDrawState('0') && newState.isRealDrawState('X')) {
          // Z->X, make sure bottom2top works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
        swapSiglines = true;
        if (sigline0==0) {
          sigline0 = evListCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(cOrigin.xpos(), y0start));
          }
        }
        sigline0->addPoint(PosInt(startX, y0start));
        sigline0->addPoint(PosInt(endX, y1end));
      }
      
      if ((currentState.isRealDrawState('0') || currentState.isRealDrawState('X'))
          && (newState.isRealDrawState('Z'))) {
        // 0->Z, X->Z need a bottom2medium line
        if (sigline0==0) {
          sigline0 = evListCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::Zero, State::Z, percentageNewStart)));
          }
        }
        sigline0->addPoint(PosInt(startX, vertPosFromState(State::Zero, State::Z, percentageNewStart)));
        sigline0->addPoint(PosInt(endX, vertPosFromState(State::Zero, State::Z, percentageNewEnd)));
      }

      if ((currentState.isRealDrawState('1') || currentState.isRealDrawState('X'))
          && (newState.isRealDrawState('Z'))) {
        // 1->Z, X->Z need a top2medium line
        if (sigline1==0) {
          sigline1 = evListCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline1->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::One, State::Z, percentageNewStart)));
          }
        }
        sigline1->addPoint(PosInt(startX, vertPosFromState(State::One, State::Z, percentageNewStart)));
        sigline1->addPoint(PosInt(endX, vertPosFromState(State::One, State::Z, percentageNewEnd)));
      }
      
      if ((currentState.isRealDrawState('Z')) && (newState.isRealDrawState('0') || newState.isRealDrawState('X'))) {
        // Z->0, Z->X need a medium2bottom line
        if (sigline0==0) {
          sigline0 = evListCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::Z, State::Zero, percentageNewStart)));
          }
        }
        sigline0->addPoint(PosInt(startX, vertPosFromState(State::Z, State::Zero, percentageNewStart)));
        sigline0->addPoint(PosInt(endX, vertPosFromState(State::Z, State::Zero, percentageNewEnd)));
        if (newState.isRealDrawState('X')) {
          // Z->X, make sure bottom2top works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
      }

      if ((currentState.isRealDrawState('Z')) && (newState.isRealDrawState('1') || newState.isRealDrawState('X'))) {
        // Z->1, Z->X need a medium2top line
        if (sigline0==0) {
          sigline0 = evListCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::Z, State::One, percentageNewStart)));
          }
        }
        sigline0->addPoint(PosInt(startX, vertPosFromState(State::Z, State::One, percentageNewStart)));
        sigline0->addPoint(PosInt(endX, vertPosFromState(State::Z, State::One, percentageNewEnd)));
        swapSiglines = true;
      }

      // handle the case that an event doesn't change the state - required
      // if it's the first event in the visible area
      if (currentState.getDrawState()==newState.getDrawState()) {
        bool isX = (newState.isRealDrawState('X') || newState.isDrawState("Named"));
        if (newState.isRealDrawState('0') || newState.isRealDrawState('Z') || isX ) {
          if (sigline0==0) {
            sigline0 = evListCompound->polyline();
            if (where==before_visible && !partialStart) {
              sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(isX? State::Zero : currentState.getDrawState(), State::One, 0.0)));
            }
          }
        }
        if (newState.isRealDrawState('1') || isX) {
          if (sigline1==0) {
            sigline1 = evListCompound->polyline();
            if (where==before_visible && !partialStart) {
              sigline1->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(isX? State::One : currentState.getDrawState(), State::One, 0.0)));
            }
          }
        }
      }
            
      if (swapSiglines) {
        sigline_tmp = sigline1;
        sigline1 = sigline0;
        sigline0 = sigline_tmp;
      }
      if (currentState.isRealDrawState('X') && (newState.isRealDrawState('1') || newState.isRealDrawState('0') || newState.isRealDrawState('Z'))) {
        if (newState.isRealDrawState('0') || newState.isRealDrawState('Z')) sigline1 = 0;
        else sigline0 = 0;
      }
      if (namedEvents) { //  && (where==in_visible || eventEnd>compoundTimeEnd ???
        string stateText = currentState.getStateName();
        if (stateText!="") {
          FText* label = evListCompound->text();
          label->setOrigin(PosInt(static_cast<int>((startX+oldEndX)/2), y0+(y1-y0)/4));
          label->setText(stateText);
          label->setJustification(FText::center);
          label->setSize(10);
        }
      }
      oldEndX = endX;
      where = in_visible;
    } else if (where == before_visible) {
      // event before compound: just get its new state (done anyway below)
    }
    currentState = newState;
  }
  
  // Add the last point of the signal
  if (sigline0!=0) {
    if (currentState==State::Z) {
      sigline0->addPoint(PosInt(xMax, vertPosFromState(State::Z, State::Z, 1.0)));
    } else {
      sigline0->addPoint(PosInt(xMax, y0end));
    }
  }
  if (sigline1!=0) {
    sigline1->addPoint(PosInt(xMax, y1end));
  }
  if (namedEvents) { //  && (where==in_visible || eventEnd>compoundTimeEnd ???
    string stateText = currentState.getStateName();
    if (stateText!="") {
      FText* label = evListCompound->text();
      label->setOrigin(PosInt(static_cast<int>((xMax+oldEndX)/2), y0+(y1-y0)/4));
      label->setText(stateText);
      label->setJustification(FText::center);
      label->setSize(10);
    }
  }

}

