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

#include "QRGenConfigDialog.h"

#include <QtGui>

#include <klocalizedstring.h>

QRGenConfigDialog::QRGenConfigDialog()
	: QDialog()
{
	qDebug()<<"QRGenConfigDialog constructor";

	QFormLayout* mainLayout = new QFormLayout();

	selectionModeCombo = new QComboBox();
	selectionModeCombo->addItem(i18n("Selection"), Config::Selection);
	selectionModeCombo->addItem(i18n("Clipboard"), Config::Clipboard);

	mainLayout->addRow(i18n("Selection mode"), selectionModeCombo);

	directEncodeCheckBox = new QCheckBox();
	mainLayout->addRow(i18n("Encode while typing"), directEncodeCheckBox);

	marginField = new QSpinBox();
	marginField->setRange(0, 100);
	marginField->setSingleStep(1);

	moduleSizeField = new QSpinBox();
	moduleSizeField->setRange(1, 100);
	moduleSizeField->setSingleStep(1);

	QFormLayout* qrLayout = new QFormLayout();
	qrLayout->addRow(i18n("Margin"), marginField);
	qrLayout->addRow(i18n("Module size"), moduleSizeField);

	errorCorrectionCombo = new QComboBox();
	errorCorrectionCombo->addItem("L", Config::L);
	errorCorrectionCombo->addItem("M", Config::M);
	errorCorrectionCombo->addItem("Q", Config::Q);
	errorCorrectionCombo->addItem("H", Config::H);
	qrLayout->addRow(i18n("Error correction level"), errorCorrectionCombo);
	//qrLayout->addRow(i18n("Encoder mode"));

	QGroupBox* groupBox = new QGroupBox( i18n("QR Code settings") );
	groupBox->setLayout( qrLayout );
	mainLayout->addRow( groupBox );

	this->setLayout( mainLayout );
}

QRGenConfigDialog::~QRGenConfigDialog()
{
}

void QRGenConfigDialog::setSelectionType( Config::SelectionMode selectionType )
{
	selectionModeCombo->setCurrentIndex( selectionModeCombo->findData( selectionType ) );
}

Config::SelectionMode QRGenConfigDialog::selectionType()
{
	return (Config::SelectionMode)selectionModeCombo->itemData( errorCorrectionCombo->currentIndex() ).toInt();
}

void QRGenConfigDialog::setModuleSize( unsigned int size )
{
	moduleSizeField->setValue( size );
}

unsigned int QRGenConfigDialog::moduleSize()
{
	return moduleSizeField->value();
}

void QRGenConfigDialog::setMargin( unsigned int margin )
{
	marginField->setValue( margin );
}

unsigned int QRGenConfigDialog::margin()
{
	return marginField->value();
}

void QRGenConfigDialog::setErrorCorrection( Config::ErrorCorrectionMode e )
{
	errorCorrectionCombo->setCurrentIndex( errorCorrectionCombo->findData(e) );
}

Config::ErrorCorrectionMode QRGenConfigDialog::errorCorrection()
{
	return (Config::ErrorCorrectionMode)errorCorrectionCombo->itemData( errorCorrectionCombo->currentIndex() ).toInt();
}

void QRGenConfigDialog::setConfig( Config config )
{
	setErrorCorrection( config.errorCorrectionMode );
	setMargin( config.margin );
	setModuleSize( config.moduleSize );
	setSelectionType( config.selectionMode );

	directEncodeCheckBox->setChecked( config.directEncode );
}

Config QRGenConfigDialog::config()
{
	Config config;

	config.errorCorrectionMode = errorCorrection();
	config.margin = margin();
	config.moduleSize = moduleSize();
	config.selectionMode = selectionType();
	config.directEncode = directEncodeCheckBox->isChecked();

	return config;
}
