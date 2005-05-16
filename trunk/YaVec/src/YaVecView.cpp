// -*- c++ -*-
// \file  
// Copyright 2004, 2005 by Ulf Klaperski
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

#include "YaVecView.h"
#include "YaVecFigure.h"

YaVecView::YaVecView(YaVecFigure *picture) {
  picture->registerView(this);
  mypicture = picture;
};

void YaVecView::drawArrow(const YVPosInt &tip, const YVPosInt &from, int color, YaVecArrow::arrowInfo *arrow) {
  double angle = tip.angle(from);
  drawArrow(tip, angle, color, arrow);
}


YaVecView::~YaVecView() {
  mypicture->unregisterView(this);
};