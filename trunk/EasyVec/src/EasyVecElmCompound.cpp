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

#include "EasyVecElmCompound.h"
#include "EasyVecElmPolyline.h"
#include "EasyVecElmBox.h"
#include "EasyVecElmText.h"
#include <fstream>
#include <iostream>


EasyVecElmCompound::EasyVecElmCompound() {
  
}

EasyVecElmPolyline* EasyVecElmCompound::polyline() {
  EasyVecElmPolyline* new_polyline = new EasyVecElmPolyline(static_cast<EasyVecElmCompound*>(this), master);
  members.push_back(new_polyline);
  return new_polyline;
}

EasyVecElmBox* EasyVecElmCompound::box(EVPosInt upper_left, EVPosInt lower_right) {
  EasyVecElmBox* new_box = new EasyVecElmBox(static_cast<EasyVecElmCompound*>(this), master, upper_left, lower_right);
  members.push_back(new_box);
  return new_box;
}

EasyVecElmText* EasyVecElmCompound::text() {
  EasyVecElmText* new_text = new EasyVecElmText(static_cast<EasyVecElmCompound*>(this), master);
  members.push_back(new_text);
  return new_text;
}

EasyVecElmCompound* EasyVecElmCompound::compound() {
  EasyVecElmCompound* new_compound = new EasyVecElmCompound(static_cast<EasyVecElmCompound*>(this), master);
  members.push_back(new_compound);
  return new_compound;
}


/*
 * This function returns the bounding box of this compound. This is the rectangular area
 * defined by all objects contained in this compound.
 */
void EasyVecElmCompound::getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right) {
  vector<EasyVecElm*>::iterator members_iter = members.begin();
  EVPosInt member_point_min, member_point_max;
  if (members_iter==members.end()) {
    upper_left = EVPosInt(0,0); // no points! how should we behave???
    lower_right = EVPosInt(0,0);
  } else {
    (*members_iter)->getBoundingBox(member_point_min, member_point_max);
    upper_left = member_point_min;
    lower_right = member_point_max;
    while (++members_iter!=members.end()) {
      (*members_iter)->getBoundingBox(member_point_min, member_point_max);
      upper_left.min_values(member_point_min);
      lower_right.max_values(member_point_max);
    }
  }
};


vector<EasyVecElm*> EasyVecElmCompound::flatList() {
  vector<EasyVecElm*> result_list, tmp_list;
  vector<EasyVecElm*>::iterator members_iter;
  vector<EasyVecElm*>::iterator tmp_iter;
  for ( members_iter = members.begin(); members_iter != members.end(); ++members_iter ) {
    tmp_list = (*members_iter)->flatList();
     for ( tmp_iter = tmp_list.begin(); tmp_iter != tmp_list.end(); ++tmp_iter ) {
       result_list.push_back(*tmp_iter);
     }
  }
  return result_list;
}

void EasyVecElmCompound::handle_change(EasyVecElm* changed_element) {
  if (parent != 0) parent->handle_change(changed_element);
}


void EasyVecElmCompound::saveElm(ofstream &fig_file) {
  EVPosInt pos_min, pos_max;
  getBoundingBox(pos_min, pos_max);
  fig_file << "6 " << pos_min.xpos() << " " << pos_min.ypos() << " " <<
           pos_max.xpos() << " " << pos_max.ypos() << " " << endl;
  save_content(fig_file);
  fig_file << "-6" << endl;
}

// separate function as it will be reused by the EasyVec class
void EasyVecElmCompound::save_content(ofstream &fig_file) {
  vector<EasyVecElm*>::iterator members_iter;
  for ( members_iter = members.begin(); members_iter != members.end(); ++members_iter ) {
    (*members_iter)->saveElm(fig_file);
  }  
}
