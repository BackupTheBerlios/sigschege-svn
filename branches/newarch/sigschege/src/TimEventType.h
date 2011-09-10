// -*- c++ -*-
// TimEventType.h
// Copyright 2009 by ingo
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


#ifndef TIMEVENTTYPE_H_
#define TIMEVENTTYPE_H_

#include <QtGui>

#include "TimLayoutData.h"

enum EventLevel {
  None, Low, High, Invert
};

class TimEvent;

/** @brief The @c TimEventType is the base class for all event types.
 *
 * The @c TimEventType class is the base class for all event types like TimEventLow or TimEventHigh.
 * It handles all event type specific actions but contains not data. Data is stored in the event class only.
 *
 */
class TimEventType {

public:

  /** @brief The class constructor
   *
   * @param parent The TimEvent that owns this event type. Default: 0.
   */
  TimEventType(TimEvent* parent = 0);

  /** @brief The standard destructor
   */
  virtual ~TimEventType();

  /** @brief Sets a new parent.
   *
   * This function replaces the owning parent of the event type.
   *
   * @param parent The new TimEvent parent
   */
  void setParent(TimEvent *parent);

  /** @brief default paint implementation
   *
   * This is the default paint implementation. It paints nothing.
   *
   * @param event A pointer to the owning event.
   * @param painter Painter context
   * @param option Style options
   * @param widget  The widget argument is optional. If provided, it points to the widget that is being painted on; otherwise, it is 0. For cached painting, widget is always 0.
   *
   */
  virtual void
      paint(TimEvent *event, QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  /** @brief Set the event level.
   *
   * The event level is used by subclasses the store the related signal level.
   *
   * @param level The new signal level.
   * @sa getLevel
   */
  void setLevel(EventLevel level);

  /** @brief Get the event level.
   *
   * This function will return the event level for this specific event.
   *
   * @return The current event level.
   * @sa setLevel
   */
  EventLevel getLevel();

protected:
  /** @brief Stores a pointer to the owning parent.
   */
  TimEvent *m_parent;

private:
  EventLevel m_level;

};

#endif /* TIMEVENTTYPE_H_ */
