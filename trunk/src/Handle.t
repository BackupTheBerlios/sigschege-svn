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
// $Id:  $

#ifndef _T_HANDLE
#define _T_HANDLE

using namespace std;

//! The Handle class allows safer handling of objects which are accessed with pointers.
/*!
 * Requirements for customer classes:
 * Integer variable refCount, a reference counter.
 * Function void incrementRefcount(void) and void decrementRefcount(void) to change the refCount.
 * Function int objRefCount(void) to return the refCount,
 */
template<class T> class Handle {

  public:
  //! The standard constructor
  /*!
   * This constructor will create a handle that does not point to an object.
   */
  Handle() {
    myObject = 0;
  }
  
  //! A general constructor, initialized with a pointer to its object. 
  /*!
   * This constructor will store the object pointer and increment its reference counter.
   */
  Handle(T* ObjectPtr) {
    myObject = ObjectPtr;
    if (myObject != 0) {
      myObject->incrementRefcount();
    }
  }

  //! The copy constructor.
  /*!
   * The copy constructor creates a new handle for the object of the copied object, therefore
   * the new object must increment its reference counter.
   */
  Handle<T>(const Handle<T>& orig) {
    myObject = orig.myObject;
    if (myObject != 0) {
      myObject->incrementRefcount();
    }
  }
    
  //! The destructor.
  /*!
   * It decrements the object's reference counter. If that is zero, the object will be deleted,
   * since obviously no one is interested in it any more.
   */
  ~Handle() {
    if (myObject != 0) {
      myObject->decrementRefcount();
      if (myObject->objRefCount()==0) {
        delete myObject;
      }
    }
  }

  //! Returns a pointer to the object.
  /*!
   * This will return a pointer to the object allowing its member functions to be called.
   * NOTE: do not store the pointer! This would bypass the security of the Handle class, as
   * you might later use an obsolete pointer.
   */
  T* operator->() { return myObject; }
  
  T* Object(void) { return myObject; }
  
private:
  T* myObject;
};

#endif // _T_HANDLE
