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

#include "PyTimSignal.h"
#include <stdio.h>

using namespace std;

extern "C" {
  
  // add a new object type to python

  static PyObject* TimSignal_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    TimSignalObject *self;
    
    self = (TimSignalObject *)type->tp_alloc(type, 0);

    return (PyObject *) self;
  }

  static int TimSignal_init(TimSignalObject *self, PyObject *args, PyObject *kwds) {
    self->signal = new TimSignal();
    return (0);
  }

  static void TimSignal_dealloc(TimSignalObject *self) {
    delete(self->signal);
    self->ob_type->tp_free((PyObject *)self);
  }

  static PyObject * TimSignal_addEvent(TimSignalObject *self) {
    self->signal->createEvent(State("1"), 20.0);
    printf("add event\n");
    return (Py_None);
  }
  
  static PyMethodDef TimSignal_methods[] = {
    {"addevent", (PyCFunction)TimSignal_addEvent, METH_NOARGS,
     "Add an event to a signal."
    },
    {NULL}  /* Sentinel */
  };

static  PyTypeObject TimSignalType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "Signal",               /*tp_name*/
    sizeof(TimSignalObject),   /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)TimSignal_dealloc,                         /*tp_dealloc*/
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

  PyMODINIT_FUNC
  initTimSignal(void) 
  {
    PyObject* m;
    
    TimSignalType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&TimSignalType) < 0)
        return;
    
    m = Py_InitModule3("TimSignal", TimSignal_methods,
                       "Timin Diagram Signal.");
    Py_INCREF(&TimSignalType);
    PyModule_AddObject(m, "TimSignal", (PyObject *)&TimSignalType);
  }

}
