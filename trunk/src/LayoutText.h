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
// $Id: $

#ifndef _H_LAYOUT_Text
#define _H_LAYOUT_Text

using namespace std;

#include "Layout.h"
#include <string>

/// Layout Text Class
/*!
 * This Text Layout Class can be used as header or footer
 */
class LayoutText : public Layout {
public:
  /// The standard constructor
  LayoutText();
  
  /// The standard destructor
  ~LayoutText();
  
  /// Return the ID of this layout object
  LayoutID getID();

  /// paint the layout object
  void paint(EasyVec& cEasyVec);

private:
  string cText;
};

#endif // _H_LAYOUT_TEXT
