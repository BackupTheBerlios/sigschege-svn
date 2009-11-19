// -*- c++ -*-
// TimSignal.h
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


#ifndef TIMSIGNAL_H_
#define TIMSIGNAL_H_

#include <QtGui>

#include "TimMember.h"
#include "TimingScene.h"
#include "TimLayoutData.h"

class TimWave;
class TimLabel;

/** @brief The @c TimSignal class represents one signal in the Timing Diagram.
 *
 */
class TimSignal: public TimMember {

public:


  /** @brief Creates a new @c TimSignal object.
   *
   * @param scene Pointer to the timing scene.
   */
  TimSignal(TimingScene *scene);

  /** @brief DTor
   * Destroys the @c TimSignal object
   */
  ~TimSignal();

  /** @brief Returns the bounding rect for this signal.
   *
   * @return Returns the bounding rect.
   */
  virtual QRectF boundingRect() const;

  /** @brief Paints the signal.
   *
   * @param painter Pointer to the painter object
   * @param option Pointer to painter options
   * @param widget Pointer to the painting widget
   */
  virtual void
      paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  /** @brief Sets the geometry of this object
   *
   * @param rect Reference to the geometry.
   */
  virtual void setGeometry(const QRectF & rect);

  virtual void SSGWrite(SSGWriter *writer);

protected:

  /* @brief Returns a hint to the size of this signal.
   *
   * @param which Defines which hint type should be returned
   * @param constraint Specified any existing constraint.
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

  /** @brief Pointer to the wave form
   */
  TimWave *m_wave;

};

#endif /* TIMSIGNAL_H_ */
