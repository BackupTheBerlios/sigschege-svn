// -*- c++ -*-
// TimLabel.h
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


#ifndef TIMLABEL_H_
#define TIMLABEL_H_

#include <QtGui>
#include "TimMember.h"
#include "TimLayoutData.h"


class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;

class DiagramTextItem : public QGraphicsTextItem
{
  Q_OBJECT
  
public:
  DiagramTextItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
  DiagramTextItem(const QString & text, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
  
signals:
    void lostFocus(DiagramTextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};


////////////////////////////////////////////////////////////////////////////////

/** @brief The @c TimLabel class is used to draw the signal labels.
 *
 * The @c TimLabel class ist used to draw the signal labels.
 */
class TimLabel: public TimMember {

public:

  /** @brief CTor
   *
   * @param parent Pointer to the parent object
   * @param scene Pointer to the timing scene.
   */
  TimLabel(TimMember *parent, TimingScene *scene);

  /** @brief CTor
   *
   * @param parent Pointer to the parent object
   * @param scene Pointer to the timing scene.
   * @param text Label text.
   */
  TimLabel(TimMember *parent, TimingScene *scene, const QString & text);

  /** @brief Returns the bounding rect.
   *
   * @return Returns the bounding rect.
   */
  virtual QRectF boundingRect() const;

  /*	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
   QWidget *widget);
   */

  /** @brief Sets the geometry
   *
   * @param rect The geometry stored in a rect.
   */
  virtual void setGeometry(const QRectF & rect);

  virtual void SSGWrite(SSGWriter *writer);
  virtual void
        paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  /** @brief Sets the text of the label
   *
   * @param text The new text of the label
   */
  void setText(const QString & text );

  /** @brief Return the text of the label
   *
   * @return text The text of the label
   */
  QString getText( void );

  /** @brief Creates a delete command
   *
   * This is a dummy implementation that returns NULL.
   *
   * @return Pointer to created delete command
   */
  virtual QUndoCommand* createDeleteCmd() {return NULL;}

protected:

  /** @brief Returns a hint of the object size.
   *
   * @param which Specifies which hint is requested.
   * @param constraint The constrains that apply.
   */
  virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
      QSizeF()) const;

  void mousePressEvent ( QGraphicsSceneMouseEvent * event );

private:

  /** @brief Stores a pointer to the layout data.
   */
  TimLayoutData *m_LayoutData;

  DiagramTextItem* m_text;
  //QString m_label;

};

inline QString TimLabel::getText( void ) {
  return m_text->toPlainText();  
}

#endif /* TIMLABEL_H_ */
