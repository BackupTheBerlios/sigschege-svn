// -*- c++ -*-
// \file  
// Copyright 2004 by Ulf Klaperski
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

#include "TimTime.h"
#include <iostream>
#include <sstream>
#include <EasyVecText.h>
#include <EasyVecPolyline.h>



/*!
 * This constructor will create an Timing Diagram Label Object
 */
TimTime::TimTime(double newStartTime, double newEndTime, bool autoCalc,
                 double newLabelDistance, double newFirstLabel, double newTickDistance) : LayoutObject() {
  cFontType = 14;
  cFontSize = 20;
  startTime = newStartTime;
  endTime = newEndTime;
  if (autoCalc) calcTicks();
  else {
    labelDistance = newLabelDistance;
    firstLabel = newFirstLabel;
    tickDistance = newTickDistance;
  }
}


TimTime::~TimTime(){
}

void TimTime::calcTicks(void) {
  // TODO
}


/*!
 * Paint this text layout object
 */
void TimTime::paint(void) {
  EasyVecText *text;
  int height, width, scaleWidth, xpos;
  double tickTime;

  // check if a compound is available
  if (getCompound()==0) return;

  // first we have to clear out compound
  getCompound()->clear();

  height = (getBottomPos()-getUpperPos())-2*cPadding;
  width  = (getRightPos()-getLeftPos())-2*cPadding;
  scaleWidth = width-cSigOffset;;

  // and then we can draw out new stuff
  // Draw the border
  LayoutObject::paint();

  // Draw the Text
  text = getCompound()->text();
  text->setText("Time");
  text->setFont(cFontType);
  text->setSize(cFontSize);
  text->setOrigin(EVPosInt(getLeftPos()+cPadding,getBottomPos()-cPadding-((height-text->getHeight())/2)));

  // draw the small ticks
  tickTime = firstLabel-tickDistance*floor((firstLabel-startTime)/tickDistance);
  while (tickTime<endTime) {
    xpos = static_cast<int>(getLeftPos()+cSigOffset+cPadding+tickTime/(endTime-startTime)*scaleWidth);
    EasyVecPolyline *tick = getCompound()->polyline();
    tick->add_point(xpos, getBottomPos()-cPadding-height/50);
    tick->add_point(xpos, getBottomPos()-cPadding-height/10 );
    
    tickTime += tickDistance;
  }

  // draw the big ticks with labels
  tickTime = firstLabel;
  while (tickTime<endTime) {
    string timeStr;
    ostringstream strConv;
    xpos = static_cast<int>(getLeftPos()+cSigOffset+cPadding+tickTime*scaleWidth/endTime-startTime);
    EasyVecPolyline *tick = getCompound()->polyline();
    tick->add_point(xpos, getBottomPos()-cPadding-height/50);
    tick->add_point(xpos, getBottomPos()-cPadding-height/5 );
    // current time as text
    text = getCompound()->text();
    strConv << tickTime;
    timeStr = strConv.str();
    text->setText(timeStr);
    text->setFont(cFontType);
    text->setSize(cFontSize/2);
    text->setJustification(EasyVecText::center);
    text->setOrigin(EVPosInt(xpos, getBottomPos()-cPadding-height*32/100));
    
    tickTime += labelDistance;
  }
  
  
}

/// Set the Font Type
void TimTime::setFontType(int new_font) {
  cFontType = new_font;
}

/// Set the Font Size
void TimTime::setFontSize(int new_size) {
  cFontSize = new_size;
}

void TimTime::setSigOffset(int sigOffset) {
  cSigOffset = sigOffset;
}
