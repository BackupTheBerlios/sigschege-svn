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

#include <Python.h>
#include <stdio.h>
#include "PyTimingDiagram.h"

static PyObject *td_module;

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
  
  // add a new object type to python
  typedef struct {
    PyObject_HEAD
  } sig_EventObject;
  
  static PyTypeObject sig_EventType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "sig.Event",               /*tp_name*/
    sizeof(sig_EventObject),   /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "Event",                   /*tp_doc */
  };

  static PyMethodDef sig_methods[] = {
    {NULL}  /* Sentinel */
  };

  PyMODINIT_FUNC
  initsig(void) 
  {
    PyObject* m;
    
    sig_EventType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&sig_EventType) < 0)
        return;
    
    m = Py_InitModule3("sig", sig_methods,
                       "Example Sigschege extentions.");
    
    Py_INCREF(&sig_EventType);
    PyModule_AddObject(m, "Event", (PyObject *)&sig_EventType);
  }



}


int main (int ARGC, char **ARGV) {
  int ret;
  PyObject *TimingDiagram_Module;
  Py_Initialize();
  initspam();
  initsig();
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
  ret = Py_Main(ARGC, ARGV);
  
  Py_Finalize();

  return(ret);
}
