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


#ifndef _H_TIMLIST
#define _H_TIMLIST

using namespace std;

#include "LayoutObject.h"
#include "TimLabel.h"
#include "TimTime.h"
#include "TimSignal.h"
#include "Handle.t"

class TimList : public LayoutObject {
public:
  //! The standard constructor
  TimList();
  
  //! The standard destructor
  ~TimList();

  //! Paint the List
  void paint(void);

  //! Add a LayoutObject to the Objectlist
  void addLast(Handle<LayoutObject> newLayoutObject);

  //! Get the height of the whole list.
  int getHeight();

  //! The time range for all elements of this TimList.
  void setTimeRange(double startTime, double endTime);
  
  
  //! Create an empty Timing Diagram Label Object
  Handle<TimLabel> createLabel();

  //! Create an empty Timing Diagram Signal Object
  Handle<TimSignal> createSignal(string label, double defaultSlope=0.0);

  //! Create a time scale
  Handle<TimTime> createTime(bool autoCalc, double newLabelDistance, double newFirstLabel, double newTickDistance);
  
  //! Create an empty Timing Diagram List Object.
  Handle<TimList> createList();

  //! Set the height for each slice
  void setSliceHeight(int nHeight);

  //! Set the Slice Space
  void setSliceSpace(int space);

protected:
  vector< Handle<LayoutObject> > cLayoutList;
  int cSliceHeight;
  int cSliceWidth;
  int cSliceSpace;
  double cStartTime, cEndTime;
  // defaults for signals/labels/time scale
  int  cDefaultHeight;
  int  cDefaultPadding;
  bool cDefaultBorder;
  int  cDefaultSigOffset;
};

#endif
