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

  Handle<TimLabel>  Label1  = tim.createLabel();
  Handle<TimSignal> Signal0 = tim.createSignal();
  Handle<TimSignal> Signal1 = tim.createSignal();
  Handle<TimTime> Time1 = tim.createTime(0.0, 222.0, false, 50.0, 0.0, 10);

  Handle<TimList> List1 = tim.createList();

  Label1->setHeight(1000);
  Label1->setText("Hello World! This is a demo timing diagram from Sigschege!");
  Label1->setFontType(2);
  Label1->setFontSize(16);
  Label1->enableBorder(true);

  Signal0->setHeight(1000);
  Signal0->setText("Input");
  Signal0->setSigOffset(1500);
  Signal0->enableBorder(true);
  Signal0->setPadding(200);

  Signal1->setHeight(1000);
  Signal1->setText("Output");
  Signal1->setSigOffset(1500);
  Signal1->enableBorder(true);
  Signal1->setPadding(200);

  Time1->setHeight(1000);
  Time1->enableBorder(true);
  Time1->setPadding(200);
  Time1->setSigOffset(1500);
  
  Handle<Event> ev1 = Signal1->createEvent(State("X"), -50.0);
  for (int i=0; i<8; i++) {
    string nstate;
    if (i==0) nstate="0x12";
    else if (i==1) nstate="0xa7";
    else if (i==2) nstate="0x33";
    else if (i==3) nstate="0x65";
    else if (i==4) nstate="0x20";
    else if (i==5) nstate="0xf0";
    else if (i==6) nstate="0x0f";
    else if (i==7) nstate="0xbc";
    ev1 = Signal1->createEvent(State(nstate), i*31-1.0);
    ev1->setSlope(7.0);
    
  }
  Signal1->setNamedEvents(true);
  
  Handle<TimLabel> Label3 = List1->createLabel();
  Label3->setText("List in a List !!!");
  Label3->setHeight(1000);
  Label3->enableBorder(true);

  Handle<TimLabel> Label4 = List1->createLabel();
  Label4->setText("One");
  Label4->setHeight(1000);
  Label4->enableBorder(true);

  Handle<TimLabel> Label5 = List1->createLabel();
  Label5->setText("Two");
  Label5->setHeight(1000);
  Label5->enableBorder(true);

  List1->enableBorder(true);
  List1->addLast(Label3.Object());
  List1->addLast(Label4.Object());
  List1->addLast(Label5.Object());

  Handle<Event> s0ev_1 = Signal0->createEvent(State("1"), -200);
  Handle<Event> s0ev0 = Signal0->createEvent(State("0"), -5);
  Handle<Event> s0ev1 = Signal0->createEvent(State("X"), 80);
  Handle<Event> s0ev2 = Signal0->createEvent();
  Handle<Event> s0ev3 = Signal0->createEvent();
  Handle<Event> s0ev4 = Signal0->createEvent(State("1"), 50, &s0ev3);
  s0ev2->setReference(s0ev1);
  s0ev3->setReference(s0ev2);
  s0ev3->setReference(s0ev1);
  s0ev1->setSlope(20.0);
  s0ev2->setDelay(50.0);
  s0ev2->setSlope(10.0);
  s0ev3->setDelay(75.0);
  s0ev3->setSlope(10.0);
  s0ev2->setNewState(State("0"));
  s0ev3->setNewState(State("1"));
  s0ev4->setSlope(10.0);
  s0ev4->setNewState(State("0"));

  s0ev_1->setSlope(20.0);
  s0ev0->setSlope(10.0);

  
  Signal0->debugEvents();
  
  tim.addLast(Label1.Object());
  tim.addLast(Signal0.Object());
  tim.addLast(List1.Object());
  tim.addLast(Signal1.Object());
  tim.addLast(Time1.Object());

  tim.setWidth(10000);
  tim.setSliceSpace(50);

  tim.exportFig("test.fig");
  tim.exportEPS("test.eps");
  return;
}

void event(void) {
  EventList mainList;
  bool never_true = false;
  bool always_true = true;
  Handle<Event> ev1 = mainList.createEvent(State("1"), 80);
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

  ev2->setNewState(State("0"));
  ev3->setNewState(State("1"));
  
  Handle<Event> ev4 = mainList.createEvent(State("1"), 50, &ev3);
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
