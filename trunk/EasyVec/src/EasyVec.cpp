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

#include "EasyVec.h"
#include "EasyVecElmText.h"
#include <fstream>
#include <iostream>
#include <cstdlib>



EasyVec::EasyVec() : EasyVecElmCompound() {

  // ugly hack, initFreetype must be called only once, we call it here, because
  // creation of a new figure won't happen too often...
  EasyVecElmText::initFreetype(); 
  auto_update = false;
  members_flat_valid = false;
  file_dpi = 1200;
  set_screen_dpi(80);
  figure = this;
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
  members_flat = flatList();
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
  fig_file << file_dpi << " 2" << endl;
  save_content(fig_file); // method from base class EasyVecElmCompound to save compound content
  return true;
}

bool EasyVec::export_fig2dev(string language, string filename) {
  string tmpfigfile = filename + "_tmp.fig";
  string fig2dev_cmd = "fig2dev ";
  save(tmpfigfile);
  fig2dev_cmd += "-L " + language + (EasyVecElmText::fig2dev_fontfix()? " ": " -F ") + tmpfigfile + " " + filename;

  cout << "Running: " << fig2dev_cmd << endl;
  
  int ret_stat = system(fig2dev_cmd.c_str());

  fig2dev_cmd = "rm -f ";
  fig2dev_cmd += tmpfigfile;
  system(fig2dev_cmd.c_str());

  return ret_stat==0;
}
