// \file  
// Copyright 2009 by Ulf Klaperski
//
// This file is part of YaVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// YaVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// YaVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the YaVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id: $

#include "YaVecFigure.h"
#include "YaVecElm.h"
#include "YaVecPolyline.h"
#include "YaVecBox.h"
#include "YaVecArc.h"
#include "YaVecText.h"
#include "YaVecVqt.h"
#include "QtExample.h"
#include <QtGui/QtGui>
#include <list>
#include <cmath>

using namespace std;
using namespace YaVec;

FPolyline* mainline;
list<FPolyline *> dlines;
list<FPolyline *> alines;
list<FArc *> arcs;
list<FText *> texts;
list<FBox *> tboxes;
list<FBox *> boxes;

MainWindow::MainWindow() :QMainWindow() {
  FFigure *ev_pic = new FFigure();
  createMenus();
  figure = new FigVqt(ev_pic, this);
  FPolyline *nline;
  nline = ev_pic->polyline();
  nline->addPoint(1500, 1500);
  nline->addPoint(300, 1500);
  nline->addPoint(3300, 1500);
  nline->addPoint(1720, 60);
  nline->depth(66);
  mainline = nline;

  FText *ntext;
  ntext = ev_pic->text();
  ntext->setText("This is a good YaVec Demo");
  ntext->penColor(2);
  ntext->setOrigin(PosInt(300, 5000));
  ntext->setSize(30);
  ntext->depth(55);

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(figure);
  QWidget *widget = new QWidget;
  widget->setLayout(layout);
  
  setCentralWidget(widget);
  state = 4;
  mainpic = ev_pic;
}
void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setStatusTip(tr("Save the document to disk as bla.*"));
    fileMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    fileMenu->addSeparator();

    toggleDPIAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Screen DPI"), this);
    toggleDPIAct->setStatusTip(tr("Save the document to disk as bla.*"));
    fileMenu->addAction(toggleDPIAct);
    connect(toggleDPIAct, SIGNAL(triggered()), this, SLOT(toggleDPI()));

    toggleMarkersAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Screen Markers"), this);
    toggleMarkersAct->setStatusTip(tr("Save the document to disk as bla.*"));
    fileMenu->addAction(toggleMarkersAct);
    connect(toggleMarkersAct, SIGNAL(triggered()), this, SLOT(toggleMarkers()));

    fileMenu->addSeparator();

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    editMenu = menuBar()->addMenu(tr("&Edit"));

    addPointAct = new QAction(QIcon(":/images/save.png"), tr("Add &Point"), this);
    addPointAct->setStatusTip(tr("Add another point to the Polyline"));
    editMenu->addAction(addPointAct);
    connect(addPointAct, SIGNAL(triggered()), this, SLOT(addPoint()));

    toggleMarkersAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Markers"), this);
    toggleMarkersAct->setStatusTip(tr("Toggle Markers"));
    editMenu->addAction(toggleMarkersAct);
    connect(toggleMarkersAct, SIGNAL(triggered()), this, SLOT(toggleMarkers()));

    toggleDashedAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Dashed Lines"), this);
    toggleDashedAct->setStatusTip(tr("Toggle Dashed Lines Demo"));
    editMenu->addAction(toggleDashedAct);
    connect(toggleDashedAct, SIGNAL(triggered()), this, SLOT(toggleDashed()));

    toggleArrowedAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Arrowed Lines"), this);
    toggleArrowedAct->setStatusTip(tr("Toggle Arrowed Lines  Demo"));
    editMenu->addAction(toggleArrowedAct);
    connect(toggleArrowedAct, SIGNAL(triggered()), this, SLOT(toggleArrowed()));

    toggleBoxesAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Boxes"), this);
    toggleBoxesAct->setStatusTip(tr("Toggle Boxes Demo"));
    editMenu->addAction(toggleBoxesAct);
    connect(toggleBoxesAct, SIGNAL(triggered()), this, SLOT(toggleBoxes()));

    toggleArcsAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Arcs"), this);
    toggleArcsAct->setStatusTip(tr("Toggle Arcs Demo"));
    editMenu->addAction(toggleArcsAct);
    connect(toggleArcsAct, SIGNAL(triggered()), this, SLOT(toggleArcs()));

    toggleTextAct = new QAction(QIcon(":/images/save.png"), tr("Toggle Text"), this);
    toggleTextAct->setStatusTip(tr("Toggle Text Demo"));
    editMenu->addAction(toggleTextAct);
    connect(toggleTextAct, SIGNAL(triggered()), this, SLOT(toggleText()));


}

bool MainWindow::save() {
}

bool MainWindow::addPoint() {
}

bool MainWindow::toggleDPI() {
  if (mainpic->getScreenDpi()==80) mainpic->setScreenDpi(160);
  else  mainpic->setScreenDpi(80);
  figure->refreshAll();
}

bool MainWindow::toggleMarkers() {
  if (++state>5) state=0;
  bool marker = (state&4)!=4;
  bool hier = (state&2)==2;
  bool comp = (state&1)==1;
  cout << "MARKERS=" << marker << " hier=" << hier << " comp=" << comp << " state=" << state <<endl;
  //mainpic->setMarkers(marker, hier, comp);
  mainpic->setMarkers(true, true, true);
  figure->refreshAll();
}

