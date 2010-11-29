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

#include "QRCodeWidget.h"

#include <QtGui>

QRCodeWidget::QRCodeWidget( QWidget * parent, Qt::WindowFlags f )
	: QLabel( parent, f )
{
	qDebug()<<"QRCodeWidget constructor";
	encoder = new QREncoder();
	encoder->margin = 2;
	encoder->size = 4;
	this->setScaledContents(true);

	QSizePolicy labelSizePolicy( QSizePolicy::Ignored, QSizePolicy::Expanding, QSizePolicy::Label );
	labelSizePolicy.setHeightForWidth(true);
	this->setSizePolicy(labelSizePolicy);
}

QRCodeWidget::~QRCodeWidget()
{
	delete encoder;
}

void QRCodeWidget::setText( QString text )
{
	code = encoder->encodePixmap( text );
	this->setPixmap(code);
}

void QRCodeWidget::mousePressEvent ( QMouseEvent * ev )
{
	if ( ev->buttons() == Qt::LeftButton )
	{
		emit clicked();
	}
}
