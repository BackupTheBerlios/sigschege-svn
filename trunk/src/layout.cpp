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

#include "layout.h"
#include <stdio.h>

CLayout::CLayout():CObject(){
}

CLayout::~CLayout(){
}

void CLayout::pushChild(CLayout* newChild) {
  CObject::pushChild((CObject*) newChild);
}

void CLayout::insertChild(CLayout* newChild, size_t index) {
  CObject::insertChild((CObject*) newChild,index);
}

CLayout* CLayout::getChild(size_t index) {
  return((CLayout*) CObject::getChild(index));
}

CLayout* CLayout::getParent() {
  return((CLayout*) CObject::getParent());
}

void CLayout::setParent(CLayout* parent) {
  CObject::setParent((CObject*) parent);
}

void CLayout::delParent() {
  CObject::delParent();
}

LayoutID CLayout::getID() {
  return(BASIC);
}
