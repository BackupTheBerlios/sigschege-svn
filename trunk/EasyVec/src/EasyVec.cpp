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

#include "EasyVec.h"
#include "EasyVecElmText.h"
#include <fstream>
#include <iostream>



EasyVec::EasyVec() : EasyVecElmCompound() {
  
  EasyVecElmText::init_freetype(); //ugly hack
  auto_update = false;
  members_flat_valid = false;
  file_dpi = 1200;
  set_screen_dpi(80);
  master = this;
}

bool EasyVec::set_screen_dpi(int new_screen_dpi) {
  if (new_screen_dpi>0) {
    screen_dpi = new_screen_dpi;
    scale_fact = file_dpi/screen_dpi;
    handle_change(0);
    return true;
  } else return false;
}

void EasyVec::build_views(void) {
  for (vector<EasyVecView*>::iterator views_iter = views.begin();
       views_iter != views.end(); views_iter++) {
    (*views_iter)->clear();
    draw_view(*views_iter);
  }
}

void EasyVec::draw_view(EasyVecView* view) {
  members_flat = flat_list();
  members_flat_valid = true;
  vector<EasyVecElm*>::iterator members_iter;
  for ( members_iter = members.begin(); members_iter != members.end(); ++members_iter ) {
    (*members_iter)->draw(view);
  }
}

void EasyVec::handle_change(EasyVecElm* changed_element) {
  build_views();
}

void EasyVec::unregister_view(EasyVecView* view) {
  vector<EasyVecView*>::iterator views_iter = views.begin();
  while (views_iter != views.end()) {
    if (*views_iter == view) {
      views_iter = views.erase(views_iter);
    } else {
      views_iter++;
    }
  }
}


bool EasyVec::save(string filename) {
  ofstream fig_file;
  fig_file.open(filename.c_str(), ios::out);
  if (!fig_file) return false;
  fig_file << "#FIG 3.2" << endl;
  fig_file << "Landscape" << endl;
  fig_file << "Inches" << endl;
  fig_file << "A4" << endl;
  fig_file << "100" << endl;
  fig_file << "Single" << endl;
  fig_file << -2 << endl;
  fig_file << "1200 2" << endl;
  save_content(fig_file);
  return true;
}
