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

EasyVecArc::EasyVecArc(EasyVecCompound* parent_compound, EasyVecFigure* figure_compound, EVPosInt p1, EVPosInt p2, EVPosInt p3)
  : EasyVecElm(parent_compound, figure_compound), EasyVecLine(), EasyVecArrow() {
  isPieWedge = false;
  setPoints(p1, p2, p3);
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

void EasyVecArc::computeArc(void) {
  EVPosInt p1, p2, p3, ptmp;
  double y0, x0, x1, y1, x2, y2, x3, y3;
  double phi1, phi2;
  p1 = elmPoint1;
  p2 = elmPoint2;
  p3 = elmPoint3;
  if ((p1.xpos()-p2.xpos())==0) {
    ptmp = p1;
    p1 = p3;
    p3 = ptmp;
  } else if ((p3.xpos()-p1.xpos())==0) {
    ptmp = p1;
    p1 = p2;
    p2 = ptmp;
  }

  x1 = p1.xpos(); y1 = p1.ypos();
  x2 = p2.xpos(); y2 = p2.ypos();
  x3 = p3.xpos(); y3 = p3.ypos();

  y0 = 0.5 * ((x3-x1)*(x2*x2-x1*x1+y2*y2-y1*y1)-(x2-x1)*(x3*x3-x1*x1+y3*y3-y1*y1)) / ((y1-y3)*(x2-x1)-(x3-x1)*(y1-y2));
  x0 = (0.5 * (x3*x3-x1*x1+y3*y3-y1*y1) + y0*(y1-y3)) / (x3-x1);
  xCenter = x0;
  yCenter = y0;
  radius = (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
  phi1 = asin((y1-y0)/radius);
  phi2 = asin((y2-y0)/radius);
  clockwise = (phi2>phi1);
  cout << "X Center: " << x0 << " Y Center: " << y0 << " clockwise:" << clockwise << endl;
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
  computeArc();
  parent->handleChange(this);
}

void EasyVecArc::setPoints(EVPosInt newPoint1, EVPosInt newPoint2, EVPosInt newPoint3) {
  elmPoint1 = newPoint1;
  elmPoint2 = newPoint2;
  elmPoint3 = newPoint3;
  computeArc();
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
           << " -1 -1 " << elmStyleValue << " 0 0 " << (forwardArrow()? 1 : 0) << " "
           << (backwardArrow()? 1 : 0) << " " << xCenter << " " << yCenter;
  fig_file << " " << elmPoint1.xpos() << " " << elmPoint1.ypos() << " " << elmPoint2.xpos() << " "
           << elmPoint2.ypos() << " " << elmPoint3.xpos() << " " << elmPoint3.ypos() << endl;

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
