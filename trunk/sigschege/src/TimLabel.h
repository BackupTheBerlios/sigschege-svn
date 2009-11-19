// -*- c++ -*-
// TimLabel.h
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


#ifndef TIMLABEL_H_
#define TIMLABEL_H_

#include <QtGui>
#include "TimMember.h"
#include "TimLayoutData.h"

/** @brief The @c TimLabel class is used to draw the signal labels.
 *
 * The @c TimLabel class ist used to draw the signal labels.
 */
class TimLabel: public TimMember {

public:

  /** @brief CTor
   *
   * @param scene Pointer to the timing scene.
   */
  TimLabel(TimingScene *scene);

  /** @brief CTor
   *
   * @param scene Pointer to the timing scene.
   * @param text Label text.
   *
   */
  TimLabel(TimingScene *scene, const QString & text);

  /** @brief Returns the bounding rect.
   *
   * @return Returns the bounding rect.
   */
  virtual QRectF boundingRect() const;

  /*	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
   QWidget *widget);
   */

  /** @brief Sets the geometry
   *
   * @param rect The geometry stored in a rect.
   */
  virtual void setGeometry(const QRectF & rect);

  virtual void SSGWrite(SSGWriter *writer);
  virtual void
        paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:

  /** @brief Returns a hint of the object size.
   *
   * @param which Specifies which hint is requested.
   * @param constraint The constrains that apply.
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

private:

  /** @brief Stores a pointer to the layout data.
   */
  TimLayoutData *m_LayoutData;

  QString m_label;

};

#endif /* TIMLABEL_H_ */
