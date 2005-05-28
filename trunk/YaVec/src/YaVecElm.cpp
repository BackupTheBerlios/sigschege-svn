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

#include "YaVecElm.h"
#include "YaVecFigure.h"

using namespace std;

namespace YaVec {

  YaVecElm::YaVecElm(void) {
    parent = 0;
    elmPenColor = 0;
    elmFillColor = 0;
    elmAreaFill = -1;
    elmDepth = 50;
  };


  YaVecElm::YaVecElm(FCompound *parent_compound, FFigure *figure_compound) {
    parent = parent_compound;
    figure = figure_compound;
    elmPenColor = parent->penColor();
    elmFillColor = parent->fillColor();
    elmAreaFill = parent->areaFill();
    elmDepth = parent->depth();
  };

  YaVecElm::~YaVecElm() {
    // notify owner? 
  };

  bool YaVecElm::checkProximity(PosInt selPos, PosInt point, int fuzzyFact, int &fuzzyRes) {
    int deltaX = abs(point.xpos()-selPos.xpos());
    int deltaY = abs(point.ypos()-selPos.ypos());
    if (deltaX>fuzzyFact || deltaY>fuzzyFact) {
      return false;
    } else {
      fuzzyRes = static_cast<int>(sqrt(static_cast<double>(deltaX)*deltaX+static_cast<double>(deltaY)*deltaY));
      if (fuzzyRes>fuzzyFact) return false;
      else return true;
    }
  }

  Array<int,3> YaVecElm::actualFillColor(void) {
    Array<int,3> zeroCol, oneCol, resultCol;
    double percentZero, percentOne;
    if (elmFillColor==-1 || elmFillColor==0) { // black or default
      zeroCol[0] = yavec_std_colors[7][0]; //white
      zeroCol[1] = yavec_std_colors[7][1]; 
      zeroCol[2] = yavec_std_colors[7][2]; 
      oneCol[0] = yavec_std_colors[0][0]; // black
      oneCol[1] = yavec_std_colors[0][1]; 
      oneCol[2] = yavec_std_colors[0][2]; 
    } else {
      zeroCol[0] = yavec_std_colors[0][0]; // black
      zeroCol[1] = yavec_std_colors[0][1]; 
      zeroCol[2] = yavec_std_colors[0][2];
      oneCol[0] = yavec_std_colors[elmFillColor][0]; // selected fill color
      oneCol[1] = yavec_std_colors[elmFillColor][1]; 
      oneCol[2] = yavec_std_colors[elmFillColor][2];     
    }
  
    if (elmAreaFill==20) return oneCol;
    else if (elmAreaFill==0) return zeroCol;
    else if (elmAreaFill>0 and elmAreaFill<21) {
      percentOne = 5.0*elmAreaFill;
      percentZero = 100.0-percentOne;
      resultCol[0] = static_cast<int>(percentZero*zeroCol[0]+percentOne*oneCol[0]);
      resultCol[1] = static_cast<int>(percentZero*zeroCol[1]+percentOne*oneCol[1]);
      resultCol[2] = static_cast<int>(percentZero*zeroCol[2]+percentOne*oneCol[2]);
    } else {
      resultCol = oneCol; // TODO
    }
    return resultCol;
  }

  void YaVecElm::getElmNearPos(PosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                               list<YaVecElmHit> &hits) {
    int fuzzyRes;
    unsigned int i;
    vector<PosInt> points;
    getPoints(points, hierarchical, withCompounds);
  
    for (i=0; i<points.size(); i++) {
      if (checkProximity(pos, points[i], fuzzyFact, fuzzyRes)) {
        YaVecElmHit newHit;
        newHit.elmP = this;
        newHit.distance = fuzzyRes;
        newHit.idx = 0;
        hits.push_back(newHit);
      }
    }
  }


  // TODO: should be inline, but type of figure not known in header file
  int YaVecElm::scale(void) {
    return figure->scale();
  }

  const int yavec_std_colors[][3] = {
    {0, 0, 0},          // 0 = black
    {0x00, 0x00, 0xff}, //  1 = blue
    {0x00, 0xff, 0x00}, //  2 = green
    {0x00, 0xff, 0xff}, //  3 = cyan
    {0xff, 0x00, 0x00}, //  4 = red
    {0xff, 0x00, 0xff}, //  5 = magenta
    {0xff, 0xff, 0x00}, //  6 = yellow
    {0xff, 0xff, 0xff}, //  7 = white
    {0x00, 0x00, 0x90}, //  8 = blue4
    {0x00, 0x00, 0xb0}, //  9 = blue3
    {0x00, 0x00, 0xd0}, // 10 = blue2
    {0x87, 0xce, 0xff}, // 11 = ltblue1
    {0x00, 0x90, 0x00}, // 12 = green4
    {0x00, 0xb0, 0x00}, // 13 = green3
    {0x00, 0xd0, 0x00}, // 14 = green2
    {0x90, 0x90, 0x00}, // 15 = cyan4
    {0xb0, 0xb0, 0x00}, // 16 = cyan3
    {0xd0, 0xd0, 0x00}, // 17 = cyan2
    {0x90, 0x00, 0x00}, // 18 = red4
    {0xb0, 0x00, 0x00}, // 19 = red3
    {0xd0, 0x00, 0x00}, // 20 = red2
    {0x90, 0x00, 0x90}, // 21 = magenta4
    {0xb0, 0x00, 0xb0}, // 22 = magenta3
    {0xd0, 0x00, 0xd0}, // 23 = magenta2
    {0x80, 0x30, 0x00}, // 24 = brown4
    {0xa0, 0x40, 0x00}, // 25 = brown3
    {0xc0, 0x60, 0x00}, // 26 = brown2
    {0xff, 0x80, 0x80}, // 27 = pink4
    {0xff, 0xa0, 0xa0}, // 28 = pink3
    {0xff, 0xc0, 0xc0}, // 29 = pink2
    {0xff, 0xe0, 0xe0}, // 30 = pink1
    {0xff, 0xd7, 0x00}  // 31 = gold
  };

}
