// -*- c++ -*-
// \file 
// Copyright 2005 by Ulf Klaperski
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

#ifndef _H_TIMINGOBJECT
#define _H_TIMINGOBJECT

#include "LayoutObject.h"

/// Base class for elements of a TimList.
/*!
 * This class provides common functionality for events of a TimList.
 */
class TimingObject : public LayoutObject {
 public:
  /// Standard constructor.
  TimingObject();
  
  /// General constructor.
  TimingObject(LayoutObject *newReference, YaVec::PosInt origin, YaVec::PosInt size, int sigOffset = 0);
    
  //! Set the horizontal offset for the signal part.
  void setSigOffset(int sigOffset) { cSigOffset = sigOffset; }

 protected:
  double cStartTime, cEndTime;
  int cSigOffset;
};

inline TimingObject::TimingObject():
  LayoutObject(), cSigOffset(0) {}

#endif // _H_TIMINGOBJECT
