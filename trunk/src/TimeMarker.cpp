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

void TimeMarker::setTimeLabel(bool shown) {
  showTimLabel = shown;
}

bool TimeMarker::getTimeLabel(void) {
  return showTimLabel;
}

void TimeMarker::setTextLabelFont(int size, int type) {
  cTextLabelSize = size;
  cTextLabelType = type;
}

void TimeMarker::setTimLabelFont(int size, int type) {
  cTimLabelSize = size;
  cTimLabelType = type;
}

void TimeMarker::setTimLabelPos(double pos) {
  timLabelPos = pos;
}

double TimeMarker::getTimLabelPos(void) {
  return timLabelPos;
}


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
  // set the default font properties
  setTextLabelFont();
  setTimLabelFont();
  
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
  int xpos;
  //TimList* parent = dynamic_cast< TimList* >(cReference.Object());

  yTop = topReference->getUpperPos();
  yBottom = bottomReference->getBottomPos();
  // Make sure the bottom reference is below the top reference
  if (yBottom<yTop) {
    LayoutObject* tmpLayoutObject;
    tmpLayoutObject = topReference.Object();
    topReference = bottomReference;
    bottomReference = tmpLayoutObject;
    yTop = topReference->getUpperPos();
    yBottom = bottomReference->getBottomPos();
  }

  // check if a compound is available
  if (getCompound()==0) return;
  
  // first we have to clear compound
  getCompound()->clear();

  // outside of visible area... nothing to do
  if (markedTime<cStartTime || markedTime>cEndTime) return;
  
  marker = getCompound()->polyline();
  xpos = timXLeft + 
    +static_cast<int>((markedTime-cStartTime)/(cEndTime-cStartTime)*timWidth);
  marker->lineStyle(YaVecLine::dashed);
  marker->penColor(cColor);

  marker->addPoint(xpos, yTop);
  marker->addPoint(xpos, yBottom);

  bool showText = cText.length()>0;
  
  if (showTimLabel || showText) {
    FText *timLabel;
    FText *textLabel;

    int ypos = static_cast<int>(yBottom+(yTop-yBottom)*timLabelPos);
    
    if (showText) {
      ypos = static_cast<int>(yBottom+(yTop-yBottom)*timLabelPos);
      
      textLabel = getCompound()->text();
      textLabel->setSize(cTextLabelSize);
      textLabel->setFont(cTextLabelType);
      textLabel->penColor(cColor);
      textLabel->setText(cText);
      textLabel->setJustification(timLabelLeft? 2 : 0);
      textLabel->setOrigin(PosInt(xpos+(timLabelLeft? -30 : 30), ypos-30));
    }

    if (showTimLabel) {
      std::ostringstream markedTimeStr;
      ypos = static_cast<int>(yBottom+(yTop-yBottom)*timLabelPos);

      timLabel = getCompound()->text();
      timLabel->setSize(cTimLabelSize);
      timLabel->setFont(cTimLabelType);
      timLabel->penColor(cColor);
      markedTimeStr << markedTime << endl;
      timLabel->setText(markedTimeStr.str());
      timLabel->setJustification(timLabelLeft? 2 : 0);
      ypos += timLabel->getHeight()+30;
      timLabel->setOrigin(PosInt(xpos+(timLabelLeft? -30 : 30), ypos));
    }

  }
}

