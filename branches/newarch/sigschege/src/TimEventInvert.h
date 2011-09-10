// -*- c++ -*-
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


#ifndef TIMEVENTINVERT_H_
#define TIMEVENTINVERT_H_

#include "TimEventType.h"

class TimEvent;

/** @brief Low signal specialisation of @c TimEventType class
 *
 * This class is a specialisation of @c TimEventType class which implements the behaviour of a "low" signal.
 *
 */
class TimEventInvert: public TimEventType {

public:

  /** @brief The class constructor
   *
   * @param parent The TimEvent that owns this event type. Default: 0.
   */
  TimEventInvert(TimEvent *parent = 0);

  /** @brief Type specific paint implementation
   *
   * This function implements the low signal type paint implementation.
   *
   * @param event A pointer to the owning event.
   * @param painter Painter context
   * @param option Style options
   * @param widget  The widget argument is optional. If provided, it points to the widget that is being painted on; otherwise, it is 0. For cached painting, widget is always 0.
   */
  virtual void
      paint(TimEvent *event, QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif /* TIMEVENTINVERT_H_ */
