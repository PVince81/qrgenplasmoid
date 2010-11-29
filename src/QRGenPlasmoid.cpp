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

#include "QRGenPlasmoid.h"

#include <QtGui>

QRGenPlasmoid::QRGenPlasmoid(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args)
{
	encoder = new QREncoder();
	encoder->margin = 2;
	encoder->size = 4;
	//resize(30, 30);
	//selectionMode = QClipboard::Clipboard;
	selectionMode = QClipboard::Selection;

	this->setMinimumSize( 32, 32 );
	this->setPopupIcon("qrviewplasmoid");
}

QRGenPlasmoid::~QRGenPlasmoid()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
    delete encoder;
}

/*
zvoid QRViewPlasmoid::paintInterface(QPainter *p,
        const QStyleOptionGraphicsItem *option,
        const QRect& contentsRect)
{
	QRect rect;
	p->drawPixmap(contentsRect, code);
}
*/

void QRGenPlasmoid::init()
{
	qDebug()<<"QRViewPlasmoid::init()";
	mainWidget = new QWidget();

	QHBoxLayout* mainLayout = new QHBoxLayout();

	QHBoxLayout* editLayout = new QHBoxLayout();
	editor = new QTextEdit();

	/*
	editLayout->addWidget(editor);

	QPushButton* encodeButton = new QPushButton();
	encodeButton->setText(tr("Encode"));
	editLayout->addWidget(encodeButton);
	*/

	codeLabel = new QLabel();
	codeLabel->setScaledContents(true);

	QSizePolicy labelSizePolicy( QSizePolicy::Ignored, QSizePolicy::Expanding, QSizePolicy::Label );
	labelSizePolicy.setHeightForWidth(true);
	codeLabel->setSizePolicy(labelSizePolicy);

	QSplitter* editSplitter = new QSplitter( Qt::Horizontal );
	editSplitter->addWidget(editor);
	editSplitter->addWidget(codeLabel);
	//mainLayout->addLayout(editLayout);
	//mainLayout->addWidget(editSplitter);
	//mainLayout->addWidget(codeLabel, Qt::AlignHCenter);
	mainLayout->addWidget(editSplitter);

	mainWidget->setLayout(mainLayout);

	//connect( encodeButton, SIGNAL( clicked() ), this, SLOT( encodeAction() ) );
	connect( editor, SIGNAL( textChanged() ), this, SLOT( encodeAction() ) );
}

QWidget* QRGenPlasmoid::widget()
{
	qDebug()<<"QRViewPlasmoid::widget()";
	return mainWidget;
}


QString QRGenPlasmoid::getClipboardContent()
{
	QString selection = QApplication::clipboard()->text( selectionMode );
	//qDebug()<<"Selection: \""<<selection<<"\"";
	return selection;
}

void QRGenPlasmoid::popupEvent( bool show )
{
	if ( !show )
	{
		return;
	}

	QString text = getClipboardContent();
	if ( !text.isEmpty() )
	{
		editor->setText( text );
		encodeAction();
	}
}

void QRGenPlasmoid::encodeAction()
{
	code = encoder->encodePixmap( editor->toPlainText() );
	codeLabel->setPixmap(code);
}


K_EXPORT_PLASMA_APPLET(qrviewplasmoid, QRGenPlasmoid)

