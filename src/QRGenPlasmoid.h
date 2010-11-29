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

#ifndef QRGENPLASMOID_H_
#define QRGENPLASMOID_H_

#include <Plasma/PopupApplet>
#include <QClipboard>
#include <QLabel>
#include <QTextEdit>
#include <KConfigDialog>

#include "ui/QRCodeWidget.h"
#include "ui/QRGenConfigDialog.h"

class QRGenPlasmoid : public Plasma::PopupApplet
{
	Q_OBJECT
private:
	QString getClipboardContent();
	QClipboard::Mode selectionMode;
	QRCodeWidget* codeWidget;
	QWidget* mainWidget;
	QTextEdit* editor;
	QRGenConfigDialog* configDialog;
protected:
    QWidget* widget();
    void popupEvent( bool show );
    void loadConfig();
    void saveConfig();
	void saveCodeImage( QString fileName );

public slots:
	void encodeAction();
	void configAccepted();
	void saveCodeImage();

public:

	QRGenPlasmoid(QObject *parent, const QVariantList &args);
	virtual ~QRGenPlasmoid();

	void createConfigurationInterface( KConfigDialog* parent );
/*
    void paintInterface(QPainter *p,
            const QStyleOptionGraphicsItem *option,
            const QRect& contentsRect);
*/

    void init();
};

#endif /* QRVIEWPLASMOID_H_ */
