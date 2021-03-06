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

/** @brief The @c TimLayoutData class stores all "global" timing diagram data.
 *
 */
class TimLayoutData {

public:

  /** @brief CTor
   */
  TimLayoutData();

  /** @brief DTor
   */
  virtual ~TimLayoutData();

  /** @brief Get the start time
   *
   * @return Start time in sec.
   */
  double get_start_time();

  /** @brief Set the start time.
   *
   * @param start Start time in sec.
   */
  void set_start_time(double start);

  /** @brief Get the end time
   *
   * @return End time in sec.
   */
  double get_end_time();

  /** @brief Set the end time.
   *
   * @param end End time in sec.
   */
  void set_end_time(double end);

  /** @brief Get the snap delta time
   *
   * @return Snap delta time in sec.
   */
  double get_snap_delta_time();

  /** @brief Set the snap delta.
   *
   * @param delta Snap delta time in sec.
   */
  void set_snap_delta_time(double delta);

  /** @brief Get the width of col 0 (label).
   *
   * @return Width in pixel.
   */
  unsigned int get_col_0_width();

  /** @brief Set width of col 0 (label)
   * @param width Width in pixel.
   */
  void set_col_0_width(unsigned int width);

  /** @brief Get the width of col 1 (waveform).
   *
   * @return Width in pixel.
   */
  unsigned int get_col_1_width();

  /** @brief Set width of col 1 (waveform)
   * @param width Width in pixel.
   */
  void set_col_1_width(unsigned int width);

  /** @brief Returns the scale factor
   * @return The scale factor
   */
  double get_scale_factor() const;

private:

  /** @brief Recalculates the m_scale_factor
   */
  void updateScaleFactor();

  /** @brief start time of wave form
   */
  double m_start_time;

  /** @brief end time of wave form
   */
  double m_end_time;

  /** @brief Set events only at certain points in time defined by m_snap_delta_time
   */
  bool m_use_snapping;

  /** @brief The distance at which events will be set
   */
  double m_snap_delta_time;

  /** @brief Label width (first col)
   */
  unsigned int m_col_0_width;

  /** @brief Width of wave form (second col)
   */
  unsigned int m_col_1_width;

  /** @brief Defines the scale factor for this diagram.
   *
   * The scale factor is calculated (m_end_time - m_start_time) / m_col_1_width
   */
  double m_scale_factor;


};

#endif /* TIMLAYOUTDATA_H_ */
