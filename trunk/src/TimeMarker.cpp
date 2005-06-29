// -*- c++ -*-
// \file  
// Copyright 2005 by Ulf Klaperski, Ingo Hinrichs
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

#include "sstream"
#include "TimList.h"
#include "TimeMarker.h"
#include "YaVecPolyline.h"
#include "YaVecText.h"

using namespace std;
using namespace YaVec;

TimeMarker::TimeMarker(double time, double startTime, double endTime, YaVec::PosInt origin, YaVec::PosInt size, int sigOffset,
                       Handle<LayoutObject> mainLayoutObject, LayoutObject* topLayoutObject,
                       LayoutObject* bottomLayoutObject, int topPercentage, int bottomPercentage):
  TimingObject(mainLayoutObject.Object(), origin, size, sigOffset) {
  setTimeRange(startTime, endTime);
  topReference = topLayoutObject;
  topReference->registerReferrer(this);
  bottomReference = bottomLayoutObject;
  bottomReference->registerReferrer(this);
  // origin and size of a time marker overlay are identical to the parent TimList object
  // TODO: we don't use our setSize/setOrigin functions as they should be disabled
  if (topReference.Object()!=0) {
    yTop = topReference->getUpperPos();
  } else {
    yTop = cReference->getUpperPos();    
  }
  if (bottomReference.Object()!=0) {
    yBottom = bottomReference->getBottomPos();
  } else {
    yBottom = cReference->getBottomPos();
  }
  markedTime = time;
  cColor = 0;
  timLabelPlace = bottomReference;
  showTimLabel = true;
  timLabelLeft = false;
  timLabelPos = 0.3;
}

TimeMarker::~TimeMarker() {
  if (topReference.Object()!=0) {
    topReference->unregisterReferrer(this);
  }
  if (bottomReference.Object()!=0) {
    bottomReference->unregisterReferrer(this);
  }
  cReference->unregisterReferrer(this);
}

/*!
 * Paint this time marker
 */
void TimeMarker::paint(void) {
  FPolyline *marker;
  int xpos, yTop, yBottom;
  TimList* parent = dynamic_cast< TimList* >(cReference.Object());

  // check if a compound is available
  if (getCompound()==0) return;
  
  // first we have to clear compound
  getCompound()->clear();

  // outside of visible area... nothing to do
  if (markedTime<cStartTime || markedTime>cEndTime) return;
  
  marker = getCompound()->polyline();
  xpos = timXLeft + 
    +static_cast<int>((markedTime-cStartTime)/(cEndTime-cStartTime)*timWidth);
  yTop = topReference->getUpperPos();
  yBottom = bottomReference->getBottomPos();
  marker->lineStyle(YaVecLine::dashed);
  marker->penColor(cColor);

  marker->addPoint(xpos, yTop);
  marker->addPoint(xpos, yBottom);
//   cout << "TMDEBUG: sigoffset= "  << parent->getDefaultSigOffset() << ", cSize.xpos()=" << cSize.xpos() <<
//     ", timpercent=" << (markedTime-cStartTime)/(cEndTime-cStartTime) << cEndTimel;
//   cout << "TIMEMARKER: line "  << xpos << ", " << yTop << "->" << yBottom << endl;
  //  * parent->cSliceWidth;

  if (showTimLabel) {
    FText *timLabel;
    std::ostringstream markedTimeStr;
    
    timLabel = getCompound()->text();
    timLabel->setOrigin(PosInt(xpos+(timLabelLeft? -30 : 30), static_cast<int>(yBottom+(yTop-yBottom)*timLabelPos)));
    timLabel->setSize(10);
    timLabel->setFont(3);
    timLabel->penColor(cColor);
    markedTimeStr << markedTime << endl;
    timLabel->setText(markedTimeStr.str());
    timLabel->setJustification(timLabelLeft? 2 : 0);
  }
  
}

