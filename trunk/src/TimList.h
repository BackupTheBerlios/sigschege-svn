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

  //! Get the Height of the whole List
  int getHeight();

  //! Create a empty Timing Diagram Label Object
  Handle<TimLabel> createLabel();

  //! Create a empty Timing Diagram Signal Object
  Handle<TimSignal> createSignal(string label, double newStartTime, double newEndTime, double defaultSlope=0.0);

  //! Create a time scale
  Handle<TimTime> createTime(double newStartTime, double newEndTime, bool autoCalc,
                             double newLabelDistance, double newFirstLabel, double newTickDistance);
  
  //! Create a empty Timing Diagram Signal Object
  Handle<TimList> createList();

  //! Set the height for each slice
  void setSliceHeight(int nHeight);

  //! Set the Slice Space
  void setSliceSpace(int space);

private:
  vector< Handle<LayoutObject> > cLayoutList;
  int cSliceHeight;
  int cSliceWidth;
  int cSliceSpace;
};

#endif
