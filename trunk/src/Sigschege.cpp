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
// $Id: TimingMain.cpp 67 2004-12-05 23:05:10Z suupkopp $

#include <Python.h>
#include <stdio.h>

extern "C" {

  static PyObject* spam_Hello(PyObject *self, PyObject *args) {
    printf("Hello\n");
    return Py_BuildValue("i", 1);
  }

  static PyMethodDef SpamMethods[] = {
    {"Hello",  spam_Hello, METH_VARARGS,"Output Hello."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
  };

  PyMODINIT_FUNC initspam(void) {
    (void) Py_InitModule("spam", SpamMethods);
  }
  
}


int main (int ARGC, char **ARGV) {
  int ret;

  Py_Initialize();
  initspam();

  ret = Py_Main(ARGC, ARGV);
  
  Py_Finalize();

  return(ret);
}
