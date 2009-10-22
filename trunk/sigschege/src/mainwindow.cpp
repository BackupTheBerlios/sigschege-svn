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

#include "mainwindow.h"
#include "TimCmdAddSignal.h"
#include "TimCmdRmSignal.h"

MainWindow::MainWindow(QWidget *parent) {

  createTopView();

  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  // handle changed selection
  connect(m_scene, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));

  resize(800, 500);

}
MainWindow::~MainWindow() {
}

void MainWindow::createActions() {
  m_exitAct = new QAction(tr("E&xit"), this);
  m_exitAct->setShortcut(tr("Ctrl+Q"));
  m_exitAct->setStatusTip(tr("Exit the application"));
  connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));

  m_addSignal = new QAction(tr("Add Signal"), this);
  m_addSignal->setIcon(QIcon(":/images/add.png"));
  m_addSignal->setStatusTip(tr("Adds a new signal to the timing diagram"));
  connect(m_addSignal, SIGNAL(triggered()), this, SLOT(cmdAddSignal()));

  m_rmSignal = new QAction(tr("Remove Signal"), this);
  m_rmSignal->setEnabled(false);
  m_rmSignal->setIcon(QIcon(":/images/rm.png"));
  m_rmSignal->setStatusTip(tr("Removes one or more signal(s) from the timing diagram"));
  connect(m_rmSignal, SIGNAL(triggered()), this, SLOT(cmdRmSignal()));

  m_undoCmd = m_scene->createUndoAction();
  m_undoCmd->setIcon(QIcon(":/images/undo.png"));
  m_redoCmd = m_scene->createRedoAction();
  m_redoCmd->setIcon(QIcon(":/images/redo.png"));

}

void MainWindow::createMenus() {

  // Create and init file menu
  m_fileMenu = menuBar()->addMenu(tr("&File"));
  m_fileMenu->addAction(m_exitAct);

  // Create and init edit menu
  m_editMenu = menuBar()->addMenu(tr("&Edit"));
  m_editMenu->addAction(m_undoCmd);
  m_editMenu->addAction(m_redoCmd);
  m_editMenu->addSeparator();
  m_editMenu->addAction(m_addSignal);
  m_editMenu->addAction(m_rmSignal);
}

void MainWindow::createToolBars() {

  // Create and init the file tool bar
  m_fileToolBar = addToolBar(tr("File"));

  // Create and init the edit tool bar
  m_editToolBar = addToolBar(tr("Edit"));
  m_editToolBar->addAction(m_addSignal);
  m_editToolBar->addAction(m_rmSignal);
  m_editToolBar->addSeparator();
  m_editToolBar->addAction(m_undoCmd);
  m_editToolBar->addAction(m_redoCmd);

}
void MainWindow::createStatusBar() {
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createTopView() {
  m_scene = new TimingScene;

  m_scene->setLabelWidth(50);
  m_scene->setSceneWidth(600);

  m_view = new QGraphicsView(m_scene);
  m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  setCentralWidget(m_view);

}

void MainWindow::cmdAddSignal() {
  m_scene->pushCmd(new TimCmdAddSignal(m_scene));
}

void MainWindow::cmdRmSignal() {
  m_scene->pushCmd(new TimCmdRmSignal(m_scene));
}

void MainWindow::selectionChanged() {

  // get new selected items
  QList<QGraphicsItem*> item_list = m_scene->selectedItems();

  // check if any signal is selected
  if(item_list.isEmpty()) {
    // disable delete signal
    m_rmSignal->setEnabled(false);
  } else {
    // enable delete signal
    m_rmSignal->setEnabled(true);
  }

}
