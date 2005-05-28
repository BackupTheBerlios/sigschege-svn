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

#ifndef _H_LAYOUTOBJECT
#define _H_LAYOUTOBJECT

using namespace std;

#include "Handle.t"
#include <vector>
#include <YaVecFigure.h>

class LayoutObject {
public:
  //! The standard constructor
  LayoutObject();

  //! General constructor setting the reference.
  LayoutObject( Handle<LayoutObject> newReference );

  
  //! The standard destructor
  virtual ~LayoutObject();

  virtual void setCompound(YaVec::FCompound *newCompound);

  YaVec::FCompound* getCompound();

  //! Paint this Layout Object
  virtual void paint(void);

  //! Register a layout object which references this layout object.
  /*!
   * Insert a layout object into the referrers list.
   * \return False if the layout object already  existed, true otherwise.
   * \param newReferrer pointer to the layout object that should be added to the referrers list
   * \sa unregisterReferrer
   */
  bool registerReferrer(Handle<LayoutObject> newReferrer);

  //! Unregister a layout object which references this layout object.  
  /*!
   * Remove an layout object from the referrers list. This is used if either the referring layout object is
   * deleted another layout object.
   * \return False if the layout object did not exist, true otherwise.
   * \param newReferrer pointer to the layout object that should be added to the referrers list
   * \sa registerReferrer
   */
  bool unregisterReferrer(Handle<LayoutObject> newReferrer);

  //! Get the pointer of the reference layout object.
  /*!
   * This function returns the pointer of the reference layout object or NULL if it has
   * no reference layout object.
   * \return A pointer to the reference layout object
   * \sa registerReferrer
   */
  Handle<LayoutObject> getReference();

  //! Set the reference layout object.
  /*!
   * The reference layout object to which the delay is relative to. This command will fail if
   * a loop of Layout Objects would be created.
   * \param new_reference The pointer to the new reference layout object
   * \return True if successful.
   * \sa hasreference getreference delreference
   */
  bool setReference(Handle<LayoutObject> new_reference);

  //! Delete the reference of this layout object.
  /*!
   * Delete the reference layout object. The parent layout object will NOT be destroyed by this function.
   * \sa hasreference getreference setreference
   */
  void delReference();

  //! Increment the reference count - only for use by Handle class!
  void incrementRefcount();
  //! Decrement the reference count - only for use by Handle class!
  void decrementRefcount();
  //! Return the current reference count 
  int objRefCount() { return refCount; }

  int getUpperPos();
  int getLeftPos();
  int getBottomPos();
  int getRightPos();
  
  //! Set the Size of this Layout Object
  void setSize(YaVec::PosInt newSize);

  //! Set the Size of this Layout Object
  void setSize(int width, int height);

  //! Set the width
  void setWidth(int width);

  //! Set the height
  void setHeight(int height);

  //! Get the Size of this Layout Object
  virtual YaVec::PosInt getSize();

  //! Get the height of this Layout Object
  virtual int getHeight();

  //! Set the Origin of this Layout Object
  void setOrigin(YaVec::PosInt newOrigin);

  //! Set the Origin of this Layout Object
  void setOrigin(int x, int y);

  //! Get the Origin of this Layout Object
  YaVec::PosInt getOrigin();

  //! Enable/Disable drawing of the Border
  void enableBorder(bool enable);

  void setPadding(int newPadding);

protected:
  // the padding of this layout object 
  int      cPadding;
  // the origin (upper left corner) of this layout object
  YaVec::PosInt cOrigin;
  YaVec::PosInt cSize;
  int refCount;
  Handle<LayoutObject> cReference;
  bool cDrawBorder;
  vector< Handle<LayoutObject> > cReferrers;
  YaVec::FCompound *cCompound;
};

#endif
