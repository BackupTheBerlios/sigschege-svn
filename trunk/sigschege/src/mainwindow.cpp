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
#include "TimSignal.h"
#include "DiaSettings.h"
#include "TimScale.h"
#include "TimCmdAddListItem.h"
#include "SSGReader.h"
#include "SSGWriter.h"
#include <QSvgGenerator>

MainWindow::MainWindow(QWidget *parent) {

  setWindowTitle(tr("Sigschege"));

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
  m_newAct = new QAction(tr("&New"), this);
  m_newAct->setShortcut(tr("Ctrl+N"));
  m_newAct->setStatusTip(tr("Start a new timing diagram"));
  connect(m_newAct, SIGNAL(triggered()), this, SLOT(cmdNew()));

  m_openAct = new QAction(tr("&Open"), this);
  m_openAct->setShortcut(tr("Ctrl+L"));
  m_openAct->setStatusTip(tr("Open a timing diagram"));
  connect(m_openAct, SIGNAL(triggered()), this, SLOT(cmdOpen()));

  m_saveAct = new QAction(tr("&Save"), this);
  m_saveAct->setShortcut(tr("Ctrl+S"));
  m_saveAct->setStatusTip(tr("Save this timing diagram"));
  connect(m_saveAct, SIGNAL(triggered()), this, SLOT(cmdSave()));

  m_saveAsAct = new QAction(tr("Save &As"), this);
  m_saveAsAct->setStatusTip(tr("Save the timing diagram under a new name"));
  connect(m_saveAsAct, SIGNAL(triggered()), this, SLOT(cmdSaveAs()));

  m_exportAct = new QAction(tr("&Export"), this);
  m_exportAct->setStatusTip(tr("Export the timing diagram as SVG"));
  connect(m_exportAct, SIGNAL(triggered()), this, SLOT(cmdExport()));

  m_exitAct = new QAction(tr("E&xit"), this);
  m_exitAct->setShortcut(tr("Ctrl+Q"));
  m_exitAct->setStatusTip(tr("Exit the application"));
  connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));

  m_addSignalAct = new QAction(tr("Add Signal"), this);
  m_addSignalAct->setIcon(QIcon(":/images/add.png"));
  m_addSignalAct->setStatusTip(tr("Adds a new signal to the timing diagram"));
  connect(m_addSignalAct, SIGNAL(triggered()), this, SLOT(cmdAddSignal()));

  m_addScaleAct = new QAction(tr("Add Time Scale"), this);
  //m_addSignalAct->setIcon(QIcon(":/images/add.png"));
  m_addScaleAct->setStatusTip(tr("Adds a new time scale to the timing diagram"));
  connect(m_addScaleAct, SIGNAL(triggered()), this, SLOT(cmdAddScale()));

  m_setDiaProps = new QAction(tr("Edit Diagram Properties"), this);
  //m_addSignalAct->setIcon(QIcon(":/images/add.png"));
  m_setDiaProps->setStatusTip(tr("Edit the global properties of this timing diagram"));
  connect(m_setDiaProps, SIGNAL(triggered()), this, SLOT(cmdEditDiaProperties()));

  m_rmSignalAct = m_scene->getActionRemoveItems();

  m_SigArrow = m_scene->getActionArrow();
  m_SigArrow->setIcon(QIcon(":/images/arrow.png"));

  m_SigH = m_scene->getActionSigH();
  m_SigH->setIcon(QIcon(":/images/SigH.png"));

  m_SigL = m_scene->getActionSigL();
  m_SigL->setIcon(QIcon(":/images/SigL.png"));

  m_SigGroup = new QActionGroup(this);
  m_SigGroup->addAction(m_SigArrow);
  m_SigGroup->addAction(m_SigH);
  m_SigGroup->addAction(m_SigL);

  m_undoCmd = m_scene->createUndoAction();
  m_undoCmd->setIcon(QIcon(":/images/undo.png"));
  m_redoCmd = m_scene->createRedoAction();
  m_redoCmd->setIcon(QIcon(":/images/redo.png"));

  sceneScaleCombo = new QComboBox;
  QStringList scales;
  scales << tr("25%") << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%")<< tr("200%") << tr("300%");
  sceneScaleCombo->addItems(scales);
  sceneScaleCombo->setCurrentIndex(3);
  connect(sceneScaleCombo, SIGNAL(currentIndexChanged(const QString &)),
	  this, SLOT(sceneScaleChanged(const QString &)));
}

void MainWindow::createMenus() {

  // Create and init file menu
  m_fileMenu = menuBar()->addMenu(tr("&File"));
  m_fileMenu->addAction(m_newAct);
  m_fileMenu->addAction(m_openAct);
  m_fileMenu->addAction(m_saveAct);
  m_fileMenu->addAction(m_saveAsAct);
  m_fileMenu->addAction(m_exportAct);
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(m_exitAct);

  // Create and init edit menu
  m_editMenu = menuBar()->addMenu(tr("&Edit"));
  m_editMenu->addAction(m_undoCmd);
  m_editMenu->addAction(m_redoCmd);
  m_editMenu->addSeparator();
  m_editMenu->addAction(m_addSignalAct);
  m_editMenu->addAction(m_addScaleAct);
  m_editMenu->addAction(m_rmSignalAct);
  m_editMenu->addAction(m_setDiaProps);
}

