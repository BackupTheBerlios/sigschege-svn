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
// $Id: TimLabel.cpp 59 2004-11-14 21:32:23Z suupkopp $

using namespace std;

#include "TimList.h"

/*!
 * Construct a Timing Diagram List
 */
TimList::TimList():LayoutObject() {

}

TimList::~TimList() {

}

/*!
 * Paint the List
 */
void TimList::paint(void) {
  vector< Handle<LayoutObject> >::iterator LayoutObjectIter;
  for (LayoutObjectIter = cLayoutList.begin(); LayoutObjectIter != cLayoutList.end(); LayoutObjectIter++){
    LayoutObjectIter->Object()->paint();
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
Handle <TimSignal> TimList::createSignal() {
  Handle<TimSignal> newTimSignal = new TimSignal;
  newTimSignal->setCompound(getCompound()->compound());
  return newTimSignal;
}

/*!
 * This Function will return a Handle a Timing Diagram Signal Object
 */
Handle <TimList> TimList::createList() {
  Handle<TimList> newTimList = new TimList;
  newTimList->setCompound(getCompound()->compound());
  return newTimList;
}
