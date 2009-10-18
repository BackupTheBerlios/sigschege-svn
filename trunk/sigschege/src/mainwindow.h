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

class MainWindow: public QMainWindow {

Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  virtual ~MainWindow();

private:
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createTopView();

private:
  QAction *m_exitAct;
  QAction *m_addSignal;
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

};

#endif // MAINWINDOW_H