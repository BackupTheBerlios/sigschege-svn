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
#include <string>
#include "Event.h"
#include <EasyVecFigure.h>
#include <EVPosInt.h>

//! EventList class for handling events
/*!
 * This class provide function to create, access and delete events.
 */
class EventList {
 public:
  //! This constructor will create an empty EventList.
  /*!
   * \param evTime The point in time from which the first event is returned. 
   * \param evTime The point in time from which the first event is returned. 
   */
  EventList(double defaultSlope=0.0);

  //! This destructor will destroy the EventList and all stored events.
  ~EventList();

  //! Return a Pointer to the the first Event at or after a point in time.
  /*!
   * This function will return a Pointer to the first event that happens at or after
   * the given time.
   * \param evTime The point in time from which the first event is returned. 
   * \return Return a pointer to the event, NULL if no event occured after evTime.
   */
  Handle<Event> getEventAfter(double evTime); 

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
  Handle<Event> createEvent(const State &eventNewState, double eventDelay, const Handle<Event> *refEvent = 0);
  

  //! Delete an Events
  /*! 
   * This function will destroy the given event 
   * \param obsoleteEvent A pointer to the Event.
   * \return False if Event did not exist in that list.
   */
  bool   deleteEvent(Handle<Event> obsoleteEvent);

  //! Delete all Events in the list.
  void clear(void);
  
  //! Sort the list of events by time;
  void sort();  
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
  void setInitialState(State newInitialState) {
    initialState->setNewState(newInitialState);
  }

  //! Set the compound
  void setCompound(EasyVecCompound *newCompound);

  //! Set the Origin
  void setOrigin(EVPosInt newOrigin);

  //! Set the Origin
  void setOrigin(int xOffset, int yOffset);

  //! Set the Size
  void setSize(EVPosInt newSize);

  //! Set the Size
  void setSize(int width, int height);

  //! Set the type of events (binary or named).
  void setNamedEvents(bool named) {
    namedEvents = named;
  };

  //! Set the default slope, which is give to all new events.
  void setDefaultSlope(double defaultSlope) { cDefaultSlope = defaultSlope; }
  
  //! Set the compound to which the signal is drawn.
  void setCompound(EasyVecCompound *newCompound, int xOffset, int yOffset, int width, int height,
                   double timeStart, double timeEnd);

  //! Set the compound to which the signal is drawn.
  void setCompound(EasyVecCompound *newCompound, EVPosInt newOrigin, EVPosInt newSize,
                   double timeStart, double timeEnd);

  //! Paint the signal into the compound
  void paint(void);
  
private:
  vector< Handle<Event> > events;
  // pseudo event to define initial state - no reference event, no time/delay (time is "-infinity")
  Handle<Event> initialState; 
  EasyVecCompound *evListCompound;
  int compoundXOffset, compoundYOffset;
  int compoundWidth, compoundHeight;
  double compoundTimeStart, compoundTimeEnd;
  EVPosInt cOrigin, cSize;
  bool namedEvents;
  double cDefaultSlope;

  // internal helper function: calculate the position from the state (0, 1, Z)
  int vertPosFromState(State::drawStateType state, State::drawStateType newState=State::Illegal, double percentageNew=0.0);

};

#endif /* _H_EVENTLIST */

