// -*- c++ -*-
// \file  
// Copyright 2004, 2005 by Ulf Klaperski
//
// This file is part of YaVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// YaVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// YaVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the YaVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#include "YaVecPolyline.h"
#include "YaVecFigure.h"
#include <fstream>
#include <iostream>

using namespace std;

YaVecPolyline::YaVecPolyline(YaVecCompound* parent_compound, YaVecFigure* figure_compound)
  : YaVecElm(parent_compound, figure_compound), YaVecLine(), YaVecArrow() {
};



void YaVecPolyline::getBoundingBox(YVPosInt &upper_left, YVPosInt &lower_right) {
  vector<YVPosInt>::iterator points_iter = points.begin();
  if (points_iter==points.end()) {
    upper_left = YVPosInt(0,0); // no points! how should we behave???
    lower_right = YVPosInt(0,0);
  } else {
    lower_right = upper_left = *points_iter;
    while (++points_iter!=points.end()) {
      upper_left.minValues(*points_iter);
      lower_right.maxValues(*points_iter);
    }
  }
}

void YaVecPolyline::addPoint(YVPosInt new_point) {
  points.push_back(new_point);
//  cout << "Adding point " << new_point.xpos() << ":" << new_point.ypos() << endl;
  parent->handleChange(this);
}

void YaVecPolyline::addPoints(vector<YVPosInt> new_points) {
  vector<YVPosInt>::iterator npoints_iter;
  for ( npoints_iter = new_points.begin(); npoints_iter != new_points.end(); ++npoints_iter ) {
    points.push_back(*npoints_iter);
  }
}

void YaVecPolyline::addAngleBox(YVPosInt corner1, YVPosInt corner3, double angle, bool clear) {
  double angleRad = angle*M_PI/180;
  
  //TODO
}

void YaVecPolyline::draw(YaVecView* view) {
  double styleLength = elmStyleValue*15;
  vector<YVPosInt>::iterator points_iter1, points_iter2;
  YVPosInt oldPoint;
  points_iter1 = points.begin();
  if (points_iter1==points.end()) return;
  points_iter2 = points_iter1;
  points_iter2++;
  if (backwardArrow() && points_iter2 != points.end()) 
    view->drawArrow((*points_iter1), (*points_iter2), elmPenColor, elmArrows[1]);
  while (points_iter2 != points.end()) {
    view->drawLine((*points_iter1), (*points_iter2), elmThickness, elmPenColor, elmLineStyle, styleLength);
    oldPoint = *points_iter1;
    points_iter1 = points_iter2;
    ++points_iter2;
  }
  if (forwardArrow() && points.size()>1) 
    view->drawArrow((*points_iter1), oldPoint, elmPenColor, elmArrows[0]);
}


void YaVecPolyline::saveElm(ofstream &fig_file) {
  vector<YVPosInt>::iterator points_iter;

  if (points.size()==0) return; // polyline without points not allowed
  
  fig_file << "2 1 " << elmLineStyle << " " << elmThickness << " " << elmPenColor << " " << elmFillColor << " " << elmDepth
           << " 0 " << elmAreaFill << " " << elmStyleValue << " 0 0 0 " << (forwardArrow()? 1 : 0) << " "
           << (backwardArrow()? 1 : 0) << " " << points.size() << endl;
  if (forwardArrow()) {
    fig_file << forwardArrowString() << endl;
  }
  if (backwardArrow()) {
    fig_file << backwardArrowString() << endl;
  }
  
  fig_file << " ";

  for ( points_iter = points.begin(); points_iter != points.end(); ++points_iter ) {
    fig_file << (*points_iter).xpos() << " " << (*points_iter).ypos() << " " ;
  }
  fig_file << endl;
}

void YaVecPolyline::getElmNearPos(YVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                                    list<YaVecElmHit> &hits) {
  vector<YVPosInt>::iterator pointsIt;
  int fuzzyRes;
  int i = 0;
  for ( pointsIt = points.begin(); pointsIt != points.end(); ++pointsIt, ++i ) {
    if (checkProximity(pos, (*pointsIt), fuzzyFact, fuzzyRes)) {
      YaVecElmHit newHit;
      newHit.elmP = this;
      newHit.distance = fuzzyRes;
      newHit.idx = i;
      hits.push_back(newHit);
    }
  }
}

void YaVecPolyline::debugPrint(ostream &dest, bool verbose, int depth) {
  dest << string(depth, ' ') << "Polyline " << points.size() << " points." << endl;
  if (verbose) {
    vector<YVPosInt>::iterator pointsIt;
    for ( pointsIt = points.begin(); pointsIt != points.end(); ++pointsIt ) {
      dest << string(depth+4, ' ') << (*pointsIt) << " -> " << endl;
    }
  }
}
