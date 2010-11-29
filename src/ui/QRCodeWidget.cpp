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
	: QWidget( parent, f )
{
	qDebug()<<"QRCodeWidget constructor";
	encoder = new QREncoder();
	encoder->margin = 2;
	encoder->size = 4;
	empty = true;
}

QRCodeWidget::~QRCodeWidget()
{
	delete encoder;
}

void QRCodeWidget::setText( QString text )
{
	if ( !text.isNull() && !text.isEmpty() )
	{
		code = encoder->encodePixmap( text );
		empty = false;
	}
	else
	{
		empty = true;
	}
	update();
}

void QRCodeWidget::mousePressEvent ( QMouseEvent * ev )
{
	if ( ev->buttons() == Qt::LeftButton )
	{
		emit clicked();
	}
}

void QRCodeWidget::setModuleSize( unsigned int size )
{
	encoder->size = size;
}

unsigned int QRCodeWidget::moduleSize()
{
	return encoder->size;
}

void QRCodeWidget::setMargin( unsigned int margin )
{
	encoder->margin = margin;
}

unsigned int QRCodeWidget::margin()
{
	return encoder->margin;
}

void QRCodeWidget::setErrorCorrection( Config::ErrorCorrectionMode e )
{
	switch (e)
	{
		case Config::L: encoder->level = QR_ECLEVEL_L; break;
		case Config::M: encoder->level = QR_ECLEVEL_M; break;
		case Config::Q: encoder->level = QR_ECLEVEL_Q; break;
		case Config::H: encoder->level = QR_ECLEVEL_H; break;
		default:
			encoder->level = QR_ECLEVEL_L;
	}
}

Config::ErrorCorrectionMode QRCodeWidget::errorCorrection()
{
	switch (encoder->level)
	{
		case QR_ECLEVEL_L: return Config::L;
		case QR_ECLEVEL_M: return Config::M;
		case QR_ECLEVEL_Q: return Config::Q;
		case QR_ECLEVEL_H: return Config::H;
		default:
			return Config::L;
	}
}

void QRCodeWidget::paintEvent(QPaintEvent * ev )
{
	QWidget::paintEvent( ev );

	if ( empty )
	{
		return;
	}
    QPainter p;
    p.begin(this);

	int width = this->width();
	int height = this->height();
	int dimension = width;
	if ( dimension > height )
	{
		dimension = height;
	}

	p.drawPixmap( 0, 0, dimension, dimension, code );
    p.end();
}
