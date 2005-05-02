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

#include "PyTimingDiagram.h"
#include <stdio.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// add Label class to TimingDiagram Module
////////////////////////////////////////////////////////////////////////////////

static PyObject* TimLabel_new(PyTypeObject *type, PyObject *argc, PyObject *kwds) {
  TimLabelObject *self;
  self = (TimLabelObject *)type->tp_alloc(type, 0);
  return(PyObject *) self;
}

static int TimLabel_init(TimLabelObject *self,PyObject *args, PyObject *kwds) {
 return (0);
}

static void TimLabel_dealloc(TimLabelObject *self) {
  //delete(self->signal);
  self->ob_type->tp_free((PyObject *)self);
}

static int TimLabel_print(TimLabelObject *obj, FILE *fp, int flags)
{
  fprintf(fp, "\"<Label: >\"");
  return 0;
}

static PyObject * TimLabel_setText(TimLabelObject *self, PyObject *args, PyObject *kwds) {
  char *text = "1";
  static char *kwlist[] = {"text", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &text))
    return NULL;
  string text_s = text;

  self->label->setText(text);
  Py_INCREF(Py_None);
  return (Py_None);
}

static PyMethodDef TimLabel_methods[] = {
  {"setText", (PyCFunction)TimLabel_setText, METH_VARARGS|METH_KEYWORDS, "Set the label text for this signal."},
  {NULL}  /* Sentinel */
};

static  PyTypeObject TimLabelType = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "Label",               /*tp_name*/
  sizeof(TimLabelObject),   /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)TimLabel_dealloc,                         /*tp_dealloc*/
  (printfunc)TimLabel_print,            /*tp_print*/
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
  "Label Object",            /*tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  TimLabel_methods,          /* tp_methods */
  0,                         /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)TimLabel_init,   /* tp_init */
  0,                         /* tp_alloc */
  TimLabel_new,              /* tp_new */
};

////////////////////////////////////////////////////////////////////////////////
// add Timescale class to TimingDiagram Module
////////////////////////////////////////////////////////////////////////////////

static PyObject* TimTimescale_new(PyTypeObject *type, PyObject *argc, PyObject *kwds) {
  TimTimescaleObject *self;
  self = (TimTimescaleObject *)type->tp_alloc(type, 0);
  return (PyObject *) self;
}

static int TimTimescale_init(TimTimescaleObject *self,PyObject *args, PyObject *kwds) {
  //self->signal = new TimSignal();
  return (0);
}

static void TimTimescale_dealloc(TimTimescaleObject *self) {
  //delete(self->signal);
  self->ob_type->tp_free((PyObject *)self);
}

static int TimTimescale_print(TimTimescaleObject *obj, FILE *fp, int flags)
{
  fprintf(fp, "\"<TimeScale: >\"");
  return 0;
}

static PyMethodDef TimTimescale_methods[] = {
  {NULL}  /* Sentinel */
};

static  PyTypeObject TimTimescaleType = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "Timescale",               /*tp_name*/
  sizeof(TimTimescaleObject),   /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)TimTimescale_dealloc,                         /*tp_dealloc*/
  (printfunc)TimTimescale_print,            /*tp_print*/
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
  "TimeScale Object",           /*tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  TimTimescale_methods,      /* tp_methods */
  0,                         /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)TimTimescale_init,      /* tp_init */
  0,                         /* tp_alloc */
  TimTimescale_new,                 /* tp_new */
};

////////////////////////////////////////////////////////////////////////////////
// add Signal class to TimingDiagram Module
////////////////////////////////////////////////////////////////////////////////

static PyObject* TimSignal_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  TimSignalObject *self;
  self = (TimSignalObject *)type->tp_alloc(type, 0);

  return (PyObject *) self;
}

static int TimSignal_init(TimSignalObject *self, PyObject *args, PyObject *kwds) {
  //self->signal = new TimSignal();
  return (0);
}

static void TimSignal_dealloc(TimSignalObject *self) {
  //delete(self->signal);
  self->ob_type->tp_free((PyObject *)self);
}

