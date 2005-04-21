// -*- c++ -*-
// \file  
// Copyright 2004 by Ulf Klaperski
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


#ifndef _YAVEC_H
#define _YAVEC_H _YAVEC_H

#include <vector>
#include <string>
#include "YaVecElm.h"
#include "YaVecCompound.h"
       
/// A vector figure class in Fig format
/*!
 * This class implements a complete vector figure in Fig format.
 *
 * It is derived from YaVecCompound since it shares a lot of code with
 * that class. Basically the figure is like an "invisible" compound.
 *
 * To create a figure, instantiate an object of this class.
 * Functions for creating objects (box, polyline, text,...) are inherited from
 * the YaVecCompound class and explained there.
 */
class YaVecFigure : public YaVecCompound {
public:
  /// constructor
  YaVecFigure();

  /// Draw the figure to this view.
  void drawView(YaVecView* view);

  // do we need a copy constructor?
  
  virtual void handleChange(YaVecElm*);

  /// Register a view showing this figure.
  void registerView(YaVecView* view) { views.push_back(view); }

  /// Unregister a view that has doesn't want to be updated any more.
  void unregisterView(YaVecView* view);

  /// Query the screen resolution in dpi
  bool setScreenDpi(int newScreenDpi);
  /// Set the screen resolution in dpi
  int getScreenDpi(void) { return screen_dpi; };

  /// Set the file resolution - should not be used (see file_dpi variable)
  int getFileDPi(void) { return file_dpi; };

  /// Return the scaling factor file_dpi/screen_dpi
  int scale(void) { return scale_fact; }

  void buildViews(void);
  /// Save the figure in the fig file 'filename'.
  bool save(string filename);

  /// Directly export into a foreign graphics format.
  bool exportFig2dev(string language, string filename);
  YaVecFigure& operator=(YaVecFigure& source);

  void updating(bool newUpdateStatus) { noViewUpdate = !newUpdateStatus; }
  
private:
  /// A flat list to be passed to views
  vector <YaVecElm*> members_flat;
  /// Indicate if members_flat is still valid or needs to be recreated
  bool members_flat_valid;
  /// Used to suspend view updating during several changes.
  bool noViewUpdate;
  /// Views don't reflect current figure and need redrawing.
  bool viewIsDirty;
  /// List of views which show this figure
  vector<YaVecView*> views;
  /// Resolution in fig file

  /*!
   * The default value of 1200 for file_dpi should not be changed, because that is what
   * xfig/transfig use in *.fig files.
   */
  int file_dpi;
  /// Resolutions for screen and file and the scaling factor between both
  int screen_dpi;
  int scale_fact;

  void sortMembersByDepth(void);
  struct membersDepthCmp {
    bool operator()(YaVecElm *x, YaVecElm *y) {
      return x->depth()>y->depth();
    }
  };
  
};

#endif /* _YAVEC_H */

