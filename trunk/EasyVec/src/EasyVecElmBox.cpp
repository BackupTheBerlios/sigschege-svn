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

#include "EasyVecElmBox.h"
#include "EasyVec.h"
#include <fstream>
#include <iostream>

using namespace std;

EasyVecElmBox::EasyVecElmBox(EasyVecElmCompound* parent_compound, EasyVec* master_compound,
                             EVPosInt upper_left, EVPosInt lower_right)
  : EasyVecElm(parent_compound, master_compound),
    elm_upper_left(upper_left),
    elm_lower_right(lower_right) {};



void EasyVecElmBox::draw(EasyVecView* view) {
  int xscale;
  EasyVec *testptr;
  testptr->scale();
  xscale = master->scale();
  EVPosInt ul, lr;
  EVPosInt ur, ll;

  ul = elm_upper_left/xscale;
  lr = elm_lower_right/xscale;

  ur = EVPosInt(lr.xpos(), ul.ypos());
  ll = EVPosInt(ul.xpos(), lr.ypos());
  
  view->draw_line(ul, ur, elm_pen_color);
  view->draw_line(ur, lr, elm_pen_color);
  view->draw_line(lr, ll, elm_pen_color);
  view->draw_line(ll, ul, elm_pen_color);

}

void EasyVecElmBox::saveElm(ofstream &fig_file) {
  vector<EVPosInt>::iterator points_iter;

  fig_file << "2 1 0 1 " << elm_pen_color << " " << elm_fill_color << " " << elm_depth
           << " 0 -1 0.0 0 0 0 0 0 " << 5 << endl;
  fig_file << " ";
  
  fig_file << elm_upper_left.xpos()  << " " << elm_upper_left.ypos()  << " "
           << elm_lower_right.xpos() << " " << elm_upper_left.ypos()  << " "
           << elm_lower_right.xpos() << " " << elm_lower_right.ypos() << " "
           << elm_upper_left.xpos()  << " " << elm_lower_right.ypos() << " "
           << elm_upper_left.xpos()  << " " << elm_upper_left.ypos();

  fig_file << endl;
}
