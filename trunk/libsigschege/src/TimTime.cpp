// -*- c++ -*-
// \file  
// Copyright 2004 - 2008 by Ulf Klaperski
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

#include "TimTime.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <YaVecText.h>
#include <YaVecPolyline.h>
#include <math.h>

using namespace std;
using namespace YaVec;

void TimTime::getTextGeometry(YaVec::PosInt &upperLeft, YaVec::PosInt &lowerRight) {
  upperLeft.set(labelXLeft, timYTop);
  lowerRight.set(labelXRight, timYBottom);
}


/*!
 * This constructor will create a Timing Diagram Label Object
 */
TimTime::TimTime(TimSchedule *schedulePtr, YaVec::PosInt origin, YaVec::PosInt size, int sigOffset,
                 double newLabelDistance, double newFirstLabel, double newTickDistance):
  TimingObject(),
  TimText("Time")
{
  cSchedulePtr = schedulePtr;
  setTicks(newLabelDistance, newFirstLabel, newTickDistance);
}

TimTime::~TimTime(){
}

void TimTime::calcTicks(int i) {
  double timeRange = cSchedulePtr->visibleTime();
  double normFactor = pow(10, floor(log10(timeRange)));
  double timeRangeNorm = timeRange/normFactor;
  double labelDistNorm;
  //cout << "DEBUG: starttime=" << cStartTime << "timeRangeNorm=" << timeRangeNorm << endl;
  if (timeRangeNorm>8.0) {
    labelDistNorm = 2.0;
  } else if (timeRangeNorm>5.0) {
    labelDistNorm = 1.0;
  } else if (timeRangeNorm>2.5) {
    labelDistNorm = 0.5;
  } else if (timeRangeNorm>1.0) {
    labelDistNorm = 0.2;
  } else {
    labelDistNorm = 0.1;
  }
  int labelCnt = static_cast<int>(floor(timeRangeNorm/labelDistNorm));
  //cout << "DEBUG: labelcnt=" << labelCnt << "labelDistNorm=" << labelDistNorm << endl;
  labelDistance = labelDistNorm*normFactor;
  if (labelCnt>5) {
    tickDistance = labelDistance/5.0;
  } else {
    tickDistance = labelDistance/10.0;
  }
  firstLabel.clear();
  for(int i = 0; i<cSchedulePtr->numVisibleTimeRanges(); i++) {
    firstLabel.push_back(ceil(cSchedulePtr->timeRangeTimes(i).cStart/labelDistance)*labelDistance);
  }
  //cout << "DEBUG: labelDistance=" << labelDistance << "firstLabel=" << firstLabel << endl;
  
}

void TimTime::setTicks(double newLabelDistance, double newFirstLabel, double newTickDistance) {
  if (newLabelDistance==0.0) {
    autoCalc = true;
    calcTicks(0);
  } else {
    autoCalc = false;
    labelDistance = newLabelDistance;
    firstLabel[0] = newFirstLabel; //TODO
    tickDistance = newTickDistance;
  }
}


/*!
 * Paint this time scale layout object
 */
void TimTime::paint(void) {
  FText *text;
  int xpos;
  double tickTime;
  
  // check if a compound is available
  if (getCompound()==0) return;
  
  // first we have to clear the compound
  getCompound()->clear();
  
  // and then we can draw new stuff
  // Draw the border
  LayoutObject::paint();
  TimText::paint(cCompound); // draw the text
  
  for(int i = 0; i<cSchedulePtr->numVisibleTimeRanges(); i++) {
    Range<double> timeRange = cSchedulePtr->timeRangeTimes(i);
    Range<int> timeArea = cSchedulePtr->timeRangeArea(i);
    // draw the small ticks
    tickTime = firstLabel[i]-tickDistance*floor((firstLabel[i]-timeRange.cStart)/tickDistance);
    while (tickTime<timeRange.cEnd) {
      xpos = static_cast<int>(timXLeft+tickTime/(timeRange.cEnd-timeRange.cStart)*timWidth);
      FPolyline *tick = getCompound()->polyline();
      tick->addPoint(xpos, getBottomPos()-cPadding-cSize.ypos()/50);
      tick->addPoint(xpos, getBottomPos()-cPadding-cSize.ypos()/10 );
      
      tickTime += tickDistance;
    }

    // draw the big ticks with labels
    tickTime = firstLabel[i];
    while (tickTime<timeRange.cEnd) {
      string timeStr;
      ostringstream strConv;
      xpos = static_cast<int>(timXLeft+tickTime*timWidth/timeRange.cEnd-timeRange.cStart);
      FPolyline *tick = getCompound()->polyline();
      tick->addPoint(xpos, getBottomPos()-cPadding-cSize.ypos()/50);
      tick->addPoint(xpos, getBottomPos()-cPadding-cSize.ypos()/5 );
      // current time as text
      text = getCompound()->text();
      strConv << tickTime;
      timeStr = strConv.str();
      text->setText(timeStr);
      text->setFont(cFontType);
      text->setSize(cFontSize/2);
      text->setJustification(FText::center);
      text->setOrigin(PosInt(xpos, cOrigin.ypos()+cSize.ypos()-cPadding-cSize.ypos()*32/100));
      
      tickTime += labelDistance;
    }
  } 
}

void TimTime::save(std::ofstream &ssg_file) {
  ssg_file << "<timescale>" << endl;
  TimText::save(ssg_file);
  ssg_file << "</timescale>" << endl;
}
