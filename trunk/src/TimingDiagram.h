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
#include "TimLabel.h"
#include "LayoutList.h"
#include "Event.h"
#include "EventList.h"
#include <string>
#include <EasyVecFigure.h>

//! The TimingDiagram Class is the toplevel class that contains the layout and the objects of a timing diagram.
/*!
 * This class represents a timing diagram comprised layout objects,timing diagram objects like signal or floating objects.
 * Also all used event will be administered by this class.
 */
class TimingDiagram {
public:
  /// The standard constructor
  TimingDiagram();

  /// The standard destructor
  ~TimingDiagram();

  /// Create a empyt Layout Text Object
  TimLabel* createTimLabel();

  /// Create a Layout Text Object with the Text newText
  TimLabel* createTimLabel(string newText);

  /// Set the width of the whole TimingDiagram Diagram
  void setWidth(int new_width);

  /// Add a Layout Object to the end of cLayoutList
  void addLast(Layout *newLayout);
    
  /// Paint Timing Diagram
  void paint();

  ///Save the Timing Diagram
  void save(string filename);

  /// set the top Border
  void setBorderTop(int newBorder);

  /// set the left Border
  void setBorderLeft(int newBorder);

  /// set the right Border
  void setBorderRight(int newBorder);

  /// set the botom Border
  void setBorderBottom(int newBorder);

  /// return the top Border
  int getBorderTop();

  /// return the left Border
  int getBorderLeft();

  /// return the right Border
  int getBorderRight();

  /// return the botom Border
  int getBorderBottom();

private:
  int        cWidth;
  EasyVecFigure    cEasyVec;
  LayoutList cLayoutList;
  EventList  cEventList;
  int        cBorderTop;
  int        cBorderLeft;
  int        cBorderRight;
  int        cBorderBottom;
};
#endif // _H_TIMING
