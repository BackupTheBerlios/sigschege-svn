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


#include "TimList.h"
#include "TimeMarker.h"
#include "YaVecPolyline.h"

using namespace std;
using namespace YaVec;

TimeMarker::TimeMarker(double time, Handle<LayoutObject> mainLayoutObject,
                       LayoutObject* topLayoutObject, LayoutObject* bottomLayoutObject,
                       int topPercentage, int bottomPercentage) : LayoutObject(mainLayoutObject) {
  topReference = topLayoutObject;
  topReference->registerReferrer(this);
  bottomReference = bottomLayoutObject;
  bottomReference->registerReferrer(this);
  // origin and size of a time marker overlay are identical to the parent TimList object
  // TODO: we don't use our setSize/setOrigin functions as they should be disabled
  cOrigin = cReference->getOrigin();
  cSize = cReference->getSize();
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
  double start, end;
  int xpos, yTop, yBottom;
  TimList* parent = dynamic_cast< TimList* >(cReference.Object());
  start = parent->startTime();
  end = parent->endTime();

  // check if a compound is available
  if (getCompound()==0) return;

  // first we have to clear compound
  getCompound()->clear();

  marker = getCompound()->polyline();
  xpos = 2*cPadding+parent->getDefaultSigOffset()
    +static_cast<int>((markedTime-start)/(end-start)*(cSize.xpos()-2*cPadding-parent->getDefaultSigOffset()));
  yTop = topReference->getUpperPos();
  yBottom = bottomReference->getBottomPos();
  marker->lineStyle(YaVecLine::dashed);
  marker->penColor(cColor);

  marker->addPoint(xpos, yTop);
  marker->addPoint(xpos, yBottom);
  cout << "TIMEMARKER: line "  << xpos << ", " << yTop << "->" << yBottom << endl;
  //  * parent->cSliceWidth;

}

