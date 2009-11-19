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


#ifndef TIMMEMBER_H_
#define TIMMEMBER_H_

#include <QtGui>

#include "TimingScene.h"
#include "TimLayoutData.h"

class SSGWriter;
class TimLabel;

/** @brief The @c TimMember class displays a time scale in the Timing Diagram.
 *
 */
class TimMember: public QGraphicsItem, public QGraphicsLayoutItem {

public:

  /** @brief Creates a new @c TimMember object.
   *
   * @param scene Pointer to the timing scene.
   */
  TimMember(TimingScene *scene);

  /** @brief DTor
   * Destroys the @c TimMember object
   */
  ~TimMember();

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
      paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

  /** @brief Sets the geometry of this object
   *
   * @param rect Reference to the geometry.
   */
  virtual void setGeometry(const QRectF & rect);

  /** @brief Sets the text of the label
   *
   * @param text The new text of the label
   */
  void setText ( const QString & text );

  virtual void SSGWrite(SSGWriter *writer) = 0;

  virtual TimLayoutData* getLayoutData() const;

  virtual TimingScene* getScene() const;

protected:

  /* @brief Returns a hint to the size of this signal.
   *
   * @param which Defines which hint type should be returned
   * @param constraint Specified any existing constraint.
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

  /** @brief Pointer to the signal label
   */
  TimLabel *m_label;

  /** @brief Pointer to the timing scene.
   *
   * This is a weak pointer.  (no ownership)
   */
  TimingScene *m_scene;
};

#endif /* TIMSCALE_H_ */
