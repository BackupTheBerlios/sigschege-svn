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


#ifndef _EASYVECARC_H
#define _EASYVECARC_H _EASYVECARC_H 

#include "EVPosInt.h"
#include "EasyVecLine.h"
#include "EasyVecArrow.h"
#include "EasyVecElm.h"
#include "EasyVecCompound.h"
#include "EasyVecView.h"
#include <vector>

using namespace std;

/// An EasyVecFigure polyline element - corresponds to fig element polyline (not box)
class EasyVecArc : public EasyVecElm, public EasyVecLine, public EasyVecArrow {
public:
  /// general constructor with no extra arguments
  EasyVecArc(EasyVecCompound* parent_compound, EasyVecFigure* figure_compound);
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right);

  /// Set point number num to the given position.
  void setPoint(int num, EVPosInt newPosition);
  /// Set all three points.
  void setPoints(EVPosInt newPoint1, EVPosInt newPoint2, EVPosInt newPoint3);

  vector<EasyVecElm*> flatList() { vector<EasyVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(EasyVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);

  /// find a figure element near the given position.
  virtual void getElmNearPos(EVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                             list<EasyVecElmHit> &hits);

private:
  EVPosInt elmPoint1, elmPoint2, elmPoint3;
  bool isPieWedge;
};

#endif /* _EASYVECARC_H */

