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

#ifndef QRCODEWIDGET_H_
#define QRCODEWIDGET_H_

#include "../encoder/QREncoder.h"

#include <QLabel>

class QRCodeWidget : public QLabel
{
	Q_OBJECT
private:
	QREncoder* encoder;
	QPixmap code;
protected:
	void mousePressEvent ( QMouseEvent * ev );
signals:
	void clicked();
public:

	QRCodeWidget( QWidget * parent = 0, Qt::WindowFlags f = 0 );
	virtual ~QRCodeWidget();

	void setText( QString text );
	QPixmap pixmap() { return code; };
};

#endif
