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
// $Id: $

#ifndef _H_OBJECTLIST
#define _H_OBJECTLIST

using namespace std;

#include <vector>
#include "Object.h"

/// Simple Class to handle object
/*!
 * This class provide basic functions to handle object.
 */
class ObjectList {
 public:
  
  /// Create a empty object list
  ObjectList();

  /// Delete the object list
  virtual ~ObjectList();

  /// Return a pointer the the object at position index
  virtual Object* getObject(size_t index);

  /// Create a new Object
  virtual size_t createObject(Object* newObject);
  
  /// Delete the object at position index
  virtual bool deleteObject(size_t index);

  /// Check if the object list is empty
  virtual bool isEmpty();

  /// Retrun the Size of the object list
  virtual const size_t size();
 private:
  vector <Object*> vec_ObjectList;
};

#endif
