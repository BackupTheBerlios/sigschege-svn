// -*- c++ -*-
// \file  
// Copyright 2004, 2005 by Ulf Klaperski
//
// This file is part of EasyVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// EasyVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// EasyVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the EasyVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#include "EasyVecView.h"
#include "EasyVecFigure.h"

EasyVecView::EasyVecView(EasyVecFigure *picture) {
  picture->registerView(this);
  mypicture = picture;
};

void EasyVecView::drawArrow(const EVPosInt &tip, const EVPosInt &from, int color, EasyVecArrow::arrowInfo *arrow) {
  double angle = tip.angle(from);
  drawArrow(tip, angle, color, arrow);
}


EasyVecView::~EasyVecView() {
  mypicture->unregisterView(this);
};
