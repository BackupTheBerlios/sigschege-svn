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

int main (int ARGC, char **ARGV) {
  TimingDiagram tim;

  tim.setWidth(10000);
  tim.setBorderTop(100);
  tim.setBorderLeft(100);
  tim.setBorderRight(100);
  tim.setBorderBottom(100);

  LayoutText *hello  = tim.createLayoutText("Hello");
  LayoutText *world  = tim.createLayoutText("World!");
  LayoutText *Slice1 = tim.createLayoutText();
  LayoutText *Slice2 = tim.createLayoutText();

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

  return(0);
}
