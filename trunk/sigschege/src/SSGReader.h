// -*- c++ -*-
// Copyright 2009 by Ulf Klaperski
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


#ifndef SSGREADER_H_
#define SSGREADER_H_

#include "TimingScene.h"
#include <QXmlStreamReader>


/** @brief The SSG Reader reads a timing diagram in XML format.
 *
 * The ...
 */
class SSGReader: public QXmlStreamReader {


public:

  /** @brief Ctor
   *
   * @param parent Pointer to the owning parent object.
   */
  SSGReader(TimingScene *tscene = 0);

  /** @brief Creates/adds and returns a new signal.
   *
   * This method .
   *
   * @return Returns success.
   */
    bool read(QIODevice *device);



private:

    TimingScene *scene;

    /** @brief Read a signal.
     *
     * This method 
     *
     * @param ?
     * @return ?
     */
    void readSigschege();
    void readSignal();
    void readTimeScale();

};

#endif /* SSGREADER_H_ */
