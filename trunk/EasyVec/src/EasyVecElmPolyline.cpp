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

#include "EasyVecElmPolyline.h"
#include "EasyVec.h"
#include <fstream>
#include <iostream>

using namespace std;

bool EasyVecElmPolyline::forward_arrow(bool new_state) {
  bool oldval = elm_forward_arrow;
  elm_forward_arrow = new_state;
  return oldval;
}

bool EasyVecElmPolyline::backward_arrow(bool new_state) {
  bool oldval = elm_backward_arrow;
  elm_backward_arrow = new_state;
  return oldval;
}

bool EasyVecElmPolyline::forward_arrow(void) {
  return elm_forward_arrow;
}

bool EasyVecElmPolyline::backward_arrow(void) {
  return elm_backward_arrow;
}

void EasyVecElmPolyline::getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right) {
  vector<EVPosInt>::iterator points_iter = points.begin();
  if (points_iter==points.end()) {
    upper_left = EVPosInt(0,0); // no points! how should we behave???
    lower_right = EVPosInt(0,0);
  } else {
    lower_right = upper_left = *points_iter;
    while (++points_iter!=points.end()) {
      upper_left.min_values(*points_iter);
      lower_right.max_values(*points_iter);
    }
  }
}

void EasyVecElmPolyline::add_point(EVPosInt new_point) {
  points.push_back(new_point);
//  cout << "Adding point " << new_point.xpos() << ":" << new_point.ypos() << endl;
  parent->handle_change(this);
}

void EasyVecElmPolyline::add_points(vector<EVPosInt> new_points) {
  vector<EVPosInt>::iterator npoints_iter;
  for ( npoints_iter = new_points.begin(); npoints_iter != new_points.end(); ++npoints_iter ) {
    points.push_back(*npoints_iter);
  }
}

void EasyVecElmPolyline::draw(EasyVecView* view) {
  int xscale;
  EasyVec *testptr;
  testptr->scale();
  xscale = figure->scale();
  vector<EVPosInt>::iterator points_iter1, points_iter2;
  points_iter1 = points.begin();
  if (points_iter1==points.end()) return;
  points_iter2 = points_iter1;
  points_iter2++;
  while (points_iter2 != points.end()) {
    view->draw_line((*points_iter1)/xscale, (*points_iter2)/xscale, elm_pen_color);
    points_iter1 = points_iter2;
    ++points_iter2;
  }
}

void EasyVecElmPolyline::saveElm(ofstream &fig_file) {
  vector<EVPosInt>::iterator points_iter;

  string fwd_arr_line = "1 1 1.00 60.00 120.00";  
  string bwd_arr_line = "1 1 1.00 60.00 120.00";
  
  fig_file << "2 1 0 1 " << elm_pen_color << " " << elm_fill_color << " " << elm_depth
           << " 0 -1 0.0 0 0 0 " << (elm_forward_arrow? 1 : 0) << " "
           << (elm_backward_arrow? 1 : 0) << " " << points.size() << endl;
  if (elm_forward_arrow) {
    fig_file << fwd_arr_line << endl;
  }
  if (elm_backward_arrow) {
    fig_file << bwd_arr_line << endl;
  }
  
  fig_file << " ";

  for ( points_iter = points.begin(); points_iter != points.end(); ++points_iter ) {
    fig_file << (*points_iter).xpos() << " " << (*points_iter).ypos() << " " ;
  }
  fig_file << endl;
}
