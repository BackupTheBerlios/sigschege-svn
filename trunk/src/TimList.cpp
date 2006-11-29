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


#include "TimList.h"

using namespace std;
using namespace YaVec;

/*!
 * Construct a Timing Diagram List
 */
TimList::TimList():LayoutObject(), cLayoutList() {
  cSliceSpace  = 0;
  setPadding(0);
  cDefaultSliceHeight = 1000;
  cDefaultPadding = 200;
  cDefaultBorder = true;
  cDefaultSigOffset = 1500;
}

TimList::~TimList() {
}

/*!
 * Paint the List
 */
void TimList::paint(void) {
  vector< Handle<TimingObject> >::iterator TimingObjectIter;
  int current_pos = cPadding;

  cSchedule.setGeometry(cDefaultSigOffset+cPadding+cOrigin.xpos(), cSize.xpos(), 10);
  
  // check if a compound is available
  if (getCompound()==0) return;

  // first we have to clear out compound
  getCompound()->clear();

  // and then we can draw out new stuff
  // Draw the border
  cSize.sety(getHeight());
  LayoutObject::paint();
  
  for (TimingObjectIter = cLayoutList.begin(); TimingObjectIter != cLayoutList.end(); TimingObjectIter++){
    TimingObjectIter->Object()->setCompound(getCompound()->compound());
    TimingObjectIter->Object()->setOrigin(cOrigin+PosInt(cPadding,current_pos));
    TimingObjectIter->Object()->setWidth(cSize.xpos()-2*cPadding);
    TimingObjectIter->Object()->paint();
    current_pos+=TimingObjectIter->Object()->getHeight()+cSliceSpace;
  }

  for (TimingObjectIter = cOverlayList.begin(); TimingObjectIter != cOverlayList.end(); TimingObjectIter++){
    TimingObjectIter->Object()->setCompound(getCompound()->compound());
    TimingObjectIter->Object()->paint();
    current_pos+=TimingObjectIter->Object()->getHeight()+cSliceSpace;
  }

}

void TimList::setTimeRange(double start, double end) {
  vector< Handle<TimingObject> >::iterator TimingObjectIter;

  cSchedule.setTimeRange(start, end);
  TimingObject *tobject;
  for (TimingObjectIter = cLayoutList.begin(); TimingObjectIter != cLayoutList.end(); TimingObjectIter++){
    tobject = TimingObjectIter->Object();
    if ( typeid(*tobject) == typeid(TimSignal) || typeid(*tobject) == typeid(TimTime)) {
      //dynamic_cast<TimingObject*>(tobject)->setTimeRange(start, end);
    }
  }
  for (TimingObjectIter = cOverlayList.begin(); TimingObjectIter != cOverlayList.end(); TimingObjectIter++){
    tobject = TimingObjectIter->Object();
    if ( typeid(*tobject) == typeid(TimeMarker)) {
      //dynamic_cast<TimingObject*>(tobject)->setTimeRange(start, end);
    }
  }  
}

/*!
 * Add a TimingObject to the end of the list
 * \param newTimingObject Handle to the Layoutobject that should be added
 */
void TimList::addLast(Handle<TimingObject> newTimingObject) {
  cLayoutList.push_back(newTimingObject);
}

void TimList::addBefore(Handle<TimingObject> newTimingObject, Handle<TimingObject> timObject) {
  vector< Handle<TimingObject> >::iterator TimingObjectIter;
  TimingObjectIter = cLayoutList.begin();
  while (TimingObjectIter!=cLayoutList.end() && TimingObjectIter->Object()!=timObject.Object()) {
    TimingObjectIter++;
  }
  cLayoutList.insert(TimingObjectIter, newTimingObject);
}

void TimList::deleteObject(Handle<TimingObject> timObject) {
  vector< Handle<TimingObject> >::iterator timingObjectIter;
  timingObjectIter = cLayoutList.begin();
  while (timingObjectIter!=cLayoutList.end() && timingObjectIter->Object()!=timObject.Object()) {
    timingObjectIter++;
  }
  cLayoutList.erase(timingObjectIter);  
}


