// -*- c++ -*-
/// \file 
 
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
// $Id: $

#ifndef _H_EVENT
#define _H_EVENT

using namespace std;

#include "Object.h"
#include <vector>

//! A Event Class store the delay, the time and the dependencies to other events
/*!
 * A Event Class consists of two time values (delay and absolute time).
 * The delay time is the realative time to a parent event whereas the aboslute time is the time measured against null.
 * Every Event can have several child events, but only one or no parent event.
 * If an event has no parent, then delay and the absolute time are equal.
 */
class Event: public Object { 
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
  void setDelay(const float delay);
  
  //! Return the event delay.
  /*!
   * This function will return the event delay.
   * \return Return the Delay of this Event
   * \sa setDelay getTime updateTime
   */
  const float getDelay();

  //! Return the absolute event time
  /*!
   * This function return the absolute event time, which will calculated of the absolute time of the parent and the event delay.
   * If no parent is set, the parent absolute time will assumed as zero.
   * \return Return the absolute event time.
   * \sa setDelay getDelay updateTime
   */
  const float getTime();

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
  void pushChild(Event* newChild);

  //! Insert a event into the child list
  /*!
   * Insert a event into the child list at define position
   * \param newChild pointer to the event that should be added to the child list
   * \param index position where to add the event in the child list
   * \sa hasChilds pushChild popChild moveChild getChild getChildCount
   */
  void insertChild(Event* newChild, size_t index);

  //! Return a pointer of the child event at position index
  /*!
   * This function will return a pointer to the child event at position index
   * \param index position of the child obejct
   * \return pointer to the child event at position index
   * \sa hasChilds pushChild popChild insertChild moveChild getChildCount
   */
  Event* getChild(size_t index);

  //! Get the pointer of the parent event
  /*!
   * This function returns the pointer of the parent function or NULL if it has no parent event
   * \return A Pointer the the parent event
   * \sa hasParent setParent delParent
   */
  Event* getParent();

  //! Set the parent event
  /*!
   * The the parent event of the event to parent.
   * \param parent The pointer to the parent event
   * \sa hasParent getParent delParent
   */
  void setParent(Event* parent);

  //! Delete the parent of this event
  /*!
   * Delete the parent event. The parent event will NOT be destroyed due this function
   * \sa hasParent getParent setParent
   */
  void delParent();

  
private:
  float EventDelay;
  float EventTime;
};

#endif
