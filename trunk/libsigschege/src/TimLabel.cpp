// -*- c++ -*-
// \file  
// Copyright 2004 - 2008 by Ingo Hinrichs, Ulf Klaperski
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


#include "TimLabel.h"
#include <iostream>
#include <YaVecText.h>
#include <YVPosInt.h>

using namespace std;
using namespace YaVec;

/*!
 * This constructor will create a Timing Diagram Label Object
 */
TimLabel::TimLabel(): TimingObject(), TimText() {
  cSigOffset = 0;
  cHAlign1 = hcenter;
}

/*!
 * This constructor will create a Timing Diagram Label Object.
 * newText will be set as Text.
 */
TimLabel::TimLabel(std::string newText): TimingObject(), TimText(newText) {
  cSigOffset = 0;
  cHAlign1 = hcenter;
}


TimLabel::~TimLabel() {
}

void TimLabel::getTextGeometry(YaVec::PosInt &upperLeft, YaVec::PosInt &lowerRight) {
  upperLeft.set(timXLeft, timYTop);
  lowerRight.set(timXRight, timYBottom);
}

/*!
 * Paint this text layout object
 */
void TimLabel::paint(void) {

  // check if a compound is available
  if(getCompound()==0) return;

  // first we have to clear out compound
  getCompound()->clear();

  // and then we can draw new stuff
  // Draw the border
  LayoutObject::paint();

  // Draw the Text
  TimText::paint(getCompound()); // draw the text
}

void TimLabel::save(std::ofstream &ssg_file) {
  ssg_file << "<label>" << endl;
  TimText::save(ssg_file);
  ssg_file << "</label>" << endl;
}
