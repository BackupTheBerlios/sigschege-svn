// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs
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
// $Id$

using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include "TimingDiagram.h"

void layout (void) {
  TimingDiagram tim;

  Handle<TimLabel> Label1 = tim.createLabel();
  Handle<TimSignal> Signal0 = tim.createSignal();
  
  Handle<TimSignal> Signal1 = tim.createSignal();
  Handle<TimTime> Time1 = tim.createTime(0.0, 20.3, false, 1.0, 0.0, 0.2);

  Label1->setULPos(0,0);
  Label1->setBRPos(1000,10000);
  Label1->setText("Hello World! This is a demo timing diagram from Sigschege!");
  Label1->setFontType(2);
  Label1->setFontSize(16);
  Label1->enableBorder(true);
  
  Signal0->setULPos(1100,0);
  Signal0->setBRPos(2100,10000);
  Signal0->setText("Input");
  Signal0->setSigOffset(1500);
  Signal0->enableBorder(true);
  Signal0->setPadding(200);

  Signal1->setULPos(2200,0);
  Signal1->setBRPos(3200,10000);
  Signal1->setText("Output");
  Signal1->setSigOffset(1500);
  Signal1->enableBorder(true);
  Signal1->setPadding(200);

  Time1->setULPos(3300,0);
  Time1->setBRPos(4300,10000);
  Time1->enableBorder(true);
  Time1->setPadding(200);
  Time1->setSigOffset(1500);
  
  Handle<Event> ev1 = Signal1->createEvent("1", 100);

  Handle<Event> s0ev1 = Signal0->createEvent("1", 80);
  Handle<Event> s0ev2 = Signal0->createEvent();
  Handle<Event> s0ev3 = Signal0->createEvent();
  Handle<Event> s0ev4 = Signal0->createEvent("1", 50, &s0ev3);
  s0ev2->setReference(s0ev1);
  s0ev3->setReference(s0ev2);
  s0ev3->setReference(s0ev1);
  s0ev1->setSlope(20.0);
  s0ev2->setDelay(50.0);
  s0ev2->setSlope(10.0);
  s0ev3->setDelay(75.0);
  s0ev3->setSlope(10.0);
  s0ev2->setNewState("0");
  s0ev3->setNewState("1");
  s0ev4->setSlope(10.0);



  tim.addLast(Label1.Object());
  tim.addLast(Signal0.Object());
  tim.addLast(Signal1.Object());
  tim.addLast(Time1.Object());


  tim.exportFig("test.fig");
  tim.exportEPS("test.eps");
  return;
}

void event(void) {
  EventList mainList;
  bool never_true = false;
  bool always_true = true;
  Handle<Event> ev1 = mainList.createEvent("1", 80);
  ev1->setSlope(20.0);
  Handle<Event> ev2 = mainList.createEvent();
  Handle<Event> ev3 = mainList.createEvent();
  ev2->setDelay(50.0);
  ev2->setSlope(10.0);
  always_true = always_true && ev2->setReference(ev1);
  always_true = always_true && ev3->setReference(ev2);
  ev3->setDelay(75.0);
  ev3->setSlope(10.0);
  always_true = always_true && ev3->setReference(ev1);

  never_true = ev2->setReference(ev2);
  never_true = never_true || ev1->setReference(ev3);

  ev2->setNewState("0");
  ev3->setNewState("1");
  
  Handle<Event> ev4 = mainList.createEvent("1", 50, &ev3);
  ev4->setSlope(10.0);

  if (always_true && (!never_true)) {
    cout << "Fine! Loop breaking worked" << endl; 
  } else {
    cout << "Fine! Loop breaking worked" << endl; 
  }
  
  cout << "Time of event1: " << ev1->getTime(0) << ":" << ev1->getTime(100) << endl; 
  cout << "Time of event2: " << ev2->getTime(0) << ":" << ev2->getTime(100) << endl;
  cout << "Time of event3: " << ev3->getTime(0) << ":" << ev3->getTime(100) << endl;
  cout << "Time of event4: " << ev4->getTime(0) << ":" << ev4->getTime(100) << endl;
  cout << "First event after 105: " << (mainList.getEventAfter(105))->getTime() << endl << endl;
  
  mainList.debugEvents();

  EasyVecFigure myDiag;

  EasyVecCompound *sig1cmp =  myDiag.compound();

  mainList.setCompound(sig1cmp, 1000, 1000, 5000, 1000, 0.0, 300.0);
  mainList.paint();
  myDiag.export_fig2dev("eps", "example_signal.eps");
  
  return;
}


int main (int ARGC, char **ARGV) {
  if (ARGC>1) {
    if (ARGV[1][0]=='l') layout();
    else if (ARGV[1][0]=='e') event();
  }
  else layout();
  return(0);
}
