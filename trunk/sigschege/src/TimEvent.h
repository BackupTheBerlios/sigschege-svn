// -*- c++ -*-
// TimEvent.h
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


#ifndef TIMEVENT_H_
#define TIMEVENT_H_

#include <QtGui>
#include "TimEventType.h"

class TimWave;

/** @brief The @c TimEvent class holds all event type independent informations.
 *
 * The @c TimEvent class holds all event type independent information. All event type dependent information
 * and behaviour (methods) are stored in subclasses of @c TimEventType.
 *
 * @c TimEvent and @c TimEventType implementing the state pattern.
 */
class TimEvent: public QGraphicsItem, public QGraphicsLayoutItem {

public:

  /** @brief Ctor
   *
   * Creates a new @c TimEvent object with default type and time.
   * Default event is TimEventLow.
   * Default time is 0.0 sec.
   *
   * @param parent Pointer to the owning TimWave object
   */
  TimEvent(TimWave *parent);

  /** @brief Ctor
   *
   * Creates a new TimEvent object with specified event type and default time of 0.0 second.
   *
   * @param parent Pointer to the owning TimWave object
   * @param type Pointer to the Event type object that should be used for this event.
   */
  TimEvent(TimWave *parent, TimEventType *type);

  /** @brief Ctor
   *
   * Creates a new TimEvent object with specified event type and time.
   *
   * @param parent Pointer to the owning TimWave object
   * @param type Pointer to the Event type object.
   * @param time Time of this event in seconds.
   */
  TimEvent(TimWave *parent, TimEventType *type, double time);

  /** @brief Dtor
   */
  ~TimEvent();

  /** @brief Set a new event type.
   *
   * This method will replace the current one with the specified event type. The old event type object
   * will be deleted.
   *
   * @param type Pointer to the new event type object.
   */
  virtual void setEventType(TimEventType *type);

  /** @brief Get the current event type.
   *
   * This method will return the current event type of this event.
   *
   * @return Returns a pointer of the current event type.
   */
  virtual TimEventType* getEventType();

  /** Get a pointer to the owning @c TimWave object.
   *
   * This method returns a pointer to the owning @c TimWave object.
   *
   * @return Returns a pointer to the owning @c TimWave object.
   */
  TimWave* getWave();

  /** @brief Calculates the horizontal event position.
   *
   * This method calculates the horizontal event position.
   *
   * @param time The time that should be converted to the horizontal position.
   * @return Returns the horizontal position in pixel.
   */
  unsigned int calcXPos(double time);

  /** @brief Insert a new event in the event linked list.
   *
   * This method insert a new event into the event linked list. The new event
   * is inserted right after this event.
   *
   * @param node Pointer to the new event.
   */
  void insertEvent(TimEvent *node);

  /** @brief Calculated the bounding rect
   *
   * @return The bounding rect.
   */
  virtual QRectF boundingRect() const;

  /** @brief Paints the event.
   *
   * This method paint the event. The real work is done in the event type classes.
   *
   * @param painter Painter environment.
   * @param option Style options
   * @param widget Drawing widget.
   */
  virtual void
      paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  /** @brief Set the geometry.
   *
   * This method set the geometry of this object.
   *
   * @param rect The geometry stored as rect.
   */
  virtual void setGeometry(const QRectF & rect);

  /** @brief Get the next @c TimEvent in the event linked list.
   *
   * This method returns the next @c TimEvent in the event linked list or Null is this event is the last.
   *
   * @return Returns a pointer to the next @c TimEvent object in the event linked list or NULL
   */
  TimEvent* getNext();

  /** @brief Get the previous @c TimEvent in the event linked list.
   *
   * This method returns the previous @c TimEvent in the event linked list or Null is this event is
   * the first.
   *
   * @return Returns a pointer to the previous @c TimEvent object in the event linked list or NULL
   */
TimEvent* getPrev();

protected:

  /** @brief Set the next pointer of the event linked list.
   *
   * @param next Pointer to the new "next" event.
   */
  void setNext(TimEvent *next);

  /** @brief Set the previous pointer of the event linked list.
   *
   * @param prev Pointer to the new "previous" event.
   */
void setPrev(TimEvent *prev);

  /** @brief Get a hint of the size that this object would like to have.
   *
   * The method return the size that this object prefers.
   *
   * @param which Specifies which size hint is requested.
   * @param constraint Specifies the size constrains that apply
   * @return Returns a hint of the size that this objects prefers.
   *
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

private:

  /** @brief Pointer to the owning @c TimWave object
   */
  TimWave *m_Wave;

  /** @brief Pointer to the previous event in the event linked list.
   */
  TimEvent *m_prev;

  /** @brief Pointer to the next event in the event linked list.
   */
  TimEvent *m_next;

  /** @brief Pointer to the event type.
   */
  TimEventType *m_EventType;

  /** @brief Time of this event.
   */
  double m_EventTime;
};

#endif /* TIMEVENT_H_ */
