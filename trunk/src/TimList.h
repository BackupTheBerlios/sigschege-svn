// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ingo Hinrichs, Ulf Klaperski
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

#include "TimingObject.h"
#include "TimLabel.h"
#include "TimTime.h"
#include "TimSignal.h"
#include "TimeMarker.h"
#include "Handle.t"

class TimList : public LayoutObject {
public:
  //! The standard constructor
  TimList();
  
  //! The standard destructor
  ~TimList();

  //! Paint the List.
  void paint(void);

  //! Add a TimingObject to the Objectlist.
  void addLast(Handle<TimingObject> newTimingObject);

  //! Add a TimingObject to the Overlay list.
  void addOverlay(Handle<TimingObject> newTimingObject);

  //! Get the height of the whole list.
  int getHeight();

  //! The time range for all elements of this TimList.
  void setTimeRange(double startTime, double endTime);
  
  //! Create an empty Timing Diagram Label Object.
  Handle<TimLabel> createLabel();

  //! Create an empty Timing Diagram Signal Object.
  Handle<TimSignal> createSignal(string label, double defaultSlope=0.0);

  //! Create a time scale.
  Handle<TimTime> createTime(double newLabelDistance, double newFirstLabel, double newTickDistance);

  //! Create a time marker.
  Handle<TimeMarker> createTimeMarker(double time, TimingObject* topTimingObject, TimingObject* bottomTimingObject);

  //! Create an empty Timing Diagram List Object.
  Handle<TimList> createList();

  //! Return start time of this timing list.
  double startTime(void) { return cStartTime; }
  //! Return end time of this timing list.
  double endTime(void) { return cEndTime; }
  
  //! Set the height for each slice
  void setSliceHeight(int nHeight);

  //! Set the Slice Space
  void setSliceSpace(int space);

  //! Set the default height of the timing diagram elements.
  void setDefaultHeight(int defaultHeight) { cDefaultHeight = defaultHeight; }
  //! Set the default padding of the timing diagram elements.
  void setDefaultPadding(int defaultPadding) { cDefaultPadding = defaultPadding; }
  //! Set the default default border of the timing diagram elements.
  void setDefaultBorder(bool defaultBorder) { cDefaultBorder = defaultBorder; }
  //! Set the default offset of signals
  void setDefaultSigOffset(int defaultSigOffset) { cDefaultSigOffset = defaultSigOffset; }
  //! Get the default offset of signals
  int getDefaultSigOffset(void) { return cDefaultSigOffset; }
  

protected:
  vector< Handle<TimingObject> > cLayoutList;
  vector< Handle<TimingObject> > cOverlayList;
  int cSliceHeight;
  int cSliceWidth;
  // the vertical space between two slices
  int cSliceSpace;
  double cStartTime, cEndTime;
  // defaults for signals/labels/time scale
  int  cDefaultHeight;
  int  cDefaultPadding;
  bool cDefaultBorder;
  // NOTE: all "time aware" children (signal, time scale, time marker) must
  // have their sigOffset consistent with the default
  int  cDefaultSigOffset;

private:
    //! Disable setting the height - it is calculated by the height of the elements.
  virtual void setHeight(int height) {};



};

#endif
