// -*- c++ -*-
/// \file 
 
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
#include "EasyVecElmText.h"
#include "EasyVec.h"

using namespace std;

FT_Library  EasyVecElmText::freetype_lib;
bool EasyVecElmText::freetype_already_initialized = false;

const char* easyvec_font_files[] = {
  "/var/lib/defoma/gs.d/dirs/fonts/n021003l.pfb", // 0 = NimbusRomNo9L-Regu = Times-Roman
  "/var/lib/defoma/gs.d/dirs/fonts/n021023l.pfb", // 1 = NimbusRomNo9L-ReguItal = Times-Italic
 	"", //  2 = Times Bold
	"", //  3 = Times Bold Italic
	"", //  4 = AvantGarde Book
	"", //  5 = AvantGarde Book Oblique
	"", //  6 = AvantGarde Demi
	"", //  7 = AvantGarde Demi Oblique
	"", //  8 = Bookman Light
	"", //  9 = Bookman Light Italic
	"", // 10 = Bookman Demi
	"", // 11 = Bookman Demi Italic
	"", // 12 = Courier
	"", // 13 = Courier Oblique
	"", // 14 = Courier Bold
	"", // 15 = Courier Bold Oblique
	"", // 16 = Helvetica
	"", // 17 = Helvetica Oblique
	"", // 18 = Helvetica Bold
	"", // 19 = Helvetica Bold Oblique
	"", // 20 = Helvetica Narrow
	"", // 21 = Helvetica Narrow Oblique
	"", // 22 = Helvetica Narrow Bold
	"", // 23 = Helvetica Narrow Bold Oblique
	"/usr/share/fonts/type1/gsfonts/c059013l.pfb", // 24 = New Century Schoolbook Roman
	"/usr/share/fonts/type1/gsfonts/c059033l.pfb", // 25 = New Century Schoolbook Italic
	"/usr/share/fonts/type1/gsfonts/c059016l.pfb", // 26 = New Century Schoolbook Bold
	"/usr/share/fonts/type1/gsfonts/c059036l.pfb", // 27 = New Century Schoolbook Bold Italic
	"", // 28 = Palatino Roman
	"", // 29 = Palatino Italic
	"", // 30 = Palatino Bold
	"", // 31 = Palatino Bold Italic
	"", // 32 = Symbol
	"", // 33 = Zapf Chancery Medium Italic
	"" // 34 = Zapf Dingbats

};

bool EasyVecElmText::init_freetype(void) {
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
void EasyVecElmText::update_dimensions() {
  draw(NULL); 
}

void EasyVecElmText::draw(EasyVecView* view) {
  string::iterator text_iter;
  char cur_char;
  FT_UInt glyph_index, old_glyph_i;
  int ft_fail;
  FT_GlyphSlot  glyph;
  int resolution;
  EVPosInt char_origin;

  if (view) {
    resolution = master->get_screen_dpi();    
  } else {
    resolution = master->get_file_dpi();
    if (fix_fig2dev_quirk) {
      resolution *= 9;
      resolution /= 10;
    }
  }
  
  ft_fail = FT_Set_Char_Size(face,    /* handle to face object */
                             elm_size*64,   /* char_width in 1/64th of points  */
                             elm_size*64,   /* char_height in 1/64th of points */
                             resolution,     /* horizontal device resolution    */
                             resolution);    /* vertical device resolution      */
  if (ft_fail!=0) cerr << "Setting face size failed" << endl;

  if (view!=0) text_width = text_height = 0;

  old_glyph_i = 0;
  char_origin = elm_origin/master->scale();
  
  for ( text_iter = elm_text.begin(); text_iter != elm_text.end(); ++text_iter ) {
    cur_char = *text_iter;
    glyph_index = FT_Get_Char_Index(face, cur_char );
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
      text_width += glyph->metrics.horiAdvance/64; // TODO: add kerning
      if (glyph->metrics.height>text_height) text_height = glyph->metrics.height;
    }
    old_glyph_i = glyph_index;
  }
}


bool EasyVecElmText::init_EasyVecElmText() {
  int ft_fail;
  elm_font = 0;
  elm_size = 18;
  elm_origin = EVPosInt(300, 300);
  ft_fail = FT_New_Face(freetype_lib, easyvec_font_files[elm_font], // Century Schoolbook L Roman
                          0, &face );
  if (ft_fail!=0) cerr << "Face creation failed" << endl;
  
  update_dimensions();
  cout << "Finis!" << endl;
  return ft_fail==0;
}


EasyVecElmText::EasyVecElmText() {
  init_EasyVecElmText();
}

EasyVecElmText::EasyVecElmText(EasyVecElmCompound* parent_compound, EasyVec* master_compound)
  : EasyVecElm(parent_compound, master_compound)
{
  init_EasyVecElmText();
};


void EasyVecElmText::get_limits(EVPosInt &upper_left, EVPosInt &lower_right) {
  upper_left  = elm_origin - EVPosInt(0, text_height/master->scale()); 
  lower_right = elm_origin + EVPosInt(text_width, 0);
}


bool EasyVecElmText::set_text(const string &new_text) {
  elm_text = new_text;
  update_dimensions();
  return true;
}

bool EasyVecElmText::set_size(int new_size) {
  elm_size = new_size;
  update_dimensions();
  return true;
}

bool EasyVecElmText::set_origin(EVPosInt new_origin) {
  elm_origin = new_origin;
  return true;
}

void EasyVecElmText::save_elm(ofstream &fig_file) {
  vector<EVPosInt>::iterator points_iter;

  fig_file << "4 0 " << elm_pen_color << " " << elm_depth
           << " 0 " << elm_font << " " << elm_size << " 0 4 " << text_height << " " << text_width
           << " " << elm_origin.xpos() << " " << elm_origin.ypos() << " "<< elm_text
           << "\\001" << endl;
}
