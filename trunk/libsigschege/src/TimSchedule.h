// -*- c++ -*-
// \file 
// Copyright 2006 by Ulf Klaperski
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
// $Id: $


#ifndef _H_TIMSCHEDULE
#define _H_TIMSCHEDULE

#include <vector>
#include <stdio.h>

template <class Type> class Range {
 public:
  Range() {}
  Range(Type start, Type end) {
    cStart = start;
    cEnd = end;
  }
  Type cStart;
  Type cEnd;
};

/// This class holds the horizontal time information.
class TimSchedule {
 public:

  TimSchedule();
  
  /// The time range for all elements of this TimList.
  void setTimeRange(double startTime, double endTime);

  /// The time range for all elements of this TimList.
  bool addEllipsis(double startTime, double endTime);

  /// Return the number of ellipses.
  int numEllipses();

  /// Set the geometry (start, end and gap between visible areas).
  void setGeometry(int xStart, int xEnd, int gap);

  //! Return start time of this timing list.
  double startTime(void) { return cRange.cStart; }
  //! Return end time of this timing list.
  double endTime(void) { return cRange.cEnd; }
  
  /// Calculate the visible time ranges.
  /*!
   * calc calculates the visible time ranges. Only ellipses that are
   * located completely inside the visible area are considered.
   * This function must be called before the time ranges are queried.
   */
  void calc();
  
  void dump();

  int numVisibleTimeRanges() { calc(); return cVisibleTimeRanges.size();}

  
  bool getTimeRange(int i, double &startTime, double &endTime, double &startX, double &endX);

  Range<double> timeRangeTimes(int i) { calc(); return cVisibleTimeRanges[i]; }

  Range<int> timeRangeArea(int i) { calc(); return cVisibleAreas[i]; }

  double visibleTime() { calc(); return cVisibleTime;} 

private:

  bool clean;

  /// The main time range that is displayed.
  Range<double> cRange;
  /// All defined ellipses in the timing diagram. 
  std::vector< Range<double> > cEllipses;
  /// Horizontal start and end of the visible area.
  int cXStart, cXEnd;
  /// The gap between to time ranges.
  int cGap;

  /// The visible ellipses in the timing diagram (calculated).
  std::vector< Range<double> > cVisibleEllipses;
  
  /// The visible time ranges in the timing diagram (calculated).
  std::vector< Range<double> > cVisibleTimeRanges;

  /// The visible geometry ranges in the timing diagram (calculated). It corresponds to cVisibleTimeRanges.
  std::vector< Range<int> > cVisibleAreas;

  /// The time that is visible in the diagram - sum of all visible time ranges.
  double cVisibleTime;
};

inline   void TimSchedule::setTimeRange(double startTime, double endTime) {
  cRange = Range<double>(startTime, endTime);
  clean = false;
}


inline int TimSchedule::numEllipses() {
  return cEllipses.size();
}

inline void TimSchedule::setGeometry(int xStart, int xEnd, int gap) {
  cXStart = xStart;
  cXEnd = xEnd;
  cGap = gap;
  clean = false;
}


#endif
