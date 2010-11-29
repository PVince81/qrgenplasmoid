/**
 * qrencode - QR Code encoder
 *
 * QR Code encoding tool
 * Copyright (C) 2006, 2007, 2008, 2009 Kentaro Fukuchi <fukuchi@megaui.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>

#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QPainter>


#include "QREncoder.h"

#define MAX_DATA_SIZE (7090 * 16) /* from the specification */

QREncoder::QREncoder()
{
	casesensitive = 1;
	eightbit = 0;
	version = 0;
	size = 3;
	margin = 4;
	structured = 0;
	level = QR_ECLEVEL_L;
	hint = QR_MODE_8;
}

QRcode *QREncoder::encode(const char *intext)
{
	QRcode *code;

	if(eightbit) {
		code = QRcode_encodeString8bit(intext, version, level);
	} else {
		code = QRcode_encodeString(intext, version, level, hint, casesensitive);
	}

	return code;
}

QRcode_List *QREncoder::encodeStructured(const char *intext)
{
	QRcode_List *list;

	if(eightbit) {
		list = QRcode_encodeString8bitStructured(intext, version, level);
	} else {
		list = QRcode_encodeStringStructured(intext, version, level, hint, casesensitive);
	}

	return list;
}

QPixmap QREncoder::encodePixmap( QString text )
{
	QRcode* qrcode = encode( text.toAscii().data() );
	if ( qrcode == NULL )
	{
		return NULL;
	}

	int realwidth = (qrcode->width + margin * 2) * size;
	QImage* image = new QImage( realwidth, realwidth, QImage::Format_Mono );
	QPainter painter(image);

	painter.fillRect( QRect( 0, 0, realwidth, realwidth ), QColor( Qt::white ) );

	QColor black( Qt::black );

	int i = 0;
	int x = 0;
	int y = 0;
	QRect rect( 0, 0, size, size );
	while ( y < qrcode->width )
	{
		x = 0;
		while ( x < qrcode->width )
		{
			// only if a block is present (black)
			if ( qrcode->data[i] & 1 )
			{
				rect.moveTo( size * ( margin + x ), size * ( margin + y ) );
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
