// -*- c++ -*-
/// \file 
 
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
// $Id: $


#ifndef _EASYVECELMBOX_H
#define _EASYVECELMBOX_H _EASYVECELMBOX_H 

#include "EVPosInt.h"
#include "EasyVecElm.h"
#include "EasyVecElmCompound.h"
#include "EasyVecView.h"
#include <vector>

using namespace std;

/// An EasyVec box element - corresponds to fig element polyline:box and polyline:arcbox
class EasyVecElmBox : public EasyVecElm {
public:
  /// general constructor with no extra arguments
  EasyVecElmBox(EasyVecElmCompound* parent_compound, EasyVec* master_compound)
    : EasyVecElm(parent_compound, master_compound) {};
  /// general constructor accepting corner points
  EasyVecElmBox(EasyVecElmCompound* parent_compound, EasyVec* master_compound, EVPosInt upper_left, EVPosInt lower_right);

  /// Return the limits of this element
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right) {
    upper_left  = elm_upper_left;
    lower_right = elm_lower_right;
  }
  /// set both corners of the box
  void set_corners(EVPosInt upper_left, EVPosInt lower_right) {
    upper_left  = elm_upper_left;
    lower_right = elm_lower_right;
  }
  
  vector<EasyVecElm*> flatList() { vector<EasyVecElm*> res; res.push_back(this); return (res); };

  /// send draw commands to the given view
  virtual void draw(EasyVecView* view);
  /// save element into a fig file
  virtual void saveElm(ofstream &fig_file);

private:
  EVPosInt elm_upper_left, elm_lower_right;
};

#endif /* _EASYVECELMBOX_H */

