// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ingo Hinrichs, Ulf Klaperski
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

#include "TimingObject.h"
#include "TimText.h"
#include <string>

/// Layout Text Class
/*!
 * This Text Layout Class can be used as header or footer
 */
class TimLabel : public TimingObject, public TimText {
public:
  /// The standard constructor
  TimLabel();
  
  /// Create a Text object with newText
  TimLabel(std::string newText);

  /// The standard destructor
  ~TimLabel();
  
  /// paint the layout object
  void paint(void);

  /// Function needed by the TimText base class to query the text area.
  virtual void getTextGeometry(YaVec::PosInt &upperLeft, YaVec::PosInt &lowerRight);
  
private:

};

#endif // _H_LAYOUT_TEXT
