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

#ifndef _H_TIMING
#define _H_TIMING

using namespace std;

#include "Layout.h"
#include "LayoutText.h"
#include "LayoutList.h"
#include "Event.h"
#include "EventList.h"
#include <string>
#include <EasyVec.h>

//! The Timing Class is the toplevel class that contains the layout and the objects of a timing diagram.
/*!
 * This class represents a timing diagram comprised layout objects,timing diagram objects like signal or floating objects.
 * Also all used event will be administered by this class.
 */
class Timing {
public:
  /// The standard constructor
  Timing();

  /// The standard destructor
  ~Timing();

  /// Create a empyt Layout Text Object
  LayoutText* createLayoutText();

  /// Create a Layout Text Object with the Text newText
  LayoutText* createLayoutText(string newText);

  /// Set the width of the whole Timing Diagram
  void setWidth(int new_width);

  /// Add a Layout Object to the end of cLayoutList
  void addLast(Layout *newLayout);
    
  /// Paint Timing Diagram
  void paint();

  ///Save the Timing Diagram
  void save(string filename);
private:
  int        cWidth;
  EasyVec    cEasyVec;
  LayoutList cLayoutList;
  EventList  cEventList;
};
#endif // _H_TIMING
