// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ingo Hinrichs, Ulf Klaperski
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


#include <stdio.h>
#include <stdlib.h>

#include "TimingDiagram.h"

using namespace std;
using namespace YaVec;

void layout (void) {
  TimingDiagram tim(0.0, 222.0);

  Handle<TimLabel>  Label1  = tim.createLabel();
  Handle<TimSignal> Signal0 = tim.createSignal("O");
  Handle<TimSignal> Signal1 = tim.createSignal("O");
  Handle<TimTime> Time1 = tim.createTime(0.0, 0.0, 0.0);

  Time1->setText1("Time");
  Time1->setText2("ns");

  Handle<TimList> List1 = tim.createList();

  Label1->setText("Hello World! This is a demo timing diagram from Sigschege!");
  Label1->setFontType(2);
  Label1->setFontSize(16);

  Signal0->setText("Input");

  Signal1->setText("Output");

  Handle<Event> ev1 = Signal1->createEvent(string("X"), -50.0);
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
    ev1 = Signal1->createEvent(nstate, i*31-1.0);
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

  Handle<TimSignal> Signal2 = tim.createSignal("O", false, 5);
  Handle<Event> s2[4];
  s2[0] = Signal2->createEvent(string("1"), 50);
  s2[1] = Signal2->createEvent(string("0"), 100);
  s2[2] = Signal2->createEvent(string("1"), 150);
  s2[3] = Signal2->createEvent(string("0"), 200);
  s2[2]->setSlope(10.0);
  Signal2->setText("Sync");

  Handle<TimLabel> Label5 = List1->createLabel();
  Label5->setText("Two");
  Label5->setHeight(1000);
  Label5->enableBorder(true);

  
  List1->addLast(Label3.Object());
  List1->addLast(Label4.Object());
  List1->addLast(Label5.Object());

  Handle<Event> s0ev_1 = Signal0->createEvent(string("1"), -200);
  Handle<Event> s0ev0 = Signal0->createEvent(string("0"), -5);
  Handle<Event> s0ev1 = Signal0->createEvent(string("X"), 80);
  Handle<Event> s0ev2 = Signal0->createEvent();
  Handle<Event> s0ev3 = Signal0->createEvent();
  Handle<Event> s0ev4 = Signal0->createEvent(string("1"), 50, &s0ev3);
  s0ev2->setReference(s0ev1);
  s0ev3->setReference(s0ev2);
  s0ev3->setReference(s0ev1);
  s0ev1->setSlope(20.0);
  s0ev2->setDelay(50.0);
  s0ev2->setSlope(10.0);
  s0ev3->setDelay(75.0);
  s0ev3->setSlope(10.0);
  s0ev2->setNewState(string("0"));
  s0ev3->setNewState(string("1"));
  s0ev4->setSlope(10.0);
  s0ev4->setNewState(string("0"));

  s0ev_1->setSlope(20.0);
  s0ev0->setSlope(10.0);

  
  Signal0->debugEvents();
  
  tim.addLast(Label1.Object());
  tim.addLast(Signal0.Object());
  //tim.addLast(List1.Object());
  tim.addLast(Signal1.Object());
  tim.addLast(Signal2.Object());
  tim.addLast(Time1.Object());


  tim.setWidth(10000);
  tim.setSliceSpace(50);

  Handle<TimeMarker> tm0;
  tm0 = tim.createTimeMarker(100.0, Signal1.Object(), Signal2.Object() );
  tm0->setColor(3);
  tim.addOverlay(tm0.Object());

  tim.exportFig("test.fig");
  tim.exportEPS("test.eps");

  Label1->setFontSize2(12);
  Label1->setText2(" (Created without the Python interface");
  tim.exportEPS("test2.eps");

  return;
}

void event(void) {
  TimSignal mainList;
  bool never_true = false;
  bool always_true = true;
  Handle<Event> ev1 = mainList.createEvent(string("1"), 80);
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

  ev2->setNewState(string("0"));
  ev3->setNewState(string("1"));
  
  Handle<Event> ev4 = mainList.createEvent(string("1"), 50, &ev3);
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

  FFigure myDiag;


  //mainList.setCompound(sig1cmp, 1000, 1000, 5000, 1000, 0.0, 300.0);
  myDiag.exportFig2dev("eps", "example_signal.eps");
  
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
