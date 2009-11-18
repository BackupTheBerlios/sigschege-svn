// -*- c++ -*-
// Copyright 2009 by ingo & ulf
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


#ifndef TIMSCALE_H_
#define TIMSCALE_H_

#include <QtGui>

#include "TimMember.h"
#include "TimingScene.h"
#include "TimLayoutData.h"

class TimLabel;

/** @brief The @c TimScale class displays a time scale in the Timing Diagram.
 *
 */
class TimScale: public TimMember {

public:

  /** @brief Creates a new @c TimScale object.
   *
   * @param layout Pointer to the layout data object.
   * @param parent Pointer to the owning parent object.
   */
  TimScale(TimLayoutData *layout, QGraphicsItem *parent = 0);

  /** @brief DTor
   * Destroys the @c TimScale object
   */
  ~TimScale();

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

};

#endif /* TIMSCALE_H_ */
