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
  cTimList.setCompound(cEasyVec.compound());
  cTimList.setPadding(0);
  cDefaultHeight = 1000;
  cDefaultPadding = 200;
  cDefaultBorder = true;
  cDefaultSigOffset = 1500;
}

TimingDiagram::~TimingDiagram() {
}

void TimingDiagram::paint() {
  cTimList.paint();
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
 * Export the Timingdiagram to an encapsulated postscript
 * \param file EPS File Name
 */
void TimingDiagram::exportEPS(string file) {
  paint();
  cEasyVec.export_fig2dev("eps", file);
}

/*!
 * Add a LayoutObject to the end of the list
 * \param newLayoutObject Handel to the Layoutobject that should be added
 */
void TimingDiagram::addLast(Handle<LayoutObject> newLayoutObject) {
  cTimList.addLast(newLayoutObject);
}

/*!
 * This Function will return a Handle to a Text Layout Object without a text
 */
Handle <TimLabel> TimingDiagram::createLabel() {
  Handle <TimLabel> newLabel = cTimList.createLabel();
  newLabel->setHeight(cDefaultHeight);
  newLabel->enableBorder(cDefaultBorder);
  return newLabel;
}


/*!
 * This Function will return a Handle to a Timing Diagram Signal Object
 */
Handle <TimSignal> TimingDiagram::createSignal(double defaultSlope) {
  Handle <TimSignal> newSignal = cTimList.createSignal(defaultSlope);
  newSignal->setHeight(cDefaultHeight);
  newSignal->enableBorder(cDefaultBorder);
  newSignal->setPadding(cDefaultPadding);
  newSignal->setSigOffset(cDefaultSigOffset);
  return newSignal;
}

/*!
 * This Function will return a Handle a Timing Diagram Signal Object
 */
Handle <TimList> TimingDiagram::createList() {
  Handle <TimList> newList = cTimList.createList();
  newList->enableBorder(cDefaultBorder);
  newList->setPadding(cDefaultPadding);
  return newList;
}

/*!
 * This Function will return a Handle to a time scale object
 */
Handle<TimTime> TimingDiagram::createTime(double newStartTime, double newEndTime, bool autoCalc,
                                    double newLabelDistance, double newFirstLabel, double newTickDistance) {
  Handle<TimTime> newTimTime = new TimTime(newStartTime, newEndTime, autoCalc, newLabelDistance,
                                           newFirstLabel, newTickDistance);
  newTimTime->setCompound(cEasyVec.compound());
  newTimTime->setHeight(cDefaultHeight);
  newTimTime->enableBorder(cDefaultBorder);
  newTimTime->setPadding(cDefaultPadding);
  newTimTime->setSigOffset(cDefaultSigOffset); 
  return newTimTime;  
}

void TimingDiagram::setWidth(int width) {
  cTimList.setWidth(width);
}

void TimingDiagram::setSliceSpace(int space) {
  cTimList.setSliceSpace(space);
}
