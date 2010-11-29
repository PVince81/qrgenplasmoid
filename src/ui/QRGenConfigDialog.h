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

#ifndef QRGENCONFIGDIALOG_H_
#define QRGENCONFIGDIALOG_H_

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>

#include "../config/Config.h"

class QRGenConfigDialog : public QDialog
{
	Q_OBJECT
private:
	QComboBox* selectionModeCombo;
	QComboBox* errorCorrectionCombo;
	QSpinBox* marginField;
	QSpinBox* moduleSizeField;
	QCheckBox* directEncodeCheckBox;
protected:

public:

	QRGenConfigDialog();
	virtual ~QRGenConfigDialog();

	void setSelectionType( Config::SelectionMode selectionType );
	Config::SelectionMode selectionType();

	void setModuleSize( unsigned int size );
	unsigned int moduleSize();

	void setMargin( unsigned int margin );
	unsigned int margin();

	void setErrorCorrection( Config::ErrorCorrectionMode e );
	Config::ErrorCorrectionMode errorCorrection();

	void setConfig( Config config );
	Config config();
};

#endif
