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


#ifndef _EASYVEC_H
#define _EASYVEC_H _EASYVEC_H

#include <vector>
#include <string>
#include "EasyVecElm.h"
#include "EasyVecElmCompound.h"
       

class EasyVec : public EasyVecElmCompound {
public:
  // constructor
  EasyVec();
  void draw_view(EasyVecView* view);
  // do we need a copy constructor?
  virtual void handle_change(EasyVecElm*);
  void register_view(EasyVecView* view) { views.push_back(view); }
  void unregister_view(EasyVecView* view);
  bool set_screen_dpi(int new_screen_dpi);
  int get_screen_dpi(void) { return screen_dpi; };
  int get_file_dpi(void) { return file_dpi; };
  int scale(void) { return scale_fact; }
  void build_views(void);
  bool save(string filename);
private:
  vector <EasyVecElm*> members_flat;
  bool members_flat_valid;
  bool auto_update;
  vector<EasyVecView*> views;
  int screen_dpi, file_dpi, scale_fact;
};

#endif /* _EASYVEC_H */

