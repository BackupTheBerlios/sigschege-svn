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


#ifndef _EASYVECELMTEXT_H
#define _EASYVECELMTEXT_H _EASYVECELMTEXT_H 

#include "EVPosInt.h"
#include "EasyVecElm.h"
#include "EasyVecElmCompound.h"
#include "EasyVecView.h"
#include <vector>
extern "C" {
#include <ft2build.h>
#include FT_FREETYPE_H
}

using namespace std;

class EasyVecElmText : public EasyVecElm {
public:
  EasyVecElmText();
  EasyVecElmText(EasyVecElmCompound* parent_compound, EasyVec* master_compound);
  virtual void get_limits(EVPosInt &upper_left, EVPosInt &lower_right);
  vector<EasyVecElm*> flat_list() { vector<EasyVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(EasyVecView* view);
  virtual void save_elm(ofstream &fig_file);
  bool set_text(const string &new_text);
  bool set_size(int new_size);
  bool set_origin(EVPosInt new_origin);
  static bool init_freetype(void); // will be called by EasyVec class

private:
  EVPosInt elm_origin;
  string elm_text;
  int elm_font, elm_size;
  static FT_Library  freetype_lib;
  static bool EasyVecElmText::freetype_already_initialized;
  FT_Face face;
  int text_height, text_width; // cache information to reduce cpu effort

  bool init_EasyVecElmText();
  void update_dimensions(); // must be called by all methods which change text size!

};



#endif /* _EASYVECELMTEXT_H */

