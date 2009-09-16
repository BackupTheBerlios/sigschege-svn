// -*- c++ -*-
// TimLayoutData.h
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



#ifndef TIMLAYOUTDATA_H_
#define TIMLAYOUTDATA_H_

class TimLayoutData {

public:
	TimLayoutData();
	virtual ~TimLayoutData();

	double get_start_time();
	void set_start_time(double start);

	double get_end_time();
	void set_end_time(double end);

	unsigned int get_col_0_width();
	void set_col_0_width(unsigned int);

	unsigned int get_col_1_width();
	void set_col_1_width(unsigned int width);

private:
	double m_start_time; // start time of wave form
	double m_end_time; // end time of wave form
	unsigned int m_col_0_width; // text
	unsigned int m_col_1_width; // wave form


};

#endif /* TIMLAYOUTDATA_H_ */
