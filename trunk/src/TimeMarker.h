// -*- c++ -*-
// \file 
// Copyright 2005 by Ulf Klaperski
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

#ifndef _H_TIMMARKER
#define _H_TIMMARKER

#include "TimingObject.h"
#include "Handle.t"
#include <iostream>

/// Layout Time Marker Class
/*!
 * This Time Scale Layout Class can be used once or more to show the time
 * as horizontal axis.
 */
class TimeMarker : public TimingObject {
public:
  //! General constructor
  TimeMarker(double time, double startTime, double endTime, YaVec::PosInt origin, YaVec::PosInt size, int sigOffset,
             Handle<LayoutObject> mainLayoutObject,
             LayoutObject* topLayoutObject = 0,
             LayoutObject* bottomLayoutObject = 0,
             int topPercentage=100, int bottomPercentage=100);
  
  //! The standard destructor
  ~TimeMarker();

  //! Set the color for this time marker.
  void setColor(int color) { cColor = color; };

  //! Set the optional text string. It will be shown unless it is an empty string.
  void setText(const std::string &text) { cText = text; }
  
  //! Return the optional text string. 
  std::string getText(void) { return cText; }

  //! Set if the time label is shown.
  void setTimeLabel(bool shown);

  //! Set the font size and type for the time label.
  void setTimLabelFont(int size = 12, int type = 2);
  
  //! Set the font size and type for the text label.
  void setTextLabelFont(int size = 12, int type = 2);
  
  //! Return if the time label is shown.
  bool getTimeLabel(void);

  //! Set the time at which to paint the time marker.
  void setTime(double time) { markedTime = time; };

  //! Return the time at which to paint the time marker.
  double getTime(void) { return markedTime; };
  
  //! Paint the Signal.
  void paint(void);

private:
  // instead of mainReference we just reuse reference from LayoutObject
  Handle<LayoutObject> topReference;
  Handle<LayoutObject> bottomReference;
  int yTop, yBottom;
  int cColor;
  double markedTime;

  bool showTimLabel;
  double timLabelPos;
  bool timLabelLeft;
  Handle<LayoutObject> timLabelPlace;

  std::string cText;

  int cTextLabelSize;
  int cTextLabelType;
  int cTimLabelSize;
  int cTimLabelType;
  
};

#endif
