// -*- c++ -*-
// TimingScene.h
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


#ifndef TIMINGSCENE_H_
#define TIMINGSCENE_H_

#include <QtGui>
#include "TimLayoutData.h"

class TimSignal;

/** @brief The timing scene holds all element of the timing diagram.
 *
 * The timing scene holds all elements of the timing diagram. Beside this element, it stores
 * the layout data as well.
 */
class TimingScene: public QGraphicsScene {
Q_OBJECT

public:

  /** @brief Ctor
   *
   * @param parent Pointer to the owning parent object.
   */
  TimingScene(QObject *parent = 0);

  /** @brief Creates/adds and returns a new signal.
   *
   * This method creates a new signal object, adds it to the timing scene and retuns a pointer to it.
   *
   * @return Returns a pointer to the new signal.
   */
  TimSignal* addTimSignal();

  /** @brief Get a pointer to the layout data.
   *
   * This method returns a pointer to the layout data of this scene.
   *
   * @return Returns a pointer to the layout data of this scene.
   */
  TimLayoutData* getLayoutData();

  /** @brief Sets the start time of the timing scene.
   *
   * This method sets the start time of the timing scene. The time itself will be stored in the layout
   * data.
   *
   * @param stime Start time in sec.
   */
  void setStartTime(double stime);

  /** @brief Sets the end time of the timing scene.
   *
   * This method sets the end time of the timing scene. The time itself will be stored in the layout
   * data.
   *
   * @param stime End time in sec.
   */
  void setEndTime(double etime);

  /** @brief Sets the label width.
   *
   * This method sets the label width. The width will be stored in the layout data.
   *
   * @param width Label width.
   */
  void setLabelWidth(unsigned int width);

  /** @brief Sets the scene width.
   *
   * This method sets the scene width. The width will be stored in the layout data.
   *
   * @param width Scene width.
   */
  void setSceneWidth(unsigned int width);

  QAction* createRedoAction();
  QAction* createUndoAction();

  void pushCmd(QUndoCommand* cmd);

private:
  /** @brief Pointer to the linear layout object.
   *
   * This layout object is used to organise the signals in a vertical list.
   */
  QGraphicsLinearLayout *m_layout;

  /** @brief Layout data object
   *
   * This object stored all "global" timing diagram data.
   */
  TimLayoutData m_LayoutData;

  QUndoStack m_undoStack;
};

#endif /* TIMINGSCENE_H_ */