static PyObject * TimSignal_addEvent(TimSignalObject *self, PyObject *args, PyObject *kwds) {
  char *state1 = "1";
  char *state2 = "";
  double time = 0.0;
  static char *kwlist[] = {"time", "state1", "state2", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "ds|s", kwlist, &time, &state1, &state2))
    return NULL;
  string state1_s = state1;
  string state2_s = state2;

  self->signal->createEvent(State(state1_s, state2_s), time);
  Py_INCREF(Py_None);
  return (Py_None);
}

static PyObject * TimSignal_setLabel(TimSignalObject *self, PyObject *args, PyObject *kwds) {
  char *text = "1";
  static char *kwlist[] = {"text", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &text))
    return NULL;
  string text_s = text;

  self->signal->setText(text);
  Py_INCREF(Py_None);
  return (Py_None);
}

static PyMethodDef TimSignal_methods[] = {
  {"addEvent", (PyCFunction)TimSignal_addEvent, METH_VARARGS|METH_KEYWORDS, "Add an event to a signal."},
  {"setLabel", (PyCFunction)TimSignal_setLabel, METH_VARARGS|METH_KEYWORDS, "Set the label text for this signal."},
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

////////////////////////////////////////////////////////////////////////////////
// add TimeMarker class to TimingDiagram Module
////////////////////////////////////////////////////////////////////////////////

static PyObject* TimeMarker_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  TimeMarkerObject *self;
  self = (TimeMarkerObject *)type->tp_alloc(type, 0);

  return (PyObject *) self;
}

static int TimeMarker_init(TimeMarkerObject *self, PyObject *args, PyObject *kwds) {
  //self->signal = new TimeMarker();
  return (0);
}

static void TimeMarker_dealloc(TimeMarkerObject *self) {
  self->ob_type->tp_free((PyObject *)self);
}

static PyObject * TimeMarker_setColor(TimeMarkerObject *self, PyObject *args, PyObject *kwds) {
  int color = 0;
  static char *kwlist[] = {"color", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &color)) return NULL;

  self->timemarker->setColor(color);
  Py_INCREF(Py_None);
  return (Py_None);
}

static PyObject * TimeMarker_setTime(TimeMarkerObject *self, PyObject *args, PyObject *kwds) {
  double time = 0.0;
  static char *kwlist[] = {"time", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "d", kwlist, &time)) return NULL;

  self->timemarker->setTime(time);
  Py_INCREF(Py_None);
  return (Py_None);
}

static PyMethodDef TimeMarker_methods[] = {
  {"setTime", (PyCFunction)TimeMarker_setTime, METH_VARARGS|METH_KEYWORDS, "Set the time to be marked."},
  {"setColor", (PyCFunction)TimeMarker_setColor, METH_VARARGS|METH_KEYWORDS, "Set the color of this time marker."},
  {NULL}  /* Sentinel */
};

static int TimeMarker_print(TimeMarkerObject *obj, FILE *fp, int flags)
{
  double time = obj->timemarker->getTime();
  fprintf(fp, "\"<TimeMarker @  %d>\"", time);
  return 0;
}

static  PyTypeObject TimeMarkerType = {
  PyObject_HEAD_INIT(NULL)
  0,                         /*ob_size*/
  "Signal",               /*tp_name*/
  sizeof(TimeMarkerObject),   /*tp_basicsize*/
  0,                         /*tp_itemsize*/
  (destructor)TimeMarker_dealloc,                         /*tp_dealloc*/
  (printfunc)TimeMarker_print,            /*tp_print*/
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
  TimeMarker_methods,                         /* tp_methods */
  0,                         /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)TimeMarker_init,      /* tp_init */
  0,                         /* tp_alloc */
  TimeMarker_new,                 /* tp_new */
};

////////////////////////////////////////////////////////////////////////////////
// add a new TimingDiagram class to python
////////////////////////////////////////////////////////////////////////////////

static PyObject* TimingDiagram_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  TimingDiagramObject *self;
    
  self = (TimingDiagramObject *)type->tp_alloc(type, 0);

  return (PyObject *) self;
}

