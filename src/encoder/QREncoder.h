/*
 * QREncoder.h
 *
 *  Created on: 23 sept. 2010
 *      Author: vincent
 */

#ifndef QRENCODER_H_
#define QRENCODER_H_

#include "qrencode.h"

#include <QPixmap>
#include <QString>

class QREncoder
{
private:
public:
	int casesensitive;
	int eightbit;
	int version;
	int size;
	int margin;
	int structured;
	QRecLevel level;
	QRencodeMode hint;

	QREncoder();

	QRcode *encode(const char *intext);
	QRcode_List *encodeStructured(const char *intext);
	QPixmap encodePixmap( QString text );
};

#endif /* QRENCODER_H_ */