bool MainWindow::toggleDashed() {
  mainpic->updating(false);
  if (dlines.empty()) {
    FPolyline *dline;
    for (int i=100; i<5000; i+=1000) {
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i, 100);
      dline->lineStyle(YaVecLine::dashed);
      dline->styleValue(8.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+200, 100);
      dline->lineStyle(YaVecLine::dotted);
      dline->styleValue(8.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+400, 100);
      dline->lineStyle(YaVecLine::dash_dotted);
      dline->styleValue(5.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+600, 100);
      dline->lineStyle(YaVecLine::dash_double_dotted);
      dline->styleValue(8.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+800, 100);
      dline->lineStyle(YaVecLine::dash_triple_dotted);
      dline->styleValue(8.0);
      dlines.push_back(dline);
    }
  } else {
    list<FPolyline*>::iterator dlineIt;
    for ( dlineIt = dlines.begin(); dlineIt != dlines.end(); ++dlineIt ) {
      if (!mainpic->remove(*dlineIt)) cerr << "ERROR: DashedLine element did not exist!" << endl; 
    }
    dlines.clear();
  }
  mainpic->updating(true);
  figure->refreshAll();
}

bool MainWindow::toggleArrowed() {
  mainpic->updating(false);
  if (alines.empty()) {
    FPolyline *aline;
    for (int i=900; i<8000; i+=499) {
      aline = mainpic->polyline();
      aline->addPoint(i, 200);
      aline->addPoint(4000, 2000);
      aline->addPoint(8500-i, 3000);
      aline->lineStyle(YaVecLine::solid);
      aline->styleValue(8.0);
      aline->lineThickness(1+(i&3));
      if ((i&1)==1) aline->forwardArrow(true);
      if ((i&1)==1) aline->penColor(3);
      if ((i&2)==2) aline->backwardArrow(true);
      aline->backwardArrowType(3);
      aline->forwardArrowType(YaVecArrow::closed_indented_butt);
      aline->forwardArrowSize(1.0, 100.0, 250.0);
      aline->forwardArrowSize(1.0, 50.0, 250.0);
      alines.push_back(aline);
    }
  } else {
    list<FPolyline*>::iterator alineIt;
    for ( alineIt = alines.begin(); alineIt != alines.end(); ++alineIt ) {
      if (!mainpic->remove(*alineIt)) cerr << "ERROR: DashedLine element did not exist!" << endl; 
    }
    alines.clear();
  }
  mainpic->updating(true);
  figure->refreshAll();
}

bool MainWindow::toggleBoxes() {
  mainpic->updating(false);
  if (boxes.empty()) {
    FBox *dbox;
    int j = 3;
    for (int i=100; i<4000; i+=499) {
      j++;
      dbox = mainpic->box(PosInt(i*2, 4200-i), PosInt((i+500)*2, 4200-i+500));
      dbox->lineStyle(YaVecLine::dashed);
      dbox->styleValue(static_cast<double>(i&15));
      dbox->fillColor(j);
      dbox->areaFill(20);
      boxes.push_back(dbox);

      dbox = mainpic->box(PosInt((i+200)*2, 4200-i+200), PosInt((i+500+200)*2, 4200-i+500+200));
      dbox->penColor(i&7);
      boxes.push_back(dbox);
    }
  } else {
    list<FBox*>::iterator boxIt;
    for ( boxIt = boxes.begin(); boxIt != boxes.end(); ++boxIt ) {
      if (!mainpic->remove(*boxIt)) cerr << "ERROR: Box element did not exist!" << endl;
    }
    boxes.clear();
  }
  mainpic->updating(true);
  figure->refreshAll();
}

bool MainWindow::toggleArcs() {
  mainpic->updating(false);
  if (arcs.empty()) {
    FArc *arc;
    for (int i=0; i<8; i++) {
      arc = mainpic->arc(PosInt(0+i*1000,4000), PosInt(600+i*1000,4600), PosInt(1200+i*1000,4000));
      arc->lineStyle(i&3);
      arc->penColor(i+8);
      arcs.push_back(arc);
      arc = mainpic->arc(PosInt(400+i*800, 2000), 380, true, M_PI*2*7/8, M_PI*2*i/8, (i%2)==1);
      arc->penColor(i&15);
      arc->lineStyle(i&3);
      arcs.push_back(arc);
    }
  } else {
    list<FArc*>::iterator arcIt;
    for ( arcIt = arcs.begin(); arcIt != arcs.end(); ++arcIt ) {
      if (!mainpic->remove(*arcIt)) cerr << "ERROR: ARC element did not exist!" << endl; 
    }
    arcs.clear();
  }
  mainpic->updating(true);
  figure->refreshAll();
}

bool MainWindow::toggleText() {
  mainpic->updating(false);
  if (texts.empty()) {
    FText *atext;
    double angle;
    FBox *nbox;
    PosInt ul, lr;
    for (int i=1; i<7; i++) {
      angle = 60*i;
      atext = mainpic->text();
      atext->penColor(i+3);
      atext->setOrigin(PosInt(4000, 4200));
      atext->setSize(30);
      atext->setAngle(angle);
      atext->setText("Text with angle AVA");
      atext->depth(11);
      atext->getBoundingBox(ul, lr);
      cout << "BBOX=" << ul << lr << endl;
      nbox = mainpic->box(ul, lr);
      nbox->depth(1);
      tboxes.push_back(nbox);
      texts.push_back(atext);
  }
  } else {
    list<FText*>::iterator textIt;
    for ( textIt = texts.begin(); textIt != texts.end(); ++textIt ) {
      if (!mainpic->remove(*textIt)) cerr << "ERROR: Text element did not exist!" << endl; 
    }
    texts.clear();
    list<FBox*>::iterator boxIt;
    for ( boxIt = tboxes.begin(); boxIt != tboxes.end(); ++boxIt ) {
      if (!mainpic->remove(*boxIt)) cerr << "ERROR: Text box element did not exist!" << endl; 
    }
    tboxes.clear();
  }
  mainpic->updating(true);
  figure->refreshAll();
}

int main(int argc, char *argv[])
{
  //Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
