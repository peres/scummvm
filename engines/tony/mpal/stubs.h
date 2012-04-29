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
 *
 */

/****************************************************************************\
*       This file contains stubs and mappings for things used by the MPAL
*		library that are handled differently under ScummVM
\****************************************************************************/

#ifndef MPAL_STUBS
#define MPAL_STUBS

#include "common/scummsys.h"
#include "common/algorithm.h"
#include "tony/mpal/memory.h"

namespace Tony {

namespace MPAL {

/****************************************************************************\
*       Types
\****************************************************************************/

typedef uint32 (*LPTHREAD_START_ROUTINE)(void *lpThreadParameter);

/****************************************************************************\
*       Defines
\****************************************************************************/

#define GMEM_FIXED 1
#define GMEM_MOVEABLE 2
#define GMEM_ZEROINIT 4

#define MB_OK 1

#define PASCAL

/****************************************************************************\
*       Templates
\****************************************************************************/

/**
 * Copies data from the range [first, last) to [dst, dst + (last - first)).
 * It requires the range [dst, dst + (last - first)) to be valid.
 * It also requires dst not to be in the range [first, last).
 */
template<class In, class Out>
Out CopyMemory(Out dst, In first, int size) {
	return Common::copy(first, first + size, dst);
}

/****************************************************************************\
*       Methods
\****************************************************************************/

extern void MessageBox(const Common::String &msg);

extern uint32 timeGetTime();

#define INFINITE 0xffffffff
#define WAIT_OBJECT_0 -2
// Horrendously bad cast
#define INVALID_HANDLE_VALUE (void *)-3

extern HANDLE CreateThread(void *lpThreadAttributes, size_t dwStackSize,
		LPTHREAD_START_ROUTINE lpStartAddress, void *lpParameter,
		uint32 dwCreationFlags, uint32 *lpThreadId);

extern void ExitThread(int ThreadId);

extern void TerminateThread(HANDLE ThreadId, uint32 dwExitCode);

extern void CloseHandle(HANDLE ThreadId);

extern void Sleep(uint32 time);

extern int WaitForSingleObject(HANDLE ThreadId, uint32 dwSleepTime);

extern uint32 WaitForMultipleObjects(uint32 nCount, const HANDLE *lpHandles, bool bWaitAll, uint32 dwMilliseconds);

extern HANDLE CreateEvent(void *lpEventAttributes, bool bManualReset, bool bInitialState, const char *lpName);

extern void SetEvent(HANDLE hEvent);

extern void ResetEvent(HANDLE hEvent);

} // end of namespace MPAL

} // end of namespace Tony

#endif
