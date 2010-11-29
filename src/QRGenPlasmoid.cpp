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
#include <KConfigGroup>

QRGenPlasmoid::QRGenPlasmoid(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args)
{
	//resize(30, 30);
	//selectionMode = QClipboard::Clipboard;
	selectionMode = QClipboard::Selection;

	this->setMinimumSize( 32, 32 );
	this->setPopupIcon("qrgenplasmoid");
}

QRGenPlasmoid::~QRGenPlasmoid()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}

/*
void QRGenPlasmoid::paintInterface(QPainter *p,
        const QStyleOptionGraphicsItem *option,
        const QRect& contentsRect)
{
	QRect rect;
	p->drawPixmap(contentsRect, code);
}
*/

void QRGenPlasmoid::init()
{
	qDebug()<<"QRGenPlasmoid::init()";
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

	codeWidget = new QRCodeWidget();

	QSplitter* editSplitter = new QSplitter( Qt::Horizontal );
	editSplitter->addWidget(editor);
	editSplitter->addWidget(codeWidget);
	//mainLayout->addLayout(editLayout);
	//mainLayout->addWidget(editSplitter);
	//mainLayout->addWidget(codeWidget, Qt::AlignHCenter);
	mainLayout->addWidget(editSplitter);

	mainWidget->setLayout(mainLayout);

	loadConfig();

	//connect( encodeButton, SIGNAL( clicked() ), this, SLOT( encodeAction() ) );
	connect( editor, SIGNAL( textChanged() ), this, SLOT( encodeAction() ) );
    connect( codeWidget, SIGNAL( clicked() ), this, SLOT( saveCodeImage() ) );
}

void QRGenPlasmoid::loadConfig()
{
	KConfigGroup cnf = config();
	QString selectionModeString = cnf.readEntry( "selectionMode", QString());
	if ( selectionModeString == "clipboard" )
	{
		selectionMode = QClipboard::Clipboard;
	}
	else
	{
		selectionMode = QClipboard::Selection;
	}
}

void QRGenPlasmoid::saveConfig()
{
	KConfigGroup cnf = config();
	QString selectionModeString = "selection";
	if ( selectionMode == QClipboard::Clipboard )
	{
		selectionModeString = "clipboard";
	}
	cnf.writeEntry( "selectionMode", selectionModeString );
	emit configNeedsSaving();
}

QWidget* QRGenPlasmoid::widget()
{
	qDebug()<<"QRGenPlasmoid::widget()";
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

void QRGenPlasmoid::configAccepted( )
{
	if ( configDialog->selectionType() == QRGenConfigDialog::Selection )
	{
		selectionMode = QClipboard::Selection;
	}
	else
	{
		selectionMode = QClipboard::Clipboard;
	}
	saveConfig();
}

void QRGenPlasmoid::encodeAction()
{
	codeWidget->setText( editor->toPlainText() );
}

void QRGenPlasmoid::createConfigurationInterface( KConfigDialog* parent )
{
	qDebug()<<"QRGenPlasmoid::createConfigurationInterface";
    configDialog = new QRGenConfigDialog();
    if ( selectionMode == QClipboard::Selection )
    {
    	configDialog->setSelectionType( QRGenConfigDialog::Selection );
    }
    else
    {
    	configDialog->setSelectionType( QRGenConfigDialog::Clipboard );
    }

    connect( parent, SIGNAL( accepted() ), this, SLOT( configAccepted() ) );

    parent->addPage( configDialog, i18n("General"), icon() );

	setHasConfigurationInterface(true);
}

void QRGenPlasmoid::saveCodeImage()
{
	QString fileName = QFileDialog::getSaveFileName(
			this->codeWidget,
			i18n("Save code image"),
			"qrcode.png",
			i18n("Images (*.png *.xpm *.jpg)")
			);
	if ( !fileName.isNull() )
	{
		saveCodeImage( fileName );
	}
}

void QRGenPlasmoid::saveCodeImage( QString fileName )
{
	codeWidget->pixmap().save( fileName );
}

K_EXPORT_PLASMA_APPLET(qrgenplasmoid, QRGenPlasmoid)

