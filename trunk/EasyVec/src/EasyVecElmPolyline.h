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


#ifndef _EASYVECELMPOLYLINE_H
#define _EASYVECELMPOLYLINE_H _EASYVECELMPOLYLINE_H 

#include "EVPosInt.h"
#include "EasyVecElm.h"
#include "EasyVecElmCompound.h"
#include "EasyVecView.h"
#include <vector>

using namespace std;

class EasyVecElmPolyline : public EasyVecElm {
public:
  EasyVecElmPolyline();
  EasyVecElmPolyline(EasyVecElmCompound* parent_compound, EasyVec* master_compound)
    : EasyVecElm(parent_compound, master_compound) {};
  virtual void get_limits(EVPosInt &upper_left, EVPosInt &lower_right);
  void add_point(EVPosInt new_point);
  void add_point(int x, int y) { this->add_point(EVPosInt(x, y)); };
  void add_points(vector<EVPosInt> new_points);
  vector<EasyVecElm*> flat_list() { vector<EasyVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(EasyVecView* view);
  virtual void save_elm(ofstream &fig_file);

private:
  vector<EVPosInt> points;
};

#endif /* _EASYVECELMPOLYLINE_H */

