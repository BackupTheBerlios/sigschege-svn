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

#ifndef _H_EVENT
#define _H_EVENT

using namespace std;

#include "Object.h"
#include <vector>

//! An Event Class stores the delay, the time and the dependencies to other events
/*!
 * An Event Class consists of two time values (delay and absolute time).
 * The delay time is the realative time to a parent event whereas the absolute time is the time measured against null.
 * Every Event can have several child events, but only one or no parent event.
 * If an event has no parent, then delay and the absolute time are equal.
 */
class Event { 
public:
  
  //! The standard constructor
  /*!
   * This constructor will create an event without a parent and with a delay and absolute time of zero.
   */
  Event();
  
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

  //! Return the absolute event time
  /*!
   * This function return the absolute event time, which will calculated of the absolute time of the parent and the event delay.
   * If no parent is set, the parent absolute time will assumed as zero.
   * \return Return the absolute event time.
   * \sa setDelay getDelay updateTime
   */
  const double getTime();

  //! update the absolute event time
  /*!
   * This function will update the absolute event time, which will calculated of the absolute time of the parent and the event delay.
   * If no parent is set, the parent absolute time will assumed as zero. If the new absolute time differ from the new one, the 
   * absolute time of all child events will be update as well.
   * \sa setDelay getDelay getTime
   */
  void  updateTime();


  //! Add a new child event
  /*!
   * Adds a new child event to the end of the child list
   * \param newChild pointer to Event that should be added to the child list
   * \sa hasChilds popChild insertChild moveChild getChild getChildCount
   */
  // BUGBUG void pushChild(Event* newChild);

  //! Register an event which references this event.  
  /*!
   * Insert an event into the referrers list.
   * \param newReferrer pointer to the event that should be added to the referrers list
   * \sa 
   */
  void registerReferrer(Event* newReferrer);

  //! Return a pointer of the child event at position index
  /*!
   * This function will return a pointer to the child event at position index
   * \param index position of the child obejct
   * \return pointer to the child event at position index
   * \sa hasChilds pushChild popChild insertChild moveChild getChildCount
   */
  // BUGBUG Event* getChild(size_t index);

  //! Get the pointer of the reference event
  /*!
   * This function returns the pointer of the reference event or NULL if it has no reference event
   * \return A pointer the the reference event
   * \sa hasreference setreference delreference
   */
  Event* getReference();

  //! Set the reference event
  /*!
   * The reference event to which the delay is relative to.
   * \param new_reference The pointer to the new reference event
   * \sa hasreference getreference delreference
   */
  void setReference(Event* new_reference);

  //! Delete the reference of this event
  /*!
   * Delete the reference event. The parent event will NOT be destroyed by this function.
   * \sa hasreference getreference setreference
   */
  void delReference();

  
private:
  double EventDelay;
  double EventTime;
  Event* reference;
  vector<Event*> referrers;
};

#endif
