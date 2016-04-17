/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef TITANIC_PET_INVENTORY_GLYPHS_H
#define TITANIC_PET_INVENTORY_GLYPHS_H

#include "titanic/carry/carry.h"
#include "titanic/pet_control/pet_glyphs.h"
#include "titanic/support/screen_manager.h"

namespace Titanic {

class CPetInventoryGlyph : public CPetGlyph {
private:
	/**
	 * Populate the details for an item
	 */
	int populateItem(CGameObject *item, int val);

	int subMode(CGameObject *item, int val);
public:
	CGameObject *_item;
	int _field34;
	int _field3C;
	int _field40;
public:
	CPetInventoryGlyph() : _item(nullptr), _field34(0), 
		_field3C(0), _field40(0) {}
	CPetInventoryGlyph(CCarry *item, int val) : _item(item),
		_field34(val), _field3C(0), _field40(0) {}

	/**
	 * Set the inventory item
	 */
	void setItem(CGameObject *item, int val);
};

class CPetCarry {
public:
	int _val;
	CCarry *_item;
public:
	CPetCarry(CCarry *item, int val) : _item(item), _val(val) {}
};

class CPetInventoryGlyphs : public CPetGlyphs {
	friend class CPetInventoryGlyph;
private:
	int fn1(int val);
public:
	/**
	 * Add a new item to the list
	 */
	void addItem(CPetCarry *item);
};

} // End of namespace Titanic

#endif /* TITANIC_PET_INVENTORY_GLYPHS_H */
