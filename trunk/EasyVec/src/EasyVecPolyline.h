// -*- c++ -*-
// \file  
// Copyright 2004 by Ulf Klaperski
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


#ifndef _EASYVECELMPOLYLINE_H
#define _EASYVECELMPOLYLINE_H _EASYVECELMPOLYLINE_H 

#include "EVPosInt.h"
#include "EasyVecLine.h"
#include "EasyVecArrow.h"
#include "EasyVecElm.h"
#include "EasyVecCompound.h"
#include "EasyVecView.h"
#include <vector>

using namespace std;

/// An EasyVecFigure polyline element - corresponds to fig element polyline (not box)
class EasyVecPolyline : public EasyVecElm, public EasyVecLine, public EasyVecArrow {
public:
  /// general constructor with no extra arguments
  EasyVecPolyline(EasyVecCompound* parent_compound, EasyVecFigure* figure_compound);
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right);
  void addPoint(EVPosInt new_point);
  void addPoint(int x, int y) { this->addPoint(EVPosInt(x, y)); };
  void addPoints(vector<EVPosInt> new_points);
  vector<EasyVecElm*> flatList() { vector<EasyVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(EasyVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);


private:
  vector<EVPosInt> points;
};

#endif /* _EASYVECELMPOLYLINE_H */

