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

#ifndef _H_LAYOUT
#define _H_LAYOUT

using namespace std;

#include "Object.h"
#include <EVPosInt.h>
#include <EasyVec.h>
#include <EasyVecElmPolyline.h>

enum LayoutID {BASIC,TEXT};

/// A Layout Class
/*!
 * Tthe Layout Class
 */
class Layout : public Object {
public:
  /// The standard constructor
  Layout();
  
  /// The standard destructor
  ~Layout();

  /// Return the ID of this layout object
  virtual LayoutID getID();

  /// Add a new child layout object
  void pushChild(Layout* newChild);

  /// Insert a layout object into the child list
  void insertChild(Layout* newChild, size_t index);

  /// Return a pointer of the child layout object at position index
  Layout* getChild(size_t index);

  /// Get the pointer of the parent layout object
  Layout* getParent();

  /// Set the parent layout object
  void setParent(Layout* parent);

  /// Delete the parent of this layout object
  void delParent();

  /// Set the boundary box of the layout object
  void setBox(const EVPosInt &newUL, const EVPosInt &newBR);

  /// Set the boundary box of the layout object 
  void setBox(int l, int u, int r, int b);

  /// return the Upper Left Point
  EVPosInt &getUL();

  /// return the Bottom Right Point
  EVPosInt &getBR();

  /// paint the layout object
  virtual void paint(EasyVec& cEasyVec);

private:
  EVPosInt cUL;
  EVPosInt cBR;
};
 
#endif // _H_LAYOUT
