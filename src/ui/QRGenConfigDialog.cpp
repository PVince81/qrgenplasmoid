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
	selectionModeCombo->addItem(i18n("Selection"));
	selectionModeCombo->addItem(i18n("Clipboard"));

	mainLayout->addRow(i18n("Selection mode"), selectionModeCombo);

	this->setLayout( mainLayout );
}

QRGenConfigDialog::~QRGenConfigDialog()
{
}

void QRGenConfigDialog::setSelectionType( QRGenConfigDialog::SelectionType selectionType )
{
	if ( selectionType == Selection )
	{
		selectionModeCombo->setCurrentIndex(0);
	}
	else
	{
		selectionModeCombo->setCurrentIndex(1);
	}
}

QRGenConfigDialog::SelectionType QRGenConfigDialog::selectionType()
{
	if ( selectionModeCombo->currentIndex() == 0 )
	{
		return Selection;
	}
	else
	{
		return Clipboard;
	}
}
