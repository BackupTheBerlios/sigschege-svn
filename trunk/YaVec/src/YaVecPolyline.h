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


#ifndef _EASYVECELMPOLYLINE_H
#define _EASYVECELMPOLYLINE_H _EASYVECELMPOLYLINE_H 

#include "YVPosInt.h"
#include "YaVecLine.h"
#include "YaVecArrow.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>

using namespace std;

/// An YaVecFigure polyline element - corresponds to fig element polyline (not box)
class YaVecPolyline : public YaVecElm, public YaVecLine, public YaVecArrow {
public:
  /// general constructor with no extra arguments
  YaVecPolyline(YaVecCompound* parent_compound, YaVecFigure* figure_compound);
  virtual void getBoundingBox(YVPosInt &upper_left, YVPosInt &lower_right);
  void addPoint(YVPosInt new_point);
  void addPoint(int x, int y) { this->addPoint(YVPosInt(x, y)); };
  void addPoints(vector<YVPosInt> new_points);
  vector<YaVecElm*> flatList() { vector<YaVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(YaVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);

  /// find a figure element near the given position.
  virtual void getElmNearPos(YVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                             list<YaVecElmHit> &hits);

private:
  vector<YVPosInt> points;
};

#endif /* _EASYVECELMPOLYLINE_H */

