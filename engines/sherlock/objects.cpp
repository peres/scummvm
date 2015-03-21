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

#include "sherlock/objects.h"
#include "sherlock/sherlock.h"
#include "sherlock/people.h"
#include "sherlock/scene.h"
#include "common/util.h"

namespace Sherlock {

#define UPPER_LIMIT 0
#define LOWER_LIMIT CONTROLS_Y
#define LEFT_LIMIT 0
#define RIGHT_LIMIT SHERLOCK_SCREEN_WIDTH

SherlockEngine *Sprite::_vm;

/**
 * Reset the data for the sprite
 */
void Sprite::clear() {
	_name = "";
	_description = "";
	_examine.clear();
	_pickUp = "";
	_sequences = nullptr;
	_images = nullptr;
	_imageFrame = nullptr;
	_walkCount = 0;
	_allow = 0;
	_frameNumber = _sequenceNumber = 0;
	_position.x = _position.y = 0;
	_delta.x = _delta.y = 0;
	_oldPosition.x = _oldPosition.y = 0;
	_oldSize.x = _oldSize.y = 0;
	_goto.x = _goto.y = 0;
	_type = INVALID;
	_pickUp.clear();
	_noShapeSize.x = _noShapeSize.y = 0;
	_status = 0;
	_misc = 0;
	_numFrames = 0;
}

/**
 * Updates the image frame poiner for the sprite
 */
void Sprite::setImageFrame() {
	int imageNumber = (*_sequences)[_sequenceNumber][_frameNumber] + 
		(*_sequences)[_sequenceNumber][0] - 2;
	_imageFrame = &(*_images)[imageNumber];
}

/**
 * This adjusts the sprites position, as well as it's animation sequence:
 */
void Sprite::adjustSprite() {
	People &people = *_vm->_people;
	Scene &scene = *_vm->_scene;

	if (_type == INVALID || (_type == CHARACTER && _vm->_animating))
		return;

	if (!_vm->_talkCounter && _type == CHARACTER && _walkCount) {
		// Handle active movement for the sprite
		_position += _delta;
		--_walkCount;

		if (!_walkCount) {
			// If there any points left for the character to walk to along the
			// route to a destination, then move to the next point
			if (!people._walkTo.empty()) {
				people._walkDest = people._walkTo.pop();
				people.setWalking();
			} else {
				people.gotoStand(*this);
			}
		}
	}

	if (_type == CHARACTER && !_vm->_onChessboard) {
		if ((_position.y / 100) > LOWER_LIMIT) {
			_position.y = LOWER_LIMIT * 100;
			people.gotoStand(*this);
		}

		if ((_position.y / 100) < UPPER_LIMIT) {
			_position.y = UPPER_LIMIT * 100;
			people.gotoStand(*this);
		}

		if ((_position.x / 100) < LEFT_LIMIT) {
			_position.x = LEFT_LIMIT * 100;
			people.gotoStand(*this);
		}
	} else if (!_vm->_onChessboard) {
		_position.y = CLIP((int)_position.y, UPPER_LIMIT, LOWER_LIMIT);
		_position.x = CLIP((int)_position.x, LEFT_LIMIT, RIGHT_LIMIT);
	}

	if (!_vm->_onChessboard || (_vm->_slowChess = !_vm->_slowChess))
		++_frameNumber;

	if ((*_sequences)[_sequenceNumber][_frameNumber] == 0) {
		switch (_sequenceNumber) {
		case STOP_UP:
		case STOP_DOWN:
		case STOP_LEFT:
		case STOP_RIGHT:
		case STOP_UPRIGHT:
		case STOP_UPLEFT:
		case STOP_DOWNRIGHT:
		case STOP_DOWNLEFT:
			// We're in a stop sequence, so reset back to the last frame, so
			// the character is shown as standing still
			--_frameNumber;
			break;

		default:
			// Move 1 past the first frame - we need to compensate, since we
			// already passed the frame increment
			_frameNumber = 1;
			break;
		}
	}

	// Update the _imageFrame to point to the new frame's image
	setImageFrame();

	// Check to see if character has entered an exit zone
	if (!_walkCount && scene._walkedInScene && scene._goToRoom == -1) {
		Common::Rect charRect(_position.x / 100 - 5, _position.y / 100 - 2,
			_position.x / 100 + 5, _position.y / 100 + 2);
		Exit *exit = scene.checkForExit(charRect);

		if (exit) {
			scene._hsavedPos = exit->_people;
			scene._hsavedFs = exit->_peopleDir;

			if (scene._hsavedFs > 100 && scene._hsavedPos.x < 1)
				scene._hsavedPos.x = 100;
		}		
	}
}

/*----------------------------------------------------------------*/

void ActionType::synchronize(Common::SeekableReadStream &s) {
	char buffer[12];
	
	_cAnimNum = s.readByte();
	_cAnimSpeed = s.readByte();

	for (int idx = 0; idx < 4; ++idx) {
		s.read(buffer, 12);
		_names[idx] = Common::String(buffer);
	}
}

/*----------------------------------------------------------------*/

void UseType::synchronize(Common::SeekableReadStream &s) {
	char buffer[12];

	_cAnimNum = s.readByte();
	_cAnimSpeed = s.readByte();

	for (int idx = 0; idx < 4; ++idx) {
		s.read(buffer, 12);
		_names[idx] = Common::String(buffer);
	}

	_useFlag = s.readUint16LE();
	_dFlag[0] = s.readUint16LE();
	_lFlag[0] = s.readUint16LE();
	_lFlag[1] = s.readUint16LE();

	s.read(buffer, 12);
	_target = Common::String(buffer);
}

/*----------------------------------------------------------------*/

SherlockEngine *Object::_vm;
bool Object::_countCAnimFrames;

void Object::setVm(SherlockEngine *vm) {
	_vm = vm;
	_countCAnimFrames = false;
}

/**
 * Load the object data from the passed stream
 */
void Object::synchronize(Common::SeekableReadStream &s) {
	char buffer[50];

	s.read(buffer, 12);
	_name = Common::String(buffer);
	s.read(buffer, 41);
	_description = Common::String(buffer);

	_examine.clear();
	_sequences = nullptr;
	_images = nullptr;
	_imageFrame = nullptr;

	s.skip(4);
	_sequenceOffset = s.readUint32LE();
	s.seek(8, SEEK_CUR);

	_walkCount = s.readByte();
	_allow = s.readByte();
	_frameNumber = s.readSint16LE();
	_sequenceNumber = s.readSint16LE();
	_position.x = s.readSint16LE();
	_position.y = s.readSint16LE();
	_delta.x = s.readSint16LE();
	_delta.y = s.readSint16LE();
	_type = (SpriteType)s.readUint16LE();
	_oldPosition.x = s.readSint16LE();
	_oldPosition.y = s.readSint16LE();
	_oldSize.x = s.readUint16LE();
	_oldSize.y = s.readUint16LE();
	_goto.x = s.readSint16LE();
	_goto.y = s.readSint16LE();
	
	_pickup = s.readByte();
	_defaultCommand = s.readByte();
	_lookFlag = s.readUint16LE();
	_pickupFlag = s.readUint16LE();
	_requiredFlag = s.readUint16LE();
	_noShapeSize.x = s.readUint16LE();
	_noShapeSize.y = s.readUint16LE();
	_status = s.readUint16LE();
	_misc = s.readByte();
	_maxFrames = s.readUint16LE();
	_flags = s.readByte();	
	_aOpen.synchronize(s);
	_aType = (AType)s.readByte();
	_lookFrames = s.readByte();
	_seqCounter = s.readByte();
	_lookPosition.x = s.readUint16LE();
	_lookPosition.y = s.readByte();
	_lookFacing = s.readByte();
	_lookcAnim = s.readByte();
	_aClose.synchronize(s);
	_seqStack = s.readByte();
	_seqTo = s.readByte();
	_descOffset = s.readUint16LE();
	_seqcounter2 = s.readByte();
	_seqSize = s.readUint16LE();
	s.skip(1);
	_aMove.synchronize(s);
	s.skip(8);
	
	for (int idx = 0; idx < 4; ++idx)
		_use[idx].synchronize(s);
}

/**
 * Toggle the type of an object between hidden and active
 */
void Object::toggleHidden() {
	if (_type != HIDDEN && _type != HIDE_SHAPE && _type != INVALID) {
		if (_seqTo != 0)
			_sequences[_frameNumber] = _seqTo + SEQ_TO_CODE + 128;
		_seqTo = 0;

		if (_images == nullptr || _images->size() == 0)
			// No shape to erase, so flag as hidden
			_type = HIDDEN;
		else
			// Otherwise, flag it to be hidden after it gets erased
			_type = HIDE_SHAPE;
	} else if (_type != INVALID) {
		if (_seqTo != 0)
			_sequences[_frameNumber] = _seqTo + SEQ_TO_CODE + 128;
		_seqTo = 0;

		_seqCounter = _seqcounter2 = 0;
		_seqStack = 0;
		_frameNumber = -1;

		if (_images == nullptr || _images->size() == 0) {
			_type = NO_SHAPE;
		} else {
			_type = ACTIVE_BG_SHAPE;
			int idx = _sequences[0];
			if (idx >= _maxFrames)
				// Turn on: set up first frame
				idx = 0;

			_imageFrame = &(*_images)[idx];
		}
	}
}

/**
 * Check the state of the object
 */
void Object::checkObject(Object &o) {
	Scene &scene = *_vm->_scene;
	Sound &sound = *_vm->_sound;
	int checkFrame = _allow ? MAX_FRAME : 32000;
	bool codeFound;

	if (_seqTo) {
		byte *ptr = &_sequences[_frameNumber];
		if (*ptr == _seqTo) {
			// The sequence is completed
			*ptr = _seqTo + SEQ_TO_CODE + 128;	// Reset to normal
			_seqTo = 0;
		} else {
			// Continue doing sequence
			if (*ptr > _seqTo)
				*ptr--;
			else
				*ptr++;

			return;
		}
	}

	++_frameNumber;

	do {
		// Check for end of sequence
		codeFound = checkEndOfSequence();

		if (_sequences[_frameNumber] >= 128 && _frameNumber < checkFrame) {
			codeFound = true;
			int v = _sequences[_frameNumber];

			if (v >= 228) {
				// Goto code found
				v -= 228;
				_seqcounter2 = _seqCounter;
				_seqStack = _frameNumber + 1;
				setObjSequence(v, false);
			} else if (v >= SOUND_CODE && (v <= (SOUND_CODE + 29))) {
				codeFound = true;
				++_frameNumber;
				v -= SOUND_CODE;

				if (sound._soundOn && !_countCAnimFrames) {
					if (!scene._sounds[v - 1]._name.empty() && sound._digitized)
						sound.playLoadedSound(v - 1, 0);
				}
			} else if (v >= FLIP_CODE && v <= (FLIP_CODE + 2)) {
				// Flip code
				codeFound = true;
				++_frameNumber;
				v -= FLIP_CODE;

				// Alter the flipped status
				switch (v) {
				case 0:
					// Clear the flag
					_flags &= ~2;
					break;
				case 1:
					// Set the flag
					_flags |= 2;
					break;
				case 2:
					// Toggle the flag
					_flags ^= 2;
					break;
				default:
					break;
				}
			} else {
				v -= 128;

				// 68-99 is a squence code
				if (v > SEQ_TO_CODE) {
					byte *p = &_sequences[_frameNumber];
					v -= SEQ_TO_CODE;	// # from 1-32
					_seqTo = v;
					*p = *(p - 1);

					if (*p > 128)
						// If the high bit is set, convert to a real frame
						*p -= (byte)(SEQ_TO_CODE - 128);

					if (*p > _seqTo)
						*p -= 1;
					else
						*p += 1;

					// Will be incremented below to return back to original value
					--_frameNumber;
					v = 0;
				} else if (v == 10) {
					// Set delta for objects
					Common::Point pt(_sequences[_frameNumber + 1], _sequences[_frameNumber + 2]);
					if (pt.x > 128)
						pt.x = (pt.x - 128) *  -1;
					else
						pt.x--;

					if (pt.y > 128)
						pt.y = (pt.y - 128) * -1;
					else
						pt.y;

					_delta = pt;
					_frameNumber += 2;
				} else if (v < 4) {
					for (int idx = 0; idx < 4; ++idx) {
						o.checkNameForCodes(_use[v]._names[idx], nullptr);
					}

					if (_use[v]._useFlag)
						_vm->setFlags(_use[v]._useFlag);
				}

				++_frameNumber;
			}
		}
	} while (codeFound);
}

bool Object::checkEndOfSequence() const {
	// TODO
	return false;
}

void Object::setObjSequence(int seq, bool wait) {
	// TODO
}

/**
* Checks for codes
* @param name		The name to check for codes
* @param messages	If provided, any messages to be returned
* @returns		0 if no codes are found, 1 if codes were found
*/
int Object::checkNameForCodes(const Common::String &name, Common::StringArray *messages) {

	// TODO
	return 0;
}

/*----------------------------------------------------------------*/

void CAnim::synchronize(Common::SeekableReadStream &s) {
	char buffer[12];
	s.read(buffer, 12);
	_name = Common::String(buffer);

	s.read(_sequences, 30);
	_position.x = s.readSint16LE();
	_position.y = s.readSint16LE();
	_size = s.readUint32LE();
	_type = (SpriteType)s.readUint16LE();
	_flags = s.readByte();
	_goto.x = s.readSint16LE();
	_goto.y = s.readSint16LE();
	_gotoDir = s.readSint16LE();
	_teleportPos.x = s.readSint16LE();
	_teleportPos.y = s.readSint16LE();
	_teleportDir = s.readSint16LE();
}

/*----------------------------------------------------------------*/

InvGraphicType::InvGraphicType() {
	_images = nullptr;
	_maxFrames = 0;
	_filesize = 0;
}

} // End of namespace Sherlock
