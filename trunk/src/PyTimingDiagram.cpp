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

#include "PyTimingDiagram.h"
#include <stdio.h>

using namespace std;

extern "C" {
  
  // add a new object type to python

  static PyObject* TimingDiagram_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    TimingDiagramObject *self;
    
    self = (TimingDiagramObject *)type->tp_alloc(type, 0);

    return (PyObject *) self;
  }

  static int TimingDiagram_init(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {
    self->tim = new TimingDiagram();
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
  
  static PyMethodDef TimingDiagram_methods[] = {
    {"exportFig", (PyCFunction)TimingDiagram_exportFig, METH_NOARGS,
     "Export the Timing Diagram as Fif Format."
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
    
    TimingDiagramType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&TimingDiagramType) < 0)
        return;
    
    m = Py_InitModule3("TimingDiagram", TimingDiagram_methods,
                       "TimingDiagram Base Class.");
    
    Py_INCREF(&TimingDiagramType);
    PyModule_AddObject(m, "TimingDiagram", (PyObject *)&TimingDiagramType);
  }

}
