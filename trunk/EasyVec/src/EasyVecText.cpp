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

#include <fstream>
#include <iostream>
#include "EasyVecText.h"
#include "EasyVecFigure.h"

using namespace std;

FT_Library  EasyVecText::freetype_lib;
bool EasyVecText::freetype_already_initialized = false;
bool EasyVecText::fix_fig2dev_quirk = false;

string EasyVecText::gs_fontpath = "/var/lib/defoma/gs.d/dirs/fonts/";

const char* easyvec_font_files[] = {
  "n021003l.pfb", // 0 = NimbusRomNo9L-Regu = Times-Roman
  "n021023l.pfb", // 1 = NimbusRomNo9L-ReguItal = Times-Italic
 	"n021004l.pfb", //  2 = NimbusRomNo9L-Medi = Times Bold
	"n021024l.pfb", //  3 = NimbusRomNo9L-MediItal = Times Bold Italic
	"a010013l.pfb", //  4 = URWGothicL-Book = AvantGarde Book
	"a010033l.pfb", //  5 = URWGothicL-BookObli = AvantGarde Book Oblique
	"a010015l.pfb", //  6 = URWGothicL-Demi = AvantGarde Demi
	"a010035l.pfb", //  7 = URWGothicL-DemiObli = AvantGarde Demi Oblique
	"b018012l.pfb", //  8 = URWBookmanL-Ligh = Bookman Light
	"b018032l.pfb", //  9 = URWBookmanL-LighItal = Bookman Light Italic
	"b018015l.pfb", // 10 = URWBookmanL-DemiBold = Bookman Demi
	"b018035l.pfb", // 11 = URWBookmanL-DemiBoldItal = Bookman Demi Italic
	"n022003l.pfb", // 12 = NimbusMonL-Regu = Courier
	"n022023l.pfb", // 13 = NimbusMonL-ReguObli = Courier Oblique
	"n022004l.pfb", // 14 = NimbusMonL-Bold = Courier Bold
	"n022024l.pfb", // 15 = NimbusMonL-BoldObli = Courier Bold Oblique
	"n019003l.pfb", // 16 = NimbusSanL-Regu = Helvetica
	"n019023l.pfb", // 17 = NimbusSanL-ReguItal = Helvetica Oblique
	"n019004l.pfb", // 18 = NimbusSanL-Bold = Helvetica Bold
	"n019024l.pfb", // 19 = NimbusSanL-BoldItal = Helvetica Bold Oblique
	"n019043l.pfb", // 20 = NimbusSanL-ReguCond = Helvetica Narrow
	"n019063l.pfb", // 21 = NimbusSanL-ReguCondItal = Helvetica Narrow Oblique
	"n019044l.pfb", // 22 = NimbusSanL-BoldCond = Helvetica Narrow Bold
	"n019064l.pfb", // 23 = NimbusSanL-BoldCondItal = Helvetica Narrow Bold Oblique
	"c059013l.pfb", // 24 = New Century Schoolbook Roman
	"c059033l.pfb", // 25 = New Century Schoolbook Italic
	"c059016l.pfb", // 26 = New Century Schoolbook Bold
	"c059036l.pfb", // 27 = New Century Schoolbook Bold Italic
	"p052003l.pfb", // 28 = URWPalladioL-Roma = Palatino Roman
	"p052023l.pfb", // 29 = URWPalladioL-Ital = Palatino Italic
	"p052004l.pfb", // 30 = URWPalladioL-Bold = Palatino Bold
	"p052024l.pfb", // 31 = URWPalladioL-BoldItal = Palatino Bold Italic
	"s050000l.pfb", // 32 = StandardSymL = Symbol
	"z003034l.pfb", // 33 = URWChanceryL-MediItal = Zapf Chancery Medium Italic
	"d050000l.pfb" // 34 = Zapf Dingbats
};

bool EasyVecText::initFreetype(void) {
  if (freetype_already_initialized) return true;
  int freetype_fail = FT_Init_FreeType( &freetype_lib );
  if (freetype_fail==0) {
    freetype_already_initialized = true;
    return true;
  } else {
    return false;
  }
}

/// update the dimensions - calls draw without a view
void EasyVecText::updateDimensions() {
  draw(NULL); 
}



