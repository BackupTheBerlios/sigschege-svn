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

#ifndef _H_EVENTLIST
#define _H_EVENTLIST

using namespace std;

#include <vector>
#include "Event.h"

//! EventList class for handling events
/*!
 * This class provide function to create, access and delete events.
 */
class EventList {
 public:
  //! This constructor will create a empty EventList
  EventList();

  //! This destructor will destroy the EventList and all stored events.
  ~EventList();

  //! Return a Pointer to the Event at position index
  /*!
   * This function will return a Pointer to the event stored at position index
   * \return Return a pointer to the event at position index
   */
  //Event* getEvent(size_t index); BUGBUG

  //! Create a new Event
  /*!
   * This function creates a new Event.
   * \return A pointer to the new event.
   * \sa deleteEvent 
   */
  Event* createEvent();
  
  //! Delete an Event
  /*! 
   * This function will destroy the given event 
   * \param obsoleteEvent A pointer to the Event.
   * \return False if Event did not exist in that list.
   */
  bool   deleteEvent(Event* obsoleteEvent);

  //! Sort the list of events by time;
  void sort();
  
struct evTimeCmp {
  bool operator()(Event* x, Event* y) {
    return x->getTime()<y->getTime();
  }
};

private:
  vector<Event*> events;
  
};

#endif /* _H_EVENTLIST */

