// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs
//
// This file is part of Sigschege - Signal Schedule Generator
// 
// #############################################################################
//
// Sigschege is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// Sigschege is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the Sigschege sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#ifndef _H_TIMLABEL
#define _H_TIMLABEL

using namespace std;

#include "LayoutObject.h"
#include <string>

/// Layout Text Class
/*!
 * This Text Layout Class can be used as header or footer
 */
class TimLabel : public LayoutObject {
public:
  /// The standard constructor
  TimLabel();
  
  /// Create a Text object with newText
  TimLabel(string newText);

  /// The standard destructor
  ~TimLabel();
  
  /// Set a new Text
  void setText(string newText);

  /// Set the Font Type
  void setFontType(int new_font);

  /// Set the Font Size
  void setFontSize(int new_size);

  /// paint the layout object
  void paint(void);

  
private:
  string cText;
  int cFontType;
  int cFontSize;
};

#endif // _H_LAYOUT_TEXT
