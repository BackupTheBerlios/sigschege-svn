// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs, Ulf Klaperski
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

#ifndef _H_EVENT
#define _H_EVENT

using namespace std;

#include "Handle.t"
#include <vector>
#include <string>

//! An Event Class stores the delay, the time and the dependencies to other events
/*!
 * An Event Class consists of two time values (delay and absolute time).
 * The delay time is the relative time to a parent event whereas the absolute time is the time measured against null.
 * Every Event can have several referring events, but only one or no reference event.
 * If an event has no reference event, the delay and the absolute time are equal.
 */
class Event { 
public:
  

  //! A general constructor
  /*!
   * This constructor will create an event with all properties defined.
   * \param setNewState A string defining the new state. Default: "0".
   * \param setEventDelay The event delay (absolute or to its reference event). Default: 0.
   * \param setReference A pointer to the reference event handle. If not given, event is absolute.
   * \param setSlopeTime The time for the transition from the old to the new state.
   */
  Event(const string &setNewState = "0", double setEventDelay = 0.0,
        const Handle<Event> *setReference = 0, double setSlopeTime = 0.0);

  
  //! The standard destructor
  ~Event();
  
  //! Set a new Delay value
  /*!
   * Set a new Delay for this Event. If the delay differ from the old one the updateTime function of this event and his child events will be called.
   * \param delay New Delay for this event
   * \sa getDelay getTime updateTime
   */
  void setDelay(const double delay);
  
  //! Return the event delay.
  /*!
   * This function will return the event delay.
   * \return Return the Delay of this Event
   * \sa setDelay getTime updateTime
   */
  const double getDelay();

  //! Set a new Slope value
  /*!
   * Set a new Slope for this Event. If the delay differ from the old one the updateTime function of this event and his child events will be called.
   * \param slope New Slope for this event
   * \sa getSlope getTime updateTime
   */
  void setSlope(const double slope);
  
  //! Return the event slope.
  /*!
   * This function will return the event slope.
   * \return Return the Slope of this Event
   * \sa setSlope getTime updateTime
   */
  const double getSlope();

  //! Set a new reference level.
  /*!
   * Set a new reference level for this Event. If the reference level differs from the old one
   the updateTime function of this event and his child events will be called. The reference level
   defines, which level of the referenced event's slope triggers this event.
   * \param rlevel New reference level for this event
   * \sa getRefLevel getTime updateTime
   */
  void setRefLevel(const int rlevel);
  
  //! Return the reference level.
  /*!
   * This function will return the reference.
   * \return Return the reference level of this Event
   * \sa setRefLevel getTime updateTime
   */
  const int getRefLevel();


  
  //! Return the absolute event time
  /*!
   * This function return the absolute event time, which will calculated of the absolute time of the parent and the event delay.
   * If no parent is set, the parent absolute time will assumed as zero.
   * \param levelPercent Which level of the slope has been reached. 0 is start, 50 the middle and
   100 the end of event. It defaults to 50.
   * \return Return the absolute event time.
   * \sa setDelay getDelay updateTime
   */
  const double getTime(int levelPercent = 50);

  //! update the absolute event time
  /*!
   * This function will update the absolute event time, which will calculated of the absolute time of the parent and the event delay.
   * If no parent is set, the parent absolute time will assumed as zero. If the new absolute time differ from the new one, the 
   * absolute time of all child events will be update as well.
   * \sa setDelay getDelay getTime
   */
  void  updateTime();


  //! Register an event which references this event.  
  /*!
   * Insert an event into the referrers list.
   * \return False if the event already  existed, true otherwise.
   * \param newReferrer pointer to the event that should be added to the referrers list
   * \sa 
   */
  bool registerReferrer(Handle<Event> newReferrer);

  //! Unregister an event which references this event.  
  /*!
   * Remove an event from the referrers list. This is used if either the referring event is
   * deleted, converted to an absolute event or refers to another event.
   * \return False if the event did not exist, true otherwise.
   * \param newReferrer pointer to the event that should be added to the referrers list
   * \sa unregisterReferrer
   */
  bool unregisterReferrer(Handle<Event> newReferrer);

  //! Get the pointer of the reference event.
  /*!
   * This function returns the pointer of the reference event or NULL if it has no reference event
   * \return A pointer the the reference event
   * \sa registerReferrer
   */
  Handle<Event> getReference();

  //! Set the reference event.
  /*!
   * The reference event to which the delay is relative to. This command will fail if
   * a loop of Events would be created.
   * \param new_reference The pointer to the new reference event
   * \return True if successful.
   * \sa hasreference getreference delreference
   */
  bool setReference(Handle<Event> new_reference);

  //! Delete the reference of this event
  /*!
   * Delete the reference event. The parent event will NOT be destroyed by this function.
   * \sa hasreference getreference setreference
   */
  void delReference();

  //! Set the new state which is created by this event
  /*!
   * This sets the new state of the event. States are defined simply as strings.
   * For binary signals use "1", "0", "X", "Z", these will be mapped to corresponding views.
   * \return The old new state is returned.
   * \sa getNewState
   */
  string setNewState(string newNewState) {
    string tmp = newState;
    newState = newNewState;
    return tmp;
  }
  
  //! Get the new state which is created by this event
  /*!
   * This returns the new state of the event. 
   * \sa setNewState
   */
  string &getNewState(void) {
    return newState;
  }
  
  //! Return the current reference count 
  int objRefCount() { return refCount; }

  // Must be a friend to access the private functions for modifying the reference count
  friend class Handle<Event>;
  
private:
  double eventDelay;
  int refLevel;
  double eventTime;
  double slopeTime;
  string newState;
  int refCount;
  Handle<Event> reference;
  vector< Handle<Event> > referrers;

  //! Increment the reference count - only for use by Handle class!
  void incrementRefcount();
  //! Decrement the reference count - only for use by Handle class!
  void decrementRefcount();
};

#endif /* _H_EVENT */
