// -*- c++ -*-
// \file 
// Copyright 2005 by Ulf Klaperski
//
// This file is part of YaVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// YaVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// YaVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the YaVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#ifndef _YAVECUTIL_H
#define _YAVECUTIL_H _YAVECUTIL_H

#include <cassert>
#include <new>

namespace YaVec {

  /// A template class which can hold a fixed array of any type.
  template <class Type, int size>
  class Array {
  public:
    /// The standard constructor, this will not initialize the array content.
    Array();
    /// A general constructor which initializes all array elements with initializer. 
    Array(Type initializer);
    /// The destructor.
    ~Array() {};

    /// Access element idx of the array.
    inline Type& operator[](int idx);  
    
  private:
    Type data[size];
  };

  template <class Type, int size>
    inline Type& Array<Type,size>::operator[](int idx) {
    assert(idx>=0 && idx<size);
    return data[idx];
  }

  template <class Type, int size>
  inline Array<Type,size>::Array<Type,size>() {
  }

  template <class Type, int size>
  inline Array<Type,size>::Array<Type,size>(Type initializer) {
    for (int i=0; i<size; i++) {
      data[i] = initializer;
    }
  }

  
}; // namespace

#endif /* _YAVECUTIL_H */
