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
// $Id: TimingMain.cpp 67 2004-12-05 23:05:10Z suupkopp $

#include "PyTimingDiagram.h"
#include <stdio.h>

using namespace std;

  
// add Signal class to TimingDiagram Module

static PyObject* TimSignal_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  TimSignalObject *self;
  cout << "Whoa! SIGNAL NEW called!" << endl;
  self = (TimSignalObject *)type->tp_alloc(type, 0);

  return (PyObject *) self;
}

static int TimSignal_init(TimSignalObject *self, PyObject *args, PyObject *kwds) {
  cout << "Whoa! SIGNAL INIT called!" << endl;
  //self->signal = new TimSignal();
  return (0);
}

static void TimSignal_dealloc(TimSignalObject *self) {
  //delete(self->signal);
  self->ob_type->tp_free((PyObject *)self);
}

static PyObject * TimSignal_addEvent(TimSignalObject *self) {
  self->signal->createEvent(State("1"), 20.0);
  printf("add event\n");
  return (Py_None);
}
  
static PyMethodDef TimSignal_methods[] = {
  {"addEvent", (PyCFunction)TimSignal_addEvent, METH_NOARGS,
   "Add an event to a signal."
  },
  {NULL}  /* Sentinel */
};

static int TimSignal_print(TimSignalObject *obj, FILE *fp, int flags)
{
  string label = obj->signal->getText();
  fprintf(fp, "\"<Signal: %s>\"", label.c_str());
  return 0;
}

static  PyTypeObject TimSignalType = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "Signal",               /*tp_name*/
  sizeof(TimSignalObject),   /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)TimSignal_dealloc,                         /*tp_dealloc*/
  (printfunc)TimSignal_print,            /*tp_print*/
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
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /*tp_flags*/
  "TimingDiagram",           /*tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  TimSignal_methods,                         /* tp_methods */
  0,                         /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)TimSignal_init,      /* tp_init */
  0,                         /* tp_alloc */
  TimSignal_new,                 /* tp_new */
};

// add a new TimingDiagram class to python

static PyObject* TimingDiagram_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  TimingDiagramObject *self;
    
  self = (TimingDiagramObject *)type->tp_alloc(type, 0);

  return (PyObject *) self;
}

static int TimingDiagram_init(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {
  cout << "Whoa! TimingDiagram INIT called!" << endl;
  self->tim = new TimingDiagram;
  return (0);
}

static void TimingDiagram_dealloc(TimingDiagramObject *self) {
  delete(self->tim);
  self->ob_type->tp_free((PyObject *)self);
}

static PyObject * TimingDiagram_exportFig(TimingDiagramObject *self) {
  self->tim->exportFig("demo.fig");
  printf("export fix\n");
  return (Py_None);
}
  
static PyObject * TimingDiagram_createSignal(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {

  char *label = "none";
  static char *kwlist[] = {"label", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &label))
    return NULL;
  string tmps;
  tmps = label;

  // create new C++ signal object with TimingDiagram class 
  Handle<TimSignal> newSignal;
  newSignal = self->tim->createSignal(tmps);
  self->tim->addLast(newSignal.Object());
  // create a Python signal object to return to user 
  PyObject *newPSignalObj;
  TimSignalObject *newPSignal;
  newPSignalObj = TimSignal_new(&TimSignalType, 0, 0);
  newPSignal = (TimSignalObject *)newPSignalObj;
  TimSignal_init(newPSignal, 0, 0);
  // attach C++ signal to Python signal
  newPSignal->signal = newSignal;
  return (newPSignalObj);
}
  
static int TimingDiagram_print(TimSignalObject *obj, FILE *fp, int flags)
{
  
  if (flags & Py_PRINT_RAW) {
  }
  else {
  }
  fprintf(fp, "<TimingDiagram Object>");
  return 0;
}

static PyMethodDef TimingDiagram_methods[] = {
  {"createSignal", (PyCFunction)TimingDiagram_createSignal, METH_VARARGS|METH_KEYWORDS,
   "Create a Signal in the Timing Diagram."
  },
  {
    "exportFig", (PyCFunction)TimingDiagram_exportFig, METH_VARARGS,
    "Export the Timing Diagram as Fig Format."
  },
  {NULL}  /* Sentinel */
};

static PyTypeObject TimingDiagramType = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "TimingDiagram",               /*tp_name*/
  sizeof(TimingDiagramObject),   /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)TimingDiagram_dealloc,                         /*tp_dealloc*/
  (printfunc)TimingDiagram_print,                         /*tp_print*/
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
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /*tp_flags*/
  "TimingDiagram",           /*tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  TimingDiagram_methods,                         /* tp_methods */
  0,                         /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)TimingDiagram_init,      /* tp_init */
  0,                         /* tp_alloc */
  TimingDiagram_new,                 /* tp_new */
};


PyMODINIT_FUNC
initTimingDiagram(void) 
{
  PyObject* m;
    
  //TimingDiagramType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&TimingDiagramType) < 0)
    return;
    
  //TimSignalType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&TimSignalType) < 0)
    return;
    
  m = Py_InitModule3("TimingDiagram", TimingDiagram_methods,
                     "TimingDiagram Base Class.");
    
  Py_INCREF(&TimingDiagramType);
  PyModule_AddObject(m, "TimingDiagram", (PyObject *)&TimingDiagramType);

  Py_INCREF(&TimSignalType);
  PyModule_AddObject(m, "Signal", (PyObject *)&TimSignalType);
}

