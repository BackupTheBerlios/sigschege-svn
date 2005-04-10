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

#include "YaVecBox.h"
#include "YaVecFigure.h"
#include <fstream>
#include <iostream>

using namespace std;

YaVecBox::YaVecBox(YaVecCompound* parent_compound, YaVecFigure* figure_compound,
                             YVPosInt upper_left, YVPosInt lower_right)
  : YaVecElm(parent_compound, figure_compound),
    YaVecLine(),
    elm_upper_left(upper_left),
    elm_lower_right(lower_right) {};



void YaVecBox::draw(YaVecView* view) {

  YVPosInt ul, lr;
  YVPosInt ur, ll;

  ul = elm_upper_left;
  lr = elm_lower_right;

  ur = YVPosInt(lr.xpos(), ul.ypos());
  ll = YVPosInt(ul.xpos(), lr.ypos());

  double styleLength = elmStyleValue*15;

  view->drawLine(ul, ur, elmThickness, elmPenColor, elmLineStyle, styleLength);
  view->drawLine(ur, lr, elmThickness, elmPenColor, elmLineStyle, styleLength);
  view->drawLine(lr, ll, elmThickness, elmPenColor, elmLineStyle, styleLength);
  view->drawLine(ll, ul, elmThickness, elmPenColor, elmLineStyle, styleLength);

}

void YaVecBox::saveElm(ofstream &fig_file) {
  vector<YVPosInt>::iterator points_iter;

  fig_file << "2 1 " << elmLineStyle << " " << elmThickness << " " << elmPenColor << " " << elmFillColor << " " << elmDepth
           << " 0 -1 " << elmStyleValue << " 0 0 0 0 0 " << 5 << endl;
  fig_file << " ";
  
  fig_file << elm_upper_left.xpos()  << " " << elm_upper_left.ypos()  << " "
           << elm_lower_right.xpos() << " " << elm_upper_left.ypos()  << " "
           << elm_lower_right.xpos() << " " << elm_lower_right.ypos() << " "
           << elm_upper_left.xpos()  << " " << elm_lower_right.ypos() << " "
           << elm_upper_left.xpos()  << " " << elm_upper_left.ypos();

  fig_file << endl;
}

void YaVecBox::getElmNearPos(YVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                                    list<YaVecElmHit> &hits) {
  vector<YVPosInt> allCorners(4);
  allCorners[0] = elm_upper_left;
  allCorners[1] = YVPosInt(elm_lower_right.xpos(), elm_upper_left.ypos());
  allCorners[2] = YVPosInt(elm_upper_left.xpos(), elm_lower_right.ypos());
  allCorners[3] = elm_lower_right;
  int fuzzyRes, i;
  for (i=0; i<4; i++) {
    if (checkProximity(pos, allCorners[i], fuzzyFact, fuzzyRes)) {
      YaVecElmHit newHit;
      newHit.elmP = this;
      newHit.distance = fuzzyRes;
      newHit.idx = i;
      hits.push_back(newHit);
    }
  }
}


void YaVecBox::debugPrint(ostream &dest, bool verbose, int depth) {
  dest << string(depth, ' ') << "Box " << endl;
  if (verbose) {
      dest << string(depth+4, ' ') << "Upper Left: " << elm_upper_left << "Lower Right: " << elm_lower_right << endl;
  }
}
