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
#include "EasyVecElm.h"
#include "EasyVecElmCompound.h"
#include "EasyVecView.h"
#include <vector>

using namespace std;

/// An EasyVec polyline element - corresponds to fig element polyline (not box)
class EasyVecElmPolyline : public EasyVecElm {
public:
  /// general constructor with no extra arguments
  EasyVecElmPolyline(EasyVecElmCompound* parent_compound, EasyVec* figure_compound)
    : EasyVecElm(parent_compound, figure_compound) {};
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right);
  void add_point(EVPosInt new_point);
  void add_point(int x, int y) { this->add_point(EVPosInt(x, y)); };
  void add_points(vector<EVPosInt> new_points);
  vector<EasyVecElm*> flatList() { vector<EasyVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(EasyVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Set the state of the forward arrow to new_state and return the old value.
  bool forward_arrow(bool new_state);
  /// Return the current state of the forward arrow
  bool forward_arrow(void);
  /// Set the state of the backward arrow to new_state and return the old value.
  bool backward_arrow(bool new_state);
  /// Return the current state of the backward arrow
  bool backward_arrow(void);
  /// Return the type of an element - values are from enum EasyVecElm::Type
  virtual EasyVecElm::Type type(void) { return Polyline; };

private:
  vector<EVPosInt> points;
  bool elm_forward_arrow, elm_backward_arrow;
};

#endif /* _EASYVECELMPOLYLINE_H */