void TimList::moveBefore(Handle<TimingObject> newTimingObject, TimingObject *timObject) {
  deleteObject(newTimingObject);
  addBefore(newTimingObject, timObject);
}


/*!
 * Add a TimingObject to the end of the overlay list
 * \param newTimingObject Handel to the Layoutobject that should be added
 */
void TimList::addOverlay(Handle<TimingObject> newTimingObject) {
  cOverlayList.push_back(newTimingObject);
}

/*!
 * This Function will return a Handle to a Text Layout Object without a text
 */
Handle <TimLabel> TimList::createLabel() {
  Handle<TimLabel> newTimLabel = new TimLabel;
  newTimLabel->setCompound(getCompound()->compound());
  newTimLabel->setHeight(cDefaultSliceHeight);
  newTimLabel->enableBorder(cDefaultBorder);
  return newTimLabel;
}

/*!
 * This Function will return a Handle to a Timing Diagram Signal Object
 */
Handle <TimSignal> TimList::createSignal(string label, bool isBool, double defaultSlope) {
  Handle<TimSignal> newTimSignal = new TimSignal(label, &cSchedule, cOrigin, PosInt(cSize.xpos()-2*cPadding, cDefaultSliceHeight),
                                                 isBool, cDefaultSigOffset, defaultSlope);
  newTimSignal->setCompound(getCompound()->compound());
  newTimSignal->setHeight(cDefaultSliceHeight);
  newTimSignal->enableBorder(cDefaultBorder);
  newTimSignal->setPadding(cDefaultPadding);
  return newTimSignal;
}

/*!
 * This Function will return a Handle to a time scale object
 */
Handle<TimTime> TimList::createTime(double newLabelDistance, double newFirstLabel, double newTickDistance) {
  Handle<TimTime> newTimTime = new TimTime(&cSchedule, cOrigin, PosInt(cSize.xpos()-2*cPadding, cDefaultSliceHeight),
                                           cDefaultSigOffset, newLabelDistance, newFirstLabel, newTickDistance);
  newTimTime->setCompound(getCompound()->compound());
  newTimTime->setHeight(cDefaultSliceHeight);
  newTimTime->enableBorder(cDefaultBorder);
  newTimTime->setPadding(cDefaultPadding);
  newTimTime->setSigOffset(cDefaultSigOffset); 
  return newTimTime;  
}


Handle<TimeMarker> TimList::createTimeMarker(double time, TimingObject* topTimingObject,
                                             TimingObject* bottomTimingObject) {
  Handle<TimeMarker> newTimeMarker = new TimeMarker(time, &cSchedule, cOrigin, PosInt(cSize.xpos()-2*cPadding, cDefaultSliceHeight),
                                                    cDefaultSigOffset, this, topTimingObject, bottomTimingObject);
  newTimeMarker->setPadding(cDefaultPadding);
  return newTimeMarker;
}


/*!
 * This Function will return a Handle a Timing Diagram Signal Object
 */
Handle <TimList> TimList::createList() {
  Handle<TimList> newTimList = new TimList;
  newTimList->setCompound(getCompound()->compound());
  newTimList->enableBorder(cDefaultBorder);
  newTimList->setPadding(cDefaultPadding);
  return newTimList;
}

/*!
 * Set the default height for each slice.
 * \param nHeight slice height
 */
void TimList::setDefaultSliceHeight(int nHeight) {
  cDefaultSliceHeight = nHeight;
}


/*!
 * Set the space between two splices
 * \param space Space between the slices
 */
void TimList::setSliceSpace(int space) {
  cSliceSpace = space;
}

/*! 
 * Get the Height of the whole List
 * \return The height of the whole list
 */
int TimList::getHeight() {
  vector< Handle<TimingObject> >::iterator TimingObjectIter;
  int current_pos = 2*cPadding;
  for (TimingObjectIter = cLayoutList.begin(); TimingObjectIter != cLayoutList.end(); TimingObjectIter++){
    current_pos+=TimingObjectIter->Object()->getHeight()+cSliceSpace;
  }
  return(current_pos);
}


