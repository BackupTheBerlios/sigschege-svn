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


#ifndef _EASYVEC_H
#define _EASYVEC_H _EASYVEC_H

#include <vector>
#include <string>
#include "EasyVecElm.h"
#include "EasyVecElmCompound.h"
       
/// A vector figure class in Fig format

/*!
 * This class implements a complete vector figure in Fig format.
 *
 * It is derived from EasyVecElmCompound since it shares a lot of code with
 * that class. Basically the figure is like an "invisible" compound.
 *
 * To create a figure, instantiate an object of this class.
 * Functions for creating objects (box, polyline, text,...) are inherited from
 * the EasyVecElmCompound class and explained there.
 */
class EasyVec : public EasyVecElmCompound {
public:
  // constructor
  EasyVec();
  void draw_view(EasyVecView* view);
  // do we need a copy constructor?
  virtual void handle_change(EasyVecElm*);
  /// Register a view showing this figure
  void register_view(EasyVecView* view) { views.push_back(view); }
  /// 
  void unregister_view(EasyVecView* view);
  bool set_screen_dpi(int new_screen_dpi);
  /// Set the screen resolution in dpi
  int get_screen_dpi(void) { return screen_dpi; };
  /// Set the file resolution - should not be used (see file_dpi variable)
  int get_file_dpi(void) { return file_dpi; };
  /// Return the scaling factor file_dpi/screen_dpi
  int scale(void) { return scale_fact; }
  void build_views(void);
  /// Save the figure in the fig file 'filename'.
  bool save(string filename);
  /// Directly export into a foreign format.
  bool export_fig2dev(string language, string filename);

private:
  /// A flat list to be passed to views
  vector <EasyVecElm*> members_flat;
  /// Indicate if members_flat is still valid or needs to be recreated
  bool members_flat_valid;
  bool auto_update;
  /// List of views which show this figure
  vector<EasyVecView*> views;
  /// Resolution in fig file

  /*!
   * The default value of 1200 for file_dpi should not be changed, because that is what
   * xfig/transfig use in *.fig files.
   */
  int file_dpi;
  /// Resolutions for screen and file and the scaling factor between both
  int screen_dpi;
  int scale_fact;
};

#endif /* _EASYVEC_H */

