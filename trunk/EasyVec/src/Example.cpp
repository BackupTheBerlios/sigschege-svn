// -*- c++ -*-
// \file  
// Copyright 2004 by Ulf Klaperski
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

#include "EVPosInt.h"
#include "EasyVec.h"
#include "EasyVecElmPolyline.h"
#include "EasyVecElmText.h"
#include <iostream>
#include <vector>

using namespace std;
int main(void) {
  EVPosInt Schortens, Dortmund;
  EVPosInt Prag(8700, 8000);

  Schortens.set(3000, 0);
  Dortmund.set(2000, 2500);

  vector<EVPosInt> points1;
  points1.push_back(EVPosInt(1200, 800));
  points1.push_back(EVPosInt(1200, 2000));
  points1.push_back(EVPosInt(5000, 2000));
  points1.push_back(EVPosInt(3000, 3000));
  points1.push_back(EVPosInt(1200, 1000));
  
  cout << "Prag ist bei " << Prag << endl;
  cout << "Entfernung Schortens-Prag: " << Schortens.distance(Prag) << endl;

  ////////////////////////////////////////////////////////////////////////////////

  EasyVec mypic;

//   EasyVecElmPolyline *line1 =  mypic.polyline();

//   line1->add_point(Schortens);
//   line1->add_point(1000, 500);
//   line1->add_point(500, 1000);
//   line1->add_point(1000, 1000);

//   EasyVecElmCompound *cmp1 =  mypic.compound();
//   EasyVecElmCompound *cmp1a =  cmp1->compound();

//   EasyVecElmPolyline *line2 =  cmp1a->polyline();

//   line2->add_points(points1);
//   EasyVecElmCompound *cmp2 =  mypic.compound();
//   EasyVecElmPolyline *line3 =  cmp2->polyline();
//   line3->add_point(Schortens+Prag);
//   line3->add_point(Prag);
//   line3->add_point(Schortens);
//   line3->add_point(Dortmund);
//   line3->pen_color(4);

  mypic.save("example.fig");

  EasyVecElmText *txt = mypic.text();
  txt->setText("Moin");
  EVPosInt text_ul, text_lr;
  txt->setOrigin(EVPosInt(500, 3000));
  //txt->setText("Use pipes rather than intermediate files");
  txt->getBoundingBox(text_ul, text_lr);

  EasyVecElmBox *textbox =  mypic.box(text_ul-EVPosInt(0, 0), text_lr+EVPosInt(0, 0));
  
  // EasyVecElmPolyline *line4 =  mypic.polyline();
  // line4->add_point(text_lr);
  // line4->add_point(text_lr-EVPosInt(0, 500));

  cout << "Lower Right is " << text_lr << endl;
  mypic.save("example_text.fig");
}
