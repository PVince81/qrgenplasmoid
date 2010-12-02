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

const char BOM[3] = { 0xEF, 0xBB, 0xBF };

QRCodeWidget::QRCodeWidget( QWidget * parent, Qt::WindowFlags f )
	: QWidget( parent, f )
{
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
		code = this->encodeText( text );
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

void QRCodeWidget::setUseBom( bool useBom )
{
	this->m_useBom = useBom;
}

bool QRCodeWidget::useBom()
{
	return this->m_useBom;
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

    QPainter p;
    p.begin(this);

	int width = this->width();
	int height = this->height();
	int dimension = width;
	if ( dimension > height )
	{
		dimension = height;
	}

    if ( empty )
	{
    	// fill with white
		p.fillRect( QRect( 0, 0, dimension, dimension ), QColor( Qt::white ) );
	}
    else
    {
    	// draw QR code
		p.drawPixmap( 0, 0, dimension, dimension, code );
    }
    p.end();
}

QPixmap QRCodeWidget::encodeText( QString text )
{
	QByteArray a = text.toUtf8();
	if ( m_useBom )
	{
		// insert BOM
		a.insert( 0, BOM );
	}
	QRcode* qrcode = encoder->encode( a.data() );
	if ( qrcode == NULL )
	{
		return NULL;
	}

	int realwidth = (qrcode->width + encoder->margin * 2) * encoder->size;
	QImage* image = new QImage( realwidth, realwidth, QImage::Format_Mono );
	QPainter painter(image);

	painter.fillRect( QRect( 0, 0, realwidth, realwidth ), QColor( Qt::white ) );

	QColor black( Qt::black );

	int i = 0;
	int x = 0;
	int y = 0;
	QRect rect( 0, 0, encoder->size, encoder->size );
	while ( y < qrcode->width )
	{
		x = 0;
		while ( x < qrcode->width )
		{
			// only if a block is present (black)
			if ( qrcode->data[i] & 1 )
			{
				rect.moveTo(encoder->size * (encoder->margin + x),
						encoder->size * (encoder->margin + y));
				painter.fillRect( rect, black );
			}
			i++;
			x++;
		}
		y++;
	}

	painter.end();

	QPixmap pixmap = QPixmap::fromImage(*image);
	return pixmap;
}
