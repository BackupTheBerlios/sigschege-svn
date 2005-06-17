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

#include "TimSignal.h"
#include <YaVecText.h>
#include <YaVecPolyline.h>
#include <iostream>

using namespace std;
using namespace YaVec;

/*!
 * Construct a Timing Diagram Signal Object
 */
TimSignal::TimSignal(double defaultSlope):LayoutObject(), EventList(defaultSlope) {
  cFontType  = 14;
  cFontSize  = 20;
  cSigOffset = 0;
}

/*!
 * Construct a Timing Diagram Signal Object with a Text Label
 * \param signalLabel Signal Label
 */
TimSignal::TimSignal(string signalLabel, double startTime, double endTime, double defaultSlope)
  : LayoutObject(), EventList(defaultSlope) {
  cText      = signalLabel;
  cFontType  = 14;
  cFontSize  = 20;
  cSigOffset = 0;
  cStartTime = startTime;
  cEndTime = endTime;
}

TimSignal::~TimSignal() {

}

/*!
 * Set a new Text
 * \param newText the new text
 */
void TimSignal::setText(string newText) {
  cText = newText;
}

//! Set the xoffset for the signal
void TimSignal::setSigOffset(int sigOffset) {
  cSigOffset = sigOffset;
}


int TimSignal::vertPosFromState(State::drawStateType state, State::drawStateType newState, double percentageNew) {
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

void TimSignal::paint(void) {
  if (cCompound==0) return;
  sort(); // makes life easier... 
  FPolyline *sigline0 = 0;
  FPolyline *sigline1 = 0;
  FPolyline *sigline_tmp = 0;
  FText *text;

  State currentState = initialState->getNewState();
  State newState;
  int xMax = cOrigin.xpos()+cSize.xpos();
  vector< Handle<Event> >::iterator eventsIter;
  double eventStart, eventEnd;
  enum { before_visible, in_visible, after_visible } where;
  double compoundTimeDiff = cEndTime-cStartTime;
  int startX, endX;
  bool partialStart;


  LayoutObject::paint(); // draw the border


  // Draw the Text
  text = getCompound()->text();
  text->setText(cText);
  text->setFont(cFontType);
  text->setSize(cFontSize);
  text->setOrigin(cOrigin+PosInt(cPadding, (cSize.ypos()+text->getHeight())/2));
  
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
      sigline0 = cCompound->polyline();
      sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::Zero)));
    } else if (currentState==State::Z) {
      sigline0 = cCompound->polyline();
      sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::Z)));
    }
    if (currentState==State::One || currentState==State::X || currentState==State::Named) {
      sigline1 = cCompound->polyline();
      sigline1->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(State::One)));
    }
  }
  
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {

    bool swapSiglines = false;
    newState = eventsIter->Object()->getNewState();
    eventStart = eventsIter->Object()->getTime(0);
    eventEnd = eventsIter->Object()->getTime(100);

    startX = cOrigin.xpos()+static_cast<int>(static_cast<double>(cSize.xpos())
                                             * (eventStart-cStartTime)/(compoundTimeDiff));
    endX = cOrigin.xpos()+static_cast<int>(static_cast<double>(cSize.xpos())
                                           * (eventEnd-cStartTime)/(compoundTimeDiff));
    
    if (where==in_visible || (where==before_visible && eventEnd>cStartTime)) {
      // we are in the visible area (2nd condition means we just entered)

      if (eventStart<cStartTime) {
        // event crosses start of visible area
        startX = cOrigin.xpos();
        percentageNewStart = (cStartTime-eventStart)/(eventEnd-eventStart);
        y1start = vertPosFromState(State::One, State::Zero, percentageNewStart);
        y0start = vertPosFromState(State::Zero, State::One, percentageNewStart);
        partialStart = true;
      } else {
        percentageNewStart = 0.0;
        y0start=y0;
        y1start=y1;
        partialStart = false;
      }

      if (eventEnd>cEndTime) {
        // event crosses end of visible area
        endX = cOrigin.xpos()+cSize.xpos();
        percentageNewEnd = (cEndTime-eventStart)/(eventEnd-eventStart);
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
          sigline1 = cCompound->polyline();
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
          sigline1 = cCompound->polyline();
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
          sigline0 = cCompound->polyline();
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
          sigline0 = cCompound->polyline();
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
          sigline0 = cCompound->polyline();
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
          sigline1 = cCompound->polyline();
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
          sigline0 = cCompound->polyline();
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
          sigline0 = cCompound->polyline();
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
            sigline0 = cCompound->polyline();
            if (where==before_visible && !partialStart) {
              sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(isX? State::Zero : currentState.getDrawState(), State::One, 0.0)));
            }
          }
        }
        if (newState.isRealDrawState('1') || isX) {
          if (sigline1==0) {
            sigline1 = cCompound->polyline();
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
      if (namedEvents) { //  && (where==in_visible || eventEnd>cEndTime ???
        string stateText = currentState.getStateName();
        if (stateText!="") {
          FText* label = cCompound->text();
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
  if (namedEvents) { //  && (where==in_visible || eventEnd>cEndTime ???
    string stateText = currentState.getStateName();
    if (stateText!="") {
      FText* label = cCompound->text();
      label->setOrigin(PosInt(static_cast<int>((xMax+oldEndX)/2), y0+(y1-y0)/4));
      label->setText(stateText);
      label->setJustification(FText::center);
      label->setSize(10);
    }
  }

}
