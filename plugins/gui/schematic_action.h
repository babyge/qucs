/***************************************************************************
    copyright            : (C) 2020 Felix Salfelder
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QUCS_SCHEMATIC_ACTION
#define QUCS_SCHEMATIC_ACTION
/*--------------------------------------------------------------------------*/
#include "doc_actions.h"
#include "schematic_edit.h"
/*--------------------------------------------------------------------------*/
class QucsDoc;
/*--------------------------------------------------------------------------*/
// merge into scene altogether?
class SchematicActions : public MouseActions{
public:
	explicit SchematicActions(QucsDoc* d);
	~SchematicActions();

private: // MouseActions
	// void handle(QEvent*) override;
	void setControls(QucsDoc* ctx) override;

protected: // Doc stuff
	QucsDoc* doc();
	SchematicScene const* scene()const;
	void updateViewport();
	QPoint snapToGrid(QPointF const&p) const;

public: // actions... private?
	     // not yet. still toggled from outside
	MouseAction* maDelete;
	MouseAction* maSelect;
	MouseAction* maWire;
	MouseAction* maMirror;
	MouseAction* maActivate;
	MouseAction* maRotate;
	MouseAction* maEditPaste;
	MouseAction* maOnGrid;
	MouseAction* maMirrorXaxis;
	MouseAction* maMirrorYaxis;
	MouseAction* maInsertGround;
	MouseAction* maInsertElement;
	MouseAction* maInsertPort;
	MouseAction* maInsertEqn;
	MouseAction* maZoomIn;
	// MouseAction* maZoomOut; // not a mouseaction
	
	// all in one go?? how?
	QAction* _actionSelect{nullptr};
	QAction* _actionRotate{nullptr};
	QAction* _actionMX{nullptr};
	QAction* _actionMY{nullptr};
	QAction* _actionInsertGround{nullptr};
	QAction* _actionInsertWire{nullptr};
	QAction* _actionInsertPort{nullptr};
};
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
#endif