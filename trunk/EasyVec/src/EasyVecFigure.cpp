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

#include "EasyVecFigure.h"
#include "EasyVecText.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>



EasyVecFigure::EasyVecFigure() : EasyVecCompound() {

  // ugly hack, initFreetype must be called only once, we call it here, because
  // creation of a new figure won't happen too often...
  EasyVecText::initFreetype(); 
  noViewUpdate = false;
  viewIsDirty = true;
  members_flat_valid = false;
  file_dpi = 1200;
  setScreenDpi(80);
  figure = this;
}

bool EasyVecFigure::setScreenDpi(int newScreenDpi) {
  if (newScreenDpi>0) {
    screen_dpi = newScreenDpi;
    scale_fact = file_dpi/screen_dpi;
    handleChange(0);
    return true;
  } else return false;
}

void EasyVecFigure::buildViews(void) {
  if (!noViewUpdate) {
    for (vector<EasyVecView*>::iterator views_iter = views.begin();
         views_iter != views.end(); views_iter++) {
      (*views_iter)->clear();
      drawView(*views_iter);
    }
    viewIsDirty = false;
  } else {
    viewIsDirty = true;
  }
}

void EasyVecFigure::drawView(EasyVecView* view) {
  if (!noViewUpdate) {
    members_flat = flatList();
    sortMembersByDepth();
    members_flat_valid = true;
    vector<EasyVecElm*>::iterator members_iter;
    cout << "================================================================================" << endl;
    for ( members_iter = members_flat.begin(); members_iter != members_flat.end(); ++members_iter ) {
      cout << "DRAWING: ";
      (*members_iter)->debugPrint(cout, true, 10);
      (*members_iter)->draw(view);
    }
    viewIsDirty = false;
  } else {
    viewIsDirty = true;
  }
}

void EasyVecFigure::handleChange(EasyVecElm* changed_element) {
  buildViews();
}

void EasyVecFigure::unregisterView(EasyVecView* view) {
  vector<EasyVecView*>::iterator views_iter = views.begin();
  while (views_iter != views.end()) {
    if (*views_iter == view) {
      views_iter = views.erase(views_iter);
    } else {
      views_iter++;
    }
  }
}

EasyVecFigure& EasyVecFigure::operator=(EasyVecFigure& source) {
  copy_members(source);
  file_dpi = source.file_dpi;
  screen_dpi = source.screen_dpi;
  members_flat_valid = false;
  buildViews();
  return *this;
}

bool EasyVecFigure::save(string filename) {
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
  save_content(fig_file); // method from base class EasyVecCompound to save compound content
  return true;
}

bool EasyVecFigure::exportFig2dev(string language, string filename) {
  string tmpfigfile = filename + "_tmp.fig";
  string fig2dev_cmd = "fig2dev ";
  save(tmpfigfile);
  fig2dev_cmd += "-L " + language + (EasyVecText::fig2dev_fontfix()? " ": " -F ") + tmpfigfile + " " + filename;

  cout << "Running: " << fig2dev_cmd << endl;
  
  int ret_stat = system(fig2dev_cmd.c_str());

  fig2dev_cmd = "rm -f ";
  fig2dev_cmd += tmpfigfile;
  system(fig2dev_cmd.c_str());

  return ret_stat==0;
}

void EasyVecFigure::sortMembersByDepth(void) {
  ::sort(members_flat.begin(), members_flat.end(), membersDepthCmp());
}
