// -*- c++ -*-
// \file  
// Copyright 2005 by Ulf Klaperski
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


#ifndef _YAVECARC_H
#define _YAVECARC_H _YAVECARC_H 

#include "YVPosInt.h"
#include "YaVecLine.h"
#include "YaVecArrow.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>

using namespace std;

/// An YaVecFigure arc element - corresponds to fig element arc
class YaVecArc : public YaVecElm, public YaVecLine, public YaVecArrow {
public:
  /// General constructor which creates the object, from center, radius, angles.
  YaVecArc(YaVecCompound* parent_compound, YaVecFigure* figure_compound, YVPosInt center, double radius, bool clockwise, double angle1, double angle3);
  /// General constructor, which creates the arc from three points.
  YaVecArc(YaVecCompound* parent_compound, YaVecFigure* figure_compound, YVPosInt p1, YVPosInt p2, YVPosInt p3);
  virtual void getBoundingBox(YVPosInt &upper_left, YVPosInt &lower_right);

  /// Set point number num to the given position.
  void setPoint(int num, YVPosInt newPosition);
  /// Set all three points.
  void setPoints(YVPosInt newPoint1, YVPosInt newPoint2, YVPosInt newPoint3);
  /// Set arc geometry by center, radius, direction and angles.
  void setArc(YVPosInt center, double radius, bool clockwise, double angle1, double angle3);

  vector<YaVecElm*> flatList() { vector<YaVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(YaVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);

  /// find a figure element near the given position.
  virtual void getElmNearPos(YVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                             list<YaVecElmHit> &hits);

private:
  YVPosInt elmPoint1, elmPoint2, elmPoint3;
  bool isPieWedge;
  double elmXCenter, elmYCenter, elmRadius;
  bool elmClockwise;
  double elmPhi1, elmPhi2, elmPhi3;

  void computeArc(void);
  
};

#endif /* _YAVECARC_H */

