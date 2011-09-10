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
#include <algorithm>
#include "YaVecCompound.h"
#include "YaVecPolyline.h"
#include "YaVecArc.h"
#include "YaVecBox.h"
#include "YaVecText.h"

using namespace std;

namespace YaVec {

  FArc* FCompound::arc(PosInt p1, PosInt p2, PosInt p3, bool isPieWedge) {
    FArc* new_arc = new FArc(static_cast<FCompound*>(this), figure,
                                     p1, p2, p3, isPieWedge);
    members.push_back(new_arc);
    return new_arc;
  
  }

  FArc* FCompound::arc(PosInt center, double radius, bool clockwise,
                               double angle1, double angle3, bool isPieWedge) {
    FArc* new_arc = new FArc(static_cast<FCompound*>(this), figure,
                                     center, radius, clockwise, angle1, angle3, isPieWedge);
    members.push_back(new_arc);
    return new_arc;  
  }


  FPolyline* FCompound::polyline() {
    FPolyline* new_polyline = new FPolyline(static_cast<FCompound*>(this), figure);
    members.push_back(new_polyline);
    return new_polyline;
  }

  FBox* FCompound::box(PosInt upper_left, PosInt lower_right) {
    FBox* new_box = new FBox(static_cast<FCompound*>(this), figure, upper_left, lower_right);
    members.push_back(new_box);
    return new_box;
  }

  FText* FCompound::text() {
    FText* new_text = new FText(static_cast<FCompound*>(this), figure);
    members.push_back(new_text);
    return new_text;
  }

  FCompound* FCompound::compound() {
    FCompound* new_compound = new FCompound(static_cast<FCompound*>(this), figure);
    members.push_back(new_compound);
    return new_compound;
  }


  bool FCompound::remove(YaVecElm* elm) {
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
  void FCompound::getBoundingBox(PosInt &upper_left, PosInt &lower_right) {
    vector<YaVecElm*>::iterator members_iter = members.begin();
    PosInt member_point_min, member_point_max;
    if (members_iter==members.end()) {
      upper_left = PosInt(0,0); // no points! how should we behave???
      lower_right = PosInt(0,0);
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


  vector<YaVecElm*> FCompound::flatList() {
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

  void FCompound::clear(void) {
    YaVecElm* last_elm;
    while (members.size()>0) {
      last_elm = members.back();
      delete last_elm; // delete the object the pointer points to
      members.pop_back(); // remove the pointer from the list
    }
  }


  /*!
    This function copies all member elements of another compound to this compound.
    It is used by the assignment operators of FCompound and the derived
    FFigure class.
    Please note that this function does not clear the members of this compound,
    you must call the clear function yourself if you want this.
  */
  void FCompound::copy_members(FCompound& source) {
    vector<YaVecElm*>::iterator source_members_iter;
    FText* new_text;
    FBox* new_box;
    FPolyline* new_polyline;
    FCompound* new_compound;
    
    for (source_members_iter = source.members.begin();
         source_members_iter != source.members.end();
         ++source_members_iter ) {
      if (typeid(**source_members_iter) == typeid(FText)) {
        new_text = text();
        *new_text = *(static_cast<FText*>(*source_members_iter));
      } else if (typeid(**source_members_iter) == typeid(FBox)) {
        new_box = box(PosInt(0,0),PosInt(0,0));
        *new_box = *(static_cast<FBox*>(*source_members_iter));
      } else if (typeid(**source_members_iter) == typeid(FPolyline)) {
        new_polyline = polyline();
        *new_polyline = *(static_cast<FPolyline*>(*source_members_iter));
      } else if (typeid(**source_members_iter) == typeid(FCompound)) {
        new_compound = compound();
        *new_compound = *(static_cast<FCompound*>(*source_members_iter));
      } else {
        throw string("Error: Unknown type");
      }
    }
  }

  FCompound& FCompound::operator=(FCompound& source) {
    clear();
    copy_members(source);
    return *this;
  }


  void FCompound::handleChange(YaVecElm* changed_element) {
    if (parent != 0) parent->handleChange(changed_element);
  }


  void FCompound::saveElm(ofstream &fig_file) {
    PosInt pos_min, pos_max;
    getBoundingBox(pos_min, pos_max);
    fig_file << "6 " << pos_min.xpos() << " " << pos_min.ypos() << " " <<
      pos_max.xpos() << " " << pos_max.ypos() << " " << endl;
    save_content(fig_file);
    fig_file << "-6" << endl;
  }

  // separate function as it will be reused by the FFigure class
  void FCompound::save_content(ofstream &fig_file) {
    vector<YaVecElm*>::iterator members_iter;
    for ( members_iter = members.begin(); members_iter != members.end(); ++members_iter ) {
      (*members_iter)->saveElm(fig_file);
    }  
  }

  void FCompound::getPoints(vector<PosInt> &points, bool hierarchical, bool withCompounds) {
    if (withCompounds) {
      PosInt upper_left;
      PosInt lower_right;
      getBoundingBox(upper_left, lower_right);
      points.push_back(upper_left);
      points.push_back(PosInt(lower_right.xpos(), upper_left.ypos()));
      points.push_back(PosInt(upper_left.xpos(), lower_right.ypos()));
      points.push_back(lower_right);    
    }
    if (hierarchical) {
      vector<YaVecElm*>::iterator membersIt;
      for ( membersIt = members.begin(); membersIt != members.end(); ++membersIt ) {
        //if (hierarchical || (typeid(**membersIt) != typeid(FCompound)))
        (*membersIt)->getPoints(points, hierarchical, withCompounds);
      }
    }
  }

  void FCompound::debugPrint(ostream &dest, bool verbose, int depth) {
    dest << string(depth, ' ') << "Compound with " << members.size() << " elements." << endl;
    if (verbose) {
      vector<YaVecElm*>::iterator membersIt;
      for ( membersIt = members.begin(); membersIt != members.end(); ++membersIt ) {
        (*membersIt)->debugPrint(dest, verbose, depth+4);
      }
      dest << endl;
    }
  }

}
