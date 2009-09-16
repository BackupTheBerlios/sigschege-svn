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

#ifndef _H_LAYOUTOBJECT
#define _H_LAYOUTOBJECT

#include "Handle.h"
#include <vector>
#include <YaVecFigure.h>
#include <fstream>

/// Generic layout object.
class LayoutObject {
public:
  //! The standard constructor
  LayoutObject();

  //! General constructor setting the reference and geometry.
  LayoutObject(LayoutObject *newReference, YaVec::PosInt origin = YaVec::PosInt(0,0), YaVec::PosInt size = YaVec::PosInt(0,0));

  
  //! The standard destructor
  virtual ~LayoutObject();

  virtual void setCompound(YaVec::FCompound *newCompound);

  /// Get a pointer to the compound of this layout object.
  YaVec::FCompound* getCompound();

  //! Paint this Layout Object
  virtual void paint(void);

  /// Save this Layout Object in XML
  virtual void save(std::ofstream &ssg_file);

  /// Register a layout object which references this layout object.
  /*!
   * Insert a layout object into the referrers list.
   * \return False if the layout object already  existed, true otherwise.
   * \param newReferrer pointer to the layout object that should be added to the referrers list
   * \sa unregisterReferrer
   */
  bool registerReferrer(Handle<LayoutObject> newReferrer);

  //! Unregister a layout object which references this layout object.  
  /*!
   * Remove a layout object from the referrers list. This is used if either the referring layout object is
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

  /// Get the upper position of this compound.
  int getUpperPos();
  /// Get the left position of this compound.
  int getLeftPos();
  /// Get the bottom position of this compound.
  int getBottomPos();
  /// Get the right position of this compound.
  int getRightPos();
  
  //! Set the Size of this Layout Object
  virtual void setSize(YaVec::PosInt newSize);

  //! Set the width.
  virtual void setWidth(int width);

  //! Set the height.
  virtual void setHeight(int height);

  //! Get the Size of this Layout Object
  virtual YaVec::PosInt getSize();

  //! Get the height of this Layout Object
  virtual int getHeight();

  //! Get the width of this Layout Object
  virtual int getWidth();

  //! Set the Origin of this Layout Object
  virtual void setOrigin(YaVec::PosInt newOrigin);

  //! Get the Origin of this Layout Object
  virtual YaVec::PosInt getOrigin();

  //! Enable/Disable drawing of the Border
  virtual void enableBorder(bool enable);

  /// Set the padding - virtual to allow adapting the content of the layout object.
  virtual void setPadding(int newPadding);

protected:
  /// The padding of this layout object.
  int      cPadding;
  /// The origin (upper left corner) of this layout object.
  YaVec::PosInt cOrigin;
  /// The size of this layout object.
  YaVec::PosInt cSize;
  /// Reference count.
  int refCount;
  /// The LayoutObject in which this one is contained.
  Handle<LayoutObject> cReference;
  /// LayoutObjects depending on this LayoutObject.
  std::vector< Handle<LayoutObject> > cReferrers;
  /// Determine if a border is needed.
  bool cDrawBorder;
  /// The compound this layout object is drawn into.
  YaVec::FCompound *cCompound;
};

#endif
