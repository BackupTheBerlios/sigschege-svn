// -*- c++ -*-
// mainwindow.h
// Copyright 2009 by Ingo Hinrichs
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "TimingScene.h"
#include "TimSignal.h"

/** @brief Main window of Sigschege
 */
class MainWindow: public QMainWindow {

Q_OBJECT

public:
  /** @brief CTor
   *
   * @param parent Pointer to the parent object
   */
  MainWindow(QWidget *parent = 0);

  /** @brief DTor
   */
  virtual ~MainWindow();

private:
  /** @brief Create all action objects
   */
  void createActions();

  /** @brief Create menus.
   */
  void createMenus();

  /** @brief Create tool bars
   */
  void createToolBars();

  /** @brief Create status bar
   */
  void createStatusBar();

  /** @brief Create timing diagram scene and view.
   */
  void createTopView();

private:
  QAction *m_exitAct;
  QAction *m_addSignal;
  QAction *m_rmSignal;
  QAction *m_undoCmd;
  QAction *m_redoCmd;
  QMenu *m_fileMenu;
  QMenu *m_editMenu;
  QToolBar *m_fileToolBar;
  QToolBar *m_editToolBar;
  QGraphicsView *m_view;
  TimingScene *m_scene;

private slots:
  void cmdAddSignal();
  void cmdRmSignal();
  void selectionChanged();

};

#endif // MAINWINDOW_H
