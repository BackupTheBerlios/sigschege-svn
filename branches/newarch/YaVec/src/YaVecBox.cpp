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

#include "YaVecUtil.h"
#include "YaVecBox.h"
#include "YaVecFigure.h"
#include <fstream>
#include <iostream>

using namespace std;
namespace YaVec {

  FBox::FBox(FCompound* parent_compound, FFigure* figure_compound,
                     PosInt upper_left, PosInt lower_right)
    : YaVecElm(parent_compound, figure_compound),
      YaVecLine(),
      elm_upper_left(upper_left),
      elm_lower_right(lower_right) {};



  void FBox::draw(FigView* view) {

    PosInt ul, lr;
    PosInt ur, ll;
    Array <int, 3> color;

    ul = elm_upper_left;
    lr = elm_lower_right;

    ur = PosInt(lr.xpos(), ul.ypos());
    ll = PosInt(ul.xpos(), lr.ypos());

    double styleLength = elmStyleValue*15;

    getPenColorRGB(color);
  
    view->drawLine(ul/scale(), ur/scale(), elmThickness, color, elmLineStyle, styleLength/scale());
    view->drawLine(ur/scale(), lr/scale(), elmThickness, color, elmLineStyle, styleLength/scale());
    view->drawLine(lr/scale(), ll/scale(), elmThickness, color, elmLineStyle, styleLength/scale());
    view->drawLine(ll/scale(), ul/scale(), elmThickness, color, elmLineStyle, styleLength/scale());

    if (elmAreaFill>=0) {
      Array<int, 3> fillCol;
      PosInt left;
      PosInt right;
      left  = ul/scale(); left.incx();  left.incy();

      right = ur/scale(); right.decx(); right.incy();

      cout << "BOXR=" << ur.xpos()/scale() << " from " << ur.xpos() << " FILLR=" << right.xpos() << endl; 
    
      fillCol = actualFillColor();
      while (left.ypos() < ll.ypos()/scale()) {
        view->drawLine(left, right, elmThickness, fillCol, YaVecLine::solid, styleLength/scale());
        left.incy();
        right.incy();
      }
    }
  
  }

  void FBox::saveElm(ofstream &fig_file) {
    vector<PosInt>::iterator points_iter;

    fig_file << "2 1 " << elmLineStyle << " " << elmThickness << " " << elmPenColor << " " << elmFillColor << " " << elmDepth
             << " 0 " << elmAreaFill << " " << elmStyleValue << " 0 0 0 0 0 " << 5 << endl;
    fig_file << " ";
  
    fig_file << elm_upper_left.xpos()  << " " << elm_upper_left.ypos()  << " "
             << elm_lower_right.xpos() << " " << elm_upper_left.ypos()  << " "
             << elm_lower_right.xpos() << " " << elm_lower_right.ypos() << " "
             << elm_upper_left.xpos()  << " " << elm_lower_right.ypos() << " "
             << elm_upper_left.xpos()  << " " << elm_upper_left.ypos();

    fig_file << endl;
  }

  void FBox::getPoints(vector<PosInt> &points, bool hierarchical, bool withCompounds) {
    points.push_back(elm_upper_left);
    points.push_back(PosInt(elm_lower_right.xpos(), elm_upper_left.ypos()));
    points.push_back(PosInt(elm_upper_left.xpos(), elm_lower_right.ypos()));
    points.push_back(elm_lower_right);
  }

  void FBox::getElmNearPos(PosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                               list<YaVecElmHit> &hits) {
    vector<PosInt> allCorners;
    getPoints(allCorners, false, false);
    int fuzzyRes;
    unsigned int i;
    for (i=0; i<allCorners.size(); i++) {
      if (checkProximity(pos, allCorners[i], fuzzyFact, fuzzyRes)) {
        YaVecElmHit newHit;
        newHit.elmP = this;
        newHit.distance = fuzzyRes;
        newHit.idx = i;
        hits.push_back(newHit);
      }
    }
  }


  void FBox::debugPrint(ostream &dest, bool verbose, int depth) {
    dest << string(depth, ' ') << "Box " << endl;
    if (verbose) {
      dest << string(depth+4, ' ') << "Upper Left: " << elm_upper_left << "Lower Right: " << elm_lower_right << endl;
    }
  }
  
}
