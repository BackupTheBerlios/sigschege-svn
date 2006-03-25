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

#include "Event.h"
#include "EventList.h"

int main (int ARGC, char **ARGV) {
  EventList List;
  Event *test1,*test2;

  printf("List is empty %d\n", List.isEmpty());

  printf ("Added item number %d.\n",List.createEvent());
  printf ("Added item number %d.\n",List.createEvent());
 
  printf("List is empty %d\n\n", List.isEmpty());

  List.getEvent(0)->setDelay(1.5);
  List.getEvent(1)->setDelay(2.5);

  printf("Set Delay of Event 0 to %f\n",List.getEvent(0)->getDelay());
  printf("Set Delay of Event 1 to %f\n",List.getEvent(1)->getDelay());

  printf("Time of Event 0 is %f\n",List.getEvent(0)->getTime());
  printf("Time of Event 1 is %f\n",List.getEvent(1)->getTime());

  List.getEvent(0)->pushChild(List.getEvent(1));
  printf("\nSet Event 1 as Child of Event 0\n");

  printf("Time of Event 0 is %f\n",List.getEvent(0)->getTime());
  printf("Time of Event 1 is %f\n",List.getEvent(1)->getTime());


  List.getEvent(0)->setDelay(10);
  printf("\nSet Delay of Event 0 to %f\n\n",List.getEvent(0)->getDelay());

  printf("Time of Event 0 is %f\n",List.getEvent(0)->getTime());
  printf("Time of Event 1 is %f\n",List.getEvent(1)->getTime());

  printf ("\nDelete item number 0.\n",List.deleteEvent(0));
  printf ("Delete item number 0.\n",List.deleteEvent(0));

  printf("List is empty %d\n", List.isEmpty());
  return(0);
}
