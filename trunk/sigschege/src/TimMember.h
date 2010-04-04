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

#include "TimLayoutData.h"
#include "TimingScene.h"

class SSGWriter;
class TimLabel;

/** @brief The @c TimMember class displays a time scale in the Timing Diagram.
 *
 */
class TimMember: public QGraphicsItem, public QGraphicsLayoutItem {

public:

  /** @brief Creates a new @c TimMember object.
   *
   * @param parent Pointer to the parent object
   * @param scene Pointer to the timing scene.
   */
  TimMember(TimMember* parent, TimingScene *scene);

  /** @brief DTor
   * Destroys the @c TimMember object
   */
  virtual ~TimMember();

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
      paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {}

  /** @brief Sets the geometry of this object
   *
   * @param rect Reference to the geometry.
   */
  virtual void setGeometry(const QRectF & rect);

  /** @brief Write XML code for this class.
   *
   * This function writes the XML code for this object while saving a Sigschege XML file.
   * It is a pure virtual function which must be implemented by the derived classes (TimSignal, 
   * TimScale, ...)
   *
   * @param writer Pointer to the SSGWriter object, needed for callback.
   */
  virtual void SSGWrite(SSGWriter *writer) {};

  /** @brief Get a pointer to layout data
   *
   * @return Returns a pointer to the layout data
   */
  virtual TimLayoutData* getLayoutData() const;


  /** @brief Get a pointer to the timing scene
   *
   * @return Returns a pointer to the timing scene
   */
  virtual TimingScene* getScene() const;

  /** @brief Creates a delete command
   *
   * This method create a delete command that deletes this item when executed.
   *
   * Note: The caller is responsible to delete the created command.
   *
   * @return Pointer to created delete command
   */
  virtual QUndoCommand* createDeleteCmd() { return NULL;}


  /** @brief This method handles a change of the time range
   *
   * This method is called when the time range changes and the geometry
   * must be recalculated. It has to be implemented by elements which depend
   * on the time. 
   */
  virtual void timeRangeChange() { }

  /** @brief This method calculates the snap time belonging to the given mouse position.
   *
   * This method is called to calculate the time that would be chosen by the time snapping
   * mechanism for the given mouse position. It can be called both from the scene for displaying
   * a marker or from the Event to calculate the place to insert a new event.
   *
   * @param xpos The horizontal position of the mouse
   * @param isWave Boolean parameter to indicate if this member is a wave or not to indicate coordinate origin. Default: false. 
   * @return A time that is a multiple of the snap distance and close to the mouse.
   */
  qreal calcSnapTime(qreal xpos, bool isWave = false);

  /** @brief This method returns the current snap time.
   *
   */
  qreal getSnapTime() { return m_snapTime; }

  /** @brief This method returns the current deviation between snap time and real time.
   *
   */
  qreal getSnapDeviation() { return m_snapDeviation; }

protected:

  /* @brief Returns a hint to the size of this signal.
   *
   * @param which Defines which hint type should be returned
   * @param constraint Specified any existing constraint.
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

  /** @brief Pointer to the timing scene.
   *
   * This is a weak pointer.  (no ownership)
   */
  TimingScene *m_scene;

  /** @brief The snap time calculated from the latest pointer movement.
   *
   */
  qreal m_snapTime;

  /** @brief Deviation between actual and snapped time.
   *
   * The deviation between the time the pointer hovers over and the time
   * that is selected by the snapping algorithm, range is -1.0 to +1.0.
   */
  qreal m_snapDeviation;

};

#endif /* TIMSCALE_H_ */
