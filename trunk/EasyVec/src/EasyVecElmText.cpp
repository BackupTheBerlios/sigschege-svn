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
// $Id: $

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

void EasyVecElmText::update_dimensions() {
  string::iterator text_iter;
  char cur_char;
  FT_UInt glyph_index, old_glyph_i;
  int ft_fail;
  FT_GlyphSlot  glyph;
  ft_fail = FT_Set_Char_Size(face,    /* handle to face object           */
                                 elm_size*64,       /* char_width in 1/64th of points  */
                                  elm_size*64,   /* char_height in 1/64th of points */
                                 1080,     /* horizontal device resolution    */
                                 1080);   /* vertical device resolution      */
  if (ft_fail!=0) cout << "Setting face size failed" << endl;

  text_width = text_height = 0;
  old_glyph_i = 0;
  for ( text_iter = elm_text.begin(); text_iter != elm_text.end(); ++text_iter ) {
    cur_char = *text_iter;
    glyph_index = FT_Get_Char_Index(face, cur_char );
         ft_fail = FT_Load_Glyph( face,          /* handle to face object */
                                  glyph_index,   /* glyph index           */
                                  FT_LOAD_NO_HINTING );  /* load flags, see below */
         //ft_fail = FT_Load_Char( face, cur_char, FT_LOAD_NO_HINTING );
         //    ft_fail |= FT_Render_Glyph( face->glyph, ft_render_mode_normal );
    if (ft_fail!=0) cout << "Glyph loading failed for char " << *text_iter << glyph_index<< endl;
    glyph = face->glyph;
    if ( old_glyph_i && glyph_index ) {
      FT_Vector delta;
      FT_Get_Kerning( face, old_glyph_i, glyph_index, FT_KERNING_DEFAULT, &delta );
      cout << "Kerning is " <<  (delta.x >> 6) << endl;
    }
    
    text_width += glyph->metrics.horiAdvance/64;
    //     if (glyph->metrics.width==0) {
    //       text_width += master->get_screen_dpi()*12/2/5;
    //     } else {
    //       text_width += glyph->metrics.width;
    //     }
    if (glyph->metrics.height>text_height) text_height = glyph->metrics.height;
    cout << "C/WD/HD/W/H: <" << cur_char << ">" << glyph->metrics.width/64 << ";" << glyph->advance.x/64 << ";" << text_width << ":" << text_height << endl;
    old_glyph_i = glyph_index;
  }
  cout << "Text width is " << text_width << endl;  
  cout << "Text height is " << text_height << endl;  
}


bool EasyVecElmText::init_EasyVecElmText() {
  int ft_fail;
  elm_font = 26;
  elm_size = 24;
  cout << "Getting font from " << easyvec_font_files[elm_font] << endl;
  ft_fail = FT_New_Face(freetype_lib, easyvec_font_files[elm_font], // Century Schoolbook L Roman
                          0, &face );
  if (ft_fail!=0) cout << "Face creation failed" << endl;
  

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
  upper_left  = elm_origin - EVPosInt(0, text_height); 
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


void EasyVecElmText::draw(EasyVecView* view) {
  int xscale;
  EasyVec *testptr;
  testptr->scale();
  xscale = master->scale();
  //    view->draw_line((*points_iter1)/xscale, (*points_iter2)/xscale, elm_pen_color);
}


void EasyVecElmText::save_elm(ofstream &fig_file) {
  vector<EVPosInt>::iterator points_iter;

  fig_file << "4 0 " << elm_pen_color << " " << elm_depth
           << " 0 " << elm_font << " " << elm_size << " 0 4 " << text_height << " " << text_width
           << " " << elm_origin.xpos() << " " << elm_origin.ypos() << " "<< elm_text
           << "\\001" << endl;
}