static int TimingDiagram_init(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {

  double startTime = 0.0;
  double endTime = 100.0;
  static char *kwlist[] = {"startTime", "endTime", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|dd", kwlist, &startTime, &endTime))
    return 1;

  self->tim = new TimingDiagram(startTime, endTime);
  self->tim->setWidth(10000);
  self->tim->setSliceSpace(50);
  return (0);
}

static void TimingDiagram_dealloc(TimingDiagramObject *self) {
  delete(self->tim);
  self->ob_type->tp_free((PyObject *)self);
}

static PyObject * TimingDiagram_exportFig(TimingDiagramObject *self) {
  self->tim->exportFig("demo.fig");
  Py_INCREF(Py_None);
  return (Py_None);
}

static PyObject *TimingDiagram_exportPic(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {
  char *filename = "demo.png";
  char *format = "png";
  static char *kwlist[] = {"filename", "format", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "ss", kwlist, &filename, &format))
    return NULL;
  string format_s = format;

  self->tim->exportAny( filename, format_s);
  printf("export fix\n");

  Py_INCREF(Py_None);
  return (Py_None);
}

static PyObject * TimingDiagram_createSignal(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {

  char *label = "none";
  static char *kwlist[] = {"label", "defaultSlope", NULL};
  static double defaultSlope = 0.0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s|d", kwlist, &label, &defaultSlope))
    return NULL;
  string tmps;
  tmps = label;

  // create new C++ signal object with TimingDiagram class 
  Handle<TimSignal> newSignal;
  newSignal = self->tim->createSignal(tmps);
  self->tim->addLast(newSignal.Object());
  newSignal->setDefaultSlope(defaultSlope);
  // create a Python signal object to return to user 
  PyObject *newPSignalObj;
  TimSignalObject *newPSignal;
  newPSignalObj = TimSignal_new(&TimSignalType, 0, 0);
  newPSignal = (TimSignalObject *)newPSignalObj;
  TimSignal_init(newPSignal, 0, 0);
  // attach C++ signal to Python signal
  newPSignal->signal = newSignal;
  Py_INCREF(newPSignalObj);
  return (newPSignalObj);
}

static LayoutObject* getLayoutFromPyObject(PyObject* pyobj) {
  LayoutObject* lptr;
  if (PyObject_IsInstance(pyobj, (PyObject*)&TimSignalType)) {
    lptr = (((TimSignalObject *)pyobj)->signal).Object();
  } else if (PyObject_IsInstance(pyobj, (PyObject*)&TimTimescaleType)) {
    lptr = (((TimTimescaleObject *)pyobj)->timescale).Object();
  } else if (PyObject_IsInstance(pyobj, (PyObject*)&TimLabelType)) {
    lptr = (((TimLabelObject *)pyobj)->label).Object();
  }
  return lptr;
}

static PyObject * TimingDiagram_createTimemarker(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {

  double time = 0.0;
  PyObject *topRef = 0;
  PyObject *bottomRef = 0;
  LayoutObject *topRefL = 0;
  LayoutObject *bottomRefL = 0;
  static char *kwlist[] = {"time", "topRef", "bottomRef", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "dOO", kwlist, &time, &topRef, &bottomRef))
    return NULL;

  topRefL = getLayoutFromPyObject(topRef);
  bottomRefL = getLayoutFromPyObject(bottomRef);

  // create new C++ signal object with TimingDiagram class 
  Handle<TimeMarker> newTimeMarker;
  newTimeMarker = self->tim->createTimeMarker(time, topRefL, bottomRefL);
  self->tim->addOverlay(newTimeMarker.Object());
  // create a Python signal object to return to user 
  PyObject *newPTimeMarkerObj;
  TimeMarkerObject *newPTimeMarker;
  newPTimeMarkerObj = TimeMarker_new(&TimeMarkerType, 0, 0);
  newPTimeMarker = (TimeMarkerObject *)newPTimeMarkerObj;
  TimeMarker_init(newPTimeMarker, 0, 0);
  // attach C++ signal to Python signal
  newPTimeMarker->timemarker = newTimeMarker;
  Py_INCREF(newPTimeMarkerObj);
  return (newPTimeMarkerObj);
}

static PyObject * TimingDiagram_createTimescale(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {

  char *label = "none";
  static char *kwlist[] = {"label", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s", kwlist, &label))
    return NULL;
  string tmps;
  tmps = label;

  // create new C++ signal object with TimingDiagram class 
  Handle<TimTime> newTimescale;
  newTimescale = self->tim->createTime(false, 50.0, 0.0, 10.0);
  self->tim->addLast(newTimescale.Object());
  // create a Python signal object to return to user 
  PyObject *newPTimescaleObj;
  TimTimescaleObject *newPTimescale;
  newPTimescaleObj = TimTimescale_new(&TimTimescaleType, 0, 0);
  newPTimescale = (TimTimescaleObject *)newPTimescaleObj;
  TimTimescale_init(newPTimescale, 0, 0);
  // attach C++ signal to Python signal
  newPTimescale->timescale = newTimescale;
  Py_INCREF(newPTimescaleObj);
  return (newPTimescaleObj);
}

static PyObject * TimingDiagram_createLabel(TimingDiagramObject *self, PyObject *args, PyObject *kwds) {

  char *label = "none";
  static char *kwlist[] = {"label", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s", kwlist, &label))
    return NULL;
  string tmps;
  tmps = label;

  // create new C++ signal object with TimingDiagram class 
  Handle<TimLabel> newLabel;
  newLabel = self->tim->createLabel();
  self->tim->addLast(newLabel.Object());
  // create a Python signal object to return to user 
  PyObject *newPLabelObj;
  TimLabelObject *newPLabel;
  newPLabelObj = TimLabel_new(&TimLabelType, 0, 0);
  newPLabel = (TimLabelObject *)newPLabelObj;
  TimLabel_init(newPLabel, 0, 0);
  // attach C++ signal to Python signal
  newPLabel->label = newLabel;
  Py_INCREF(newPLabelObj);
  return (newPLabelObj);
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
  {"createTimescale", (PyCFunction)TimingDiagram_createTimescale, METH_VARARGS|METH_KEYWORDS,
   "Create a Time Scale in the Timing Diagram."
  },
  {"createTimemarker", (PyCFunction)TimingDiagram_createTimemarker, METH_VARARGS|METH_KEYWORDS,
   "Create a Time Marker in the Timing Diagram."
  },
  {"createLabel", (PyCFunction)TimingDiagram_createLabel, METH_VARARGS|METH_KEYWORDS,
   "Create a Label in the Timing Diagram."
  },
  {
    "exportFig", (PyCFunction)TimingDiagram_exportFig, METH_VARARGS,
    "Export the Timing Diagram as Fig format."
  },
  {
    "exportPic", (PyCFunction)TimingDiagram_exportPic, METH_VARARGS|METH_KEYWORDS,
    "Export the Timing Diagram as any picture format."
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

////////////////////////////////////////////////////////////////////////////////
// initialize the sigschege objects
////////////////////////////////////////////////////////////////////////////////

PyMODINIT_FUNC
initTimingDiagram(void) 
{
  PyObject* m;
    
  //TimingDiagramType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&TimingDiagramType) < 0) return;
    
  //TimSignalType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&TimSignalType) < 0) return;

  //TimTimescaleType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&TimTimescaleType) < 0) return;

  //TimTimescaleType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&TimLabelType) < 0) return;
    
  if (PyType_Ready(&TimeMarkerType) < 0) return;
    
  m = Py_InitModule3("TimingDiagram", TimingDiagram_methods,
                     "TimingDiagram Base Class.");
    
  Py_INCREF(&TimingDiagramType);
  PyModule_AddObject(m, "TimingDiagram", (PyObject *)&TimingDiagramType);

  Py_INCREF(&TimSignalType);
  PyModule_AddObject(m, "Signal", (PyObject *)&TimSignalType);

  Py_INCREF(&TimTimescaleType);
  PyModule_AddObject(m, "Timescale", (PyObject *)&TimTimescaleType);

  Py_INCREF(&TimLabelType);
  PyModule_AddObject(m, "Label", (PyObject *)&TimLabelType);

  Py_INCREF(&TimeMarkerType);
  PyModule_AddObject(m, "Timemarker", (PyObject *)&TimeMarkerType);
}

