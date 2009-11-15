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
class TimScale;

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
   * This method creates a new signal object, adds it to the timing scene and returns a pointer to it.
   *
   * @return Returns a pointer to the new signal.
   */
  TimSignal* addTimSignal();

  /** @brief Adds and returns a new signal.
   *
   * This method adds signal object to the timing scene and returns a pointer to it.
   *
   * @param signal Pointer to TimSignal object
   * @return Returns a pointer to the new signal.
   */
  TimSignal* addTimSignal(TimSignal* signal);

  /** @brief Adds and returns a new signal.
   *
   * This method adds signal object to the timing scene and returns a pointer to it.
   *
   * @param signal Pointer to TimSignal object
   * @param index Add signal after this index.
   * @return Returns a pointer to the new signal.
   */
  TimSignal* addTimSignal(int index, TimSignal* signal);

  /** @brief Removes the signal from the timing scene
   *
   * This method removes the signal from the timing scene. It will not destroy the signal.
   *
   * @param signal Pointer to the signal to remove.
   * @returns Returns the old index.
   */
  int removeTimSignal(TimSignal *signal);

  /** @brief Creates/adds and returns a new timescale.
   *
   * This method creates a new timescale object, adds it to the timing scene and returns a pointer to it.
   *
   * @return Returns a pointer to the new timescale.
   */
  TimScale* addTimScale();

  /** @brief Adds and returns a new timescale.
   *
   * This method adds a timescale object to the timing scene and returns a pointer to it.
   *
   * @param timescale Pointer to TimScale object
   * @return Returns a pointer to the new timescale.
   */
  TimScale* addTimScale(TimScale* timescale);

  /** @brief Adds and returns a new timescale.
   *
   * This method adds timescale object to the timing scene and returns a pointer to it.
   *
   * @param timescale Pointer to TimScale object
   * @param index Add timescale after this index.
   * @return Returns a pointer to the new timescale.
   */
  TimScale* addTimScale(int index, TimScale* timescale);

  /** @brief Removes the timescale from the timing scene
   *
   * This method removes the timescale from the timing scene. It will not destroy the timescale.
   *
   * @param timescale Pointer to the timescale to remove.
   * @returns Returns the old index.
   */
  int removeTimScale(TimScale *timescale);

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
   * @param etime End time in sec.
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

  /** @brief Creates a redo action
   *
   * This method creates a redo action that can be used in toolbars and menus.
   *
   * @return Redo action
   */
  QAction* createRedoAction();

  /** @brief Creates a undo action
   *
   * This method creates a undo action that can be used in toolbars and menus.
   *
   * @return Undo action
   */
  QAction* createUndoAction();

  /** @brief Push a command to the undo stack
   *
   * This method will execute and push the command to the undo stack.
   *
   * @param cmd Pointer to the command to execute and push to the undo stack.
   */
  void pushCmd(QUndoCommand* cmd);

  /** @brief Return if the diagram is unmodified 
   *
   * This method returns true if the timing diagram has not been changed since being opened,
   * saved or created.
   *
   * @return modified flag
   */
  bool isClean (void) { return m_undoStack.isClean(); };
 
  /** @brief Reset the modification status of the diagram 
   *
   * This method allows to reset the modification status of this diagram manually, e.g. if some
   * modifications are done implicitly after creation, which shouldn't count as modification.
   *
   */
  void setClean(void) { m_undoStack.setClean(); };

  /** @brief Clears the diagram completely 
   *
   * This method the diagram completely and resets it to its starting state, directly after construction.
   * Note that this is not an undoable action of course.
   *
   */
  void clear(void);

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
