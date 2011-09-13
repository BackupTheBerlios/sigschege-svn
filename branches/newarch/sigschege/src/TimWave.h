// -*- c++ -*-
// TimWave.h
// Copyright 2011 by Ingo Hinrichs
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

#ifndef TIMWAVEFORM_H_
#define TIMWAVEFORM_H_

#include <QtGui>

#include "TimMember.h"

#include "TimingScene.h"
#include "TimLayoutData.h"

#include "TimEvent.h"
#include "TimEventPainter.h"

/** @brief Waveform object of a signals
 */
class TimWave: public TimMember {

public:

  /** @brief CTor
   *
   * @param parent Pointer to the parent object
   * @param scene Pointer to the timing scene.
   */
  TimWave(TimMember *parent, TimingScene *scene);

  /** @brief DTor
   */
  virtual ~TimWave();

  /** @brief Returns the bounding rect.
   *
   * @return Bounding rect.
   */
  virtual QRectF boundingRect() const;

  /** @brief Paints the waveform
   *
   * Actually the event draw the waveform, but border etc are drawn here.
   *
   * @param painter Pointer to the painter object.
   * @param option Pointer to the paint options.
   * @param widget Pointer to the drawing widget.
   */
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  /** @brief Get a pointer to the layout data object.
   *
   * @return Pointer to the layout data object.
   */
  TimLayoutData* getLayoutData() const;

  /** @brief Adds a new timing event
   *
   * @param painter Pointer to the painter for this event
   * @param time Time of the new timing event
   * @return True on success, false otherwise
   */
  bool addTimEvent(double time, TimEventPainter *painter, double setup, double hold);

  /** Removes the Timing event at time
   *
   * @param time Time of the timing event
   * @return True on success, false otherwise
   */
  bool rmTimEvent(double time);

protected:

  /** @brief Get s hint of the required waveform size.
   *
   * @param which Selects the requested hint type.
   * @param constraint Specifies existing area constrains.
   * @return Size hint.
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint = QSizeF()) const;

  void mousePressEvent ( QGraphicsSceneMouseEvent * event );

  void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event);

private:

  TimEventSet_t m_event_set;

};

#endif /* TIMWAVEFORM_H_ */
