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
 * $URL$
 * $Id$
 *
 */

#include "common/stream.h"
#include "common/util.h"

#include "audio/mixer.h"
#include "audio/mididrv.h"
#include "audio/midiparser.h"
#include "audio/softsynth/emumidi.h"

#include "parallaction/sound.h"


namespace Parallaction {

class AdlibMidiDriver : public MidiDriver_Emulated {

public:
	AdlibMidiDriver(Audio::Mixer *mixer);
	virtual ~AdlibMidiDriver() { }

	virtual int open();
	virtual void close();
	virtual void send(uint32 b);
	virtual MidiChannel* allocateChannel();
	virtual MidiChannel* getPercussionChannel();
	virtual bool isStereo() const;
	virtual int getRate() const;
	virtual void generateSamples(int16* data, int len);
};

AdlibMidiDriver::AdlibMidiDriver(Audio::Mixer *mixer) : MidiDriver_Emulated(mixer) {

}

int AdlibMidiDriver::open() {
	return MidiDriver_Emulated::open();
}

void AdlibMidiDriver::close() {

}

void AdlibMidiDriver::send(uint32 b) {

}

MidiChannel* AdlibMidiDriver::allocateChannel() {
	return 0;
}

MidiChannel* AdlibMidiDriver::getPercussionChannel() {
	return 0;
}

bool AdlibMidiDriver::isStereo() const {
	return false;
}

int AdlibMidiDriver::getRate() const {
	return _mixer->getOutputRate();
}

void AdlibMidiDriver::generateSamples(int16* data, int len) {
	memset(data, 0, len);
}




MidiDriver *createAdlibMidiDriver(Audio::Mixer *mixer) {
	return new AdlibMidiDriver(mixer);
}

} // namespace Parallaction
