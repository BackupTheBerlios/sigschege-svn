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
// $Id: TimLabel.h 58 2004-11-10 21:12:15Z suupkopp $

#ifndef _H_TIMSIGNAL
#define _H_TIMSIGNAL

using namespace std;

#include "LayoutObject.h"
#include "EventList.h"
#include <string>

//! Signal Call
class TimSignal : public LayoutObject, protected EventList {
public:
  //! The standard constructor
  TimSignal(double defaultSlope=0.0);

  //! Create a Signal with Text
  TimSignal(string signalLabel);

  //! The standard destructor
  ~TimSignal();

  //! Set the xoffset for the signal
  void setSigOffset(int sigOffset);

  //! Set a new Text
  void setText(string newText);

  //! Paint the Signal
  void paint(void);

  LayoutObject::setCompound;
  EventList::createEvent;
  EventList::deleteEvent;
  EventList::debugEvents;
  EventList::setNamedEvents;
private:
  string    cText;
  int       cFontType;
  int       cFontSize;
  int       cSigOffset;
};

#endif
