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

  tim.setWidth(10000);
  tim.setBorderTop(100);
  tim.setBorderLeft(100);
  tim.setBorderRight(100);
  tim.setBorderBottom(100);

  TimLabel *hello  = tim.createTimLabel("Hello");
  TimLabel *world  = tim.createTimLabel("World!");
  TimLabel *Slice1 = tim.createTimLabel();
  TimLabel *Slice2 = tim.createTimLabel();

  hello->setFontType(11);
  hello->setFontSize(10);
  hello->drawBoundaryBox(true);
  hello->setPadding(50);

  world->setFontType(10);
  world->setFontSize(20);
  world->setPadding(50);

  Slice1->setBoundaryHeight(200);
  Slice1->drawBoundaryBox(true);
  Slice1->setPadding(50);

  Slice2->setText("Slice2");
  Slice2->setPadding(50);

  tim.addLast(hello);
  tim.addLast(world);
  tim.addLast(Slice1);
  tim.addLast(Slice2);
  tim.addLast(Slice2);
  
  tim.save("test.fig");

  return;
}

void event(void) {
  EventList mainList;
  bool never_true = false;
  bool always_true = true;
  Handle<Event> ev1 = mainList.createEvent("1", 100);
  Handle<Event> ev2 = mainList.createEvent();
  Handle<Event> ev3 = mainList.createEvent();
  ev2->setDelay(50.0);
  always_true = always_true && ev2->setReference(ev1);
  always_true = always_true && ev3->setReference(ev2);
  ev3->setDelay(25.0);
  always_true = always_true && ev3->setReference(ev1);

  never_true = ev2->setReference(ev2);
  never_true = never_true || ev1->setReference(ev3);

  ev2->setNewState("0");
  ev3->setNewState("1");
  
  Handle<Event> ev4 = mainList.createEvent("1", 50, &ev3);

  if (always_true && (!never_true)) {
    cout << "Fine! Loop breaking worked" << endl; 
  } else {
    cout << "Fine! Loop breaking worked" << endl; 
  }
  
  cout << "Time of event1: " << ev1->getTime() << endl; 
  cout << "Time of event2: " << ev2->getTime() << endl;
  cout << "Time of event3: " << ev3->getTime() << endl;
  cout << "Time of event4: " << ev4->getTime() << endl;
  cout << "First event after 105: " << (mainList.getEventAfter(105))->getTime() << endl << endl;
  
  mainList.debugEvents();

  EasyVec myDiag;

  EasyVecElmCompound *sig1cmp =  myDiag.compound();

  mainList.setCompound(sig1cmp, 1000, 1000, 5000, 1000, 0.0, 222.0);
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
