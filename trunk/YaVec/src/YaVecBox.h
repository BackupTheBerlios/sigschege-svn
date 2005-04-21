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


#ifndef _YAVECBOX_H
#define _YAVECBOX_H _YAVECBOX_H 

#include "YVPosInt.h"
#include "YaVecLine.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>

using namespace std;

/// An YaVec box element - corresponds to fig element polyline:box and polyline:arcbox
class YaVecBox : public YaVecElm, public YaVecLine  {
public:
  /// general constructor with no extra arguments
  YaVecBox(YaVecCompound* parent_compound, YaVecFigure* figure_compound)
    : YaVecElm(parent_compound, figure_compound) {};
  /// general constructor accepting corner points
  YaVecBox(YaVecCompound* parent_compound, YaVecFigure* figure_compound, YVPosInt upper_left, YVPosInt lower_right);

  /// Return the limits of this element
  virtual void getBoundingBox(YVPosInt &upper_left, YVPosInt &lower_right) {
    upper_left  = elm_upper_left;
    lower_right = elm_lower_right;
  }
  /// set both corners of the box
  void set_corners(YVPosInt upper_left, YVPosInt lower_right) {
    upper_left  = elm_upper_left;
    lower_right = elm_lower_right;
  }
  
  vector<YaVecElm*> flatList() { vector<YaVecElm*> res; res.push_back(this); return (res); };

  /// send draw commands to the given view
  virtual void draw(YaVecView* view);
  /// save element into a fig file
  virtual void saveElm(ofstream &fig_file);

  /// find a figure element near the given position.
  virtual void getElmNearPos(YVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                             list<YaVecElmHit> &hits);

  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);


private:
  YVPosInt elm_upper_left, elm_lower_right;
};

#endif /* _YAVECBOX_H */

