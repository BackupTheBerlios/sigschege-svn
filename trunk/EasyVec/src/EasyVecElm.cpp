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

#include "EasyVecElm.h"
#include "EasyVecElmCompound.h"

EasyVecElm::EasyVecElm(void) {
  parent = 0;
  elm_pen_color = 0;
  elm_fill_color = 0;
  elm_depth = 0;
};


EasyVecElm::EasyVecElm(EasyVecElmCompound *parent_compound, EasyVec *master_compound) {
  parent = parent_compound;
  master = master_compound;
  elm_pen_color = parent->pen_color();
  elm_fill_color = parent->fill_color();
  elm_depth = parent->depth();
  
};

EasyVecElm::~EasyVecElm() {
  // notify owner? 
};


const int easyvec_std_colors[][3] = {
  {0, 0, 0}, // 0 = black
  {0x00, 0x00, 0xff}, // 1 = blue
  {0x00, 0xff, 0x00}, // 2 = green
  {0x00, 0xff, 0xff}, // 3 = Cyan
  {0xff, 0x00, 0x00}, // 4 = Red
  {0xff, 0x00, 0xff}, // 5 = Magenta
  {0xff, 0xff, 0x00}, // 6 = Yellow
  {0xff, 0xff, 0xff}  // 7 = White
};
