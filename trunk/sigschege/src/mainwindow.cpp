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

MainWindow::MainWindow(QWidget *parent) {

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	createTopView();

	resize(800,500);

}
MainWindow::~MainWindow() {
}

void MainWindow::createActions() {
  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcut(tr("Ctrl+Q"));
  exitAct->setStatusTip(tr("Exit the application"));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

}

void MainWindow::createMenus() {
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAct);
}

void MainWindow::createToolBars() {
	fileToolBar = addToolBar(tr("File"));
}
void MainWindow::createStatusBar() {
	statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createTopView() {
	m_scene = new TimingScene;

	m_scene->setLabelWidth(50);
	m_scene->setSceneWidth(600);

	m_scene->addTimSignal();
	m_scene->addTimSignal();


	m_view = new QGraphicsView(m_scene);
	m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	setCentralWidget(m_view);

}
