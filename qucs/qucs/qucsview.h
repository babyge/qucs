/***************************************************************************
                          qucsview.h  -  description
                             -------------------
    begin                : Thu Aug 28 18:17:41 CEST 2003
    copyright            : (C) 2003 by Michael Margraf
    email                : margraf@mwt.ee.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QUCSVIEW_H
#define QUCSVIEW_H

// include files for QT
#include <qscrollview.h>
#include <qwidget.h>
#include <qptrlist.h>
#include <qstring.h>
#include <qpen.h>
#include <qpoint.h>
#include <qpainter.h>
#include <qlabel.h>
#include <qcolor.h>
#include <qevent.h>
#include <qdir.h>


// application specific includes
#include "component.h"
#include "wire.h"
#include "qucsdoc.h"



// ********************************************************************************
// ********** This class provides an incomplete base for the application **********
// ********** view. (scematics, data displays etc.)                      **********
// ********************************************************************************

class QucsView : public QScrollView
{
  Q_OBJECT

public:
//	DrawArea(QWidget *parent=0, const char *name=0, WFlags f=0);
  QucsView(QWidget *parent=0);
  ~QucsView();

  double Zoom(double s);

  Component *selComp;   // component selected in IconView
  Diagram   *selDiag;   // diagram selected in IconView

  bool drawn;   // indicates whether the scheme component was drawn the last time
  QDir ProjDir; // holds the project directory, if project open
  QString ProjName;

  // -------------------------------------------------------------------
  QPtrList<QucsDoc>  Docs;  // instances of the documents (schematics, data displays)

protected:
  virtual void drawContents(QPainter *p, int clipx, int clipy, int clipw, int cliph);
  virtual void contentsMouseMoveEvent(QMouseEvent *Event);
  virtual void contentsMousePressEvent(QMouseEvent *Event);
  virtual void contentsMouseDoubleClickEvent(QMouseEvent *Event);
  virtual void contentsMouseReleaseEvent(QMouseEvent *Event);

//private:
public:
  double Scale;

  void MouseDoNothing(QMouseEvent *Event);
  void MMoveSelect(QMouseEvent *Event);
  void MMoveComponent(QMouseEvent *Event);
  void MMoveDiagram(QMouseEvent *Event);
  void MMoveWire1(QMouseEvent *Event);
  void MMoveWire2(QMouseEvent *Event);
  void (QucsView::*MouseMoveAction) (QMouseEvent*); // pointer to actual mouse move method

  void MPressSelect(QMouseEvent *Event);
  void MPressDelete(QMouseEvent *Event);
  void MPressActivate(QMouseEvent *Event);
  void MPressComponent(QMouseEvent *Event);
  void MPressDiagram(QMouseEvent *Event);
  void MPressLabel(QMouseEvent *Event);
  void MPressWire1(QMouseEvent *Event);
  void MPressWire2(QMouseEvent *Event);
  void (QucsView::*MousePressAction) (QMouseEvent*); // pointer to actual mouse press button method

  void MDoubleClickSelect(QMouseEvent *Event);
  void MDoubleClickWire2(QMouseEvent *Event);
  void (QucsView::*MouseDoubleClickAction) (QMouseEvent*); // pointer to actual mouse double click method
  
  void MReleaseSelect(QMouseEvent *Event);
  void (QucsView::*MouseReleaseAction) (QMouseEvent*); // pointer to actual mouse release button method

signals:
  void AreaMouseMove(QMouseEvent *Event);
  void AreaMousePress(QMouseEvent *Event);

private:
  int MAx1, MAy1,MAx2, MAy2, MAx3, MAy3;  // cache for mouse movements
};

#endif
