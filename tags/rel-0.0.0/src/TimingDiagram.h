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

#include "LayoutObject.h"
#include "TimLabel.h"
#include "TimSignal.h"
#include "Handle.t"
#include <string>
#include <EasyVecFigure.h>
#include "EventList.h"
#include <vector>

//! The TimingDiagram Class is the toplevel class that contains the layout and the objects of a timing diagram.
/*!
 * This class represents a timing diagram comprised layout objects,timing diagram objects like signal or floating objects.
 * Also all used event will be administered by this class.
 */
class TimingDiagram {
public:
  //! The standard constructor
  TimingDiagram();

  //! The standard destructor
  ~TimingDiagram();

  //! Draw the whole Timing Diagram
  void paint();

  //! Add a LayoutObject to the Objectlist
  void addLast(Handle<LayoutObject> newLayoutObject);

  //! Export the Timing Diagram to a xfig file
  void exportFig(string file);

  //! Create a empty Timing Diagram Label Object
  Handle<TimLabel> createLabel();

  //! Create a empty Timing Diagram Signal Object
  Handle<TimSignal> createSignal();
  
private:
  vector< Handle<LayoutObject> > cLayoutList;
  EasyVecFigure    cEasyVec;
};
#endif // _H_TIMING
