// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ulf Klaperski
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

#include <fstream>
#include <iostream>
#include <typeinfo>
#include "EasyVecCompound.h"
#include "EasyVecPolyline.h"
#include "EasyVecArc.h"
#include "EasyVecBox.h"
#include "EasyVecText.h"

EasyVecArc* EasyVecCompound::arc(EVPosInt p1, EVPosInt p2, EVPosInt p3) {
  EasyVecArc* new_arc = new EasyVecArc(static_cast<EasyVecCompound*>(this), figure, p1, p2, p3);
  members.push_back(new_arc);
  return new_arc;
  
}

EasyVecPolyline* EasyVecCompound::polyline() {
  EasyVecPolyline* new_polyline = new EasyVecPolyline(static_cast<EasyVecCompound*>(this), figure);
  members.push_back(new_polyline);
  return new_polyline;
}

EasyVecBox* EasyVecCompound::box(EVPosInt upper_left, EVPosInt lower_right) {
  EasyVecBox* new_box = new EasyVecBox(static_cast<EasyVecCompound*>(this), figure, upper_left, lower_right);
  members.push_back(new_box);
  return new_box;
}

EasyVecText* EasyVecCompound::text() {
  EasyVecText* new_text = new EasyVecText(static_cast<EasyVecCompound*>(this), figure);
  members.push_back(new_text);
  return new_text;
}

EasyVecCompound* EasyVecCompound::compound() {
  EasyVecCompound* new_compound = new EasyVecCompound(static_cast<EasyVecCompound*>(this), figure);
  members.push_back(new_compound);
  return new_compound;
}


bool EasyVecCompound::remove(EasyVecElm* elm) {
  vector<EasyVecElm*>::iterator elmIt;
  elmIt = find(members.begin(), members.end(), elm);
  if (elmIt!=members.end()) {
    members.erase(elmIt);
    return true;
  } else {
    return false;
  }  
}


/*
 * This function returns the bounding box of this compound. This is the rectangular area
 * defined by all objects contained in this compound.
 */
void EasyVecCompound::getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right) {
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


vector<EasyVecElm*> EasyVecCompound::flatList() {
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

void EasyVecCompound::clear(void) {
  EasyVecElm* last_elm;
  while (members.size()>0) {
    last_elm = members.back();
    delete last_elm; // delete the object the pointer points to
    members.pop_back(); // remove the pointer from the list
  }
}


/*!
  This function copies all member elements of another compound to this compound.
  It is used by the assignment operators of EasyVecCompound and the derived
  EasyVecFigure class.
  Please note that this function does not clear the members of this compound,
  you must call the clear function yourself if you want this.
 */
void EasyVecCompound::copy_members(EasyVecCompound& source) {
  vector<EasyVecElm*>::iterator source_members_iter;
  EasyVecText* new_text;
  EasyVecBox* new_box;
  EasyVecPolyline* new_polyline;
  EasyVecCompound* new_compound;
    
  for (source_members_iter = source.members.begin();
       source_members_iter != source.members.end();
       ++source_members_iter ) {
    if (typeid(**source_members_iter) == typeid(EasyVecText)) {
      new_text = text();
      *new_text = *(static_cast<EasyVecText*>(*source_members_iter));
    } else if (typeid(**source_members_iter) == typeid(EasyVecBox)) {
      new_box = box(EVPosInt(0,0),EVPosInt(0,0));
      *new_box = *(static_cast<EasyVecBox*>(*source_members_iter));
    } else if (typeid(**source_members_iter) == typeid(EasyVecPolyline)) {
      new_polyline = polyline();
      *new_polyline = *(static_cast<EasyVecPolyline*>(*source_members_iter));
    } else if (typeid(**source_members_iter) == typeid(EasyVecCompound)) {
      new_compound = compound();
      *new_compound = *(static_cast<EasyVecCompound*>(*source_members_iter));
    } else {
      throw string("Error: Unknown type");
    }
  }
}

EasyVecCompound& EasyVecCompound::operator=(EasyVecCompound& source) {
  clear();
  copy_members(source);
  return *this;
}


void EasyVecCompound::handleChange(EasyVecElm* changed_element) {
  if (parent != 0) parent->handleChange(changed_element);
}


void EasyVecCompound::saveElm(ofstream &fig_file) {
  EVPosInt pos_min, pos_max;
  getBoundingBox(pos_min, pos_max);
  fig_file << "6 " << pos_min.xpos() << " " << pos_min.ypos() << " " <<
           pos_max.xpos() << " " << pos_max.ypos() << " " << endl;
  save_content(fig_file);
  fig_file << "-6" << endl;
}

// separate function as it will be reused by the EasyVecFigure class
void EasyVecCompound::save_content(ofstream &fig_file) {
  vector<EasyVecElm*>::iterator members_iter;
  for ( members_iter = members.begin(); members_iter != members.end(); ++members_iter ) {
    (*members_iter)->saveElm(fig_file);
  }  
}

void EasyVecCompound::getElmNearPos(EVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                                    list<EasyVecElmHit> &hits) {
  vector<EasyVecElm*>::iterator membersIt;
  for ( membersIt = members.begin(); membersIt != members.end(); ++membersIt ) {
    if (hierarchical || (typeid(**membersIt) != typeid(EasyVecCompound)))
      (*membersIt)->getElmNearPos(pos, fuzzyFact, hierarchical, withCompounds, hits);
  }
}


void EasyVecCompound::debugPrint(ostream &dest, bool verbose, int depth) {
  dest << string(depth, ' ') << "Compound with " << members.size() << " elements." << endl;
  if (verbose) {
    vector<EasyVecElm*>::iterator membersIt;
    for ( membersIt = members.begin(); membersIt != members.end(); ++membersIt ) {
      (*membersIt)->debugPrint(dest, verbose, depth+4);
    }
    dest << endl;
  }
}
