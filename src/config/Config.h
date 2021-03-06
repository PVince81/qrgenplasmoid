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

#ifndef CONFIG_H_
#define CONFIG_H_

typedef struct Config
{
	enum SelectionMode
	{
		Selection, Clipboard
	};

	enum ErrorCorrectionMode
	{
		L, M, Q, H
	};

	SelectionMode selectionMode;
	unsigned int moduleSize;
	unsigned int margin;
	ErrorCorrectionMode errorCorrectionMode;

	/**
	 * Whether to encode directly while the user
	 * is typing.
	 */
	bool directEncode;

	/*
	 * Whether to use UTF-8 BOM prefix
	 */
	bool useBom;
} Config;

#endif /* CONFIG_H_ */
