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

#include "TimSignal.h"
#include <EasyVecText.h>
#include <iostream>

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
TimSignal::TimSignal(string signalLabel, double defaultSlope):LayoutObject(), EventList(defaultSlope) {
  cText      = signalLabel;
  cFontType  = 14;
  cFontSize  = 20;
  cSigOffset = 0;
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

/*!
 * Paint this Signal object
 */
void TimSignal::paint(void) {
  EasyVecText *text;

  // check if a compound is available
  if (getCompound()==0) return;

  // first we have to clear out compound
  getCompound()->clear();

  // Draw the border
  LayoutObject::paint();

  // Draw the Text
  text = getCompound()->text();
  text->setText(cText);
  text->setFont(cFontType);
  text->setSize(cFontSize);
  text->setOrigin(LayoutObject::cOrigin+EVPosInt(cPadding,(LayoutObject::cSize.ypos()+text->getHeight())/2));
  
  EventList::setCompound(getCompound()->compound(),LayoutObject::cOrigin+EVPosInt(cPadding+cSigOffset,cPadding),LayoutObject::cSize-EVPosInt(cSigOffset+2*cPadding,2*cPadding), 0, 222.0);
  EventList::paint();

}

