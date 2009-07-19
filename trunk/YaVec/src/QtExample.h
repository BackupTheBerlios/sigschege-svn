/********************************************************************************
** Form generated from reading ui file 'QtExampleDs5959.ui'
**
** Created: Thu Jul 9 12:11:59 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef QTEXAMPLE_H
#define QTEXAMPLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "YaVecVqt.h"

QT_BEGIN_NAMESPACE

using namespace YaVec;

class MainWindow : public QMainWindow
{
  Q_OBJECT

    public:
  MainWindow();
  
  private slots:
  bool save();
  bool addPoint();
  bool toggleDPI();
  bool toggleMarkers();
  bool toggleDashed();
  bool toggleArrowed();
  bool toggleBoxes();
  bool toggleArcs();
  bool toggleText();

  
  private:
  void createMenus();
  QMenu *fileMenu;
  QMenu *editMenu;
  QAction *saveAct;
  QAction *exitAct;
  QAction *addPointAct;
  QAction *toggleDPIAct;
  QAction *toggleMarkersAct;
  QAction *toggleDashedAct;
  QAction *toggleArrowedAct;
  QAction *toggleBoxesAct;
  QAction *toggleArcsAct;
  QAction *toggleTextAct;
  FigVqt *figure; 
  FFigure *mainpic;
  int state;

};

#endif // QTEXAMPLE_H
