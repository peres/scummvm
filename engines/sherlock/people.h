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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef SHERLOCK_PEOPLE_H
#define SHERLOCK_PEOPLE_H

#include "common/scummsys.h"
#include "common/stack.h"
#include "sherlock/objects.h"

namespace Sherlock {

// People definitions
enum PeopleId {
	PLAYER	= 0,
	AL		= 0,
	PEG		= 1,
	MAX_PEOPLE = 2
};

// Animation sequence identifiers for characters
enum {
	WALK_RIGHT = 0, WALK_DOWN = 1, WALK_LEFT = 2, WALK_UP = 3, STOP_LEFT = 4,
	STOP_DOWN = 5, STOP_RIGHT = 6, STOP_UP = 7, WALK_UPRIGHT = 8,
	WALK_DOWNRIGHT = 9, WALK_UPLEFT = 10, WALK_DOWNLEFT = 11,
	STOP_UPRIGHT = 12, STOP_UPLEFT = 13, STOP_DOWNRIGHT = 14,
	STOP_DOWNLEFT = 15, TALK_RIGHT = 6, TALK_LEFT = 4,
};
enum {
	MAP_UP = 1, MAP_UPRIGHT = 2, MAP_RIGHT = 1, MAP_DOWNRIGHT = 4,
	MAP_DOWN = 5, MAP_DOWNLEFT = 6, MAP_LEFT = 2, MAP_UPLEFT = 8
};

class SherlockEngine;

class People {
private:
	SherlockEngine *_vm;
	Sprite _data[MAX_PEOPLE];
	Sprite &_player;
	bool _walkLoaded;
	int _oldWalkSequence;
	bool _allowWalkAbort;
public:
	Common::Point _walkDest;
	Common::Stack<Common::Point> _walkTo;
	bool _holmesOn;
public:
	People(SherlockEngine *vm);
	~People();

	Sprite &operator[](PeopleId id) { return _data[id]; }

	bool isHolmesActive() const { return _walkLoaded && _holmesOn; }

	void reset();

	bool loadWalk();

	void setWalking();

	void gotoStand(Sprite &sprite);

	void walkToCoords(const Common::Point &destPos, int destDir);
};

} // End of namespace Sherlock

#endif
