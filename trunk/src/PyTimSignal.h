// -*- c++ -*-
// \file 
// Copyright 2005 by Ingo Hinrichs, Ulf Klaperski
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

#ifndef _H_PYSIGNAL
#define _H_PYSIGNAL

using namespace std;

#include <Python.h>
#include "TimSignal.h"


typedef struct {
  PyObject_HEAD
  TimSignal *signal;
} TimSignalObject;


//extern PyTypeObject TimSignalType;

extern "C" {

  PyMODINIT_FUNC initTimSignal(void);

}

#endif
