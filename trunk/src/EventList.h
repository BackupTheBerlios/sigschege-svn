// -*- c++ -*-
// \file 
// Copyright 2004, 2005, 2006 by Ingo Hinrichs, Ulf Klaperski
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

#include <vector>
#include <string>
#include "Event.h"
#include <YaVecFigure.h>
#include <YVPosInt.h>

//! EventList class for handling events
/*!
 * This class provide function to create, access and delete events.
 */
class EventList {
 public:
  //! This constructor will create an empty EventList.
  EventList(double defaultSlope=0.0);

  //! This destructor will destroy the EventList and all stored events.
  ~EventList();

  //! Return a Pointer to the the first Event at or after a point in time.
  /*!
   * This function will return a Pointer to the first event that happens at or after
   * the given time.
   * \param evTime The point in time from which the first event is returned. 
   * \param percentageLevel The level to which the event must have been completed.
   * Default is 0, which means the event can just have started.
   * \param newState Limit search to events with a transition to the state newState.
   * To find an event regardless of the new state leave the default value of an empty string.
   * \return Return a pointer to the event, NULL if no event occured after evTime.
   */
  Handle<Event> getEventAfter(double evTime, int percentageLevel=0, std::string newState=std::string("")); 

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
  Handle<Event> createEvent(const std::string &eventNewState, double eventDelay, Handle<Event> *refEvent = 0);
  

  //! Delete an Event.
  /*! 
   * This function will destroy the given event 
   * \param obsoleteEvent A pointer to the Event.
   * \return False if Event did not exist in that list.
   */
  bool deleteEvent(Handle<Event> obsoleteEvent);

  //! Delete all Events in the list.
  void clear(void);
  
  //! Sort the list of events by time;
  void sort();
  /// Helper function for sort to compare two events by time.
  struct evTimeCmp {
    bool operator()(Handle<Event> x, Handle<Event> y) {
      return x.Object()->getTime()<y.Object()->getTime();
    }
  };

  //! A function for debugging the event list - not for general use! 
  void debugEvents(void);

  //! Set the initial state of the EventList.
  /*!
   * The initial state is the value used before the first actual event.
   */
  void setInitialState(std::string newInitialState) {
    initialState->setNewState(newInitialState);
  }

  //! Set the type of events (binary or named).
  void setNamedEvents(bool named) {
    namedEvents = named;
  };

  //! Set the default slope, which is give to all new events.
  void setDefaultSlope(double defaultSlope) { cDefaultSlope = defaultSlope; }
  
  //! Paint the signal into the compound
  void paint(void);
  
protected:
  /// List of all value transistions of this signal.
  std::vector< Handle<Event> > events;
  /// pseudo event to define initial state - no reference event, no time/delay (time is "-infinity")
  Handle<Event> initialState;
  /// Use named events (e.g. bus values). 
  bool namedEvents;
  /// Default slope for new events.
  double cDefaultSlope;
  /// The state map, which defines how to visualize states.
  StateMap smap;
  
};

#endif /* _H_EVENTLIST */

