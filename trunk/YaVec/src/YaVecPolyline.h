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


#ifndef _YAVECELMPOLYLINE_H
#define _YAVECELMPOLYLINE_H _YAVECELMPOLYLINE_H 

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
  /// General constructor with no extra arguments.
  YaVecPolyline(YaVecCompound* parent_compound, YaVecFigure* figure_compound);
  /// Get the bounding box of this polyline.
  virtual void getBoundingBox(YVPosInt &upper_left, YVPosInt &lower_right);
  /// Add this point (given as YVPosInt).
  void addPoint(YVPosInt new_point);
  /// Add this point (given as integers).
  void addPoint(int x, int y) { this->addPoint(YVPosInt(x, y)); };
  /// Add a complete vector of  points (given as YVPosInt).
  void addPoints(vector<YVPosInt> new_points);
  /// Sets points for a box at a random angle
  void addAngleBox(YVPosInt corner1, YVPosInt corner2, double angle, bool clear=true);
  /// Collect all figure elements hierarchicallly as a flat list (just return myself).
  vector<YaVecElm*> flatList() { vector<YaVecElm*> res; res.push_back(this); return (res); };
  /// Draw the polyline to the given view.
  virtual void draw(YaVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);

  /// Return a list of significant points, which can be used for selection
  virtual void getPoints(vector<YVPosInt> &points, bool hierarchical, bool withCompounds);

private:
  vector<YVPosInt> linePoints;
};

#endif /* _YAVECELMPOLYLINE_H */

