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


#ifndef _EASYVECARC_H
#define _EASYVECARC_H _EASYVECARC_H 

#include "EVPosInt.h"
#include "YaVecLine.h"
#include "YaVecArrow.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>

using namespace std;

/// An YaVecFigure polyline element - corresponds to fig element polyline (not box)
class YaVecArc : public YaVecElm, public YaVecLine, public YaVecArrow {
public:
  /// general constructor with no extra arguments
  YaVecArc(YaVecCompound* parent_compound, YaVecFigure* figure_compound, EVPosInt p1, EVPosInt p2, EVPosInt p3);
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right);

  /// Set point number num to the given position.
  void setPoint(int num, EVPosInt newPosition);
  /// Set all three points.
  void setPoints(EVPosInt newPoint1, EVPosInt newPoint2, EVPosInt newPoint3);
  /// Set arc geometry by center, radius, direction and angles.
  void setArc(EVPosInt center, double radius, bool clockwise, double angle1, double angle3);

  vector<YaVecElm*> flatList() { vector<YaVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(YaVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);

  /// find a figure element near the given position.
  virtual void getElmNearPos(EVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                             list<YaVecElmHit> &hits);

private:
  EVPosInt elmPoint1, elmPoint2, elmPoint3;
  bool isPieWedge;
  double xCenter, yCenter, radius;
  bool clockwise;
  double phi1, phi2, phi3;

  void computeArc(void);
  
};

#endif /* _EASYVECARC_H */

