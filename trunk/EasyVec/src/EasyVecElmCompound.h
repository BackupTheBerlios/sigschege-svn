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
// $Id$


#ifndef _EASYVECELMCOMPOUND_H
#define _EASYVECELMCOMPOUND_H _EASYVECELMCOMPOUND_H 

class EasyVecElmPolyline;
class EasyVecElmBox;
class EasyVecElmText;

#include <vector>
#include "EVPosInt.h"
#include "EasyVecElm.h"
using namespace std;


class EasyVecElmCompound : public EasyVecElm {
public:
  EasyVecElmCompound();
  EasyVecElmCompound(EasyVecElmCompound* parent_compound, EasyVec* master_compound)
    : EasyVecElm(parent_compound, master_compound) {};

  EasyVecElmPolyline* polyline();
  EasyVecElmBox* box(EVPosInt &upper_left, EVPosInt &lower_right);
  EasyVecElmText* text();
  EasyVecElmCompound* compound();
  virtual void get_limits(EVPosInt &upper_left, EVPosInt &lower_right);
  virtual vector<EasyVecElm*> flat_list();
  virtual void draw(EasyVecView* view) {};
  virtual void handle_change(EasyVecElm*);
  virtual void save_elm(ofstream &fig_file);
  void save_content(ofstream &fig_file);

protected:
  vector<EasyVecElm*> members;
};

#endif /* _EASYVECELMCOMPOUND_H */

