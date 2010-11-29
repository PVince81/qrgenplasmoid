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

	this->setMinimumSize( 32, 32 );
	this->setPopupIcon("qrgenplasmoid");

	configuration.errorCorrectionMode = Config::L;
	configuration.moduleSize = 5;
	configuration.margin = 1;
	configuration.selectionMode = Config::Selection;
	configuration.directEncode = true;
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

	QVBoxLayout* editLayout = new QVBoxLayout();
	editor = new QTextEdit();

	editLayout->addWidget(editor);

	encodeButton = new QPushButton();
	encodeButton->setText(i18n("Encode"));
	editLayout->addWidget(encodeButton);

	codeWidget = new QRCodeWidget();

	QSplitter* editSplitter = new QSplitter( Qt::Horizontal );

	QWidget* editWidget = new QWidget();
	editWidget->setLayout(editLayout);

	editSplitter->addWidget(editWidget);
	editSplitter->addWidget(codeWidget);
	//mainLayout->addLayout(editLayout);
	//mainLayout->addWidget(editSplitter);
	//mainLayout->addWidget(codeWidget, Qt::AlignHCenter);
	mainLayout->addWidget(editSplitter);

	mainWidget->setLayout(mainLayout);

	loadConfig();
	applyConfig();

	mainWidget->resize(400, 200);

	connect( encodeButton, SIGNAL( clicked() ), this, SLOT( encodeAction() ) );
	connect( editor, SIGNAL( textChanged() ), this, SLOT( textChanged() ) );
    connect( codeWidget, SIGNAL( clicked() ), this, SLOT( saveCodeImage() ) );
}

void QRGenPlasmoid::loadConfig()
{
	KConfigGroup cnf = config();
	QString selectionModeString = cnf.readEntry( "selectionMode", "selection" );
	if ( selectionModeString == "clipboard" )
	{
		configuration.selectionMode = Config::Clipboard;
	}
	else
	{
		configuration.selectionMode = Config::Selection;
	}

	QString errorCorrectionString = cnf.readEntry( "errorCorrectionMode", "L" );
	if ( errorCorrectionString == "H" )
	{
		configuration.errorCorrectionMode = Config::H;
	}
	else if ( errorCorrectionString == "Q" )
	{
		configuration.errorCorrectionMode = Config::Q;
	}
	else if ( errorCorrectionString == "M" )
	{
		configuration.errorCorrectionMode = Config::M;
	}
	else
	{
		configuration.errorCorrectionMode = Config::L;
	}

	configuration.moduleSize = cnf.readEntry( "moduleSize", 5 );
	configuration.margin = cnf.readEntry( "margin", 1 );
	configuration.directEncode = cnf.readEntry( "directEncode", true );
}

void QRGenPlasmoid::saveConfig()
{
	KConfigGroup cnf = config();
	QString selectionModeString = "selection";
	if ( configuration.selectionMode == Config::Clipboard )
	{
		selectionModeString = "clipboard";
	}
	cnf.writeEntry( "selectionMode", selectionModeString );

	QString errorCorrectionString;
	switch ( configuration.errorCorrectionMode )
	{
		case Config::H: errorCorrectionString = "H"; break;
		case Config::Q: errorCorrectionString = "Q"; break;
		case Config::M: errorCorrectionString = "M"; break;
		default: errorCorrectionString = "L"; break;
	}

	cnf.writeEntry( "moduleSize", configuration.moduleSize );
	cnf.writeEntry( "margin", configuration.margin );
	cnf.writeEntry( "directEncode", configuration.directEncode );

	emit configNeedsSaving();
}

QWidget* QRGenPlasmoid::widget()
{
	qDebug()<<"QRGenPlasmoid::widget()";
	return mainWidget;
}


QString QRGenPlasmoid::getClipboardContent()
{
	QString selection = QApplication::clipboard()->text(
			(configuration.selectionMode == Config::Clipboard)?
					QClipboard::Clipboard
					:QClipboard::Selection
					 );
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
	configuration = configDialog->config();
	applyConfig();
	saveConfig();

	if ( configuration.directEncode )
	{
		// refresh the already displayed code
		encodeAction();
	}
}

void QRGenPlasmoid::applyConfig()
{
	codeWidget->setMargin(configuration.margin);
	codeWidget->setModuleSize(configuration.moduleSize);
	codeWidget->setErrorCorrection(configuration.errorCorrectionMode);

	encodeButton->setVisible( !configuration.directEncode );
}

void QRGenPlasmoid::textChanged()
{
	if ( configuration.directEncode )
	{
		encodeAction();
	}
}

void QRGenPlasmoid::encodeAction()
{
	codeWidget->setText( editor->toPlainText() );
}

void QRGenPlasmoid::createConfigurationInterface( KConfigDialog* parent )
{
    configDialog = new QRGenConfigDialog();
    configDialog->setConfig( configuration );

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

