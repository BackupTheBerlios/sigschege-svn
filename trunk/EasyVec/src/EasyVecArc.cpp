// -*- c++ -*-
// \file  
// Copyright 2005 by Ulf Klaperski
//
// This file is part of EasyVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// EasyVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// EasyVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the EasyVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#include "EasyVecArc.h"
#include "EasyVecFigure.h"
#include <fstream>
#include <iostream>

using namespace std;

EasyVecArc::EasyVecArc(EasyVecCompound* parent_compound, EasyVecFigure* figure_compound)
  : EasyVecElm(parent_compound, figure_compound), EasyVecLine(), EasyVecArrow() {
};



void EasyVecArc::getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right) {
//   vector<EVPosInt>::iterator points_iter = points.begin();
//   if (points_iter==points.end()) {
//     upper_left = EVPosInt(0,0); // no points! how should we behave???
//     lower_right = EVPosInt(0,0);
//   } else {
//     lower_right = upper_left = *points_iter;
//     while (++points_iter!=points.end()) {
//       upper_left.min_values(*points_iter);
//       lower_right.max_values(*points_iter);
//     }
//   }
}

void EasyVecArc::setPoint(int num, EVPosInt newPosition) {
  switch (num) {
  case 0:
    elmPoint1 = newPosition;
    break;
  case 1:
    elmPoint2 = newPosition;
    break;
  case 2:
    elmPoint3 = newPosition;
    break;
  default:
    throw string("Illegal value for point in arc");
  }
  parent->handleChange(this);
}

void EasyVecArc::setPoints(EVPosInt newPoint1, EVPosInt newPoint2, EVPosInt newPoint3) {
  elmPoint1 = newPoint1;
  elmPoint2 = newPoint2;
  elmPoint3 = newPoint3;
  parent->handleChange(this);
}

void EasyVecArc::draw(EasyVecView* view) {
  double styleLength = elmStyleValue*15;
//   vector<EVPosInt>::iterator points_iter1, points_iter2;
//   EVPosInt oldPoint;
//   points_iter1 = points.begin();
//   if (points_iter1==points.end()) return;
//   points_iter2 = points_iter1;
//   points_iter2++;
//   if (backwardArrow() && points_iter2 != points.end()) 
//     view->drawArrow((*points_iter1), (*points_iter2), elmPenColor, elmArrows[1]);
//   while (points_iter2 != points.end()) {
//     view->drawLine((*points_iter1), (*points_iter2), elmThickness, elmPenColor, elmLineStyle, styleLength);
//     oldPoint = *points_iter1;
//     points_iter1 = points_iter2;
//     ++points_iter2;
//   }
//   if (forwardArrow() && points.size()>1) 
//     view->drawArrow((*points_iter1), oldPoint, elmPenColor, elmArrows[0]);
}


void EasyVecArc::saveElm(ofstream &fig_file) {
  vector<EVPosInt>::iterator points_iter;
  
  fig_file << "5 " << (isPieWedge? "2 " : "1 ") << elmLineStyle << " " << elmThickness << " " << elmPenColor << " " << elmFillColor << " " << elmDepth
           << " 0 -1 " << elmStyleValue << " 0 0 0 " << (forwardArrow()? 1 : 0) << " "
           << (backwardArrow()? 1 : 0);
  fig_file << " " << elmPoint1.xpos() << " " << elmPoint1.ypos() << elmPoint2.xpos() << " "
           << elmPoint2.ypos() << elmPoint3.xpos() << " " << elmPoint3.ypos() << endl;

  if (forwardArrow()) {
    fig_file << forwardArrowString() << endl;
  }
  if (backwardArrow()) {
    fig_file << backwardArrowString() << endl;
  }
}

void EasyVecArc::getElmNearPos(EVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                                    list<EasyVecElmHit> &hits) {
  vector<EVPosInt> allPoints(3);
  allPoints[0] = elmPoint1;
  allPoints[1] = elmPoint2;
  allPoints[2] = elmPoint3;
  int fuzzyRes, i;
  for (i=0; i<3; i++) {
    if (checkProximity(pos, allPoints[i], fuzzyFact, fuzzyRes)) {
      EasyVecElmHit newHit;
      newHit.elmP = this;
      newHit.distance = fuzzyRes;
      newHit.idx = i;
      hits.push_back(newHit);
    }
  }
}

void EasyVecArc::debugPrint(ostream &dest, bool verbose, int depth) {
  dest << string(depth, ' ') << "Arc " << endl;
  if (verbose) {
    dest << string(depth+4, ' ') << elmPoint1 << " -> " << elmPoint2 << " -> " << elmPoint3 << endl;
  }
}
