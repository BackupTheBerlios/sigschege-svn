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

#include "EasyVecElmCompound.h"
#include "EasyVecElmPolyline.h"
#include "EasyVecElmBox.h"
#include "EasyVecElmText.h"
#include <fstream>
#include <iostream>



EasyVecElmPolyline* EasyVecElmCompound::polyline() {
  EasyVecElmPolyline* new_polyline = new EasyVecElmPolyline(static_cast<EasyVecElmCompound*>(this), figure);
  members.push_back(new_polyline);
  return new_polyline;
}

EasyVecElmBox* EasyVecElmCompound::box(EVPosInt upper_left, EVPosInt lower_right) {
  EasyVecElmBox* new_box = new EasyVecElmBox(static_cast<EasyVecElmCompound*>(this), figure, upper_left, lower_right);
  members.push_back(new_box);
  return new_box;
}

EasyVecElmText* EasyVecElmCompound::text() {
  EasyVecElmText* new_text = new EasyVecElmText(static_cast<EasyVecElmCompound*>(this), figure);
  members.push_back(new_text);
  return new_text;
}

EasyVecElmCompound* EasyVecElmCompound::compound() {
  EasyVecElmCompound* new_compound = new EasyVecElmCompound(static_cast<EasyVecElmCompound*>(this), figure);
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

void EasyVecElmCompound::clear(void) {
  EasyVecElm* last_elm;
  while (members.size()>0) {
    last_elm = members.back();
    delete last_elm;
    members.pop_back();
  }
}


/*!
  This function copies all member elements of another compound to this compound.
  It is used by the assignment operators of EasyVecElmCompound and the derived
  EasyVec class.
  Please note that this function does not clear the members of this compound,
  you must call the clear function yourself if you want this.
 */
void EasyVecElmCompound::copy_members(EasyVecElmCompound& source) {
  vector<EasyVecElm*>::iterator source_members_iter;
  EasyVecElmText* new_text;
  EasyVecElmBox* new_box;
  EasyVecElmPolyline* new_polyline;
  EasyVecElmCompound* new_compound;
    
  for (source_members_iter = source.members.begin();
       source_members_iter != source.members.end();
       ++source_members_iter ) {
    switch ((*source_members_iter)->type()) {
    case Text:
      new_text = text();
      *new_text = *(static_cast<EasyVecElmText*>(*source_members_iter));
      break;
    case Box:
      new_box = box(EVPosInt(0,0),EVPosInt(0,0));
      *new_box = *(static_cast<EasyVecElmBox*>(*source_members_iter));
      break;
    case Polyline:
      new_polyline = polyline();
      *new_polyline = *(static_cast<EasyVecElmPolyline*>(*source_members_iter));
      break;
    case Compound:
      new_compound = compound();
      *new_compound = *(static_cast<EasyVecElmCompound*>(*source_members_iter));
      break;
    default:
      cerr << "Error: Unknown type" << endl;
    }
  }
}

EasyVecElmCompound& EasyVecElmCompound::operator=(EasyVecElmCompound& source) {
  clear();
  copy_members(source);
  return *this;
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

