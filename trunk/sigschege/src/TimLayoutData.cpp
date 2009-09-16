// -*- c++ -*-
// TimLayoutData.cpp
// Copyright 2009 by ingo
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

#include "TimLayoutData.h"

TimLayoutData::TimLayoutData() {
	m_start_time = 0.0;
	m_end_time = 100.0;
	m_col_0_width = 50;
	m_col_1_width = 300;
}

TimLayoutData::~TimLayoutData() {

}

double TimLayoutData::get_start_time() {
	return m_start_time;
}

void TimLayoutData::set_start_time(double start) {
	m_start_time = start;
}

double TimLayoutData::get_end_time() {
	return m_end_time;
}

void TimLayoutData::set_end_time(double end) {
	m_end_time = end;
}

unsigned int TimLayoutData::get_col_0_width() {
	return m_col_0_width;
}

void TimLayoutData::set_col_0_width(unsigned int width) {
	m_col_0_width = width;
}

unsigned int TimLayoutData::get_col_1_width() {
	return m_col_1_width;
}

void TimLayoutData::set_col_1_width(unsigned int width) {
	m_col_1_width = width;
}
