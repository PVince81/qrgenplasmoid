/*
 * QREncoder.h
 *
 *  Created on: 23 sept. 2010
 *      Author: vincent
 */

#ifndef QRENCODER_H_
#define QRENCODER_H_

#include "qrencode.h"

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
};

#endif /* QRENCODER_H_ */
