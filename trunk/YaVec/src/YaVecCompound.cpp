// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ulf Klaperski
//
// This file is part of YaVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// YaVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// YaVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the YaVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#include <fstream>
#include <iostream>
#include <typeinfo>
#include "YaVecCompound.h"
#include "YaVecPolyline.h"
#include "YaVecArc.h"
#include "YaVecBox.h"
#include "YaVecText.h"

YaVecArc* YaVecCompound::arc(YVPosInt p1, YVPosInt p2, YVPosInt p3) {
  YaVecArc* new_arc = new YaVecArc(static_cast<YaVecCompound*>(this), figure, p1, p2, p3);
  members.push_back(new_arc);
  return new_arc;
  
}

YaVecArc* YaVecCompound::arc(YVPosInt center, double radius, bool clockwise, double angle1, double angle3) {
  YaVecArc* new_arc = new YaVecArc(static_cast<YaVecCompound*>(this), figure, center, radius, clockwise, angle1, angle3);
  members.push_back(new_arc);
  return new_arc;  
}


YaVecPolyline* YaVecCompound::polyline() {
  YaVecPolyline* new_polyline = new YaVecPolyline(static_cast<YaVecCompound*>(this), figure);
  members.push_back(new_polyline);
  return new_polyline;
}

YaVecBox* YaVecCompound::box(YVPosInt upper_left, YVPosInt lower_right) {
  YaVecBox* new_box = new YaVecBox(static_cast<YaVecCompound*>(this), figure, upper_left, lower_right);
  members.push_back(new_box);
  return new_box;
}

YaVecText* YaVecCompound::text() {
  YaVecText* new_text = new YaVecText(static_cast<YaVecCompound*>(this), figure);
  members.push_back(new_text);
  return new_text;
}

YaVecCompound* YaVecCompound::compound() {
  YaVecCompound* new_compound = new YaVecCompound(static_cast<YaVecCompound*>(this), figure);
  members.push_back(new_compound);
  return new_compound;
}


bool YaVecCompound::remove(YaVecElm* elm) {
  vector<YaVecElm*>::iterator elmIt;
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
void YaVecCompound::getBoundingBox(YVPosInt &upper_left, YVPosInt &lower_right) {
  vector<YaVecElm*>::iterator members_iter = members.begin();
  YVPosInt member_point_min, member_point_max;
  if (members_iter==members.end()) {
    upper_left = YVPosInt(0,0); // no points! how should we behave???
    lower_right = YVPosInt(0,0);
  } else {
    (*members_iter)->getBoundingBox(member_point_min, member_point_max);
    upper_left = member_point_min;
    lower_right = member_point_max;
    while (++members_iter!=members.end()) {
      (*members_iter)->getBoundingBox(member_point_min, member_point_max);
      upper_left.minValues(member_point_min);
      lower_right.maxValues(member_point_max);
    }
  }
};


vector<YaVecElm*> YaVecCompound::flatList() {
  vector<YaVecElm*> result_list, tmp_list;
  vector<YaVecElm*>::iterator members_iter;
  vector<YaVecElm*>::iterator tmp_iter;
  for ( members_iter = members.begin(); members_iter != members.end(); ++members_iter ) {
    tmp_list = (*members_iter)->flatList();
     for ( tmp_iter = tmp_list.begin(); tmp_iter != tmp_list.end(); ++tmp_iter ) {
       result_list.push_back(*tmp_iter);
     }
  }
  return result_list;
}

void YaVecCompound::clear(void) {
  YaVecElm* last_elm;
  while (members.size()>0) {
    last_elm = members.back();
    delete last_elm; // delete the object the pointer points to
    members.pop_back(); // remove the pointer from the list
  }
}


/*!
  This function copies all member elements of another compound to this compound.
  It is used by the assignment operators of YaVecCompound and the derived
  YaVecFigure class.
  Please note that this function does not clear the members of this compound,
  you must call the clear function yourself if you want this.
 */
void YaVecCompound::copy_members(YaVecCompound& source) {
  vector<YaVecElm*>::iterator source_members_iter;
  YaVecText* new_text;
  YaVecBox* new_box;
  YaVecPolyline* new_polyline;
  YaVecCompound* new_compound;
    
  for (source_members_iter = source.members.begin();
       source_members_iter != source.members.end();
       ++source_members_iter ) {
    if (typeid(**source_members_iter) == typeid(YaVecText)) {
      new_text = text();
      *new_text = *(static_cast<YaVecText*>(*source_members_iter));
    } else if (typeid(**source_members_iter) == typeid(YaVecBox)) {
      new_box = box(YVPosInt(0,0),YVPosInt(0,0));
      *new_box = *(static_cast<YaVecBox*>(*source_members_iter));
    } else if (typeid(**source_members_iter) == typeid(YaVecPolyline)) {
      new_polyline = polyline();
      *new_polyline = *(static_cast<YaVecPolyline*>(*source_members_iter));
    } else if (typeid(**source_members_iter) == typeid(YaVecCompound)) {
      new_compound = compound();
      *new_compound = *(static_cast<YaVecCompound*>(*source_members_iter));
    } else {
      throw string("Error: Unknown type");
    }
  }
}

YaVecCompound& YaVecCompound::operator=(YaVecCompound& source) {
  clear();
  copy_members(source);
  return *this;
}


void YaVecCompound::handleChange(YaVecElm* changed_element) {
  if (parent != 0) parent->handleChange(changed_element);
}


void YaVecCompound::saveElm(ofstream &fig_file) {
  YVPosInt pos_min, pos_max;
  getBoundingBox(pos_min, pos_max);
  fig_file << "6 " << pos_min.xpos() << " " << pos_min.ypos() << " " <<
           pos_max.xpos() << " " << pos_max.ypos() << " " << endl;
  save_content(fig_file);
  fig_file << "-6" << endl;
}

// separate function as it will be reused by the YaVecFigure class
void YaVecCompound::save_content(ofstream &fig_file) {
  vector<YaVecElm*>::iterator members_iter;
  for ( members_iter = members.begin(); members_iter != members.end(); ++members_iter ) {
    (*members_iter)->saveElm(fig_file);
  }  
}

void YaVecCompound::getElmNearPos(YVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                                    list<YaVecElmHit> &hits) {
  vector<YaVecElm*>::iterator membersIt;
  for ( membersIt = members.begin(); membersIt != members.end(); ++membersIt ) {
    if (hierarchical || (typeid(**membersIt) != typeid(YaVecCompound)))
      (*membersIt)->getElmNearPos(pos, fuzzyFact, hierarchical, withCompounds, hits);
  }
}


void YaVecCompound::debugPrint(ostream &dest, bool verbose, int depth) {
  dest << string(depth, ' ') << "Compound with " << members.size() << " elements." << endl;
  if (verbose) {
    vector<YaVecElm*>::iterator membersIt;
    for ( membersIt = members.begin(); membersIt != members.end(); ++membersIt ) {
      (*membersIt)->debugPrint(dest, verbose, depth+4);
    }
    dest << endl;
  }
}
