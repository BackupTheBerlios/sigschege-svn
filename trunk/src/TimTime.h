// -*- c++ -*-
// \file 
// Copyright 2004 by Ulf Klaperski
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

#ifndef _H_TIMTIME
#define _H_TIMTIME

using namespace std;

#include "LayoutObject.h"
#include <string>

/// Layout Time Scale Class
/*!
 * This Time Scale Layout Class can be used once or more to show the time
 * as horizontal axis.
 */
class TimTime : public LayoutObject {
public:
  /// General constructor
  TimTime(double newStartTime, double newEndTime, bool autoCalc = true,
          double newLabelDistance = 0.0, double newFirstLabel = 0.0, double newTickDistance = 0.0);
  
  /// The standard destructor
  ~TimTime();
  
  /// Set the Font Type
  void setFontType(int new_font);

  /// Set the Font Size
  void setFontSize(int new_size);

  /// automatically calculate the position of ticks and labels
  void calcTicks(void);
  
  /// paint the layout object
  void paint(void);

  //! Set the horizontal offset for the time scale
  void setSigOffset(int sigOffset);
  
private:
  double labelDistance;
  double firstLabel;
  double tickDistance;
  double startTime, endTime;
  int cFontType;
  int cFontSize;
  int cSigOffset;
};

#endif // _H_TIMTIME