void MainWindow::createToolBars() {

  // Create and init the file tool bar
  m_fileToolBar = addToolBar(tr("File"));

  // Create and init the edit tool bar
  m_editToolBar = addToolBar(tr("Edit"));
  m_editToolBar->addAction(m_undoCmd);
  m_editToolBar->addAction(m_redoCmd);
  m_editToolBar->addSeparator();
  m_editToolBar->addAction(m_addSignalAct);
  m_editToolBar->addAction(m_rmSignalAct);
  m_editToolBar->addWidget(sceneScaleCombo);

  // Create and init the signal tool bar
  m_signalToolBar = new QToolBar(tr("Signal"), this);
  addToolBar(Qt::LeftToolBarArea, m_signalToolBar);
  m_signalToolBar->addAction(m_SigArrow);
  m_signalToolBar->addAction(m_SigH);
  m_signalToolBar->addAction(m_SigL);

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

void MainWindow::cmdNew() {
  maybeSave();
}

void MainWindow::cmdOpen() {

  if (!maybeSave()) {
    return;
  }

  QString
      fileName =
          QFileDialog::getOpenFileName(this, tr("Open Timing Diagram"), QDir::currentPath(), tr("Sigschege Timing Diagrams (*.ssg)"));
  if (fileName.isEmpty())
    return;

  QFile file(fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("QXmlStream Sigschege Timing Diagram"), tr("Cannot read file %1:\n%2.") .arg(fileName) .arg(file.errorString()));
    return;
  }

  SSGReader reader(m_scene);
  if (!reader.read(&file)) {
    QMessageBox::warning(this, tr("QXmlStream Sigschege Timing Diagram"), tr("Parse error in file %1 at line %2, column %3:\n%4") .arg(fileName) .arg(reader.lineNumber()) .arg(reader.columnNumber()) .arg(reader.errorString()));
  } else {
    statusBar()->showMessage(tr("File loaded"), 2000);
    m_filename = fileName;
  }

}

QString MainWindow::askForFileName(void) {
  return QFileDialog::getSaveFileName(this, tr("Save Diagram As"),
				 QDir::currentPath(),
				 tr("Sigschege Files (*.ssg)"));
}

bool MainWindow::save(QString &fileName) {
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("QXmlStream Bookmarks"),
			 tr("Cannot write file %1:\n%2.")
			 .arg(fileName)
			 .arg(file.errorString()));
    return false;
  }


  SSGWriter writer(m_scene);
  return writer.write(&file);
}

void MainWindow::cmdSave() {
  if (m_filename.isEmpty())
    m_filename =  askForFileName();
  save(m_filename);
}

void MainWindow::cmdSaveAs() {
  QString fileName = askForFileName();
    
  if (fileName.isEmpty())
    return;
  
  save(fileName);
  
}

void MainWindow::cmdExport() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Export Diagram To"),
						  QDir::currentPath(),
						  tr("Scalable Vector Graphics (*.svg)"));
    
  if (fileName.isEmpty())
    return;
  
  QSvgGenerator *gen = new QSvgGenerator();
  gen->setFileName(fileName);
  gen->setTitle(tr("Timing Diagram generated by Sigschege"));
  QRectF srect = m_scene->itemsBoundingRect();
  QSizeF ssize = srect.size();
  gen->setResolution(72);
  gen->setViewBox(srect);
  gen->setSize(QSize(ssize.width(),ssize.height()));
  QPainter *svgPainter = new QPainter(gen);
  m_scene->render(svgPainter);
  svgPainter->end();
  delete svgPainter;
  delete gen;
  
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (maybeSave()) {
    event->accept();
  } else {
    event->ignore();
  }
}

void MainWindow::cmdAddSignal() {

  m_scene->pushCmd(new TimCmdAddListItem(m_scene, -1, new TimSignal(0, m_scene)));

}

void MainWindow::cmdAddScale() {
  m_scene->pushCmd(new TimCmdAddListItem(m_scene, -1, new TimScale(0,m_scene)));
}

void MainWindow::selectionChanged() {

  // get new selected items
  QList<QGraphicsItem*> item_list = m_scene->selectedItems();

  // check if any item is selected
  if (item_list.isEmpty()) {
    // disable delete item
    m_rmSignalAct->setEnabled(false);
  } else {
    // enable delete item
    m_rmSignalAct->setEnabled(true);
  }

}

bool MainWindow::maybeSave() {
  bool affirmative = true;
  if (!m_scene->isClean()) {
    QMessageBox::StandardButton user_choice;
    user_choice
        = QMessageBox::warning(this, tr("Application"), tr("The timing diagram is modified.\n"
          "Do you want to save the changes?"), QMessageBox::Save
            | QMessageBox::Discard | QMessageBox::Cancel);
    if (user_choice == QMessageBox::Save)
      affirmative = save(m_filename);
    else if (user_choice == QMessageBox::Cancel)
      affirmative = false;
  }

  if (affirmative) {
    m_scene->clear();
    return true;
  } else
    return false;

}

void MainWindow::cmdEditDiaProperties() {
  DiaSettings setting_dialog(this, m_scene);

  setting_dialog.exec();
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = m_view->matrix();
    m_view->resetMatrix();
    m_view->translate(oldMatrix.dx(), oldMatrix.dy());
    m_view->scale(newScale, newScale);
}
