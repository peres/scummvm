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

#ifndef GARGOYLE_UNICODE_H
#define GARGOYLE_UNICODE_H

#include "gargoyle/glk_types.h"

namespace Gargoyle {

typedef glui32 gli_case_block_t[2]; /* upper, lower */
enum BufferChangeCase { CASE_UPPER = 0, CASE_LOWER = 1, CASE_TITLE = 2, CASE_IDENT = 3 };
enum BufferChangeCond { COND_ALL = 0, COND_LINESTART = 1 };

/*
 * Get the length of a unicode string
 */
size_t strlen_uni(const uint32 *s);

/**
 * Apply a case change to the buffer. The len is the length of the buffer
 * array; numchars is the number of characters originally in it. (This
 * may be less than len.) The result will be clipped to fit len, but
 * the return value will be the full number of characters that the
 *converted string should have contained.
 */
extern glui32 bufferChangeCase(glui32 *buf, glui32 len,
                               glui32 numchars, BufferChangeCase destcase, BufferChangeCond cond, int changerest);

} // End of namespace Gargoyle

#endif
