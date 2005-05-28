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

namespace YaVec {

  FPolyline::FPolyline(FCompound* parent_compound, FFigure* figure_compound)
    : YaVecElm(parent_compound, figure_compound), YaVecLine(), YaVecArrow() {
  };



  void FPolyline::getBoundingBox(PosInt &upper_left, PosInt &lower_right) {
    vector<PosInt>::iterator points_iter = linePoints.begin();
    if (points_iter==linePoints.end()) {
      upper_left = PosInt(0,0); // no points! how should we behave???
      lower_right = PosInt(0,0);
    } else {
      lower_right = upper_left = *points_iter;
      while (++points_iter!=linePoints.end()) {
        upper_left.minValues(*points_iter);
        lower_right.maxValues(*points_iter);
      }
    }
  }

  void FPolyline::addPoint(PosInt new_point) {
    linePoints.push_back(new_point);
    //  cout << "Adding point " << new_point.xpos() << ":" << new_point.ypos() << endl;
    parent->handleChange(this);
  }

  void FPolyline::addPoints(vector<PosInt> new_points) {
    vector<PosInt>::iterator npoints_iter;
    for ( npoints_iter = new_points.begin(); npoints_iter != new_points.end(); ++npoints_iter ) {
      linePoints.push_back(*npoints_iter);
    }
  }

  void FPolyline::addAngleBox(PosInt corner1, PosInt corner3, double angle, bool clear) {
    //double angleRad = angle*M_PI/180;
  
    //TODO
  }

  void FPolyline::draw(FigView* view) {
    double styleLength = elmStyleValue*15;
    vector<PosInt>::iterator points_iter1, points_iter2;
    PosInt oldPoint;
    Array <int, 3> color;

    points_iter1 = linePoints.begin();
    if (points_iter1==linePoints.end()) return;
    points_iter2 = points_iter1;
    points_iter2++;

    getPenColorRGB(color);
  
    if (backwardArrow() && points_iter2 != linePoints.end()) 
      drawArrow((*points_iter1), (*points_iter2), color, elmThickness, view, scale(), true);
    while (points_iter2 != linePoints.end()) {
      view->drawLine((*points_iter1)/scale(), (*points_iter2)/scale(), elmThickness, color, elmLineStyle, styleLength/scale());
      oldPoint = *points_iter1;
      points_iter1 = points_iter2;
      ++points_iter2;
    }
    if (forwardArrow() && linePoints.size()>1) 
      drawArrow((*points_iter1), oldPoint, color, elmThickness, view, scale(), false);
  }


  void FPolyline::saveElm(ofstream &fig_file) {
    vector<PosInt>::iterator points_iter;

    if (linePoints.size()==0) return; // polyline without points not allowed
  
    fig_file << "2 1 " << elmLineStyle << " " << elmThickness << " " << elmPenColor << " " << elmFillColor << " " << elmDepth
             << " 0 " << elmAreaFill << " " << elmStyleValue << " 0 0 0 " << (forwardArrow()? 1 : 0) << " "
             << (backwardArrow()? 1 : 0) << " " << linePoints.size() << endl;
    if (forwardArrow()) {
      fig_file << forwardArrowString() << endl;
    }
    if (backwardArrow()) {
      fig_file << backwardArrowString() << endl;
    }
  
    fig_file << " ";

    for ( points_iter = linePoints.begin(); points_iter != linePoints.end(); ++points_iter ) {
      fig_file << (*points_iter).xpos() << " " << (*points_iter).ypos() << " " ;
    }
    fig_file << endl;
  }

  void FPolyline::getPoints(vector<PosInt> &points, bool hierarchical, bool withCompounds) {
    vector<PosInt>::iterator pointsIt;
    for ( pointsIt = linePoints.begin(); pointsIt != linePoints.end(); ++pointsIt ) {
      points.push_back((*pointsIt));
    }
  }


  void FPolyline::debugPrint(ostream &dest, bool verbose, int depth) {
    dest << string(depth, ' ') << "Polyline " << linePoints.size() << " linePoints." << endl;
    if (verbose) {
      vector<PosInt>::iterator pointsIt;
      for ( pointsIt = linePoints.begin(); pointsIt != linePoints.end(); ++pointsIt ) {
        dest << string(depth+4, ' ') << (*pointsIt) << " -> " << endl;
      }
    }
  }

}
