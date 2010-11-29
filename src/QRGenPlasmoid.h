/**
 *  This file is part of qrgenplasmoid
 *  Copyright (C) 2010 Vincent Petry
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#ifndef QRVIEWPLASMOID_H_
#define QRVIEWPLASMOID_H_

#include <Plasma/PopupApplet>
#include <QClipboard>
#include <QLabel>
#include <QTextEdit>

#include "encoder/QREncoder.h"

class QRGenPlasmoid : public Plasma::PopupApplet
{
	Q_OBJECT
private:
	QREncoder* encoder;
	QPixmap code;
	QString getClipboardContent();
	QClipboard::Mode selectionMode;
	QLabel* codeLabel;
	QWidget* mainWidget;
	QTextEdit* editor;
protected:
    QWidget* widget();
    void popupEvent( bool show );

public slots:
	void encodeAction();

public:

	QRGenPlasmoid(QObject *parent, const QVariantList &args);
	virtual ~QRGenPlasmoid();
/*
    void paintInterface(QPainter *p,
            const QStyleOptionGraphicsItem *option,
            const QRect& contentsRect);
*/

    void init();
};

#endif /* QRVIEWPLASMOID_H_ */
