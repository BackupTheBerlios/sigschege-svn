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
#include "TimList.h"
#include "TimLabel.h"
#include "TimSignal.h"
#include "TimTime.h"
#include "Handle.t"
#include <string>
#include <YaVecFigure.h>
#include "EventList.h"
#include <vector>

//! The TimingDiagram Class is the toplevel class that contains the layout and the objects of a timing diagram.
/*!
 * This class represents a timing diagram comprised layout objects,timing diagram objects like signal or floating objects.
 * Also all used event will be administered by this class.
 */

class TimingDiagram : public TimList {
public:
  //! The standard constructor
  TimingDiagram(double newStartTime=0.0, double newEndTime=100.0);

  //! The standard destructor
  ~TimingDiagram();

  //! Export the Timing Diagram to an xfig file
  void exportFig(string file);

  //! Export the Timing Diagram to an encapsulated postscript (EPS)
  void exportEPS(string file);

  //! Export the Timing Diagram to any picture format (supported by fig2dev)
  void exportAny(string file, string format);
  
private:
  YaVec::FFigure cYaVec;

};
#endif // _H_TIMING
