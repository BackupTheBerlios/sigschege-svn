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
// $Id: TimingObject.cpp 129 2005-06-25 00:12:21Z ro_kenn $

using namespace std;
#include "TimSchedule.h"
#include <stdio.h>

TimSchedule::TimSchedule(): clean(false), cRange(0, 100) {
}

bool TimSchedule::addEllipsis(double startTime, double endTime) {
  vector< Range<double> >::iterator ellipsesIter;
  vector< Range<double> >::iterator ellipsesNextIter;

  if (startTime>endTime) return false;
  
  ellipsesIter = cEllipses.begin();

  while (ellipsesIter!=cEllipses.end() && ellipsesIter->cEnd<startTime) {
    ellipsesIter++;
  }
  // overlapping ellipses are not allowed
  if (ellipsesIter!=cEllipses.end()) {
    ellipsesNextIter = ellipsesIter;
    ellipsesNextIter++;
    if (ellipsesNextIter!=cEllipses.end() && ellipsesNextIter->cStart<startTime) return false;
  }

  if (ellipsesIter!=cEllipses.end()) {
    std::insert_iterator< std::vector< Range<double> > > insertIter(cEllipses, ellipsesIter);
    *insertIter = Range<double>(startTime, endTime);
  } else {
    cEllipses.push_back(Range<double>(startTime, endTime));
  }
  clean = false;
  return true;
}

void TimSchedule::calc() {
  if (clean) return;
  // collect all ellipsis that are completely in the visible area into cVisibleEllipses
  // all the others are not considered
  std::vector< Range<double> >::iterator rdblIter;
  cVisibleEllipses.clear();
  for (rdblIter = cEllipses.begin(); rdblIter != cEllipses.end(); ++rdblIter) {
    if (rdblIter->cStart>cRange.cStart && rdblIter->cEnd<cRange.cEnd) {
      cVisibleEllipses.push_back(*rdblIter);
    }
  }
  // calculate the visible ranges
  std::insert_iterator< std::vector< Range<double> > > insertIter(inserter(cVisibleTimeRanges, cVisibleTimeRanges.begin()));

  double startTime(cRange.cStart);
  rdblIter = cVisibleEllipses.begin();
  bool moretodo = true;
  cVisibleTime = 0.0;
  cVisibleTimeRanges.clear();
  do {
    if (rdblIter != cVisibleEllipses.end()) {
      cVisibleTimeRanges.push_back(Range<double>(startTime, rdblIter->cStart));
      cVisibleTime += rdblIter->cStart-startTime;
      startTime = rdblIter->cEnd;
      rdblIter++;
    } else {
      cVisibleTimeRanges.push_back(Range<double>(startTime, cRange.cEnd));      
      cVisibleTime += cRange.cEnd-startTime;
      moretodo = false;
    }
  } while (moretodo);

  int effectiveWidth = cXEnd-cXStart - cGap*cVisibleEllipses.size();
  double effectiveTime = 0.0;
  for (unsigned int idx=0; idx<cVisibleTimeRanges.size(); idx++) {
    effectiveTime += cVisibleTimeRanges[idx].cEnd-cVisibleTimeRanges[idx].cStart;
  }
  // calculate the geometrical positions of the visible ranges
  int xpos = 0;
  int width;
  cVisibleAreas.clear();
  for (unsigned int idx=0; idx<cVisibleTimeRanges.size(); idx++) {
    width = static_cast<int>(static_cast<double>(effectiveWidth)*
                             (cVisibleTimeRanges[idx].cEnd-cVisibleTimeRanges[idx].cStart)/effectiveTime);
    cVisibleAreas.push_back(Range<int>(xpos, xpos+width));
    xpos += width+cGap;
  }
  
  clean = true;
}

bool TimSchedule::getTimeRange(int i, double &startTime, double &endTime, double &startX, double &endX) {
  if (!clean) calc();
  if (i>=0 && i<numVisibleTimeRanges()) {
      startTime = cVisibleTimeRanges[i].cStart;
      endTime   = cVisibleTimeRanges[i].cEnd;
      startX    = cVisibleAreas[i].cStart;
      endX      = cVisibleAreas[i].cEnd;
      return true;
    }
  return false;
}

void TimSchedule::dump() {
  std::vector< Range<double> >::iterator trIter;
  calc();
  printf("TimeRange: %f:%f\n", cRange.cStart, cRange.cEnd);
  printf("GeomRange: %d:%d, Gap=%d\n", cXStart, cXEnd, cGap);
  printf("Ellipses:");
  for (trIter = cEllipses.begin(); trIter != cEllipses.end(); ++trIter) {
    printf(" %f:%f \n", trIter->cStart, trIter->cEnd);
  }
  printf("Visible Ellipses:");
  for (trIter = cVisibleEllipses.begin(); trIter != cVisibleEllipses.end(); ++trIter) {
    printf(" %f:%f \n", trIter->cStart, trIter->cEnd);
  }
  printf("Time Ranges:");
  int idx=0;
  for (trIter = cVisibleTimeRanges.begin(); trIter != cVisibleTimeRanges.end(); ++trIter) {
    printf(" %f:%f pos=%d:%d\n", trIter->cStart, trIter->cEnd, cVisibleAreas[idx].cStart, cVisibleAreas[idx].cEnd);
    idx++;
  }
}
