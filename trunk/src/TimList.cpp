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

#include "TimList.h"

/*!
 * Construct a Timing Diagram List
 */
TimList::TimList():LayoutObject(), cLayoutList() {
  cSliceHeight = 500;
  cSliceWidth  = 500;
  cSliceSpace  = 0;
}

TimList::~TimList() {

}

/*!
 * Paint the List
 */
void TimList::paint(void) {
  vector< Handle<LayoutObject> >::iterator LayoutObjectIter;
  int current_pos = cPadding;

  // check if a compound is available
  if(getCompound()==0) return;

  // first we have to clear out compound
  getCompound()->clear();

  // and then we can draw out new stuff
  // Draw the border
  cSize.sety(getHeight());
  LayoutObject::paint();
  
  for (LayoutObjectIter = cLayoutList.begin(); LayoutObjectIter != cLayoutList.end(); LayoutObjectIter++){
    LayoutObjectIter->Object()->setCompound(getCompound()->compound());
    LayoutObjectIter->Object()->setOrigin(cOrigin+EVPosInt(cPadding,current_pos));
    LayoutObjectIter->Object()->setWidth(cSize.xpos()-2*cPadding);
    LayoutObjectIter->Object()->paint();
    current_pos+=LayoutObjectIter->Object()->getHeight()+cSliceSpace;
  }


}

/*!
 * Add a LayoutObject to the end of the list
 * \param newLayoutObject Handel to the Layoutobject that should be added
 */
void TimList::addLast(Handle<LayoutObject> newLayoutObject) {
  cLayoutList.push_back(newLayoutObject);
}

/*!
 * This Function will return a Handle to a Text Layout Object without a text
 */
Handle <TimLabel> TimList::createLabel() {
  Handle<TimLabel> newTimLabel = new TimLabel;
  newTimLabel->setCompound(getCompound()->compound());
  return newTimLabel;
}

/*!
 * This Function will return a Handle to a Timing Diagram Signal Object
 */
Handle <TimSignal> TimList::createSignal(string label, double newStartTime, double newEndTime, double defaultSlope) {
  Handle<TimSignal> newTimSignal = new TimSignal(label, newStartTime, newEndTime, defaultSlope);
  newTimSignal->setCompound(getCompound()->compound());
  return newTimSignal;
}

/*!
 * This Function will return a Handle to a time scale object
 */
Handle<TimTime> TimList::createTime(double newStartTime, double newEndTime, bool autoCalc,
                                    double newLabelDistance, double newFirstLabel, double newTickDistance) {
  Handle<TimTime> newTimTime = new TimTime(newStartTime, newEndTime, autoCalc, newLabelDistance,
                                           newFirstLabel, newTickDistance);
  newTimTime->setCompound(getCompound()->compound());
  return newTimTime;  
}

/*!
 * This Function will return a Handle a Timing Diagram Signal Object
 */
Handle <TimList> TimList::createList() {
  Handle<TimList> newTimList = new TimList;
  newTimList->setCompound(getCompound()->compound());
  return newTimList;
}

/*!
 * Set the height for each slice
 * \param nHeight slice height
 */
void TimList::setSliceHeight(int nHeight) {
  cSliceHeight = nHeight;
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
  vector< Handle<LayoutObject> >::iterator LayoutObjectIter;
  int current_pos = 2*cPadding;
  for (LayoutObjectIter = cLayoutList.begin(); LayoutObjectIter != cLayoutList.end(); LayoutObjectIter++){
    current_pos+=LayoutObjectIter->Object()->getHeight()+cSliceSpace;
  }
  return(current_pos);
}
