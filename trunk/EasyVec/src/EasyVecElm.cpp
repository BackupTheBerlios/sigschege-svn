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

#include "EasyVecElm.h"
#include "EasyVecCompound.h"

EasyVecElm::EasyVecElm(void) {
  parent = 0;
  elmPenColor = 0;
  elmFillColor = 0;
  elmDepth = 50;
};


EasyVecElm::EasyVecElm(EasyVecCompound *parent_compound, EasyVecFigure *figure_compound) {
  parent = parent_compound;
  figure = figure_compound;
  elmPenColor = parent->penColor();
  elmFillColor = parent->fillColor();
  elmDepth = parent->depth();
  
};

EasyVecElm::~EasyVecElm() {
  // notify owner? 
};


const int easyvec_std_colors[][3] = {
  {0, 0, 0},          // 0 = black
  {0x00, 0x00, 0xff}, //  1 = blue
  {0x00, 0xff, 0x00}, //  2 = green
  {0x00, 0xff, 0xff}, //  3 = cyan
  {0xff, 0x00, 0x00}, //  4 = red
  {0xff, 0x00, 0xff}, //  5 = magenta
  {0xff, 0xff, 0x00}, //  6 = yellow
  {0xff, 0xff, 0xff}, //  7 = white
  {0x00, 0x00, 0x90}, //  8 = blue4
  {0x00, 0x00, 0xb0}, //  9 = blue3
  {0x00, 0x00, 0xd0}, // 10 = blue2
  {0x87, 0xce, 0xff}, // 11 = ltblue1
  {0x00, 0x90, 0x00}, // 12 = green4
  {0x00, 0xb0, 0x00}, // 13 = green3
  {0x00, 0xd0, 0x00}, // 14 = green2
  {0x90, 0x90, 0x00}, // 15 = cyan4
  {0xb0, 0xb0, 0x00}, // 16 = cyan3
  {0xd0, 0xd0, 0x00}, // 17 = cyan2
  {0x90, 0x00, 0x00}, // 18 = red4
  {0xb0, 0x00, 0x00}, // 19 = red3
  {0xd0, 0x00, 0x00}, // 20 = red2
  {0x90, 0x00, 0x90}, // 21 = magenta4
  {0xb0, 0x00, 0xb0}, // 22 = magenta3
  {0xd0, 0x00, 0xd0}, // 23 = magenta2
  {0x80, 0x30, 0x00}, // 24 = brown4
  {0xa0, 0x40, 0x00}, // 25 = brown3
  {0xc0, 0x60, 0x00}, // 26 = brown2
  {0xff, 0x80, 0x80}, // 27 = pink4
  {0xff, 0xa0, 0xa0}, // 28 = pink3
  {0xff, 0xc0, 0xc0}, // 29 = pink2
  {0xff, 0xe0, 0xe0}, // 30 = pink1
  {0xff, 0xd7, 0x00}  // 31 = gold
};
