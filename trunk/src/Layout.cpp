// -*- c++ -*-
/// \file 
 
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

using namespace std;

#include "Layout.h"
#include <stdio.h>

Layout::Layout():Object(){
}

Layout::~Layout(){
}

void Layout::pushChild(Layout* newChild) {
  Object::pushChild((Object*) newChild);
}

void Layout::insertChild(Layout* newChild, size_t index) {
  Object::insertChild((Object*) newChild,index);
}

Layout* Layout::getChild(size_t index) {
  return((Layout*) Object::getChild(index));
}

Layout* Layout::getParent() {
  return((Layout*) Object::getParent());
}

void Layout::setParent(Layout* parent) {
  Object::setParent((Object*) parent);
}

void Layout::delParent() {
  Object::delParent();
}

LayoutID Layout::getID() {
  return(BASIC);
}
