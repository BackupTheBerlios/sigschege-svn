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

//! Singal Call
class TimSignal : public LayoutObject {
public:
  //! The standard constructor
  TimSignal();

  //! Create a Signal with Text
  TimSignal(string signalLabel);

  //! The standard destructor
  ~TimSignal();

  //! Create a new Event
  /*!
   * This function creates a new Event.
   * \return A pointer to the new event.
   * \sa deleteEvent 
   */
  Handle<Event> createEvent();

  //! Create a new Event
  /*!
   * This function creates a new Event.
   * \param refEvent A Handle to the referenced event. If it is a 0 pointer the delay is the absolute time.
   * \param eventDelay The delay to the reference event, or the absolute time if there is no reference event.
   * \param eventNewState The new state created by the event.
   * \return A pointer to the new event.
   * \sa deleteEvent 
   */
  Handle<Event> createEvent(const string &eventNewState, double eventDelay, const Handle<Event> *refEvent = 0);
  

  //! Delete an Events
  /*! 
   * This function will destroy the given event 
   * \param obsoleteEvent A pointer to the Event.
   * \return False if Event did not exist in that list.
   */
  bool   deleteEvent(Handle<Event> obsoleteEvent);

  //! Set the xoffset for the signal
  void setSigOffset(int sigOffset);

  //! Set a new Text
  void setText(string newText);

  //! Paint the Signal
  void paint(void);

private:
  EventList cEventList;
  string    cText;
  int       cFontType;
  int       cFontSize;
  int       cSigOffset;
};

#endif
