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

  //! Return a Pointer to the the first Event at or after a point in time.
  /*!
   * This function will return a Pointer to the first event that happens at or after
   * the given time.
   * \param evTime The point in time from which the first event is returned. 
   * \return Return a pointer to the event, NULL if no event occured after evTime.
   */
  Event* getEventAfter(double evTime); 

  //! Create a new Event
  /*!
   * This function creates a new Event.
   * \return A pointer to the new event.
   * \sa deleteEvent 
   */
  Event* createEvent();
  
  //! Delete an Events
  /*! 
   * This function will destroy the given event 
   * \param obsoleteEvent A pointer to the Event.
   * \return False if Event did not exist in that list.
   */
  bool   deleteEvent(Event* obsoleteEvent);

  //! Delete all Events in the list.
  void clear(void);
  
  //! Sort the list of events by time;
  void sort();  
  struct evTimeCmp {
    bool operator()(Event* x, Event* y) {
      return x->getTime()<y->getTime();
    }
  };

  //! A function for debugging the event list - not for general use! 
  void debugEvents(void);
  
private:
  vector<Event*> events;
  
};

#endif /* _H_EVENTLIST */

