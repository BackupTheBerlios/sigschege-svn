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
  cWidth  = 0;
}

TimingDiagram::~TimingDiagram() {
}

/// Create a empyt Layout Text Object
/*!
 * This Function will return a pointer to a Text Layout Object without a text
 */
LayoutText* TimingDiagram::createLayoutText() {
  return(new LayoutText());
}

/*!
 * This Function will return a pointer to a Text Layout Object with the text newText
 */
LayoutText* TimingDiagram::createLayoutText(string newText) {
  return(new LayoutText(newText));
}


/// Set the width of the whole Timing Diagram
void TimingDiagram::setWidth(int new_width) {
  cWidth = new_width;
}


/*!
 * add the newLayout at the end of the Layout Object List
 */
void TimingDiagram::addLast(Layout *newLayout) {
  cLayoutList.createLayout(newLayout);
}

/*!
 * paint Every Layput Object in the Layout List
 */
void TimingDiagram::paint() {
  unsigned int yOffset = 0;
  unsigned int xOffset = 100;
  for(size_t walk=0;walk<cLayoutList.size();walk++){
    cLayoutList.getLayout(walk)->setBoundaryWidth(cWidth);
    yOffset += (cLayoutList.getLayout(walk)->paint(cEasyVec,xOffset, yOffset));
  }
  cEasyVec.box(EVPosInt(0,0),EVPosInt(cWidth,yOffset));
}

void TimingDiagram::save(string filename) {
  paint();
  cEasyVec.save(filename);
}
