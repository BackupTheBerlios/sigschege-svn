// -*- c++ -*-
// \file  
// Copyright 2004, 2005, 2006 by Ingo Hinrichs, Ulf Klaperski
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

void TimSignal::getTextGeometry(YaVec::PosInt &upperLeft, YaVec::PosInt &lowerRight) {
  upperLeft.set(labelXLeft, timYTop);
  lowerRight.set(labelXRight, timYBottom);
}


/*!
 * Construct a Timing Diagram Signal Object
 */
TimSignal::TimSignal(bool isBool, double defaultSlope): TimingObject(), EventList(isBool, defaultSlope) {
  cSigOffset = 0;
}

/*!
 * Construct a Timing Diagram Signal Object with a text label.
 * \param signalLabel Signal label.
 * \param startTime The start time of the visible area.
 * \param endTime The end time of the visible area.
 * \param origin The origin in the timing diagram in xfig units.
 * \param size The complete size in xfig units.
 * \param sigOffset The horizontal offset at which the signal part starts.
 * \param defaultSlope The default slope for all events.
 */
TimSignal::TimSignal(string signalLabel, TimSchedule *schedulePtr, YaVec::PosInt origin,
                     YaVec::PosInt size, bool isBool, int sigOffset, double defaultSlope)
  : TimingObject(0, origin, size, sigOffset, schedulePtr),
    EventList(isBool, defaultSlope),
    TimText(signalLabel)
{
}

TimSignal::~TimSignal() {
}

int TimSignal::vertPosFromState(StateVisual::visualType visual, StateVisual::visualType newVisual, double percentageNew) {
  int pos = timYTop;
  if (visual==StateVisual::Zero) {
    pos += timHeight;
    if (newVisual==StateVisual::One) {
      pos -= static_cast<int>(percentageNew*timHeight);
    } else if (newVisual==StateVisual::Z) {
      pos -= static_cast<int>(0.5*percentageNew*timHeight);
    }
  } else if  (visual==StateVisual::One) {
    if (newVisual==StateVisual::Zero) {
      pos += static_cast<int>(percentageNew*timHeight);
    } else if (newVisual==StateVisual::Z) {
      pos += static_cast<int>(0.5*percentageNew*timHeight);
    }
  } else {
    pos += static_cast<int>(0.5*timHeight);
    if (newVisual==StateVisual::Zero) {
      pos += static_cast<int>(0.5*percentageNew*timHeight);
    } else if (newVisual==StateVisual::One) {
      pos -= static_cast<int>(0.5*percentageNew*timHeight);
    }
  }
  return pos;
}

//void TimSignal::paintTimeRange(void) {
//}

