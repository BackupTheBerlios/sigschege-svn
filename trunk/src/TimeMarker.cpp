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


#include "TimeMarker.h"
using namespace std;

TimeMarker::TimeMarker(double time, Handle<LayoutObject> mainLayoutObject,
                       Handle<LayoutObject> topLayoutObject, Handle<LayoutObject> bottomLayoutObject,
                       int topPercentage, int bottomPercentage) : LayoutObject(mainLayoutObject) {
  topReference = topLayoutObject;
  topReference->registerReferrer(this);
  bottomReference = bottomLayoutObject;
  bottomReference->registerReferrer(this);
  setOrigin(reference->getOrigin());
  if (topReference.Object()!=0) {
    yTop = topReference->getUpperPos();
  } else {
    yTop = reference->getUpperPos();    
  }
  if (bottomReference.Object()!=0) {
    yBottom = bottomReference->getBottomPos();
  } else {
    yBottom = reference->getBottomPos();
  }
  markedTime = time;
}
  
TimeMarker::~TimeMarker() {
  if (topReference.Object()!=0) {
    topReference->unregisterReferrer(this);
  }
  if (bottomReference.Object()!=0) {
    bottomReference->unregisterReferrer(this);
  }
  reference->unregisterReferrer(this);
}

/*!
 * Paint this Signal object
 */
void TimeMarker::paint(void) {
  YaVecPolyline *marker;

  // check if a compound is available
  if (getCompound()==0) return;

  // first we have to clear compound
  getCompound()->clear();

  marker = getCompound()->polyline();
  

}

