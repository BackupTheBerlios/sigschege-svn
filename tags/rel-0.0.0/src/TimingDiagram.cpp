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

#include "TimingDiagram.h"
#include <stdio.h>

TimingDiagram::TimingDiagram() {
}

TimingDiagram::~TimingDiagram() {
}

void TimingDiagram::paint() {
  vector< Handle<LayoutObject> >::iterator LayoutObjectIter;
  for (LayoutObjectIter = cLayoutList.begin(); LayoutObjectIter != cLayoutList.end(); LayoutObjectIter++){
    LayoutObjectIter->Object()->paint();
  }
}

/*!
 * Export the Timingdiagram to a xfig-format
 * \param file XFig File Name
 */
void TimingDiagram::exportFig(string file) {
  paint();
  cEasyVec.save(file);
}

/*!
 * Add a LayoutObject to the end of the list
 * \param newLayoutObject Handel to the Layoutobject that should be added
 */
void TimingDiagram::addLast(Handle<LayoutObject> newLayoutObject) {
  cLayoutList.push_back(newLayoutObject);
}

/*!
 * This Function will return a pointer to a Text Layout Object without a text
 */
Handle <TimLabel> TimingDiagram::createLabel() {
  Handle<TimLabel> newTimLabel = new TimLabel;
  newTimLabel->setCompound(cEasyVec.compound());
  return newTimLabel;
}


/*!
 * This Function will return a pointer to a Timing Diagram Signal Object
 */
Handle <TimSignal> TimingDiagram::createSignal() {
  Handle<TimSignal> newTimSignal = new TimSignal;
  newTimSignal->setCompound(cEasyVec.compound());
  return newTimSignal;
}