void TimSignal::paintRange(int rangeNum, Event* initialStateP) {

  Range<double> tRange = cSchedulePtr->timeRangeTimes(rangeNum);
  
  
  FPolyline *sigline0 = 0;
  FPolyline *sigline1 = 0;
  FPolyline *sigline_tmp = 0;

  string currentStateStr = initialStateP->getNewState();
  StateVisual currentState = smap[currentStateStr];

  StateVisual newState;
  string newStateStr;
  StateVisual::visualType currentVisual = currentState.visualization();
  StateVisual::visualType newVisual;

  vector< Handle<Event> >::iterator eventsIter;
  double eventStart, eventEnd;
  enum { before_visible, in_visible, after_visible } where;
  double compoundTimeDiff = tRange.cEnd-tRange.cStart;
  int startX, endX;
  bool partialStart;


  TimingObject::paint(); // draw the border
  TimText::paint(cCompound); // draw the text
  
  int y0 = vertPosFromState(StateVisual::Zero);
  int y1 = vertPosFromState(StateVisual::One);    
  int y0start, y0end, y1start, y1end; // variations of y0/y1 in case an event crosses start/end

  where = before_visible;
  y0end = y0;
  y1end = y1;
  double percentageNewStart;
  double percentageNewEnd; 
  
  double oldEndX = timXLeft;

  // calculate the height of the label font
  PosInt upper_left, lower_right;
  int labelheight;
  FText* label = cCompound->text();
  label->setOrigin(PosInt(0, 0));
  label->setText("0gAq");
  label->setJustification(FText::center);
  label->setSize(12);
  label->getBoundingBox(upper_left, lower_right);
  labelheight = upper_left.ypos()-lower_right.ypos();
  cCompound->remove(label);
  
  // make sure the starting points are set if the event list is empty
  if (events.size()==0) {
    if (currentVisual==StateVisual::Zero || currentVisual==StateVisual::X) {
      sigline0 = cCompound->polyline();
      sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(StateVisual::Zero)));
    } else if (currentVisual==StateVisual::Z) {
      sigline0 = cCompound->polyline();
      sigline0->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(StateVisual::Z)));
    }
    if (currentVisual==StateVisual::One || currentVisual==StateVisual::X) {
      sigline1 = cCompound->polyline();
      sigline1->addPoint(PosInt(cOrigin.xpos(), vertPosFromState(StateVisual::One)));
    }
  }
  
  for ( eventsIter = events.begin(); eventsIter != events.end(); ++eventsIter ) {

    bool swapSiglines = false;
    newStateStr = eventsIter->Object()->getNewState();
    newState = smap[newStateStr];
    newVisual = newState.visualization();
    eventStart = eventsIter->Object()->getTime(0);
    eventEnd = eventsIter->Object()->getTime(100);

    startX = timXLeft+static_cast<int>(static_cast<double>(timWidth)
                                             * (eventStart-tRange.cStart)/(compoundTimeDiff));
    endX = timXLeft+static_cast<int>(static_cast<double>(timWidth)
                                           * (eventEnd-tRange.cStart)/(compoundTimeDiff));
    
    if ((where==in_visible || (where==before_visible && eventEnd>tRange.cStart)) && eventStart<tRange.cEnd) {
      // we are in the visible area (2nd condition means we just entered)

      if (eventStart<tRange.cStart) {
        // event crosses start of visible area
        startX = timXLeft;
        percentageNewStart = (tRange.cStart-eventStart)/(eventEnd-eventStart);
        y1start = vertPosFromState(StateVisual::One, StateVisual::Zero, percentageNewStart);
        y0start = vertPosFromState(StateVisual::Zero, StateVisual::One, percentageNewStart);
        partialStart = true;
      } else {
        percentageNewStart = 0.0;
        y0start=y0;
        y1start=y1;
        partialStart = false;
      }

      if (eventEnd>tRange.cEnd) {
        // event crosses end of visible area
        endX = timXRight;
        percentageNewEnd = (tRange.cEnd-eventStart)/(eventEnd-eventStart);
        y1end = static_cast<int>(timYTop+timHeight*(1.0-percentageNewEnd));
        y0end = static_cast<int>(timYTop+timHeight*percentageNewEnd);
        where = after_visible;
      } else {
        percentageNewEnd = 1.0;
        y0end=y0;
        y1end=y1;
      }

      if ((currentVisual==StateVisual::One && newVisual==StateVisual::X) ||
          (currentVisual==StateVisual::X && newVisual==StateVisual::One)) {
        // 1->X and X->1 need a top2top line
        if (sigline1==0) {
          sigline1 = cCompound->polyline();
          if (where==before_visible) {
            sigline1->addPoint(PosInt(timXLeft, y1));
          }
        }
        sigline1->addPoint(PosInt(startX, y1));
        sigline1->addPoint(PosInt(endX, y1));
        if (newVisual==StateVisual::X) {
          // 1->X, make sure top2bottom works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
      }
      
      if ((currentVisual==StateVisual::One || currentVisual==StateVisual::X) &&
          (newVisual==StateVisual::Zero || newVisual==StateVisual::X)) {
        // 1->0, 1->X, X->X, X->0 need a top2bottom line
        if (sigline1==0) {
          sigline1 = cCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline1->addPoint(PosInt(timXLeft, y1start));
          }
        }
        sigline1->addPoint(PosInt(startX, y1start));
        sigline1->addPoint(PosInt(endX, y0end));
        swapSiglines = true;
      }
      
      if ((currentVisual==StateVisual::Zero && newVisual==StateVisual::X) || (currentVisual==StateVisual::X && newVisual==StateVisual::Zero)) {
        // 0->X and X->0 need a bottom2bottom line
        if (sigline0==0) {
          sigline0 = cCompound->polyline();
          if (where==before_visible) {
            sigline0->addPoint(PosInt(timXLeft, y0));
          }
        }
        sigline0->addPoint(PosInt(startX, y0));
        sigline0->addPoint(PosInt(endX, y0));
      }
      
      if ((currentVisual==StateVisual::Zero || currentVisual==StateVisual::X)
          && (newVisual==StateVisual::One || newVisual==StateVisual::X)) {
        // 0->1, 0->X, X->X and X->1 need a bottom2top line
        if (currentVisual==StateVisual::Zero && newVisual==StateVisual::X) {
          // Z->X, make sure bottom2top works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
        swapSiglines = true;
        if (sigline0==0) {
          sigline0 = cCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(timXLeft, y0start));
          }
        }
        sigline0->addPoint(PosInt(startX, y0start));
        sigline0->addPoint(PosInt(endX, y1end));
      }
      
      if ((currentVisual==StateVisual::Zero || currentVisual==StateVisual::X)
          && (newVisual==StateVisual::Z)) {
        // 0->Z, X->Z need a bottom2medium line
        if (sigline0==0) {
          sigline0 = cCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(timXLeft, vertPosFromState(StateVisual::Zero, StateVisual::Z, percentageNewStart)));
          }
        }
        sigline0->addPoint(PosInt(startX, vertPosFromState(StateVisual::Zero, StateVisual::Z, percentageNewStart)));
        sigline0->addPoint(PosInt(endX, vertPosFromState(StateVisual::Zero, StateVisual::Z, percentageNewEnd)));
      }

      if ((currentVisual==StateVisual::One || currentVisual==StateVisual::X)
          && (newVisual==StateVisual::Z)) {
        // 1->Z, X->Z need a top2medium line
        if (sigline1==0) {
          sigline1 = cCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline1->addPoint(PosInt(timXLeft, vertPosFromState(StateVisual::One, StateVisual::Z, percentageNewStart)));
          }
        }
        sigline1->addPoint(PosInt(startX, vertPosFromState(StateVisual::One, StateVisual::Z, percentageNewStart)));
        sigline1->addPoint(PosInt(endX, vertPosFromState(StateVisual::One, StateVisual::Z, percentageNewEnd)));
      }
      
      if ((currentVisual==StateVisual::Z) && (newVisual==StateVisual::Zero || newVisual==StateVisual::X)) {
        // Z->0, Z->X need a medium2bottom line
        if (sigline0==0) {
          sigline0 = cCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(timXLeft, vertPosFromState(StateVisual::Z, StateVisual::Zero, percentageNewStart)));
          }
        }
        sigline0->addPoint(PosInt(startX, vertPosFromState(StateVisual::Z, StateVisual::Zero, percentageNewStart)));
        sigline0->addPoint(PosInt(endX, vertPosFromState(StateVisual::Z, StateVisual::Zero, percentageNewEnd)));
        if (newVisual==StateVisual::X) {
          // Z->X, make sure bottom2top works on the right sigline
          sigline_tmp = sigline1;
          sigline1 = sigline0;
          sigline0 = sigline_tmp;
        }
      }

      if ((currentVisual==StateVisual::Z) && (newVisual==StateVisual::One || newVisual==StateVisual::X)) {
        // Z->1, Z->X need a medium2top line
        if (sigline0==0) {
          sigline0 = cCompound->polyline();
          if (where==before_visible && !partialStart) {
            sigline0->addPoint(PosInt(timXLeft, vertPosFromState(StateVisual::Z, StateVisual::One, percentageNewStart)));
          }
        }
        sigline0->addPoint(PosInt(startX, vertPosFromState(StateVisual::Z, StateVisual::One, percentageNewStart)));
        sigline0->addPoint(PosInt(endX, vertPosFromState(StateVisual::Z, StateVisual::One, percentageNewEnd)));
        swapSiglines = true;
      }

      // handle the case that an event doesn't change the state - required
      // if it's the first event in the visible area
      if (currentVisual==newVisual) {
        bool isX = (newVisual==StateVisual::X);
        if (newVisual==StateVisual::Zero || newVisual==StateVisual::Z || isX ) {
          if (sigline0==0) {
            sigline0 = cCompound->polyline();
            if (where==before_visible && !partialStart) {
              sigline0->addPoint(PosInt(timXLeft, vertPosFromState(isX? StateVisual::Zero : currentVisual, StateVisual::One, 0.0)));
            }
          }
        }
        if (newVisual==StateVisual::One || isX) {
          if (sigline1==0) {
            sigline1 = cCompound->polyline();
            if (where==before_visible && !partialStart) {
              sigline1->addPoint(PosInt(timXLeft, vertPosFromState(isX? StateVisual::One : currentVisual, StateVisual::One, 0.0)));
            }
          }
        }
      }
            
      if (swapSiglines) {
        sigline_tmp = sigline1;
        sigline1 = sigline0;
        sigline0 = sigline_tmp;
      }
      if (currentVisual==StateVisual::X && (newVisual==StateVisual::One || newVisual==StateVisual::Zero || newVisual==StateVisual::Z)) {
        if (newVisual==StateVisual::Zero || newVisual==StateVisual::Z) sigline1 = 0;
        else sigline0 = 0;
      }
      if (currentState.showLabel()) { //  && (where==in_visible || eventEnd>tRange.cEnd ???
        //        if (currentStateStrstateText!="") {
        FText* label = cCompound->text();
        label->setOrigin(PosInt(static_cast<int>((startX+oldEndX)/2), y0+(y1-y0-labelheight)/2));
        label->setText(currentStateStr);
        label->setJustification(FText::center);
        label->setSize(12);
        //        }
      }
      oldEndX = endX;
      where = in_visible;
    } else if (where == before_visible) {
      // event before compound: just get its new state (done anyway below)
    }
    currentStateStr = newStateStr;
    currentState = newState;
    currentVisual = newVisual;
  }
  
  // Add the last point of the signal
  if (sigline0!=0) {
    if (currentVisual==StateVisual::Z) {
      sigline0->addPoint(PosInt(timXRight, vertPosFromState(StateVisual::Z, StateVisual::Z, 1.0)));
    } else {
      sigline0->addPoint(PosInt(timXRight, y0end));
    }
  }
  if (sigline1!=0) {
    sigline1->addPoint(PosInt(timXRight, y1end));
  }
  if (currentState.showLabel()) {
    FText* label = cCompound->text();
    label->setOrigin(PosInt(static_cast<int>((timXRight+oldEndX)/2), y0+(y1-y0-labelheight)/2));
    label->setText(currentStateStr);
    label->setJustification(FText::center);
    label->setSize(12);
  }


}

void TimSignal::paint(void) {
  if (cCompound==0) return;
  sort(); // makes life easier... 

  Event* initState4Range = initialState.Object();
  
  for(int i = 0; i<cSchedulePtr->numVisibleTimeRanges(); i++) {

    paintRange(i, initState4Range);

  }
}
