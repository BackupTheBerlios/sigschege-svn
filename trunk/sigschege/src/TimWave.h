// -*- c++ -*-
// TimWave.h
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


#ifndef TIMWAVE_H_
#define TIMWAVE_H_

#include <QtGui>
#include "TimLayoutData.h"
#include "TimEvent.h"

class TimSignal;

/** @brief Waveform object of a signals
 */
class TimWave: public QGraphicsItem, public QGraphicsLayoutItem {

public:
  /** @brief CTor
   *
   * @param layoutdata Pointer to the layout data object.
   * @param parent Pointer to the parent object.
   */
  TimWave(TimLayoutData *layoutdata, QGraphicsItem *parent = 0);

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
  virtual void
      paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  /** @brief Set the waveform geometry
   *
   * @param rect New geometry.
   */
  virtual void setGeometry(const QRectF & rect);

  /** @brief Get a pointer to the layout data object.
   *
   * @return Pointer to the layout data object.
   */
  TimLayoutData* getLayoutData();

protected:

  /** @brief Get s hint of the required waveform size.
   *
   * @param which Selects the requested hint type.
   * @param constraint Specifies existing area constrains.
   * @return Size hint.
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

private:
  TimEvent *m_TimEvent;
  TimLayoutData *m_LayoutData;

};

#endif /* TIMWAVE_H_ */
