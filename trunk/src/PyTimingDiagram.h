// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs, Ulf Klaperski
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
// $Id: State.h 72 2004-12-25 16:22:22Z ro_kenn $

#ifndef _H_PYTIMINGDIARAM
#define _H_PYTIMINGDIARAM

using namespace std;

#include <Python.h>
#include "TimingDiagram.h"

extern "C" {

  typedef struct {
    PyObject_HEAD
    TimingDiagram *tim;
  } TimingDiagramObject;

  PyMODINIT_FUNC initTimingDiagram(void);

}

#endif