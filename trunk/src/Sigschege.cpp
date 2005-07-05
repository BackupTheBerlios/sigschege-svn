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

#include <Python.h>
#include <stdio.h>
#include "PyTimingDiagram.h"

using namespace std;

static PyObject *td_module;

int main (int ARGC, char **ARGV) {
  int ret;
  PyObject *TimingDiagram_Module;
  Py_Initialize();
  initTimingDiagram();
  // TODO: why does importing from C++ not work???
//   TimingDiagram_Module = PyImport_ImportModule("TimingDiagram");
//   if (TimingDiagram_Module==0) {
//     PyErr_Print();
//   } else {
//     //td_module = PyImport_AddModule("TimingDiagram");
//     td_module = PyModule_GetDict(TimingDiagram_Module);
//     initTimingDiagram();
//     Py_INCREF(td_module);
//   }
  PyRun_SimpleString("import TimingDiagram");

  // TODO: automate version number and add GPL stuff
  cout << "Sigschege 0.0 - a program for creating timing diagrams" << endl;
  cout << "(c) 2004-2005 by Ulf Klaperski and Ingo Hinrichs" << endl;
  
  ret = Py_Main(ARGC, ARGV);
  
  Py_Finalize();

  return(ret);
}
