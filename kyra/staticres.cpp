/* ScummVM - Scumm Interpreter
 * Copyright (C) 2004-2005 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

#include "common/stdafx.h"
#include "kyra/kyra.h"
#include "kyra/screen.h"

namespace Kyra {

const ScreenDim Screen::_screenDimTable[] = {
	{ 0x00, 0x00, 0x28, 0xC8, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x08, 0x48, 0x18, 0x38, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x01, 0x08, 0x26, 0x80, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x00, 0xC2, 0x28, 0x06, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x00, 0x90, 0x28, 0x38, 0x04, 0x0C, 0x00, 0x00 },
	{ 0x01, 0x94, 0x26, 0x30, 0x04, 0x1B, 0x00, 0x00 },
	{ 0x00, 0x90, 0x28, 0x38, 0x0F, 0x0D, 0x00, 0x00 },
	{ 0x01, 0x96, 0x26, 0x32, 0x0F, 0x0D, 0x00, 0x00 },
	{ 0x00, 0x00, 0x28, 0x88, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x01, 0x20, 0x26, 0x80, 0x0F, 0x0C, 0x00, 0x00 },
	{ 0x03, 0x28, 0x22, 0x46, 0x0F, 0x0D, 0x00, 0x00 }
};

const int Screen::_screenDimTableCount = ARRAYSIZE(_screenDimTable);

const Screen::DrawShapePlotPixelCallback Screen::_drawShapePlotPixelTable[] = {
	&Screen::drawShapePlotPixelCallback1
	// XXX
};

const int Screen::_drawShapePlotPixelCount = ARRAYSIZE(_drawShapePlotPixelTable);

const uint8 KyraEngine::_seq_introData_Forest[] = {
	0x00, 0x05, 0x01, 0x00, 0x07, 0x01, 0x1A, 0x02, 0x07, 0x00, 0x00, 0x00, 0x08, 0x02, 0x05, 0x00, 
	0x98, 0x00, 0x38, 0x0A, 0x00, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x0B, 0x00, 0x41, 0x00, 
	0x18, 0x16, 0x03, 0x07, 0x02, 0x05, 0x01, 0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 
	0x00, 0x03, 0x07, 0x02, 0x05, 0x03, 0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 
	0x03, 0x07, 0x02, 0x05, 0x01, 0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 
	0x07, 0x02, 0x05, 0x00, 0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x0A, 0x05, 
	0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x0B, 0x05, 0x0E, 0x00, 0x18, 0x16, 0x03, 0x07, 0x02, 
	0x05, 0x01, 0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 0x07, 0x02, 0x05, 
	0x03, 0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 0x07, 0x02, 0x05, 0x01, 
	0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 0x07, 0x02, 0x05, 0x04, 0x98, 
	0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 
	0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x03, 0x07, 0x02, 0x05, 0x05, 0x98, 0x00, 0x38, 0x16, 
	0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x03, 0x07, 0x16, 
	0x02, 0x06, 0x09, 0x00, 0x03, 0x07, 0x02, 0x05, 0x06, 0x98, 0x00, 0x38, 0x16, 0x02, 0x16, 0x03, 
	0x06, 0x09, 0x00, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 
	0x00, 0x18, 0x25, 0x0A, 0x00, 0x03, 0x07, 0x03, 0x05, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 
	0x0B, 0x00, 0x09, 0x00, 0x0A, 0x06, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x0B, 0x06, 0x0E, 
	0x00, 0x18, 0x17, 0x0A, 0x01, 0x03, 0x07, 0x03, 0x05, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 
	0x0B, 0x01, 0x0D, 0x00, 0x18, 0x25, 0x0A, 0x07, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x0B, 
	0x07, 0x0E, 0x00, 0x18, 0x18, 0x03, 0x07, 0x03, 0x05, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 
	0x03, 0x07, 0x03, 0x05, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 0x07, 0x03, 0x05, 0x16, 
	0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x03, 0x07, 0x03, 0x05, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 
	0x00, 0x03, 0x07, 0x03, 0x05, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x06, 0x12, 0x00, 0x18, 
	0x25, 0x0A, 0x02, 0x03, 0x07, 0x03, 0x05, 0x16, 0x02, 0x16, 0x03, 0x06, 0x09, 0x00, 0x0B, 0x02, 
	0x07, 0x00, 0x0A, 0x03, 0x03, 0x07, 0x16, 0x02, 0x06, 0x09, 0x00, 0x0B, 0x03, 0x0F, 0x00, 0x13, 
	0x13, 0x01, 0x07, 0x01, 0x05, 0x1D
};

const uint8 KyraEngine::_seq_introData_KallakWriting[] = {
	0x00, 0x00, 0x01, 0x0E, 0x1A, 0x1B, 0x17, 0x00, 0x00, 0x00, 0x3F, 0x01, 0xC7, 0x0C, 0x00, 0x0C, 
	0x00, 0x19, 0x39, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x05, 0x00, 0x95, 0x00, 0x20, 0x09, 0x14, 
	0x0F, 0x2E, 0x02, 0x00, 0x01, 0x00, 0x00, 0x10, 0x05, 0x01, 0x94, 0x00, 0x1B, 0x07, 0x06, 0x00, 
	0x18, 0x1D, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 0x14, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x03, 0x00, 0x00, 0x10, 0x05, 0x01, 0x90, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x04, 0x00, 0x00, 0x10, 0x05, 0x00, 0x8D, 0x00, 0x20, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 
	0x05, 0x00, 0x00, 0x10, 0x05, 0x01, 0x8A, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x06, 0x00, 
	0x00, 0x10, 0x05, 0x02, 0x88, 0x00, 0x14, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x07, 0x00, 
	0x00, 0x10, 0x05, 0x01, 0x85, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x10, 
	0x05, 0x00, 0x82, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x09, 0x00, 0x00, 0x10, 0x05, 0x01, 
	0x7F, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x0A, 0x00, 0x00, 0x10, 0x05, 0x02, 0x7C, 0x00, 
	0x14, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x0B, 0x00, 0x00, 0x10, 0x05, 0x01, 0x79, 0x00, 
	0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x0C, 0x00, 0x00, 0x10, 0x05, 0x00, 0x76, 0x00, 0x20, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x0D, 0x00, 0x00, 0x10, 0x05, 0x01, 0x73, 0x00, 0x1B, 0x07, 0x06, 0x00, 
	0x18, 0x1D, 0x02, 0x00, 0x0E, 0x00, 0x00, 0x10, 0x05, 0x02, 0x70, 0x00, 0x14, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x0F, 0x00, 0x00, 0x10, 0x05, 0x01, 0x6D, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x10, 0x00, 0x00, 0x10, 0x05, 0x00, 0x6A, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x11, 0x00, 
	0x00, 0x10, 0x05, 0x01, 0x67, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x12, 0x00, 
	0x00, 0x10, 0x05, 0x02, 0x65, 0x00, 0x14, 0x07, 0x06, 0x00, 0x02, 0x00, 0x13, 0x00, 0x00, 0x10, 
	0x05, 0x01, 0x63, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x14, 0x00, 0x00, 0x10, 0x05, 0x00, 
	0x63, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x15, 0x00, 0x00, 0x10, 0x05, 0x00, 0x65, 0x00, 
	0x1F, 0x07, 0x06, 0x00, 0x02, 0x00, 0x16, 0x00, 0x00, 0x10, 0x05, 0x00, 0x6A, 0x00, 0x1D, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x17, 0x00, 0x00, 0x10, 0x05, 0x00, 0x70, 0x00, 0x19, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x18, 0x00, 0x00, 0x10, 0x05, 0x00, 0x76, 0x00, 0x17, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x19, 0x00, 0x00, 0x10, 0x05, 0x00, 0x7C, 0x00, 0x16, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1A, 0x00, 
	0x00, 0x10, 0x05, 0x00, 0x82, 0x00, 0x17, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1B, 0x00, 0x00, 0x10, 
	0x05, 0x00, 0x88, 0x00, 0x19, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1C, 0x00, 0x00, 0x10, 0x05, 0x00, 
	0x8D, 0x00, 0x1D, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1D, 0x00, 0x00, 0x10, 0x05, 0x00, 0x93, 0x00, 
	0x1F, 0x07, 0x06, 0x00, 0x1C, 0x1B, 0x0F, 0x2F, 0x02, 0x00, 0x01, 0x00, 0x00, 0x10, 0x05, 0x01, 
	0x94, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x10, 0x05, 0x01, 0x94, 0x00, 
	0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 
	0x14, 0x07, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 0x14, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x10, 0x05, 0x01, 0x90, 0x00, 0x1B, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x04, 0x00, 0x00, 0x10, 0x05, 0x00, 0x8D, 0x00, 0x20, 0x07, 0x06, 0x00, 0x18, 0x1D, 
	0x02, 0x00, 0x05, 0x00, 0x00, 0x10, 0x05, 0x01, 0x8A, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x05, 0x00, 0x00, 0x10, 0x05, 0x01, 0x8A, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x06, 0x00, 
	0x00, 0x10, 0x05, 0x02, 0x88, 0x00, 0x14, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x07, 0x00, 
	0x00, 0x10, 0x05, 0x01, 0x85, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x10, 
	0x05, 0x00, 0x82, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x09, 0x00, 0x00, 0x10, 0x05, 0x01, 
	0x7F, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x0A, 0x00, 0x00, 0x10, 0x05, 0x02, 0x7C, 0x00, 
	0x14, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x0B, 0x00, 0x00, 0x10, 0x05, 0x01, 0x79, 0x00, 
	0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x0C, 0x00, 0x00, 0x10, 0x05, 0x00, 0x76, 0x00, 0x20, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x0D, 0x00, 0x00, 0x10, 0x05, 0x01, 0x73, 0x00, 0x1B, 0x07, 0x06, 0x00, 
	0x18, 0x1D, 0x02, 0x00, 0x0E, 0x00, 0x00, 0x10, 0x05, 0x02, 0x70, 0x00, 0x14, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x0F, 0x00, 0x00, 0x10, 0x05, 0x01, 0x6D, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x10, 0x00, 0x00, 0x10, 0x05, 0x00, 0x6A, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x11, 0x00, 
	0x00, 0x10, 0x05, 0x01, 0x67, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x12, 0x00, 
	0x00, 0x10, 0x05, 0x02, 0x65, 0x00, 0x14, 0x07, 0x06, 0x00, 0x02, 0x00, 0x13, 0x00, 0x00, 0x10, 
	0x05, 0x01, 0x63, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x14, 0x00, 0x00, 0x10, 0x05, 0x00, 
	0x63, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x15, 0x00, 0x00, 0x10, 0x05, 0x00, 0x65, 0x00, 
	0x1F, 0x07, 0x06, 0x00, 0x02, 0x00, 0x16, 0x00, 0x00, 0x10, 0x05, 0x00, 0x6A, 0x00, 0x1D, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x17, 0x00, 0x00, 0x10, 0x05, 0x00, 0x70, 0x00, 0x19, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x18, 0x00, 0x00, 0x10, 0x05, 0x00, 0x76, 0x00, 0x17, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x19, 0x00, 0x00, 0x10, 0x05, 0x00, 0x7C, 0x00, 0x16, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1A, 0x00, 
	0x00, 0x10, 0x05, 0x00, 0x82, 0x00, 0x17, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1B, 0x00, 0x00, 0x10, 
	0x05, 0x00, 0x88, 0x00, 0x19, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1C, 0x00, 0x00, 0x10, 0x05, 0x00, 
	0x8D, 0x00, 0x1D, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1D, 0x00, 0x00, 0x10, 0x05, 0x00, 0x93, 0x00, 
	0x1F, 0x07, 0x06, 0x00, 0x1C, 0x1B, 0x0F, 0x30, 0x02, 0x00, 0x01, 0x00, 0x00, 0x10, 0x05, 0x01, 
	0x94, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x10, 0x05, 0x01, 0x94, 0x00, 
	0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 
	0x14, 0x07, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 0x14, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 0x14, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x03, 0x00, 0x00, 0x10, 0x05, 0x01, 0x90, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x03, 0x00, 0x00, 0x10, 0x05, 0x01, 0x90, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x04, 0x00, 
	0x00, 0x10, 0x05, 0x00, 0x8D, 0x00, 0x20, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x05, 0x00, 
	0x00, 0x10, 0x05, 0x01, 0x8A, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x06, 0x00, 0x00, 0x10, 
	0x05, 0x02, 0x88, 0x00, 0x14, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x07, 0x00, 0x00, 0x10, 
	0x05, 0x01, 0x85, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x10, 0x05, 0x00, 
	0x82, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x09, 0x00, 0x00, 0x10, 0x05, 0x01, 0x7F, 0x00, 
	0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x0A, 0x00, 0x00, 0x10, 0x05, 0x02, 0x7C, 0x00, 0x14, 0x07, 
	0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x0B, 0x00, 0x00, 0x10, 0x05, 0x01, 0x79, 0x00, 0x1B, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x0C, 0x00, 0x00, 0x10, 0x05, 0x00, 0x76, 0x00, 0x20, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x0D, 0x00, 0x00, 0x10, 0x05, 0x01, 0x73, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 
	0x02, 0x00, 0x0E, 0x00, 0x00, 0x10, 0x05, 0x02, 0x70, 0x00, 0x14, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x0F, 0x00, 0x00, 0x10, 0x05, 0x01, 0x6D, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x10, 0x00, 
	0x00, 0x10, 0x05, 0x00, 0x6A, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x11, 0x00, 0x00, 0x10, 
	0x05, 0x01, 0x67, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x12, 0x00, 0x00, 0x10, 
	0x05, 0x02, 0x65, 0x00, 0x14, 0x07, 0x06, 0x00, 0x02, 0x00, 0x13, 0x00, 0x00, 0x10, 0x05, 0x01, 
	0x63, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x14, 0x00, 0x00, 0x10, 0x05, 0x00, 0x63, 0x00, 
	0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x15, 0x00, 0x00, 0x10, 0x05, 0x00, 0x65, 0x00, 0x1F, 0x07, 
	0x06, 0x00, 0x02, 0x00, 0x16, 0x00, 0x00, 0x10, 0x05, 0x00, 0x6A, 0x00, 0x1D, 0x07, 0x06, 0x00, 
	0x02, 0x00, 0x17, 0x00, 0x00, 0x10, 0x05, 0x00, 0x70, 0x00, 0x19, 0x07, 0x06, 0x00, 0x02, 0x00, 
	0x18, 0x00, 0x00, 0x10, 0x05, 0x00, 0x76, 0x00, 0x17, 0x07, 0x06, 0x00, 0x02, 0x00, 0x19, 0x00, 
	0x00, 0x10, 0x05, 0x00, 0x7C, 0x00, 0x16, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1A, 0x00, 0x00, 0x10, 
	0x05, 0x00, 0x82, 0x00, 0x17, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1B, 0x00, 0x00, 0x10, 0x05, 0x00, 
	0x88, 0x00, 0x19, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1C, 0x00, 0x00, 0x10, 0x05, 0x00, 0x8D, 0x00, 
	0x1D, 0x07, 0x06, 0x00, 0x02, 0x00, 0x1D, 0x00, 0x00, 0x10, 0x05, 0x00, 0x93, 0x00, 0x1F, 0x07, 
	0x06, 0x00, 0x1C, 0x06, 0x3C, 0x00, 0x1B, 0x0F, 0x31, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x05, 
	0x00, 0x95, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x05, 0x00, 0x95, 
	0x00, 0x20, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0x10, 0x05, 0x01, 0x94, 
	0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x10, 0x05, 0x01, 0x94, 0x00, 0x1B, 
	0x07, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 0x14, 0x07, 0x06, 
	0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x10, 0x05, 0x02, 0x93, 0x00, 0x14, 0x07, 0x06, 0x00, 0x18, 
	0x1D, 0x02, 0x00, 0x03, 0x00, 0x00, 0x10, 0x05, 0x01, 0x90, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 
	0x00, 0x04, 0x00, 0x00, 0x10, 0x05, 0x00, 0x8D, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x05, 
	0x00, 0x00, 0x10, 0x05, 0x01, 0x8A, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x06, 
	0x00, 0x00, 0x10, 0x05, 0x02, 0x88, 0x00, 0x14, 0x07, 0x06, 0x00, 0x02, 0x00, 0x07, 0x00, 0x00, 
	0x10, 0x05, 0x01, 0x85, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x08, 0x00, 0x00, 
	0x10, 0x05, 0x00, 0x82, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 0x00, 0x09, 0x00, 0x00, 0x10, 0x05, 
	0x01, 0x7F, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x0A, 0x00, 0x00, 0x10, 0x05, 0x02, 0x7C, 
	0x00, 0x14, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x0B, 0x00, 0x00, 0x10, 0x05, 0x01, 0x79, 
	0x00, 0x1B, 0x07, 0x06, 0x00, 0x02, 0x00, 0x0C, 0x00, 0x00, 0x10, 0x05, 0x00, 0x76, 0x00, 0x20, 
	0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 0x00, 0x0D, 0x00, 0x00, 0x10, 0x05, 0x01, 0x73, 0x00, 0x1B, 
	0x07, 0x06, 0x00, 0x02, 0x00, 0x0E, 0x00, 0x00, 0x10, 0x05, 0x02, 0x70, 0x00, 0x14, 0x07, 0x06, 
	0x00, 0x02, 0x00, 0x0F, 0x00, 0x00, 0x10, 0x05, 0x01, 0x6D, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 
	0x1D, 0x02, 0x00, 0x10, 0x00, 0x00, 0x10, 0x05, 0x00, 0x6A, 0x00, 0x20, 0x07, 0x06, 0x00, 0x02, 
	0x00, 0x11, 0x00, 0x00, 0x10, 0x05, 0x01, 0x67, 0x00, 0x1B, 0x07, 0x06, 0x00, 0x18, 0x1D, 0x02, 
	0x00, 0x12, 0x00, 0x00, 0x10, 0x05, 0x02, 0x65, 0x00, 0x14, 0x07, 0x06, 0x00, 0x06, 0x3C, 0x00, 
	0x02, 0x00, 0x1E, 0x00, 0x00, 0x10, 0x08, 0x12, 0x06, 0x1E, 0x00, 0x0A, 0x01, 0x02, 0x00, 0x1F, 
	0x00, 0x00, 0x10, 0x07, 0x0A, 0x00, 0x02, 0x00, 0x20, 0x00, 0x00, 0x10, 0x07, 0x0A, 0x00, 0x02, 
	0x00, 0x21, 0x00, 0x00, 0x10, 0x07, 0x0A, 0x00, 0x02, 0x00, 0x22, 0x00, 0x00, 0x10, 0x07, 0x0A, 
	0x00, 0x0B, 0x01, 0x02, 0x00, 0x18, 0x1F, 0x06, 0x0A, 0x00, 0x02, 0x00, 0x23, 0x00, 0x00, 0x10, 
	0x07, 0x14, 0x00, 0x18, 0x1E, 0x02, 0x00, 0x24, 0x00, 0x00, 0x10, 0x07, 0x14, 0x00, 0x02, 0x00, 
	0x25, 0x00, 0x00, 0x10, 0x07, 0x14, 0x00, 0x18, 0x1F, 0x02, 0x00, 0x26, 0x00, 0x00, 0x10, 0x07, 
	0x14, 0x00, 0x02, 0x00, 0x27, 0x00, 0x00, 0x10, 0x07, 0x14, 0x00, 0x18, 0x1E, 0x02, 0x00, 0x28, 
	0x00, 0x00, 0x10, 0x08, 0x06, 0x3C, 0x00, 0x18, 0x1E, 0x03, 0x00, 0x07, 0x06, 0x00, 0x18, 0x1E, 
	0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 
	0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x18, 0x1E, 
	0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 
	0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 
	0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x18, 0x1E, 0x03, 
	0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 
	0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 
	0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x18, 0x1E, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 
	0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 
	0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 
	0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x03, 0x00, 0x07, 0x06, 0x00, 0x13, 0x1C, 0x19, 0x01, 0x0E, 
	0x06, 0x3C, 0x00, 0x13, 0x01, 0x00, 0x1D
};

const uint8 KyraEngine::_seq_introData_KyrandiaLogo[] = {
	0x15, 0x00, 0x02, 0x00, 0x06, 0x01, 0x1A, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x06, 
	0x06, 0x00, 0x18, 0x14, 0x16, 0x04, 0x0A, 0x00, 0x03, 0x06, 0x16, 0x00, 0x0B, 0x00, 0x0B, 0x00, 
	0x06, 0x3C, 0x00, 0x18, 0x27, 0x0A, 0x01, 0x03, 0x06, 0x16, 0x00, 0x0B, 0x01, 0x0F, 0x00, 0x06, 
	0x3C, 0x00, 0x18, 0x27, 0x0A, 0x02, 0x04, 0x06, 0x16, 0x00, 0x0B, 0x02, 0x0F, 0x00, 0x02, 0x06, 
	0x0D, 0x00, 0x00, 0x00, 0x16, 0x00, 0x06, 0x06, 0x00, 0x06, 0x78, 0x00, 0x18, 0x14, 0x0A, 0x02, 
	0x04, 0x06, 0x16, 0x00, 0x0B, 0x02, 0x0C, 0x00, 0x13, 0x01, 0x06, 0x1D
};

const uint8 KyraEngine::_seq_introData_KallakMalcom[] = {
	0x00, 0x04, 0x01, 0x1A, 0x0E, 0x17, 0x00, 0x00, 0x00, 0x3F, 0x01, 0xC7, 0x0C, 0x00, 0x0C, 0x03, 
	0x0D, 0x00, 0x17, 0x00, 0x00, 0x88, 0x3F, 0x01, 0xC7, 0x0C, 0x02, 0x19, 0x00, 0x02, 0x04, 0x00, 
	0x10, 0x00, 0x3A, 0x09, 0x19, 0x00, 0x19, 0x3A, 0x14, 0x18, 0x23, 0x0A, 0x00, 0x03, 0x04, 0x07, 
	0x07, 0x00, 0x0B, 0x00, 0x22, 0x00, 0x10, 0x02, 0x50, 0x00, 0x3A, 0x05, 0x0A, 0x01, 0x03, 0x04, 
	0x07, 0x07, 0x00, 0x0B, 0x01, 0x07, 0x00, 0x06, 0x3C, 0x00, 0x10, 0x03, 0x50, 0x00, 0x3A, 0x05, 
	0x0A, 0x02, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x02, 0x17, 0x00, 0x06, 0x3C, 0x00, 0x10, 0x04, 
	0x50, 0x00, 0x3A, 0x05, 0x0A, 0x03, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x03, 0x0A, 0x00, 0x06, 
	0x3C, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 
	0x00, 0x10, 0x05, 0xF0, 0x00, 0x3A, 0x0F, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 
	0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x06, 0x3C, 0x00, 0x10, 0x06, 
	0xF0, 0x00, 0x3A, 0x0F, 0x0A, 0x04, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x04, 0x12, 0x00, 0x06, 
	0x3C, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 
	0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x06, 0x78, 0x00, 0x10, 0x07, 0xF0, 0x00, 0x3A, 0x0F, 0x0A, 
	0x05, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x05, 0x11, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 0x07, 
	0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x10, 0x08, 0x50, 0x00, 0x3A, 0x05, 0x0A, 0x06, 0x03, 
	0x04, 0x07, 0x07, 0x00, 0x0B, 0x06, 0x07, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 
	0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x10, 0x09, 0x50, 0x00, 0x3A, 0x05, 
	0x0A, 0x07, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x07, 0x0A, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 
	0x07, 0x07, 0x00, 0x10, 0x0A, 0x50, 0x00, 0x3A, 0x05, 0x0A, 0x08, 0x03, 0x04, 0x07, 0x07, 0x00, 
	0x0B, 0x08, 0x10, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x10, 0x0B, 0xF0, 0x00, 
	0x3A, 0x0F, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 
	0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 
	0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 0x07, 
	0x07, 0x00, 0x10, 0x0C, 0xF0, 0x00, 0x3A, 0x0F, 0x0A, 0x09, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 
	0x09, 0x0E, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 
	0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x03, 
	0x04, 0x07, 0x07, 0x00, 0x10, 0x0D, 0x50, 0x00, 0x3A, 0x05, 0x0A, 0x0A, 0x03, 0x04, 0x07, 0x07, 
	0x00, 0x0B, 0x0A, 0x0E, 0x00, 0x06, 0x3C, 0x00, 0x0A, 0x0B, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 
	0x0B, 0x02, 0x00, 0x18, 0x20, 0x0A, 0x0C, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x0C, 0x06, 0x00, 
	0x18, 0x21, 0x0A, 0x0D, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x0D, 0x0C, 0x00, 0x18, 0x22, 0x0A, 
	0x0E, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x0E, 0x0B, 0x00, 0x10, 0x0E, 0x50, 0x00, 0x3A, 0x05, 
	0x0A, 0x0F, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x0F, 0x09, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 
	0x07, 0x07, 0x00, 0x10, 0x0F, 0x50, 0x00, 0x3A, 0x05, 0x0A, 0x10, 0x03, 0x04, 0x07, 0x07, 0x00, 
	0x0B, 0x10, 0x09, 0x00, 0x06, 0x3C, 0x00, 0x03, 0x04, 0x07, 0x07, 0x00, 0x10, 0x10, 0x50, 0x00, 
	0x3A, 0x05, 0x0A, 0x11, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x11, 0x0F, 0x00, 0x06, 0x3C, 0x00, 
	0x03, 0x04, 0x07, 0x07, 0x00, 0x10, 0x11, 0x50, 0x00, 0x3A, 0x05, 0x0A, 0x12, 0x03, 0x04, 0x07, 
	0x07, 0x00, 0x0B, 0x12, 0x14, 0x00, 0x06, 0x3C, 0x00, 0x0A, 0x13, 0x03, 0x04, 0x07, 0x07, 0x00, 
	0x0B, 0x13, 0x06, 0x00, 0x18, 0x23, 0x0A, 0x13, 0x03, 0x04, 0x07, 0x07, 0x00, 0x0B, 0x13, 0x07, 
	0x00, 0x11, 0x06, 0x3C, 0x00, 0x13, 0x19, 0x01, 0x0E, 0x13, 0x01, 0x04, 0x1D
};

const uint8 KyraEngine::_seq_introData_MalcomTree[] = {
	0x00, 0x01, 0x00, 0x1A, 0x0E, 0x17, 0x00, 0x00, 0x00, 0x3F, 0x01, 0xC7, 0x0C, 0x00, 0x0C, 0x01, 
	0x0D, 0x01, 0x09, 0x02, 0x01, 0x00, 0x00, 0x00, 0x10, 0x19, 0x38, 0x09, 0x18, 0x1E, 0x14, 0x18, 
	0x1F, 0x0A, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x0B, 0x00, 0x1F, 0x00, 0x18, 0x19, 0x0A, 0x01, 
	0x03, 0x01, 0x06, 0x06, 0x00, 0x0B, 0x01, 0x0F, 0x00, 0x18, 0x26, 0x10, 0x1F, 0x50, 0x00, 0x2D, 
	0x05, 0x0A, 0x02, 0x03, 0x01, 0x06, 0x06, 0x00, 0x0B, 0x02, 0x10, 0x00, 0x11, 0x18, 0x1F, 0x03, 
	0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x18, 0x24, 
	0x18, 0x1F, 0x03, 0x01, 0x06, 0x06, 0x00, 0x18, 0x1E, 0x0A, 0x03, 0x03, 0x01, 0x06, 0x06, 0x00, 
	0x0B, 0x03, 0x15, 0x00, 0x10, 0x16, 0x50, 0x00, 0x2D, 0x05, 0x18, 0x1F, 0x03, 0x01, 0x06, 0x06, 
	0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x18, 0x1E, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 
	0x06, 0x00, 0x18, 0x1F, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 
	0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x18, 0x1E, 0x03, 0x01, 0x06, 0x06, 0x00, 0x18, 
	0x1A, 0x18, 0x1E, 0x0A, 0x05, 0x03, 0x01, 0x06, 0x06, 0x00, 0x0B, 0x05, 0x09, 0x00, 0x11, 0x0A, 
	0x06, 0x03, 0x01, 0x06, 0x06, 0x00, 0x0B, 0x06, 0x14, 0x00, 0x18, 0x1A, 0x18, 0x1F, 0x10, 0x17, 
	0x50, 0x00, 0x2D, 0x05, 0x06, 0x3C, 0x00, 0x0A, 0x07, 0x03, 0x01, 0x06, 0x06, 0x00, 0x0B, 0x07, 
	0x06, 0x00, 0x18, 0x1E, 0x06, 0x1E, 0x00, 0x10, 0x18, 0x50, 0x00, 0x2D, 0x05, 0x03, 0x01, 0x06, 
	0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x0A, 0x08, 0x04, 0x01, 
	0x06, 0x06, 0x00, 0x04, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 
	0x06, 0x00, 0x0B, 0x08, 0x01, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x06, 0x78, 0x00, 0x0A, 0x09, 
	0x03, 0x01, 0x06, 0x06, 0x00, 0x0B, 0x09, 0x04, 0x00, 0x18, 0x1B, 0x0A, 0x0A, 0x03, 0x01, 0x06, 
	0x06, 0x00, 0x0B, 0x0A, 0x09, 0x00, 0x06, 0x14, 0x00, 0x10, 0x19, 0x50, 0x00, 0x2D, 0x05, 0x03, 
	0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x0A, 0x0B, 0x03, 0x01, 0x06, 0x06, 0x00, 
	0x04, 0x01, 0x06, 0x06, 0x00, 0x04, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 
	0x01, 0x06, 0x06, 0x00, 0x0B, 0x0B, 0x01, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x03, 0x01, 0x06, 
	0x06, 0x00, 0x03, 0x01, 0x06, 0x06, 0x00, 0x10, 0x1A, 0x50, 0x00, 0x2D, 0x05, 0x0A, 0x0C, 0x03, 
	0x01, 0x06, 0x06, 0x00, 0x0B, 0x0C, 0x12, 0x00, 0x03, 0x01, 0x01, 0x01, 0x11, 0x15, 0x00, 0x02, 
	0x00, 0x02, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x10, 0x10, 0x1C, 0x50, 0x00, 0x2D, 0x05, 0x06, 
	0x3C, 0x00, 0x03, 0x02, 0x03, 0x02, 0x06, 0x06, 0x00, 0x11, 0x18, 0x1C, 0x0A, 0x0F, 0x03, 0x02, 
	0x06, 0x06, 0x00, 0x0B, 0x0F, 0x0D, 0x00, 0x10, 0x1D, 0x50, 0x00, 0x2D, 0x05, 0x0A, 0x10, 0x03, 
	0x02, 0x06, 0x06, 0x00, 0x03, 0x02, 0x06, 0x06, 0x00, 0x03, 0x02, 0x06, 0x06, 0x00, 0x04, 0x02, 
	0x06, 0x06, 0x00, 0x04, 0x02, 0x06, 0x06, 0x00, 0x04, 0x02, 0x06, 0x06, 0x00, 0x0B, 0x10, 0x02, 
	0x00, 0x10, 0x1E, 0x50, 0x00, 0x2D, 0x05, 0x0A, 0x11, 0x03, 0x02, 0x06, 0x06, 0x00, 0x03, 0x02, 
	0x06, 0x06, 0x00, 0x03, 0x02, 0x06, 0x06, 0x00, 0x04, 0x02, 0x06, 0x06, 0x00, 0x04, 0x02, 0x06, 
	0x06, 0x00, 0x04, 0x02, 0x06, 0x06, 0x00, 0x0B, 0x11, 0x02, 0x00, 0x06, 0xB4, 0x00, 0x13, 0x19, 
	0x01, 0x0E, 0x01, 0x01, 0x13, 0x01, 0x02, 0x1D	
};

const uint8 KyraEngine::_seq_introData_WestwoodLogo[] = {
	0x00, 0x03, 0x01, 0x1A, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x16, 0x01, 0x06, 0x06, 0x00, 0x06, 
	0x3C, 0x00, 0x18, 0x14, 0x0A, 0x00, 0x03, 0x03, 0x16, 0x01, 0x0B, 0x00, 0x08, 0x00, 0x06, 0x3C, 
	0x00, 0x18, 0x27, 0x0A, 0x01, 0x03, 0x03, 0x16, 0x01, 0x0B, 0x01, 0x0B, 0x00, 0x06, 0x78, 0x00, 
	0x18, 0x14, 0x02, 0x03, 0x0A, 0x00, 0x00, 0x00, 0x16, 0x01, 0x06, 0x06, 0x00, 0x0A, 0x02, 0x04, 
	0x03, 0x16, 0x01, 0x0B, 0x02, 0x09, 0x00, 0x13, 0x01, 0x03, 0x1D
};

const uint8 KyraEngine::_seq_codeSizeTable[] = {
	2, 1, 5, 1, 1, 4, 2, 2, 0, 0, 1, 3, 1, 1, 0, 1,
	5, 0, 0, 0, 0, 2, 1, 8, 1, 1, 0, 0, 0, 0, 0, 0
};

const char *KyraEngine::_seq_WSATable[] = {
	"kallak.wsa",
	"tree1.wsa",
	"tree2.wsa",
	"westwood.wsa",
	"mal-kal.wsa",
	"destruct.wsa",
	"kyrandia.wsa",
	"shore.wsa",
	"reunion.wsa",
	"reuniont.wsa",
	"latern.wsa"
};

const char *KyraEngine::_seq_CPSTable[] = {
	"gemcut.cps",
	"tree.cps"
};

const char *KyraEngine::_seq_COLTable[] = {
	"kallak.col",
	"tree_exp.col",
	"ww.col",
	"mal-kal.col"
};

const char *KyraEngine::_seq_textsTableEN[] = {
	"This is a text test - 1",
	"This is a text test - 2",
	"Greetings, Kallak...",
	"...Powerful leader of the Royal Mystics!",
	"Did I frighten you?",
	"Malcolm!",
	"I heard yesterday of your escape.",
	"And have expected you before now.",
	"Why would I rush?",
	"I rule this land!",
	"Your puny curse restrains me naught.",
	"So, slay me now!",
	"I have little magic left.",
	"I mean to harm you, have no doubt...",
	"...Now you are stone...",
	"...Yet I leave your eyes.",
	"I shed no tears for Kyrandia...",
	"...But cannot deny you yours.",
	"Malcolm the Jester has broken free!",
	"He now controls the Kyragem...",
	"...source of all magic in Kyrandia!",
	"",
	"How dare you trip ME!",
	"But no, something special for you...",
	"A humorous hex!",
	"But I shall give fair warning.",
	"Don't jump on THAT tree!",
	"Don't climb up THAT tree little squirrel!",
	"Boo!",
	"Tis funnier that way...",
	"...Is it not?",
	"Ha ha ha...",
	"Aren't fingers wonderful?",
	"It's great to be alive!",
	"Brandon!",
	"Grandfather! We did it!",
	"No! YOU did it!",
	"Long live King Brandon!",
	"Long live the Royal Mystics!",
	"Now, let's go put Kyrandia back together!",
	"Good idea!",
	"As my first Royal Proclamation...",
	"I name sandals as the official footwear of Kyrandia!",
	"Well done, Brandon!",
	"The Land no longer weeps...",
	"And your friends have been restored!",
	"Dear Brynn...",
	"Malcolm has broken free!",
	"Soon he will come for me.",
	"Please help Brandon...",
	""
};

} // End of namespace Kyra