EVPosInt EasyVecText::drawOrCalc(EasyVecView* view, bool noUpdate) {
  string::iterator text_iter;
  char cur_char;
  FT_UInt glyph_index, old_glyph_i;
  int ft_fail;
  FT_GlyphSlot  glyph;
  int resolution;
  EVPosInt char_origin;

  if (view) {
    resolution = figure->get_screen_dpi();    
  } else {
    resolution = figure->get_file_dpi();
    if (fix_fig2dev_quirk) {
      resolution *= 9;
      resolution /= 10;
    }
  }
  
  ft_fail = FT_Set_Char_Size(face,    /* handle to face object */
                             elmSize*64,   /* char_width in 1/64th of points  */
                             elmSize*64,   /* char_height in 1/64th of points */
                             resolution,     /* horizontal device resolution    */
                             resolution);    /* vertical device resolution      */
  if (ft_fail!=0) cerr << "Setting face size failed" << endl;

  if (view==0 && !noUpdate) textWidth = textHeight = 0;

  old_glyph_i = 0;
  char_origin = elmOrigin/figure->scale();
  
  for ( text_iter = elmText.begin(); text_iter != elmText.end(); ++text_iter ) {
    cur_char = *text_iter;
    glyph_index = FT_Get_Char_Index(face, cur_char);
    ft_fail = FT_Load_Glyph( face, glyph_index, FT_LOAD_NO_HINTING );
    if (view) ft_fail |= FT_Render_Glyph( face->glyph, FT_RENDER_MODE_MONO );
    if (ft_fail!=0) cerr << "Glyph loading failed for char " << *text_iter << glyph_index<< endl;
    glyph = face->glyph;
    if ( old_glyph_i && glyph_index ) {
      FT_Vector delta;
      FT_Get_Kerning( face, old_glyph_i, glyph_index, FT_KERNING_DEFAULT, &delta );
    }
    
    if (view) {
      FT_Bitmap cbitmap;
      cbitmap = glyph->bitmap;
      view->draw_char(char_origin-EVPosInt(0, glyph->bitmap_top), cbitmap.rows, cbitmap.width, cbitmap.pitch, cbitmap.buffer, elm_pen_color);
      char_origin = char_origin+EVPosInt(glyph->metrics.horiAdvance/64, 0);
    } else {
      textWidth += glyph->metrics.horiAdvance/64; // TODO: add kerning
      if (glyph->metrics.height/64>textHeight) textHeight = glyph->metrics.height/64;
    }
    old_glyph_i = glyph_index;
  }
}


void EasyVecText::draw(EasyVecView* view) {
  drawOrCalc(view);
}


bool EasyVecText::initEasyVecText() {
  bool success;
  elmFont = 0;
  elmSize = 18;
  elmOrigin = EVPosInt(300, 300);
  elmJustification = left;
  success = setFont(0);  
  // updateDimensions(); ... is already done in setFont!
  return success;
}


EasyVecText::EasyVecText() {
  initEasyVecText();
}

EasyVecText::EasyVecText(EasyVecCompound* parent_compound, EasyVecFigure* figure_compound)
  : EasyVecElm(parent_compound, figure_compound)
{
  initEasyVecText();
};


void EasyVecText::getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right) {
  upper_left  = elmOrigin - EVPosInt(0, textHeight); 
  lower_right = elmOrigin + EVPosInt(textWidth, 0);
}

bool EasyVecText::setText(const string &new_text) {
  elmText = new_text;
  updateDimensions();
  return true;
}

bool EasyVecText::setFont(int new_font) {
  int ft_fail;
  if (new_font>=0 && new_font<34) {
    elmFont = new_font;
    string font = gs_fontpath + string(easyvec_font_files[elmFont]);
    ft_fail = FT_New_Face(freetype_lib, font.c_str(), 0, &face );
    if (ft_fail!=0) cerr << "Face creation failed" << endl;
    updateDimensions();
    return ft_fail==0;
  } else return false;
}


bool EasyVecText::setSize(int new_size) {
  elmSize = new_size;
  updateDimensions();
  return true;
}

bool EasyVecText::setOrigin(EVPosInt new_origin) {
  elmOrigin = new_origin;
  return true;
}

int EasyVecText::sizeForBox(int height, int width, bool allowIncrease) {
  // TODO
}


void EasyVecText::saveElm(ofstream &fig_file) {
  vector<EVPosInt>::iterator points_iter;

  fig_file << "4 " << elmJustification << " " << elm_pen_color << " " << elm_depth
           << " 0 " << elmFont << " " << elmSize << " 0 4 " << textHeight << " " << textWidth
           << " " << elmOrigin.xpos() << " " << elmOrigin.ypos() << " "<< elmText
           << "\\001" << endl;
}
