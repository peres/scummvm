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

#include "common/config-manager.h"

#include "trecision/nl/3d/3dinc.h"
#include "trecision/nl/define.h"
#include "trecision/nl/extern.h"
#include "trecision/nl/message.h"
#include "trecision/nl/proto.h"
#include "trecision/nl/struct.h"
#include "trecision/logic.h"
#include "trecision/dialog.h"
#include "trecision/sound.h"
#include "trecision/graphics.h"
#include "trecision/trecision.h"
#include "trecision/video.h"

namespace Trecision {
LogicManager::LogicManager(TrecisionEngine *vm) : _vm(vm) {
	for (int i = 0; i < 7; ++i)
		_comb35[i] = 0;
	_count35 = 0;

	for (int i = 0; i < 4; ++i)
		_comb49[i] = 0;

	for (int i = 0; i < 6; ++i) {
		_comb58[i] = 0;
		_comb4CT[i] = 0;
	}
	_count58 = 0;

	_wheel = 0xFFFF;
	for (int i = 0; i < 3; ++i)
		_wheelPos[i] = 0;

	_slotMachine41Counter = 0;
}
LogicManager::~LogicManager() {}

void LogicManager::syncGameStream(Common::Serializer &ser) {
	for (int i = 0; i < 7; i++)
		ser.syncAsUint16LE(_comb35[i]);
	for (int i = 0; i < 4; i++)
		ser.syncAsUint16LE(_comb49[i]);
	for (int i = 0; i < 6; i++)
		ser.syncAsUint16LE(_comb4CT[i]);
	for (int i = 0; i < 6; i++)
		ser.syncAsUint16LE(_comb58[i]);
	for (int i = 0; i < 3; i++)
		ser.syncAsUint16LE(_wheelPos[i]);
	ser.syncAsUint16LE(_wheel);
	ser.syncAsUint16LE(_count35);
	ser.syncAsUint16LE(_count58);
	ser.syncAsUint16LE(_slotMachine41Counter);
}

void LogicManager::initScript() {
	int f = 0;

	_vm->_script[s16CARD]._firstFrame = f;
	_vm->_script[s16CARD]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_CHARACTER;
	_vm->_scriptFrame[f]._event = ME_CHARACTERACTION;
	_vm->_scriptFrame[f++]._u16Param1 = a166USECREDITCARD;

	_vm->_scriptFrame[f]._class = MC_ACTION;
	_vm->_scriptFrame[f]._event = ME_MOUSEOPERATE;
	_vm->_scriptFrame[f++]._u32Param = oTICKETOFFICE16;

	_vm->_script[S16MONEY]._firstFrame = ++f;
	_vm->_script[S16MONEY]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_CHARACTER;
	_vm->_scriptFrame[f]._event = ME_CHARACTERACTION;
	_vm->_scriptFrame[f++]._u16Param1 = a167USEMONEY;

	_vm->_scriptFrame[f]._class = MC_ACTION;
	_vm->_scriptFrame[f]._event = ME_MOUSEOPERATE;
	_vm->_scriptFrame[f++]._u32Param = oTICKETOFFICE16;

	_vm->_script[s19EVA]._firstFrame = ++f;
	_vm->_script[s19EVA]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._event = ME_MRIGHT;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param1 = 214;
	_vm->_scriptFrame[f]._u16Param2 = TOP + 140;
	_vm->_scriptFrame[f++]._u32Param = ocEVA19;

	_vm->_script[s4AHELLEN]._firstFrame = ++f;
	_vm->_script[s4AHELLEN]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_CHARACTER;
	_vm->_scriptFrame[f]._event = ME_CHARACTERACTION;
	_vm->_scriptFrame[f++]._u16Param1 = a4A2;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param1 = 336;
	_vm->_scriptFrame[f]._u16Param2 = 263 + TOP;
	_vm->_scriptFrame[f++]._u32Param = 0;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param1 = 336;
	_vm->_scriptFrame[f]._u16Param2 = 260 + TOP;
	_vm->_scriptFrame[f++]._u32Param = 0;

	_vm->_scriptFrame[f]._class = MC_DIALOG;
	_vm->_scriptFrame[f]._event = ME_STARTDIALOG;
	_vm->_scriptFrame[f++]._u16Param1 = dF4A3;

	_vm->_script[s49SUNDIAL]._firstFrame = ++f;
	_vm->_script[s49SUNDIAL]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_SCRIPT;
	_vm->_scriptFrame[f]._event = ME_CHANGER;
	_vm->_scriptFrame[f]._u16Param1 = kRoom49;
	_vm->_scriptFrame[f]._u16Param2 = a496;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f++]._u32Param = 1;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param1 = 360;
	_vm->_scriptFrame[f]._u16Param2 = 255 + TOP;
	_vm->_scriptFrame[f++]._u32Param = 0;

	_vm->_scriptFrame[f]._class = MC_SCRIPT;
	_vm->_scriptFrame[f]._event = ME_CHANGER;
	_vm->_scriptFrame[f]._u16Param1 = kRoom4A;
	_vm->_scriptFrame[f]._u16Param2 = 0;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f++]._u32Param = 1;

	//	Fast change room in double room of level 2
	_vm->_script[s21TO22]._firstFrame = ++f;
	_vm->_script[s21TO22]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 317;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 166;
	_vm->_scriptFrame[f]._event = ME_MRIGHT;
	_vm->_scriptFrame[f++]._u32Param = oCATENAT21;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 429;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 194;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f++]._u32Param = od21TO22;

	_vm->_script[s21TO23]._firstFrame = ++f;
	_vm->_script[s21TO23]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 317;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 166;
	_vm->_scriptFrame[f]._event = ME_MRIGHT;
	_vm->_scriptFrame[f++]._u32Param = oCATENAT21;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 204;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 157;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f++]._u32Param = od21TO23;

	_vm->_script[s24TO23]._firstFrame = ++f;
	_vm->_script[s24TO23]._flag = 0;
	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 316;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 213;
	_vm->_scriptFrame[f]._event = ME_MRIGHT;
	_vm->_scriptFrame[f++]._u32Param = oPASSAGE24;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 120;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 196;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f++]._u32Param = od24TO23;

	_vm->_script[s24TO26]._firstFrame = ++f;
	_vm->_script[s24TO26]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 316;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 213;
	_vm->_scriptFrame[f]._event = ME_MRIGHT;
	_vm->_scriptFrame[f++]._u32Param = oPASSAGE24;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 527;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 187;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f++]._u32Param = od24TO26;

	_vm->_script[s2ETO2C]._firstFrame = ++f;
	_vm->_script[s2ETO2C]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 420;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 238;
	_vm->_scriptFrame[f]._event = ME_MRIGHT;
	_vm->_scriptFrame[f++]._u32Param = oCATWALKA2E;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 66;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 336;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f++]._u32Param = od2ETO2C;

	_vm->_script[s2ETO2F]._firstFrame = ++f;
	_vm->_script[s2ETO2F]._flag = 0;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 420;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 238;
	_vm->_scriptFrame[f]._event = ME_MRIGHT;
	_vm->_scriptFrame[f++]._u32Param = oCATWALKA2E;

	_vm->_scriptFrame[f]._class = MC_MOUSE;
	_vm->_scriptFrame[f]._u16Param1 = 213;
	_vm->_scriptFrame[f]._u8Param = 1;
	_vm->_scriptFrame[f]._u16Param2 = 69;
	_vm->_scriptFrame[f]._event = ME_MLEFT;
	_vm->_scriptFrame[f]._u32Param = oENTRANCE2E;
}

void LogicManager::setupAltRoom(uint16 room, bool altRoomFl) {
	switch (room) {
	case kRoom21:
		if (!altRoomFl) {
			read3D("21.3d");
			_vm->_room[kRoom21]._flag &= ~kObjFlagExtra;
			setPosition(14);
			_vm->_obj[oCATENAT21]._position = 5;
			_vm->_obj[oUSCITA21]._position = 11;

			// if we can go beyond
			if (((_vm->iconPos(iSBARRA21) != MAXICON) && ((_vm->_dialogMgr->_choice[436]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[466]._flag & kObjFlagDone)))
				|| ((_vm->_dialogMgr->_choice[451]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[481]._flag & kObjFlagDone))) {
				_vm->_obj[od21TO23]._flag |= kObjFlagRoomOut;
				_vm->_obj[od21TO23]._flag &= ~kObjFlagExamine;
			} else {
				_vm->_obj[od21TO23]._flag &= ~kObjFlagRoomOut;
				_vm->_obj[od21TO23]._flag |= kObjFlagExamine;
			}

			_vm->_obj[od21TO23]._anim = 0;
			_vm->_obj[oUSCITA21]._mode |= OBJMODE_OBJSTATUS;

			_vm->_obj[od21TO22]._flag |= kObjFlagRoomOut;
			_vm->_obj[od21TO22]._flag &= ~kObjFlagExamine;
			_vm->_obj[od21TO22]._anim = aWALKOUT;
			_vm->_obj[oDOORA21]._anim = a212;
			_vm->_obj[oDOORC21]._anim = a219;

			_vm->_obj[oCUNICOLO21]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oCARTELLONE21]._mode |= OBJMODE_OBJSTATUS;
		} else {
			read3D("212.3d");
			_vm->_room[kRoom21]._flag |= kObjFlagExtra;
			setPosition(15);
			_vm->_obj[oCATENAT21]._position = 6;
			_vm->_obj[oUSCITA21]._position = 21;

			_vm->_obj[od21TO23]._flag |= kObjFlagRoomOut;
			_vm->_obj[od21TO23]._flag &= ~kObjFlagExamine;
			_vm->_obj[od21TO23]._anim = aWALKOUT;
			_vm->_obj[oUSCITA21]._mode |= OBJMODE_OBJSTATUS;

			// If we can go beyond
			if (((_vm->iconPos(iSBARRA21) != MAXICON) && ((_vm->_dialogMgr->_choice[436]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[466]._flag & kObjFlagDone)))
				|| ((_vm->_dialogMgr->_choice[451]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[481]._flag & kObjFlagDone))) {
				_vm->_obj[od21TO22]._flag |= kObjFlagRoomOut;
				_vm->_obj[od21TO22]._flag &= ~kObjFlagExamine;
			} else {
				_vm->_obj[od21TO22]._flag &= ~kObjFlagRoomOut;
				_vm->_obj[od21TO22]._flag |= kObjFlagExamine;
			}
			_vm->_obj[od21TO22]._anim = 0;
			_vm->_obj[od21TO22]._examine = 335;
			_vm->_obj[od21TO22]._action = 335;
			_vm->_obj[oDOORA21]._anim = 0;
			_vm->_obj[oDOORC21]._anim = 0;

			_vm->_obj[oCUNICOLO21]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCARTELLONE21]._mode &= ~OBJMODE_OBJSTATUS;
		}
		break;
	case kRoom24:
		if (!altRoomFl) {
			read3D("24.3d");
			_vm->_room[kRoom24]._flag &= ~kObjFlagExtra;
			_vm->_obj[oPASSAGE24]._position = 3;
			_vm->_obj[oMACERIE24]._position = 3;
			_vm->_obj[oDUMMY24]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oDUMMY24A]._mode |= OBJMODE_OBJSTATUS;
		} else {
			read3D("242.3d");
			_vm->_room[kRoom24]._flag |= kObjFlagExtra;
			_vm->_obj[od24TO26]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPASSAGE24]._position = 4;
			_vm->_obj[oMACERIE24]._position = 4;
			_vm->_obj[oDUMMY24A]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oDUMMY24]._mode |= OBJMODE_OBJSTATUS;
		}
		break;

	case kRoom2A:
		if (!altRoomFl) {
			read3D("2A.3d");
			_vm->_room[kRoom2A]._flag &= ~kObjFlagExtra;
			_vm->_obj[oDUMMY2A2]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oDUMMY2A]._mode &= ~OBJMODE_OBJSTATUS;
		} else {
			read3D("2A2.3d");
			_vm->_room[kRoom2A]._flag |= kObjFlagExtra;
			_vm->_obj[oDUMMY2A]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oDUMMY2A2]._mode &= ~OBJMODE_OBJSTATUS;
		}
		break;
	case kRoom2B:
		if (!altRoomFl) {
			read3D("2B.3d");
			_vm->_room[kRoom2B]._flag &= ~kObjFlagExtra;
			_vm->_obj[oDOOR2B]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[od2BALLA28]._mode &= ~OBJMODE_OBJSTATUS;
		} else {
			read3D("2B2.3d");
			_vm->_room[kRoom2B]._flag |= kObjFlagExtra;
			_vm->_obj[oDOOR2B]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[od2BALLA28]._mode |= OBJMODE_OBJSTATUS;
		}
		break;
	case kRoom2E:
		if (!altRoomFl) {
			_vm->_obj[oCATWALKA2E]._nbox = BACKGROUND;
			_vm->_obj[oCATWALKA2E]._position = 2;
			_vm->_obj[oCATWALKA2E]._anim = a2E2PRIMAPALLONTANANDO;
			read3D("2E.3d");
			_vm->_room[kRoom2E]._flag &= ~kObjFlagExtra;
			_vm->_obj[oDUMMY2E]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oENTRANCE2E]._flag &= ~kObjFlagExamine;
			_vm->_obj[oPASSERELLAB2E]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCRATERE2E]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oARBUSTI2E]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCREPACCIO2E]._position = 6;
		} else {
			_vm->_obj[oCATWALKA2E]._position = 3;
			_vm->_obj[oCATWALKA2E]._anim = a2E3PRIMAPAVVICINANDO;
			read3D("2E2.3d");
			_vm->_room[kRoom2E]._flag |= kObjFlagExtra;
			_vm->_obj[oDUMMY2E]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oENTRANCE2E]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oENTRANCE2E]._flag |= kObjFlagExamine;
			_vm->_obj[oPASSERELLAB2E]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oCRATERE2E]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oARBUSTI2E]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oCREPACCIO2E]._position = 7;
			_vm->_obj[oCATWALKA2E]._nbox = FOREGROUND;
		}
		break;
	case kRoom2GV:
		if (!altRoomFl) {
			_vm->_obj[oVIADOTTO2GV]._position = 7;
			_vm->_obj[oVIADOTTO2GV]._anim = a2G7ATTRAVERSAPONTICELLO;
			read3D("2GV.3d");
			_vm->_room[kRoom2GV]._flag &= ~kObjFlagExtra;
			_vm->_obj[oDUMMY2GV]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oRAGAZZOS2GV]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCOCCODRILLO2GV]._mode &= ~OBJMODE_OBJSTATUS;
		}
		break;
	default:
		break;
	}
}

void LogicManager::endChangeRoom() {
	//	Specific management of magnetic fields
	if ((_vm->_curRoom == kRoom2E) && (_vm->_obj[oPULSANTEADS2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG2E]._flag |= SMKANIM_OFF1;
		_vm->_obj[oCAMPO2E]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOA2E]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOS2E]._mode |= OBJMODE_OBJSTATUS;
	} else if ((_vm->_curRoom == kRoom2E) && (_vm->_obj[oPULSANTEADA2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG2E]._flag &= ~SMKANIM_OFF1;
		_vm->_obj[oCAMPO2E]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOA2E]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOS2E]._mode &= ~OBJMODE_OBJSTATUS;
	}

	if ((_vm->_curRoom == kRoom2C) && (_vm->_obj[oPULSANTEACS2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG2C]._flag |= SMKANIM_OFF1;
		_vm->_obj[oCAMPO2C]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOA2C]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOS2C]._mode |= OBJMODE_OBJSTATUS;
	} else if ((_vm->_curRoom == kRoom2C) && (_vm->_obj[oPULSANTEACA2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG2C]._flag &= ~SMKANIM_OFF1;
		_vm->_obj[oCAMPO2C]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOS2C]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOA2C]._mode |= OBJMODE_OBJSTATUS;
	}

	if ((_vm->_curRoom == kRoom28) && (_vm->_obj[oPULSANTEBBS2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG28]._flag |= SMKANIM_OFF2;
		_vm->_obj[oCESPUGLIO28]._anim = a283;
		_vm->_obj[oSERPENTETM28]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oSERPENTEAM28]._mode |= OBJMODE_OBJSTATUS;
		RegenRoom();
	} else if ((_vm->_curRoom == kRoom28) && (_vm->_obj[oPULSANTEBBA2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG28]._flag &= ~SMKANIM_OFF2;
		_vm->_obj[oCESPUGLIO28]._anim = a282;
		_vm->_obj[oSERPENTETM28]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oSERPENTEAM28]._mode &= ~OBJMODE_OBJSTATUS;
		RegenRoom();
	}

	if ((_vm->_curRoom == kRoom28) && (_vm->_obj[oPULSANTEABS2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG28]._flag |= (SMKANIM_OFF1 | SMKANIM_OFF3);
		_vm->_obj[oCAMPO28]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOA28]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOS28]._mode |= OBJMODE_OBJSTATUS;
		read3D("282.3d");
	} else if ((_vm->_curRoom == kRoom28) && (_vm->_obj[oPULSANTEABA2D]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_animMgr->_animTab[aBKG28]._flag &= ~(SMKANIM_OFF1 | SMKANIM_OFF3);
		_vm->_obj[oCAMPO28]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOA28]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oCARTELLOS28]._mode &= ~OBJMODE_OBJSTATUS;
	}
	// End of specific management for the magnetic fields

	// Actions
	if ((_vm->_curRoom == kRoom12) && ((_vm->_oldRoom == kRoom13) || (_vm->_oldRoom == kRoom16)))
		StartCharacterAction(a1213ARRIVACONASCENSORE, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom16) && ((_vm->_oldRoom == kRoom13) || (_vm->_oldRoom == kRoom12)))
		StartCharacterAction(a1617SCENDECONASCENSORE, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom13) && (_vm->_oldRoom == kRoom12))
		StartCharacterAction(a1315ARRIVAASCENSOREALTOENTRA, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom13) && (_vm->_oldRoom == kRoom16))
		StartCharacterAction(a1314ARRIVAASCENSOREDABASSO, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom14) && (_vm->_oldRoom == kRoom13))
		StartCharacterAction(a1414ENTERROOM, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom18) && (_vm->_oldRoom == kRoom17) && !(_vm->_room[kRoom18]._flag & kObjFlagDone))
		StartCharacterAction(a186GUARDAPIAZZA, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom18) && (_vm->_oldRoom == kRoom19))
		StartCharacterAction(a189ENTRADALCLUB, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom1A) && (_vm->_oldRoom == kRoom18) && (_vm->_room[kRoom1A]._flag & kObjFlagDone)) {
		StartCharacterAction(a1A5ENTRA, 0, 0, 0);
		_vm->_animMgr->_animTab[aBKG1A]._flag |= SMKANIM_OFF1;
	} else if ((_vm->_curRoom == kRoom1C) && (_vm->_oldRoom == kRoom1B))
		StartCharacterAction(a1C1ENTRACUNICOLO, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom1B) && (_vm->_oldRoom == kRoom1C))
		StartCharacterAction(a1B11ESCETOMBINO, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom1D) && (_vm->_oldRoom == kRoom1B) && (_vm->_obj[oDONNA1D]._mode & OBJMODE_OBJSTATUS)) {
		StartCharacterAction(a1D1SCENDESCALE, 0, 1, 0);
		_vm->_actor->_lim[0] = 60;
		_vm->_actor->_lim[2] = 240;
	} else if ((_vm->_curRoom == kRoom1D) && (_vm->_oldRoom == kRoom1B) && !(_vm->_obj[oDONNA1D]._mode & OBJMODE_OBJSTATUS)) {
		StartCharacterAction(a1D12SCENDESCALA, 0, 1, 0);
		_vm->_actor->_lim[0] = 60;
		_vm->_actor->_lim[2] = 240;
	} else if ((_vm->_curRoom == kRoom1B) && (_vm->_oldRoom == kRoom1D))
		StartCharacterAction(a1B4ESCEBOTOLA, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom1B) && (_vm->_oldRoom == kRoom18) && (_vm->_animMgr->_animTab[aBKG1B]._flag & SMKANIM_OFF1))
		StartCharacterAction(a1B12SCAPPATOPO, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom24) && (_vm->_oldRoom == kRoom2H))
		StartCharacterAction(a242, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom25) && (_vm->_oldRoom == kRoom2A))
		StartCharacterAction(a257, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom28) && (_vm->_oldRoom == kRoom27))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom29) && (_vm->_oldRoom == kRoom2A))
		StartCharacterAction(a298ESCEBOTOLA, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom29L) && (_vm->_oldRoom == kRoom2A))
		StartCharacterAction(a2910ESCEBOTOLA, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom2A) && (_vm->_oldRoom == kRoom25))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom2A) && ((_vm->_oldRoom == kRoom29) || (_vm->_oldRoom == kRoom29L)))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom2B) && (_vm->_oldRoom == kRoom2A))
		StartCharacterAction(a2B2ESCEPOZZO, 0, 2, 0);
	else if ((_vm->_curRoom == kRoom2H) && (_vm->_oldRoom == kRoom24))
		StartCharacterAction(a2H1ARRIVA, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom2E) && (_vm->_oldRoom == kRoom2F))
		StartCharacterAction(a2E5SECONDAPARRIVANDO, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom2F) && (_vm->_oldRoom == kRoom2E))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom23B) && (_vm->_oldRoom == kRoom21))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom23A) && (_vm->_oldRoom == kRoom21) && (_vm->_room[kRoom23A]._flag & kObjFlagDone))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom23A) && (_vm->_oldRoom == kRoom21) && (!(_vm->_room[kRoom23A]._flag & kObjFlagDone)))
		_vm->_flagShowCharacter = false;
	else if ((_vm->_curRoom == kRoom21) && ((_vm->_oldRoom == kRoom23A) || (_vm->_oldRoom == kRoom23B)))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if (_vm->isCloseupOrControlRoom()) { // Screens without inventory
		_vm->_flagShowCharacter = false;
		_vm->_flagCharacterExists = false;
		_vm->_flagInventoryLocked = true;
	} else if ((_vm->_curRoom == kRoom31P) || (_vm->_curRoom == kRoom35P)) { // Screens with inventory
		_vm->_flagShowCharacter = false;
		_vm->_flagCharacterExists = false;
	} else if ((_vm->_curRoom == kRoom2F) && (_vm->_oldRoom == kRoom31))
		StartCharacterAction(a2F4ESCEASCENSORE, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom31) && (_vm->_oldRoom == kRoom2F))
		StartCharacterAction(a3114ESCEPASSAGGIO, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom31) && !(_vm->_room[kRoom31]._flag & kObjFlagDone))
		setPosition(14);
	else if ((_vm->_curRoom == kRoom32) && (_vm->_oldRoom == kRoom31))
		StartCharacterAction(a321SALEMONTACARICHI, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom33) && (_vm->_oldRoom == kRoom32) && (_vm->_obj[oBRUCIATURA33]._mode & OBJMODE_OBJSTATUS))
		StartCharacterAction(a3311SALESCALE, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom33) && (_vm->_oldRoom == kRoom32) && !(_vm->_obj[oBRUCIATURA33]._mode & OBJMODE_OBJSTATUS))
		StartCharacterAction(a3313CHIUDEBOTOLA, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom32) && (_vm->_oldRoom == kRoom33))
		StartCharacterAction(a325SCENDESCALE, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom36) && (_vm->_oldRoom == kRoom35))
		StartCharacterAction(a361ESCEASCENSORE, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom35) && (_vm->_oldRoom == kRoom36))
		StartCharacterAction(a3515ESCEASCENSORE, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom44) && (_vm->_oldRoom == kRoom45 || _vm->_oldRoom == kRoom45S) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra))
		StartCharacterAction(a445, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom45 || _vm->_curRoom == kRoom45S) && (_vm->_oldRoom == kRoom44) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra))
		StartCharacterAction(a457, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom46) && (_vm->_oldRoom == kRoom47 || _vm->_oldRoom == kRoom48 || _vm->_oldRoom == kRoom49) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra))
		StartCharacterAction(aWALKIN, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom47) && (_vm->_oldRoom == kRoom46) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra))
		StartCharacterAction(a476, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom48) && (_vm->_oldRoom == kRoom46) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra))
		StartCharacterAction(a485, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom49) && (_vm->_oldRoom == kRoom46) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra))
		StartCharacterAction(a494, 0, 0, 0);
	else if ((_vm->_curRoom == kRoom54) && (_vm->_oldRoom == kRoom53)) {
		StartCharacterAction(a5411, 0, 11, 0);
		_vm->_inventoryObj[iLASER35]._examine = 1599;
	} else if ((_vm->_oldRoom == kRoom41D) && (_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra)) {
		setPosition(30);
		drawCharacter(CALCPOINTS);
	}

	// FullMotion
	if ((_vm->_curRoom == kRoom17) && (_vm->_oldRoom == kRoom16)) {
		_vm->_dialogMgr->playDialog(dF171);
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom16) && (_vm->_oldRoom == kRoom17)) {
		_vm->_dialogMgr->playDialog(dF161);
		_vm->_soundMgr->waitEndFading();
		_vm->removeIcon(iFOGLIO14);
	} else if ((_vm->_curRoom == kRoom21) && (_vm->_oldRoom == kRoom1C)) {
		_vm->_dialogMgr->playDialog(dF1C1);
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom23B) && (_vm->_oldRoom == kRoom23A)) {
		_vm->_dialogMgr->playDialog(dF231);
		_vm->_soundMgr->waitEndFading();
		_vm->removeIcon(iMAPPA17);
	} else if ((_vm->_curRoom == kRoom29L) && (_vm->_oldRoom == kRoom29)) {
		_vm->_dialogMgr->playDialog(dF291);
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom2GV) && (_vm->_oldRoom == kRoom2G)) {
		_vm->_dialogMgr->playDialog(dF2G2);
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom31) && (_vm->_oldRoom == kRoom32) && (_vm->_room[kRoom32]._flag & kObjFlagExtra)) {
		_vm->_dialogMgr->playDialog(dF321);
		_vm->_flagShowCharacter = false;
		_vm->_soundMgr->waitEndFading();
		_vm->_room[kRoom32]._flag &= ~kObjFlagExtra;
	} else if ((_vm->_curRoom == kRoom19) && !(_vm->_room[kRoom19]._flag & kObjFlagDone)) {
		_vm->playScript(s19EVA);
		_vm->_flagNoPaintScreen = false;
		_vm->clearText();
		_vm->redrawString();
		_vm->_soundMgr->waitEndFading();
	}
	// CHECKME: This check is identical to the 3rd one, thus it's always false
	else if ((_vm->_curRoom == kRoom21) && (/*!( _room[_vm->_curRoom]._flag & OBJFLAG_DONE ) || */ (_vm->_oldRoom == kRoom1C))) {
		setPosition(10);
		TendIn();
		_vm->_flagNoPaintScreen = false;
		_vm->clearText();
		_vm->redrawString();
	} else if ((_vm->_curRoom == kRoom46) && (_vm->_oldRoom == kRoom43) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra)) {
		_vm->_dialogMgr->playDialog(dF431);
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom45S) && (_vm->_oldRoom == kRoom45) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra)) {
		_vm->_dialogMgr->playDialog(dF451);
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom4A) && (_vm->_oldRoom == kRoom49) && !(_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra)) {
		_vm->_dialogMgr->playDialog(dF491);
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom4A) && (_vm->_oldRoom == kRoom41D) && (_vm->_inventoryObj[iDISLOCATORE]._flag & kObjFlagExtra) && (_vm->_obj[ocHELLEN4A]._mode & OBJMODE_OBJSTATUS)) {
		_vm->_soundMgr->waitEndFading();
		_vm->_dialogMgr->playDialog(dC4A1);
	} else if ((_vm->_curRoom == kRoom4P) && (_vm->_oldRoom == kRoom4O) && !(_vm->_room[kRoom4P]._flag & kObjFlagDone)) {
		_vm->_dialogMgr->playDialog(dF4PI);
		_vm->_flagShowCharacter = false;
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom51) && (_vm->_oldRoom == kRoom4CT)) {
		_vm->_dialogMgr->playDialog(dF4C1);
		_vm->_flagShowCharacter = false;
		_vm->_soundMgr->waitEndFading();
	} else if ((_vm->_curRoom == kRoom1A) && (_vm->_oldRoom == kRoom18)) {
		if (!(_vm->_room[kRoom1A]._flag & kObjFlagDone)) {
			_vm->_dialogMgr->playDialog(dF1A1);
			_vm->_soundMgr->waitEndFading();
			_vm->_obj[oTOPO1C]._flag |= kObjFlagTake;
			_vm->_obj[oTOPO1C]._anim = a1C3RACCOGLIETOPO;
		} else {
			TendIn();
			_vm->_flagNoPaintScreen = false;
			_vm->redrawString();
		}
	} else {
		TendIn();
		_vm->_flagNoPaintScreen = false;
		_vm->clearText();
		_vm->redrawString();
	}

	//	Sentence
	if ((_vm->_curRoom == kRoom17) && (_vm->_oldRoom == kRoom18) && !(_vm->_room[kRoom17]._flag & kObjFlagDone) && (_vm->_obj[oRETE17]._mode & OBJMODE_OBJSTATUS))
		CharacterSay(189);

	if (((_vm->_curRoom == kRoom12CU) || (_vm->_curRoom == kRoom13CU)) && _vm->_closeUpObj && _vm->_obj[_vm->_closeUpObj]._examine)
		CharacterSay(_vm->_obj[_vm->_closeUpObj]._examine);
	else if ((_vm->_curRoom == kRoom23A) && (_vm->_oldRoom == kRoom21) && !(_vm->_room[kRoom23A]._flag & kObjFlagDone)) {
		_vm->_flagShowCharacter = true;
		StartCharacterAction(aWALKIN, 0, 0, 361);
	} else if ((_vm->_curRoom == kRoom24) && !(_vm->_room[kRoom24]._flag & kObjFlagDone))
		CharacterSay(381);
	else if ((_vm->_curRoom == kRoom2G) && !(_vm->_room[kRoom2G]._flag & kObjFlagDone))
		CharacterSay(688);
	else if ((_vm->_curRoom == kRoom4C) && (_vm->_oldRoom == kRoom4CT))
		CharacterSay(1163);
	else if ((_vm->_curRoom == kRoom41) && (_vm->_oldRoom == kRoom36) && !(_vm->_room[kRoom41]._flag & kObjFlagDone))
		CharacterSay(900);
	else if ((_vm->_curRoom == kRoom58) && (_vm->_obj[oGUARDIA58]._mode & OBJMODE_OBJSTATUS) && (_vm->_obj[oGUARDIA58]._anim)) {
		_vm->_curObj = oGUARDIA58;
		doEvent(MC_MOUSE, ME_MRIGHT, MP_DEFAULT, 372, 335 + TOP, 0, oGUARDIA58);
	} else if ((_vm->_curRoom == kRoom59L))
		CharacterSay(1394);
	else if ((_vm->_curRoom == kRoom58) && (_vm->_oldRoom == kRoom58T))
		CharacterSay(1368);
	else if ((_vm->_curRoom == kRoom5A) && !(_vm->_room[kRoom5A]._flag & kObjFlagDone))
		CharacterSay(1408);
	else if ((_vm->_curRoom == kRoomControlPanel) && (_vm->_oldRoom == kRoomControlPanel))
		_vm->_logicMgr->DoSys(o00LOAD);
	_vm->_inventoryObj[iDISLOCATORE]._flag &= ~kObjFlagExtra;
}

void LogicManager::initInventory() {
	_vm->_inventorySize = 0;
	_vm->_inventory[_vm->_inventorySize++] = iBANCONOTE;
	_vm->_inventory[_vm->_inventorySize++] = iSAM;
	_vm->_inventory[_vm->_inventorySize++] = iCARD03;
	_vm->_inventory[_vm->_inventorySize++] = iPEN;
	_vm->_inventory[_vm->_inventorySize++] = iKEY05;
}

void LogicManager::useInventoryWithInventory(bool *updateInventory, bool *printSentence) {
	*updateInventory = true;
	*printSentence = true;

	switch (_vm->_useWith[USED]) {
	case iSTAGNOLA:
		if (_vm->_useWith[WITH] == iFUSE) {
			_vm->removeIcon(iSTAGNOLA);
			_vm->replaceIcon(iFUSE, iFUSES);
			StartCharacterAction(hUSEGG, 0, 0, 1441);
			*printSentence = false;
		}
		break;

	case iFUSE:
		if (_vm->_useWith[WITH] == iSTAGNOLA) {
			_vm->removeIcon(iSTAGNOLA);
			_vm->replaceIcon(iFUSE, iFUSES);
			StartCharacterAction(hUSEGG, 0, 0, 1441);
			*printSentence = false;
		}
		break;

	case iTOPO1C:
		if (_vm->_useWith[WITH] == iSKATE) {
			_vm->removeIcon(iSKATE);
			_vm->removeIcon(iTOPO1C);
			_vm->addIcon(iTOPO1D);
			StartCharacterAction(hUSEGG, 0, 0, 1497);
			*printSentence = false;
		}
		break;

	case iSKATE:
		if (_vm->_useWith[WITH] == iTOPO1C) {
			_vm->removeIcon(iSKATE);
			_vm->removeIcon(iTOPO1C);
			_vm->addIcon(iTOPO1D);
			StartCharacterAction(hUSEGG, 0, 0, 1497);
			*printSentence = false;
		}
		break;

	case iBAR11:
		if (_vm->_useWith[WITH] == iMAGNETE) {
			_vm->removeIcon(iBAR11);
			_vm->replaceIcon(iMAGNETE, iSBARRA21);
			StartCharacterAction(hUSEGG, 0, 0, 1438);
			*printSentence = false;
		}
		break;

	case iMAGNETE:
		if (_vm->_useWith[WITH] == iBAR11) {
			_vm->removeIcon(iBAR11);
			_vm->replaceIcon(iMAGNETE, iSBARRA21);
			StartCharacterAction(hUSEGG, 0, 0, 1533);
			*printSentence = false;
		}
		break;

	case iSIGARO:
		if (_vm->_useWith[WITH] == iSCOPA27) {
			_vm->removeIcon(iSCOPA27);
			_vm->replaceIcon(iSIGARO, iTORCIA32);
			StartCharacterAction(hUSEGG, 0, 0, 1575);
			*printSentence = false;
		}
		break;

	case iSCOPA27:
		if (_vm->_useWith[WITH] == iSIGARO) {
			_vm->removeIcon(iSCOPA27);
			_vm->replaceIcon(iSIGARO, iTORCIA32);
			StartCharacterAction(hUSEGG, 0, 0, 1546);
			*printSentence = false;
		}
		break;

	case iPROIETTORE31:
		if (_vm->_useWith[WITH] == iTRIPLA) {
			_vm->removeIcon(iTRIPLA);
			_vm->replaceIcon(iPROIETTORE31, iPROIETTORE35);
			StartCharacterAction(hUSEGG, 0, 0, 0);
			*printSentence = false;
		}
		break;

	case iTRIPLA:
		if (_vm->_useWith[WITH] == iPROIETTORE31) {
			_vm->removeIcon(iTRIPLA);
			_vm->replaceIcon(iPROIETTORE31, iPROIETTORE35);
			StartCharacterAction(hUSEGG, 0, 0, 0);
			*printSentence = false;
		}
		break;

	case iSALNITRO:
	case iCARBONE:
	case iZOLFO:
	case iCARSAL:
	case iCARZOL:
	case iSALZOL:
		if ((_vm->_useWith[WITH] == iSALNITRO) || (_vm->_useWith[WITH] == iCARBONE) || (_vm->_useWith[WITH] == iZOLFO) ||
			(_vm->_useWith[WITH] == iCARSAL) || (_vm->_useWith[WITH] == iCARZOL) || (_vm->_useWith[WITH] == iSALZOL)) {
			_vm->removeIcon(_vm->_useWith[USED]);
			_vm->removeIcon(_vm->_useWith[WITH]);

			if (((_vm->_useWith[USED] == iSALNITRO) && (_vm->_useWith[WITH] == iCARBONE)) ||
				((_vm->_useWith[WITH] == iSALNITRO) && (_vm->_useWith[USED] == iCARBONE)))
				_vm->addIcon(iCARSAL);
			if (((_vm->_useWith[USED] == iZOLFO) && (_vm->_useWith[WITH] == iCARBONE)) ||
				((_vm->_useWith[WITH] == iZOLFO) && (_vm->_useWith[USED] == iCARBONE)))
				_vm->addIcon(iCARZOL);
			if (((_vm->_useWith[USED] == iZOLFO) && (_vm->_useWith[WITH] == iSALNITRO)) ||
				((_vm->_useWith[WITH] == iZOLFO) && (_vm->_useWith[USED] == iSALNITRO)))
				_vm->addIcon(iSALZOL);

			if ((_vm->_useWith[USED] == iZOLFO) || (_vm->_useWith[WITH] == iZOLFO))
				_vm->addIcon(iBARATTOLO);
			if ((_vm->_useWith[USED] >= iCARSAL) || (_vm->_useWith[WITH] >= iCARSAL))
				_vm->addIcon(iPOLVERE48);
			StartCharacterAction(hUSEGG, 0, 0, 1663);
			*printSentence = false;
		}
		break;

	case iPISTOLA4B:
		if (_vm->_useWith[WITH] == iPOLVERE48) {
			_vm->replaceIcon(iPOLVERE48, iPOLVERE4P);
			_vm->replaceIcon(iPISTOLA4B, iPISTOLA4PC);
			StartCharacterAction(hUSEGG, 0, 0, 1676);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == iPOLVERE4P) {
			_vm->removeIcon(iPOLVERE4P);
			_vm->replaceIcon(iPISTOLA4B, iPISTOLA4PC);
			StartCharacterAction(hUSEGG, 0, 0, 1700);
			*printSentence = false;
		}
		break;

	case iPOLVERE48:
		if (_vm->_useWith[WITH] == iPISTOLA4B) {
			_vm->replaceIcon(iPOLVERE48, iPOLVERE4P);
			_vm->replaceIcon(iPISTOLA4B, iPISTOLA4PC);
			StartCharacterAction(hUSEGG, 0, 0, 1676);
			*printSentence = false;
		}
		break;

	case iPOLVERE4P:
		if (_vm->_useWith[WITH] == iPISTOLA4B) {
			_vm->removeIcon(iPOLVERE4P);
			_vm->replaceIcon(iPISTOLA4B, iPISTOLA4PC);
			StartCharacterAction(hUSEGG, 0, 0, 1700);
			*printSentence = false;
		}
		break;

	case iBIGLIAA:
	case iBIGLIAB:
		if ((_vm->_useWith[WITH] == iPISTOLA4PC) && !(_vm->_inventoryObj[iPISTOLA4PC]._flag & kObjFlagExtra)) {
			_vm->removeIcon(_vm->_useWith[USED]);
			_vm->replaceIcon(iPISTOLA4PC, iPISTOLA4PD);
			StartCharacterAction(hUSEGG, 0, 0, 1683);
			_vm->_inventoryObj[iPISTOLA4PC]._flag |= kObjFlagExtra;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == iPISTOLA4PC) {
			CharacterSay(1688);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == iPISTOLA4B) {
			CharacterSay(2009);
			*printSentence = false;
		}
		break;

	case iBIGLIA4U:
		if (_vm->_useWith[WITH] == iPISTOLA4PC) {
			_vm->removeIcon(iBIGLIA4U);
			_vm->replaceIcon(iPISTOLA4PC, iPISTOLA4PD);
			StartCharacterAction(hUSEGG, 0, 0, 1718);
			_vm->_inventoryObj[iPISTOLA4PD]._flag |= kObjFlagExtra;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == iPISTOLA4B) {
			CharacterSay(2011);
			*printSentence = false;
		}
		break;

	case iSIRINGA37:
		if (_vm->_useWith[WITH] == iFIALE) {
			_vm->removeIcon(iSIRINGA37);
			_vm->replaceIcon(iFIALE, iSIRINGA59);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		}
		break;

	case iFIALE:
		if (_vm->_useWith[WITH] == iSIRINGA37) {
			_vm->removeIcon(iSIRINGA37);
			_vm->replaceIcon(iFIALE, iSIRINGA59);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		}
		break;

	case iFILO:
		if (_vm->_useWith[WITH] == iGUANTI57) {
			_vm->removeIcon(iFILO);
			_vm->replaceIcon(iGUANTI57, iGUANTI5A);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == iSIRINGA59) {
			_vm->removeIcon(iFILO);
			_vm->replaceIcon(iSIRINGA59, iSIRINGA5A);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		}
		break;

	case iGUANTI57:
		if (_vm->_useWith[WITH] == iFILO) {
			_vm->removeIcon(iFILO);
			_vm->replaceIcon(iGUANTI57, iGUANTI5A);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == iSIRINGA5A) {
			_vm->removeIcon(iSIRINGA5A);
			_vm->replaceIcon(iGUANTI57, iARMAEVA);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		}
		break;

	case iSIRINGA59:
		if (_vm->_useWith[WITH] == iFILO) {
			_vm->removeIcon(iFILO);
			_vm->replaceIcon(iSIRINGA59, iSIRINGA5A);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == iGUANTI5A) {
			_vm->removeIcon(iSIRINGA59);
			_vm->replaceIcon(iGUANTI5A, iARMAEVA);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		}
		break;

	case iGUANTI5A:
		if (_vm->_useWith[WITH] == iSIRINGA59) {
			_vm->removeIcon(iSIRINGA59);
			_vm->replaceIcon(iGUANTI5A, iARMAEVA);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		}
		break;

	case iSIRINGA5A:
		if (_vm->_useWith[WITH] == iGUANTI57) {
			_vm->removeIcon(iSIRINGA5A);
			_vm->replaceIcon(iGUANTI57, iARMAEVA);
			StartCharacterAction(hUSEGG, 0, 0, 1756);
			*printSentence = false;
		}
		break;

	default:
		*updateInventory = false;
		break;
	}
}

void LogicManager::useInventoryWithScreen(bool *updateInventory, bool *printSentence) {
	*updateInventory = true;
	*printSentence = true;

	switch (_vm->_useWith[USED]) {
	case iBANCONOTE:
		if (_vm->_useWith[WITH] == oDISTRIBUTORE13 && !(_vm->_obj[oDISTRIBUTORE13]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a131USABANCONOTA, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
			_vm->_obj[oDISTRIBUTORE13]._flag |= kObjFlagExtra;
		} else if ((_vm->_useWith[WITH] == oDISTRIBUTORE13) && (_vm->_obj[oDISTRIBUTORE13]._flag & kObjFlagExtra) && (_vm->_obj[oLATTINA13]._mode & OBJMODE_OBJSTATUS)) {
			CharacterSay(1410);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oDISTRIBUTORE13) && (_vm->_obj[oDISTRIBUTORE13]._flag & kObjFlagExtra)) {
			if (!(_vm->_obj[oSCOMPARTO13]._flag & kObjFlagExtra)) {
				_vm->_obj[oSCOMPARTO13]._flag |= kObjFlagExtra;
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1311DABOTTADISTRIBUTORE, 0, 0, _vm->_useWith[WITH]);
			} else
				CharacterSay(1411);

			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oTICKETOFFICE16) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a165USABANCONOTA, 0, 0, _vm->_useWith[WITH]);
			_vm->_inventoryObj[iBANCONOTE]._flag |= kObjFlagExtra;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == ocPOLIZIOTTO16) && (_vm->_inventoryObj[iBANCONOTE]._flag & kObjFlagExtra)) {
			_vm->_dialogMgr->_choice[62]._flag &= ~DLGCHOICE_HIDE;
			_vm->_dialogMgr->playDialog(dPOLIZIOTTO16);
			*printSentence = false;
		}
		break;
	case iLETTER12:
		if (_vm->_useWith[WITH] == oPENPADA13) {
			if (_vm->_room[kRoom14]._flag & kObjFlagDone)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1312METTELETTERARICALCA, kRoom14, 14, _vm->_useWith[WITH]);
			else {
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a135METTELETTERA, 0, 0, _vm->_useWith[WITH]);
				_vm->_obj[oLETTERA13]._mode |= OBJMODE_OBJSTATUS;
				_vm->_inventoryObj[iLETTER12]._flag |= kObjFlagExtra;
				_vm->removeIcon(iLETTER12);
				RegenRoom();
			}
			*printSentence = false;
		}
		break;
	case iFUSES:
		if (_vm->_useWith[WITH] == oPANELA12) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a127USEWRAPPEDFUSED, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;
	case iFUSE:
		if (_vm->_useWith[WITH] == oPANELA12) {
			CharacterSay(62);
			*printSentence = false;
		}
		break;
	case iKEY05:
		if (_vm->_useWith[WITH] == oBOXES12) {
			if (!(_vm->_obj[oBOXES12]._flag & kObjFlagExtra)) {
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a121BOXTEST, 0, 0, _vm->_useWith[WITH]);
				_vm->_obj[oBOXES12]._flag |= kObjFlagExtra;
				*printSentence = false;
			} else {
				CharacterSay(1426);
				*printSentence = false;
			}
		} else if (_vm->_useWith[WITH] == oBOX12 && !(_vm->_inventoryObj[iLETTER12]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a122APREBOX, 0, 0, oBOX12);
			_vm->_inventoryObj[iLETTER12]._flag |= kObjFlagExtra;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oBOX12) && (_vm->_inventoryObj[iLETTER12]._flag & kObjFlagExtra)) {
			CharacterSay(1429);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oCARA11) || (_vm->_useWith[WITH] == oCARB11) || (_vm->_useWith[WITH] == oTAKE12) || (_vm->_useWith[WITH] == oSTRONGBOXC15) || (_vm->_useWith[WITH] == oDOOR18) || (_vm->_useWith[WITH] == oPADLOCK1B) || (_vm->_useWith[WITH] == oDOORC21) || (_vm->_useWith[WITH] == oPANELC23) || (_vm->_useWith[WITH] == oDOOR2A) || (_vm->_useWith[WITH] == oDOORC33) || (_vm->_useWith[WITH] == oFRONTOFFICEC35) || (_vm->_useWith[WITH] == oCASSETTOC36) || (_vm->_useWith[WITH] == oDOORC54) || (_vm->_useWith[WITH] == oDOOR57C55) || (_vm->_useWith[WITH] == oDOOR58C55) || (_vm->_useWith[WITH] == oDOORS56) || (_vm->_useWith[WITH] == oDOORS57)) {
			*printSentence = false;
			CharacterSay(1426);
		}
		break;
	case iCARD03:
		if (_vm->_useWith[WITH] == oSLOT12 || _vm->_useWith[WITH] == oSLOT13 || _vm->_useWith[WITH] == oSLOT16) {
			*printSentence = false;
			_vm->_inventoryObj[iCARD03]._flag |= kObjFlagExtra;
			_vm->_obj[oSLOT12]._flag |= kObjFlagPerson;
			_vm->_obj[oLIFTA12]._flag |= kObjFlagPerson;
			doMouseTalk(_vm->_useWith[WITH]);
		} else if ((_vm->_useWith[WITH] == oTICKETOFFICE16) || (_vm->_useWith[WITH] == oSLOT23) || (_vm->_useWith[WITH] == oFRONTOFFICEA35) || (_vm->_useWith[WITH] == oSLOTA58) || (_vm->_useWith[WITH] == oSLOTB58)) {
			*printSentence = false;
			CharacterSay(1419);
		}
		break;
	case iPEN:
		*printSentence = false;
		if (((_vm->_useWith[WITH] == oPENPADA13) || (_vm->_useWith[WITH] == oLETTERA13)) && (_vm->_obj[oLETTERA13]._mode & OBJMODE_OBJSTATUS))
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a137RICALCAFIRMA, kRoom14, 14, _vm->_useWith[WITH]);
		else if ((_vm->_useWith[WITH] == oPENPADA13) && (_vm->_room[kRoom14]._flag & kObjFlagDone))
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1312METTELETTERARICALCA, kRoom14, 14, _vm->_useWith[WITH]);
		else if (_vm->_useWith[WITH] == oPENPADA13) {
			if (!(_vm->_obj[oBOX12]._mode & OBJMODE_OBJSTATUS)) {
				*printSentence = false;
				CharacterSay(2005);
			} else
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a134USAMAGNETICPEN, 0, 0, _vm->_useWith[WITH]);
		} else
			*printSentence = true;
		break;

	case iACIDO15:
		if (_vm->_useWith[WITH] == oBAR11) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, kAnim113UseVial, 0, 0, _vm->_useWith[WITH]);
			_vm->replaceIcon(iACIDO15, iFIALAMETA);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oPADLOCK1B) {
			if (_vm->_obj[oTOMBINOA1B]._mode & OBJMODE_OBJSTATUS)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B2AVERSAACIDO, 0, 0, _vm->_useWith[WITH]);
			else
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B2VERSAACIDO, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oBOTOLAC1B]._anim = a1B3APREBOTOLA;
			_vm->replaceIcon(iACIDO15, iFIALAMETA);
			_vm->_animMgr->_animTab[kAnim113UseVial]._atFrame[0]._index = 1483;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == ocGUARD18) || (_vm->_useWith[WITH] == oMANHOLEC1B)) {
			*printSentence = false;
			CharacterSay(1476);
		}
		break;

	case iFIALAMETA:
		if (_vm->_useWith[WITH] == oBAR11) {
			_vm->_animMgr->_animTab[kAnim113UseVial]._atFrame[0]._index = 1483;
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, kAnim113UseVial, 0, 0, _vm->_useWith[WITH]);
			_vm->removeIcon(iFIALAMETA);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oPADLOCK1B) {
			_vm->_animMgr->_animTab[a1B2AVERSAACIDO]._atFrame[2]._index = 1483;
			_vm->_animMgr->_animTab[a1B2VERSAACIDO]._atFrame[2]._index = 1483;
			if (_vm->_obj[oTOMBINOA1B]._mode & OBJMODE_OBJSTATUS)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B2AVERSAACIDO, 0, 0, _vm->_useWith[WITH]);
			else
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B2VERSAACIDO, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oBOTOLAC1B]._anim = a1B3APREBOTOLA;
			_vm->removeIcon(iFIALAMETA);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oDOOR2A) || (_vm->_useWith[WITH] == oDOOR2B)) {
			*printSentence = false;
			CharacterSay(1508);
		}
		break;

	case iKEY15:
		if (_vm->_useWith[WITH] == oSTRONGBOXC15) {
			_vm->_dialogMgr->playDialog(dF151);
			_vm->_obj[oSTRONGBOXC15]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCASSAFORTEA15]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oSLOT13]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oASCENSOREA13]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oASCENSOREC13]._mode |= OBJMODE_OBJSTATUS;
			_vm->addIcon(iPISTOLA15);
			_vm->addIcon(iACIDO15);
			_vm->addIcon(iRAPPORTO);
			_vm->removeIcon(iKEY15);
			*printSentence = false;
			*updateInventory = false;
		} else if ((_vm->_useWith[WITH] == oCARA11) || (_vm->_useWith[WITH] == oCARB11) || (_vm->_useWith[WITH] == oTAKE12) || (_vm->_useWith[WITH] == oBOX12) || (_vm->_useWith[WITH] == oDOOR18) || (_vm->_useWith[WITH] == oPADLOCK1B) || (_vm->_useWith[WITH] == oDOORC21) || (_vm->_useWith[WITH] == oPANELC23) || (_vm->_useWith[WITH] == oDOOR2A) || (_vm->_useWith[WITH] == oDOORC33) || (_vm->_useWith[WITH] == oFRONTOFFICEC35) || (_vm->_useWith[WITH] == oCASSETTOC36) || (_vm->_useWith[WITH] == oDOORC54) || (_vm->_useWith[WITH] == oDOOR57C55) || (_vm->_useWith[WITH] == oDOOR58C55) || (_vm->_useWith[WITH] == oDOORS56) || (_vm->_useWith[WITH] == oDOORS57)) {
			*printSentence = false;
			CharacterSay(1469);
		}
		break;

	case iBAR11:
		if (_vm->_useWith[WITH] == oMANHOLEC1B) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B1USASBARRA, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oBOTOLAA1B]._anim = a1B6ASCENDEBOTOLA;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oCATENAT21) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a216, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oALTOPARLANTE25) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a251, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oDOORC33) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a333LOSEBAR, 0, 0, _vm->_useWith[WITH]);
			_vm->removeIcon(iBAR11);
			*printSentence = false;
		} else if (_vm->_obj[_vm->_useWith[WITH]]._flag & kObjFlagPerson) {
			CharacterSay(1436);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oTAKE12) || (_vm->_useWith[WITH] == oSTRONGBOXC15) || (_vm->_useWith[WITH] == oDOOR18) || (_vm->_useWith[WITH] == oPADLOCK1B) || (_vm->_useWith[WITH] == oDOORC21) || (_vm->_useWith[WITH] == oPANELC23) || (_vm->_useWith[WITH] == oDOOR2A) || (_vm->_useWith[WITH] == oDOOR2B)) {
			*printSentence = false;
			CharacterSay(1435);
		}
		break;

	case iCARD14:
		if ((_vm->_useWith[WITH] == oTICKETOFFICE16) && (_vm->_obj[oMAPPA16]._flag & kObjFlagExtra)) {
			if (_vm->_dialogMgr->_choice[49]._flag & kObjFlagDone) {
				CharacterSay(1457);
				*printSentence = false;
			} else {
				_vm->_dialogMgr->_choice[46]._flag |= DLGCHOICE_HIDE;
				_vm->_dialogMgr->_choice[47]._flag |= DLGCHOICE_HIDE;
				_vm->_dialogMgr->_choice[48]._flag |= DLGCHOICE_HIDE;
				_vm->_dialogMgr->_choice[49]._flag &= ~DLGCHOICE_HIDE;
				_vm->playScript(s16CARD);
				*printSentence = false;
			}
		} else if (_vm->_useWith[WITH] == oSLOT23) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2311, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSLOT12) || (_vm->_useWith[WITH] == oSLOT13) || (_vm->_useWith[WITH] == oSLOT16) || (_vm->_useWith[WITH] == oFRONTOFFICEA35) || (_vm->_useWith[WITH] == oSLOTA58) || (_vm->_useWith[WITH] == oSLOTB58)) {
			*printSentence = false;
			CharacterSay(1419);
		}
		break;

	case iMONETA13:
		if ((_vm->_useWith[WITH] == oTICKETOFFICE16) && (_vm->_obj[oMAPPA16]._flag & kObjFlagExtra)) {
			_vm->_dialogMgr->_choice[46]._flag |= DLGCHOICE_HIDE;
			_vm->_dialogMgr->_choice[47]._flag |= DLGCHOICE_HIDE;
			_vm->_dialogMgr->_choice[48]._flag |= DLGCHOICE_HIDE;
			_vm->_dialogMgr->_choice[50]._flag &= ~DLGCHOICE_HIDE;
			_vm->playScript(S16MONEY);
			*printSentence = false;
			_vm->removeIcon(iMONETA13);
			_vm->_obj[oFINGERPADP16]._flag |= kObjFlagRoomOut;
		} else if (_vm->_useWith[WITH] == oTICKETOFFICE16) {
			CharacterSay(146);
			*printSentence = false;
		}
		break;

	case iPLASTICA:
		if (_vm->_useWith[WITH] == oTELEFAXF17) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a172USAPLASTICA, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oTELEFAXF17]._examine = 1486;
			*printSentence = false;
		}
		break;

	case iFOTO:
		if ((_vm->_useWith[WITH] == ocTRAMP17) && (_vm->_dialogMgr->_choice[81]._flag & kObjFlagDone)) {
			CharacterSay(1463);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == ocTRAMP17) && (_vm->_dialogMgr->_choice[91]._flag & kObjFlagDone)) {
			_vm->_obj[ocTRAMP17]._action = 1462;
			CharacterSay(_vm->_obj[ocTRAMP17]._action);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == ocTRAMP17) && (!(_vm->_dialogMgr->_choice[78]._flag & kObjFlagDone) || ((_vm->_dialogMgr->_choice[79]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[83]._flag & kObjFlagDone) && !(_vm->_dialogMgr->_choice[92]._flag & kObjFlagDone)))) {
			_vm->_dialogMgr->_choice[78]._flag &= ~DLGCHOICE_HIDE;
			if ((_vm->_dialogMgr->_choice[79]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[83]._flag & kObjFlagDone)) {
				_vm->_dialogMgr->_choice[92]._flag &= ~DLGCHOICE_HIDE;
				if (_vm->_dialogMgr->_choice[80]._flag & kObjFlagDone)
					_vm->_dialogMgr->_choice[121]._flag &= ~DLGCHOICE_HIDE;
				else
					_vm->_dialogMgr->_choice[122]._flag &= ~DLGCHOICE_HIDE;
			} else
				_vm->_dialogMgr->_choice[91]._flag &= ~DLGCHOICE_HIDE;
			_vm->_dialogMgr->playDialog(dTRAMP171);
			*updateInventory = false;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == ocPOLIZIOTTO16) {
			_vm->_obj[ocPOLIZIOTTO16]._flag |= kObjFlagExtra;
			CharacterSay(1461);
			if ((_vm->_dialogMgr->_choice[61]._flag & kObjFlagDone) && (_vm->_dialogMgr->_choice[62]._flag & kObjFlagDone) && (_vm->_obj[ocPOLIZIOTTO16]._flag & kObjFlagExtra))
				_vm->_obj[ocPOLIZIOTTO16]._mode &= ~OBJMODE_OBJSTATUS;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == ocGUARD18) {
			if (_vm->_dialogMgr->_choice[152]._flag & kObjFlagDone)
				CharacterSay(1465);
			else
				CharacterSay(1464);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == ocNEGOZIANTE1A) {
			CharacterSay(1466);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == ocEVA19) {
			CharacterSay(1465);
			*printSentence = false;
		}

		break;

	case iLATTINA13:
		if (_vm->_useWith[WITH] == ocTRAMP17) {
			if ((_vm->_dialogMgr->_choice[79]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[83]._flag & kObjFlagDone)) {
				_vm->_dialogMgr->_choice[80]._flag &= ~DLGCHOICE_HIDE;
				if (_vm->_dialogMgr->_choice[81]._flag & kObjFlagDone) {
					_vm->_dialogMgr->_choice[81]._flag &= ~DLGCHOICE_HIDE;
					_vm->_dialogMgr->_choice[80]._flag &= ~DLGCHOICE_EXITDLG;
				}
				_vm->_dialogMgr->playDialog(dTRAMP171);
				*updateInventory = false;
				_vm->removeIcon(iLATTINA13);
				*printSentence = false;
			} else { // if( !(_vm->_dialogMgr->_choice[79]._flag & OBJFLAG_DONE) )
				_vm->_dialogMgr->_choice[79]._flag &= ~DLGCHOICE_HIDE;
				if (!(_vm->_dialogMgr->_choice[78]._flag & kObjFlagDone)) {
					_vm->_dialogMgr->_choice[106]._flag &= ~DLGCHOICE_HIDE;
					_vm->_obj[ocTRAMP17]._action = 213;
				} else {
					_vm->_dialogMgr->_choice[107]._flag &= ~DLGCHOICE_HIDE;
					if (_vm->_dialogMgr->_choice[80]._flag & kObjFlagDone)
						_vm->_dialogMgr->_choice[121]._flag &= ~DLGCHOICE_HIDE;
					else
						_vm->_dialogMgr->_choice[122]._flag &= ~DLGCHOICE_HIDE;
				}
				_vm->_dialogMgr->playDialog(dTRAMP171);
				*updateInventory = false;
				_vm->removeIcon(iLATTINA13);
				*printSentence = false;
			}
		}

		break;

	case iBOTTIGLIA14:
		if (_vm->_useWith[WITH] == ocTRAMP17) {
			if ((_vm->_dialogMgr->_choice[79]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[83]._flag & kObjFlagDone)) {
				_vm->_dialogMgr->_choice[80]._flag &= ~DLGCHOICE_HIDE;
				if (_vm->_dialogMgr->_choice[81]._flag & kObjFlagDone) {
					_vm->_dialogMgr->_choice[81]._flag &= ~DLGCHOICE_HIDE;
					_vm->_dialogMgr->_choice[80]._flag &= ~DLGCHOICE_EXITDLG;
				}
				_vm->_dialogMgr->playDialog(dTRAMP171);
				*updateInventory = false;
				_vm->removeIcon(iBOTTIGLIA14);
				*printSentence = false;
			} else {
				_vm->_dialogMgr->_choice[83]._flag &= ~DLGCHOICE_HIDE;
				if (!(_vm->_dialogMgr->_choice[78]._flag & kObjFlagDone)) {
					_vm->_dialogMgr->_choice[106]._flag &= ~DLGCHOICE_HIDE;
					_vm->_obj[ocTRAMP17]._action = 213;
				} else {
					_vm->_dialogMgr->_choice[107]._flag &= ~DLGCHOICE_HIDE;
					if (_vm->_dialogMgr->_choice[80]._flag & kObjFlagDone)
						_vm->_dialogMgr->_choice[121]._flag &= ~DLGCHOICE_HIDE;
					else
						_vm->_dialogMgr->_choice[122]._flag &= ~DLGCHOICE_HIDE;
				}
				_vm->_dialogMgr->playDialog(dTRAMP171);
				*updateInventory = false;
				_vm->removeIcon(iBOTTIGLIA14);
				*printSentence = false;
			}
		}

		break;

	case iBOTTIGLIA1D:
		if (_vm->_useWith[WITH] == ocNEGOZIANTE1A) {
			*printSentence = false;
			if (_vm->_dialogMgr->_choice[183]._flag & kObjFlagDone) {
				_vm->_dialogMgr->_choice[185]._flag &= ~DLGCHOICE_HIDE;
				_vm->_dialogMgr->_dialog[dSHOPKEEPER1A]._startLen = 0;
				_vm->_dialogMgr->playDialog(dSHOPKEEPER1A);
				*updateInventory = false;
				_vm->_dialogMgr->_dialog[dSHOPKEEPER1A]._startLen = 1;
				_vm->replaceIcon(iBOTTIGLIA1D, iTESSERA);
			} else
				CharacterSay(2006);
		}
		break;

	case iTESSERA:
		if ((_vm->_useWith[WITH] == ocGUARD18) && !(_vm->_dialogMgr->_choice[155]._flag & kObjFlagDone)) {
			_vm->_dialogMgr->_choice[155]._flag &= ~DLGCHOICE_HIDE;
			_vm->_dialogMgr->playDialog(dGUARDIAN18);
			*updateInventory = false;
			_vm->_obj[ocGUARD18]._flag &= ~kObjFlagPerson;
			_vm->_obj[oDOORC18]._flag |= kObjFlagRoomOut;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == ocGUARD18) {
			CharacterSay(1494);
			*printSentence = false;
		}
		break;

	case iTOPO1D:
		if ((_vm->_useWith[WITH] == oDONNA1D) && (_vm->_mouseX >= _vm->_obj[oDONNA1D]._lim.left && (_vm->_mouseY >= _vm->_obj[oDONNA1D]._lim.top + TOP) && (_vm->_mouseX <= _vm->_obj[oDONNA1D]._lim.right) && (_vm->_mouseY <= _vm->_obj[oDONNA1D]._lim.bottom + TOP))) {
			_vm->_dialogMgr->playDialog(dF1D1);
			*updateInventory = false;
			_vm->removeIcon(iTOPO1D);
			read3D("1d2.3d"); // after skate
			_vm->_obj[oDONNA1D]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_room[_vm->_curRoom]._flag |= kObjFlagExtra;
			_vm->_animMgr->_animTab[aBKG1D]._flag |= SMKANIM_OFF1;
			*printSentence = false;
		}
		break;

	case iPISTOLA15:
		if ((_vm->_useWith[WITH] == oDOORC21) && !(_vm->_room[kRoom21]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a211, 0, 0, _vm->_useWith[WITH]);
			_vm->_inventoryObj[iPISTOLA15]._examine = 1472;
			_vm->_inventoryObj[iPISTOLA15]._action = 1473;
			*printSentence = false;
		}
		break;

	case iCACCIAVITE:
		if (_vm->_useWith[WITH] == oESSE21) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a213, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oCOPERCHIOC31) {
			_vm->_soundMgr->play(wCOVER31);
			_vm->_obj[oCOPERCHIOC31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCOPERCHIOA31]._mode |= OBJMODE_OBJSTATUS;
			RegenRoom();
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oCOPERCHIOA31) {
			_vm->_obj[oCOPERCHIOA31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCOPERCHIOC31]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOM31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOMA31]._mode |= OBJMODE_OBJSTATUS;
			if (_vm->_obj[oFILOTC31]._mode & OBJMODE_OBJSTATUS) {
				_vm->_obj[oPANNELLOM31]._anim = 0;
				_vm->_obj[oPANNELLOM31]._examine = 715;
				_vm->_obj[oPANNELLOM31]._action = 716;
				_vm->_obj[oPANNELLOM31]._flag &= ~kObjFlagRoomOut;
			}
			_vm->_soundMgr->play(wCOVER31);
			RegenRoom();
			*printSentence = false;
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom31, a3118CHIUDEPANNELLO, 3, _vm->_curObj);
		} else if (_vm->_useWith[WITH] == oPANNELLO55) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a5512, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oPANNELLOC56) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a568, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSLOT23) || (_vm->_useWith[WITH] == oPRESA35) || (_vm->_useWith[WITH] == oSERRATURA33)) {
			*printSentence = false;
			CharacterSay(1520);
		}
		break;

	case iESSE:
		if (_vm->_useWith[WITH] == oCATENA21) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a214, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iTANICHETTA27:
		if (_vm->_useWith[WITH] == oMANIGLIONE22) {
			if (_vm->_obj[oARMADIETTORC22]._mode & OBJMODE_OBJSTATUS)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a228, 0, 0, _vm->_useWith[WITH]);
			else
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a228A, 0, 0, _vm->_useWith[WITH]);
			_vm->removeIcon(iTANICHETTA27);
			_vm->addIcon(iTANICHETTA22);
			if (_vm->_inventoryObj[iLATTINA28]._flag & kObjFlagExtra) {
				_vm->removeIcon(iTANICHETTA22);
				_vm->replaceIcon(iLATTINA28, iLATTINE);
			}
			*printSentence = false;
		} else
			break;

	case iKEY22:
		if (_vm->_useWith[WITH] == oDOOR2A) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2A2USEKEY, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oPANELC23) || (_vm->_useWith[WITH] == oDOORC33) || (_vm->_useWith[WITH] == oFRONTOFFICEC35) || (_vm->_useWith[WITH] == oCASSETTOC36) || (_vm->_useWith[WITH] == oDOORC54) || (_vm->_useWith[WITH] == oDOOR57C55) || (_vm->_useWith[WITH] == oDOOR58C55) || (_vm->_useWith[WITH] == oDOORS56) || (_vm->_useWith[WITH] == oDOORS57)) {
			*printSentence = false;
			CharacterSay(1512);
		}
		break;

	case iLAMPADINA29:
		if ((_vm->_useWith[WITH] == oPORTALAMPADE2B) && !(_vm->_obj[_vm->_useWith[WITH]]._anim)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2B6METTELAMPADINA, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iPIPEWRENCH:
		if (_vm->_useWith[WITH] == oPANELC23) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a233, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oDOORC33) || (_vm->_useWith[WITH] == oFRONTOFFICEC35) || (_vm->_useWith[WITH] == oCASSETTOC36) || (_vm->_useWith[WITH] == oDOORC54) || (_vm->_useWith[WITH] == oDOOR57C55) || (_vm->_useWith[WITH] == oDOOR58C55) || (_vm->_useWith[WITH] == oDOORS56) || (_vm->_useWith[WITH] == oDOORS57)) {
			*printSentence = false;
			CharacterSay(1525);
		}
		break;

	case iCAVI:
		if ((_vm->_useWith[WITH] == oCONTATTI23) && (_vm->_obj[oLEVAS23]._mode & OBJMODE_OBJSTATUS)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a236, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oLEVAG23) {
			CharacterSay(2015);
			*printSentence = false;
		}
		break;

	case iTRONCHESE:
		if ((_vm->_useWith[WITH] == oCAVO2H) && (_vm->_obj[oCARTELLONE2H]._mode & OBJMODE_OBJSTATUS)) {
			_vm->_dialogMgr->playDialog(dF2H1);
			_vm->_obj[oPASSAGE24]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[omPASSAGGIO24]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oCARTELLONE24]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCARTELLONE2H]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oPASSERELLA24]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oMACERIE24]._mode &= ~OBJMODE_OBJSTATUS;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oTUBOT34) && (_vm->_obj[oVALVOLAC34]._mode & OBJMODE_OBJSTATUS)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a341USAPINZE, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oTUBOT34) && (_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS)) {
			CharacterSay(2007);
			*printSentence = false;
		} else
			*printSentence = true;
		break;

	case iLATTINA28:
		if ((_vm->_useWith[WITH] == oSERBATOIOA2G) && !(_vm->_inventoryObj[iLATTINA28]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2G4VERSALATTINA, 0, 0, _vm->_useWith[WITH]);
			_vm->_inventoryObj[iLATTINA28]._flag |= kObjFlagExtra;
			_vm->_inventoryObj[iLATTINA28]._examine = 1537;
			if (_vm->iconPos(iTANICHETTA22) != MAXICON) {
				_vm->removeIcon(iTANICHETTA22);
				_vm->replaceIcon(iLATTINA28, iLATTINE);
			}
			if ((_vm->_inventoryObj[iBOMBOLA]._flag & kObjFlagExtra) && (_vm->_inventoryObj[iLATTINA28]._flag & kObjFlagExtra)) {
				_vm->_obj[oSERBATOIOA2G]._examine = 670;
				_vm->_obj[oSERBATOIOA2G]._action = 671;
			} else {
				_vm->_obj[oSERBATOIOA2G]._examine = 667;
				_vm->_obj[oSERBATOIOA2G]._action = 669;
			}
			*printSentence = false;
		}
		break;

	case iBOMBOLA:
		if (_vm->_useWith[WITH] == oSERBATOIOA2G) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2G5METTEBOMBOLA, 0, 0, _vm->_useWith[WITH]);
			_vm->_inventoryObj[iBOMBOLA]._flag |= kObjFlagExtra;
			if ((_vm->_inventoryObj[iBOMBOLA]._flag & kObjFlagExtra) && (_vm->_inventoryObj[iLATTINA28]._flag & kObjFlagExtra)) {
				_vm->_obj[oSERBATOIOA2G]._examine = 670;
				_vm->_obj[oSERBATOIOA2G]._action = 671;
			} else {
				_vm->_obj[oSERBATOIOA2G]._examine = 668;
				_vm->_obj[oSERBATOIOA2G]._action = 669;
			}
			*printSentence = false;
		}
		break;

	case iCANDELOTTO:
		if ((_vm->_useWith[WITH] == oSERBATOIOA2G) && (_vm->_inventoryObj[iBOMBOLA]._flag & kObjFlagExtra) && (_vm->_inventoryObj[iLATTINA28]._flag & kObjFlagExtra)) {
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom2GV, 0, 0, _vm->_useWith[WITH]);
			_vm->removeIcon(iCANDELOTTO);
			*printSentence = false;
		}
		break;

	case iRIFLE:
		if (_vm->_useWith[WITH] == oDINOSAURO2E) {
			_vm->_dialogMgr->playDialog(dF2E2);
			_vm->_obj[oDINOSAURO2E]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCATWALKA2E]._anim = a2E2PRIMAPALLONTANANDO;
			_vm->_animMgr->_animTab[aBKG2E]._flag |= SMKANIM_OFF2;
			*printSentence = false;
		}
		break;

	case iPINZA:
	case iSBARRA21:
		if (_vm->_useWith[WITH] == oCATENAT21) {
			if (_vm->_room[_vm->_curRoom]._flag & kObjFlagExtra) {
				if (_vm->_useWith[USED] == iPINZA)
					_vm->_dialogMgr->playDialog(dF212B);
				else
					_vm->_dialogMgr->playDialog(dF212);
				*printSentence = false;
			} else {
				if (_vm->_useWith[USED] == iPINZA)
					_vm->_dialogMgr->playDialog(dF213B);
				else
					_vm->_dialogMgr->playDialog(dF213);
				*printSentence = false;
			}
		} else if ((_vm->_useWith[WITH] == oDOORC33) && (_vm->_useWith[USED] == iSBARRA21)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a333LOSEBAR, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSNAKEU52) && (_vm->_useWith[USED] == iPINZA)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a527, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oSCAVO51]._anim = a516;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSERPENTEA52) && (_vm->_useWith[USED] == iPINZA)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a528, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSERPENTEB52) && (_vm->_useWith[USED] == iPINZA) && (_vm->iconPos(iSERPENTEA) == MAXICON)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a523, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iLAMPADINA2B:
		if (_vm->_useWith[WITH] == oPORTALAMPADE29) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a293AVVITALAMPADINA, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iLATTINA27:
		if ((_vm->_useWith[WITH] == oBRACIERES28) && (_vm->_obj[oBRACIERES28]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a286, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oBRACIERES28]._examine = 456;
			*printSentence = false;
		} else
			*printSentence = true;
		break;

	case iTELECOMANDO2G:
		if (_vm->_useWith[WITH] == oTASTO2F) {
			if (_vm->_obj[oASCENSORE2F]._mode & OBJMODE_OBJSTATUS) {
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2F10PANNELLOSICHIUDE, 0, 0, _vm->_useWith[WITH]);
				_vm->_obj[oBIDONE2F]._anim = a2F5CFRUGABIDONE;
			} else {
				if (!(_vm->_inventoryObj[iTELECOMANDO2G]._flag & kObjFlagExtra))
					doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2F9PPANNELLOSIAPRE, 0, 0, _vm->_useWith[WITH]);
				else
					doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2F9PANNELLOSIAPRE, 0, 0, _vm->_useWith[WITH]);
				_vm->_inventoryObj[iTELECOMANDO2G]._flag |= kObjFlagExtra;
				_vm->_obj[oBIDONE2F]._anim = a2F5FRUGABIDONE;
			}
			*printSentence = false;
		}
		break;

	case iSAMROTTO:
		if (_vm->_useWith[WITH] == oSERRATURA33) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a338POSASAM, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iTORCIA32:
		if ((_vm->_useWith[WITH] == oSENSOREV32) && (_vm->_obj[oFILOTC31]._mode & OBJMODE_OBJSTATUS)) {
			_vm->_obj[oPANNELLOMA31]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOM31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOMA31]._examine = 717;
			_vm->_obj[oPANNELLOMA31]._action = 718;
			_vm->_obj[oCORPO31]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[od31ALLA35]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[omd31ALLA35]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oMONTACARICHI31]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLO31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLON31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_room[kRoom32]._flag |= kObjFlagExtra;
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom31, 0, 11, _vm->_useWith[WITH]);

			*printSentence = false;
		}
		break;

	case iPROIETTORE31:
		if (_vm->_useWith[WITH] == oPRESA35) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a351PROVAPROIETTOREPRESA, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oTRIPLA35) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a355ATTPROIETTORETRIPLAEPRESA, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oRIBELLEA35)) {
			*printSentence = false;
			CharacterSay(1578);
		}
		break;

	case iPROIETTORE35:
		if (_vm->_useWith[WITH] == oPRESA35) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a352ATTPROIETTOREETRIPLAPRESA, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oRIBELLEA35)) {
			*printSentence = false;
			CharacterSay(1590);
		}
		break;

	case iTRIPLA:
		if (_vm->_useWith[WITH] == oPRESA35) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a353ATTACCATRIPLAPRESA, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iLASER35:
		if (_vm->_useWith[WITH] == oFRONTOFFICEC35) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a3511APRESPORTELLO, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oSNAKEU52) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a522, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oSCAVO51]._anim = a516;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oLUCCHETTO53) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a532, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oDOORMC36) || (_vm->_useWith[WITH] == oPORTALC36) || (_vm->_useWith[WITH] == oSCANNERMA36) || (_vm->_useWith[WITH] == oSCANNERLA36) || (_vm->_useWith[WITH] == oCASSETTOC36) || (_vm->_useWith[WITH] == oRETE52) || (_vm->_useWith[WITH] == oTELECAMERA52) || (_vm->_useWith[WITH] == oSERPENTET52) || (_vm->_useWith[WITH] == oLAGO53)) {
			*printSentence = false;
			CharacterSay(1597);
		}
		break;

	case iKEY35:
		if (_vm->_useWith[WITH] == oCASSETTOC36) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a364APRECASSETTO, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oFRONTOFFICEC35) || (_vm->_useWith[WITH] == oDOORC54) || (_vm->_useWith[WITH] == oDOOR57C55) || (_vm->_useWith[WITH] == oDOOR58C55) || (_vm->_useWith[WITH] == oDOORS56) || (_vm->_useWith[WITH] == oDOORS57)) {
			*printSentence = false;
			CharacterSay(1594);
		}
		break;

	case iSTETOSCOPIO:
		if (_vm->_useWith[WITH] == oPORTALC36) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a368USASTETOSCOPIO, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iCARD36:
		if ((_vm->_useWith[WITH] == oFRONTOFFICEA35) && !(_vm->_obj[oFRONTOFFICEA35]._flag & kObjFlagExtra)) {
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom35P, 0, 10, _vm->_useWith[WITH]);
			_vm->removeIcon(iCARD36);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oFRONTOFFICEA35) && (_vm->_obj[oFRONTOFFICEA35]._flag & kObjFlagExtra)) {
			CharacterSay(1844);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSLOTA58) || (_vm->_useWith[WITH] == oSLOTB58)) {
			*printSentence = false;
			CharacterSay(1602);
		}
		break;

	case iMONETA4L:
		if ((_vm->_useWith[WITH] == oFESSURA41) &&
			((_vm->_obj[oFUCILE42]._anim != 0) && (_vm->_obj[oFUCILE42]._anim != a428) && (_vm->_obj[oFUCILE42]._anim != a429))) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a412, 0, 0, _vm->_useWith[WITH]);
			if (_vm->_obj[oZAMPA41]._mode & OBJMODE_OBJSTATUS)
				_vm->_obj[oSLOT41]._anim = a417;
			else if (_slotMachine41Counter <= 2)
				_vm->_obj[oSLOT41]._anim = a414;
			else
				CharacterSay(2015);
			_slotMachine41Counter++;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oFESSURA41) && ((_vm->_obj[oFUCILE42]._anim == 0) || (_vm->_obj[oFUCILE42]._anim == a428) || (_vm->_obj[oFUCILE42]._anim == a429))) {
			CharacterSay(2010);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oFESSURA42) {
			CharacterSay(924);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oCAMPANA4U) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4U3, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oCAMPANA4U]._flag |= kObjFlagExtra;
			if ((_vm->_obj[oCAMPANA4U]._flag & kObjFlagExtra) && (_vm->_inventoryObj[iBIGLIAA]._flag & kObjFlagExtra)) {
				_vm->_obj[oCAMPANA4U]._examine = 1202;
				_vm->_obj[oCAMPANA4U]._action = 1203;
			} else
				_vm->_obj[oCAMPANA4U]._examine = 1200;
			*printSentence = false;
		}
		break;

	case iMARTELLO:
		if ((_vm->_useWith[WITH] == oRAGNO41) && !(_vm->_obj[oRAGNO41]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a416, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oRAGNO41]._flag |= kObjFlagExtra;
			_vm->_obj[oRAGNO41]._anim = 0;
			if (_vm->_obj[oSLOT41]._anim == a414)
				_vm->_obj[oSLOT41]._anim = a417;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSLOT41) || (_vm->_useWith[WITH] == oVETRINETTA42) || (_vm->_useWith[WITH] == oTAMBURO43) || (_vm->_useWith[WITH] == oSFIATO45) || (_vm->_useWith[WITH] == oDOORC4A) || (_vm->_useWith[WITH] == oDOORC4B) || (_vm->_useWith[WITH] == oSERRATURA4B) || (_vm->_useWith[WITH] == oLICANTROPO4P)) {
			*printSentence = false;
			CharacterSay(1619);
		}
		break;

	case iMONETE:
		if ((_vm->_useWith[WITH] == oFESSURA42) && (_vm->_obj[oFUCILE42]._anim == a427)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a421, 0, 0, _vm->_useWith[WITH]);
			if (_vm->_obj[oPOLTIGLIA42]._mode & OBJMODE_OBJSTATUS)
				_vm->_obj[oFUCILE42]._anim = a429;
			else
				_vm->_obj[oFUCILE42]._anim = a428;
			*printSentence = false;
		}
		break;

	case iPOLTIGLIA:
		if (_vm->_useWith[WITH] == oGUIDE42) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a423, 0, 0, _vm->_useWith[WITH]);
			if (_vm->_obj[oFUCILE42]._anim != a427)
				_vm->_obj[oFUCILE42]._anim = a429;
			*printSentence = false;
		}
		break;

	case iMAZZA:
		if ((_vm->_useWith[WITH] == oTAMBURO43) && !(_vm->_obj[oTAMBURO43]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a435, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oTAMBURO43]._flag |= kObjFlagExtra;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oDOORC4B) || (_vm->_useWith[WITH] == oSERRATURA4B) || (_vm->_useWith[WITH] == oLICANTROPO4P)) {
			*printSentence = false;
			CharacterSay(1679);
		}
		break;

	case iPUPAZZO:
		if (_vm->_useWith[WITH] == oCASSETTOAA44) {
			_vm->replaceIcon(iPUPAZZO, iTELECOMANDO44);
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a442, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iSTRACCIO:
		if (_vm->_useWith[WITH] == oMANOPOLAR45) {
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom45S, 0, 2, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oCAMPANA4U) && (_vm->_inventoryObj[iBIGLIAA]._flag & kObjFlagExtra) && (_vm->_obj[oCAMPANA4U]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4U5, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oCAMPANA4U]._examine = 1204;
			_vm->_obj[oCAMPANA4U]._action = 1205;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oCAMPANA4U) {
			CharacterSay(1713);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSPIDER46) || (_vm->_useWith[WITH] == oLICANTROPO4P)) {
			*printSentence = false;
			CharacterSay(1711);
		}
		break;

	case iSKULL:
		if (_vm->_useWith[WITH] == oTILE48) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4810, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iTORCH47:
		if (_vm->_useWith[WITH] == oSKULL48) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4811, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oBOILERS45) || (_vm->_useWith[WITH] == oSPIDER46)) {
			*printSentence = false;
			CharacterSay(1640);
		}
		break;

	case iMATCH:
		if (_vm->_useWith[WITH] == oTORCHS48) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4812, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oTORCHS48]._lim = Common::Rect(0, 0, 0, 0);
			*printSentence = false;
		}
		break;

	case iROD:
		if (_vm->_useWith[WITH] == oSUNDIAL49) {
			_vm->removeIcon(iROD);
			StartCharacterAction(a491, kRoom49M, 1, 0);
			*printSentence = false;
		}
		break;

	case iPISTOLA4PD:
		if ((_vm->_useWith[WITH] == oLICANTROPO4P) && (_vm->_inventoryObj[iPISTOLA4PD]._flag & kObjFlagExtra)) {
			_vm->replaceIcon(iPISTOLA4PD, iPISTOLA4B);
			_vm->_obj[oLICANTROPO4P]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oLICANTROPOM4P]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oSANGUE4P]._mode |= OBJMODE_OBJSTATUS;
			_vm->_room[kRoom4P]._flag |= kObjFlagExtra;
			read3D("4p2.3d"); // after werewolf
			_vm->_animMgr->_animTab[aBKG4P]._flag |= SMKANIM_OFF1;
			_vm->_dialogMgr->playDialog(dF4P2);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oLICANTROPO4P) {
			_vm->replaceIcon(iPISTOLA4PD, iPISTOLA4B);
			_vm->_dialogMgr->playDialog(dF4P1);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oSPIDER46) || (_vm->_useWith[WITH] == oDOORC4B) || (_vm->_useWith[WITH] == oSERRATURA4B)) {
			*printSentence = false;
			CharacterSay(1706);
		}
		break;

	case iBARATTOLO:
		if ((_vm->_useWith[WITH] == oSANGUE4P) || (_vm->_useWith[WITH] == oLICANTROPOM4P)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4P7, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iCAMPANA:
		if (_vm->_useWith[WITH] == oPOZZA4U) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4U2, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iBIGLIAA:
	case iBIGLIAB:
		if ((_vm->_useWith[WITH] == oCAMPANA4U) && (_vm->_inventoryObj[iBIGLIAA]._flag & kObjFlagExtra)) {
			CharacterSay(1684);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oCAMPANA4U) {
			_vm->removeIcon(_vm->_useWith[USED]);
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4U4, 0, 0, _vm->_useWith[WITH]);
			_vm->_inventoryObj[iBIGLIAA]._flag |= kObjFlagExtra;
			if ((_vm->_obj[oCAMPANA4U]._flag & kObjFlagExtra) && (_vm->_inventoryObj[iBIGLIAA]._flag & kObjFlagExtra)) {
				_vm->_obj[oCAMPANA4U]._examine = 1202;
				_vm->_obj[oCAMPANA4U]._action = 1203;
			} else
				_vm->_obj[oCAMPANA4U]._examine = 1201;
			*printSentence = false;
		}
		break;

	case iPAPAVERINA:
		if ((_vm->_useWith[WITH] == oCHOCOLATES4A) && (_vm->_animMgr->smkCurFrame(kSmackerBackground) < 370 || _vm->_animMgr->smkCurFrame(kSmackerBackground) > 480)) {
			_vm->playScript(s4AHELLEN);
			_vm->_obj[oPULSANTE4A]._anim = a4A3;
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oCHOCOLATES4A) {
			_vm->_obj[oPULSANTE4A]._anim = a4A3;
			*printSentence = false;
			_vm->_obj[oCHOCOLATES4A]._flag |= kObjFlagExtra;
		}
		break;

	case iSANGUE:
		if (_vm->_useWith[WITH] == oSERRATURA4B) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4B4, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oDOORC4B]._anim = a4B5;
			*printSentence = false;
		}
		break;

	case iDIAPA4B:
		if ((_vm->_useWith[WITH] == oPROIETTORE4B) && (_vm->_obj[oPROIETTORE4B]._anim < a4B9A)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4B6A, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oPROIETTORE4B]._anim = a4B9A;
			*printSentence = false;
		}
		break;

	case iDIAPB4B:
		if ((_vm->_useWith[WITH] == oPROIETTORE4B) && (_vm->_obj[oPROIETTORE4B]._anim < a4B9A)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4B6B, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oPROIETTORE4B]._anim = a4B9B;
			*printSentence = false;
		}
		break;

	case iDIAP4C:
		if ((_vm->_useWith[WITH] == oPROIETTORE4B) && (_vm->_obj[oPROIETTORE4B]._anim < a4B9A)) {
			//
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4B6C, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oPROIETTORE4B]._anim = a4B9C;
			*printSentence = false;
		}
		break;

	case iUOVO:
		if ((_vm->_useWith[WITH] == oRETE52) || (_vm->_useWith[WITH] == oSERPENTET52)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a521, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iSERPENTEA:
		if (_vm->_useWith[WITH] == oLAGO53) {
			*printSentence = false;
			if (!(_vm->_obj[oLUCCHETTO53]._mode & OBJMODE_OBJSTATUS)) {
				StartCharacterAction(a533, kRoom54, 11, 0);
				_vm->removeIcon(_vm->_useWith[USED]);
			} else if (_vm->_useWith[USED] != iSERPENTEB) {
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a534, 0, 0, _vm->_useWith[WITH]);
				_vm->removeIcon(_vm->_useWith[USED]);
				_vm->_obj[oLAGO53]._examine = 1237;
			} else
				CharacterSay(1740);
		}
		break;

	case iSERPENTEB:
		if (_vm->_useWith[WITH] == oLAGO53) {
			*printSentence = false;
			if (!(_vm->_obj[oLUCCHETTO53]._mode & OBJMODE_OBJSTATUS)) {
				StartCharacterAction(a533C, kRoom54, 11, 0);
				_vm->removeIcon(_vm->_useWith[USED]);
			} else if (_vm->_useWith[USED] != iSERPENTEB) {
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a534, 0, 0, _vm->_useWith[WITH]);
				_vm->removeIcon(_vm->_useWith[USED]);
				_vm->_obj[oLAGO53]._examine = 1237;
			} else
				CharacterSay(1740);
		}
		break;

	case iSAPONE:
		if (_vm->_useWith[WITH] == oSECCHIOA54) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a543, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iLATTINE:
		if (_vm->_useWith[WITH] == oLAVATRICEF54) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a546, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oLAVATRICEL54]._anim = a547;
			*printSentence = false;
		}
		break;

	case iCHIAVI:
		if (_vm->_useWith[WITH] == oDOORS56) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a563, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oDOOR57C55) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a551, kRoom57, 17, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oDOOR58C55) && (!(_vm->_dialogMgr->_choice[871]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[901]._flag & kObjFlagDone))) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a552, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oDOOR58C55) && (_vm->_dialogMgr->_choice[871]._flag & kObjFlagDone)) {
			CharacterSay(1287);
			*printSentence = false;
		}
		break;

	case iMDVD:
		if ((_vm->_useWith[WITH] == oTASTIERA56) && (_vm->_dialogMgr->_choice[260]._flag & kObjFlagDone) && !(_vm->_dialogMgr->_choice[262]._flag & kObjFlagDone) && (_vm->_inventoryObj[iMDVD]._examine != 1752)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a566, 0, 0, _vm->_useWith[WITH]);
			_vm->_dialogMgr->_choice[262]._flag &= ~DLGCHOICE_HIDE;
			_vm->_inventoryObj[iMDVD]._examine = 1752;
			*printSentence = false;
		} else if ((_vm->_useWith[WITH] == oTASTIERA56) && (_vm->_inventoryObj[iMDVD]._examine == 1752)) {
			CharacterSay(1753);
			*printSentence = false;
		} else
			*printSentence = true;
		break;

	case iTESTER:
		if ((_vm->_useWith[WITH] == oPANNELLOA) && (_vm->_dialogMgr->_choice[856]._flag & kObjFlagDone)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a569, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oPANNELLOA]._flag |= kObjFlagExtra;
			*printSentence = false;
		}
		break;

	case iCUTTER:
		if ((_vm->_useWith[WITH] == oPANNELLOA) && (_vm->_obj[oPANNELLOA]._flag & kObjFlagExtra)) {
			_vm->_dialogMgr->playDialog(dF562);
			_vm->_obj[oPANNELLOA]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCAVOTAGLIATO56]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oDOOR58C55]._mode |= OBJMODE_OBJSTATUS;
			setPosition(6);
			_vm->removeIcon(iCUTTER);
			*printSentence = false;
		} else if (_vm->_useWith[WITH] == oPANNELLOA) {
			CharacterSay(2012);
			*printSentence = false;
		}
		break;

	case iGUANTI59:
		if (_vm->_useWith[WITH] == oBOMBOLA57) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a575, 0, 0, _vm->_useWith[WITH]);
			*printSentence = false;
		}
		break;

	case iARMAEVA:
		if ((_vm->_useWith[WITH] == oWINDOWA5A) && (_vm->_dialogMgr->_choice[871]._flag & kObjFlagDone) && !(_vm->_dialogMgr->_choice[286]._flag & kObjFlagDone)) {
			_vm->removeIcon(iARMAEVA);
			_vm->_dialogMgr->playDialog(dC5A1);
			_vm->_obj[oWINDOWA58]._anim = a587;
			*printSentence = false;
			_vm->_room[kRoom5A]._flag |= kObjFlagExtra;
		} else if ((_vm->_useWith[WITH] == oWINDOWA5A) && (_vm->_dialogMgr->_choice[871]._flag & kObjFlagDone)) {
			_vm->removeIcon(iARMAEVA);
			_vm->_dialogMgr->playDialog(dF5A1);
			_vm->_obj[oWINDOWA58]._anim = a587;
			*printSentence = false;
		}
		break;

	default:
		*updateInventory = false;
		break;
	}
}

bool LogicManager::useScreenWithScreen() {
	bool printSentence = true;

	switch (_vm->_useWith[USED]) {
	case oRAMPINO21:
		if (_vm->_useWith[WITH] == oTUBO21) {
			_vm->_dialogMgr->playDialog(dF211);
			_vm->setRoom(kRoom21, true);
			_vm->_animMgr->_animTab[aBKG21]._flag &= ~SMKANIM_OFF1;
			_vm->_obj[oRAMPINO21]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oTUBO21]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCATENAT21]._mode |= OBJMODE_OBJSTATUS;
			printSentence = false;
		}
		break;

	case oCAVIE23:
		if (_vm->_useWith[WITH] == oCAMPO23) {
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom23B, 0, 0, _vm->_useWith[WITH]);
			printSentence = false;
		} else {
			StartCharacterAction(hBOH, 0, 0, 0);
			printSentence = false;
		}
		break;

	case oTUBOP33:
		if (_vm->_useWith[WITH] == oTUBOF33) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a337PRENDETUBO, 0, 0, _vm->_useWith[WITH]);
			_vm->_obj[oTUBOF34]._examine = 1832;
			_vm->_obj[oTUBOFT34]._examine = 773;
			printSentence = false;
		}
		break;

	case oTUBET33:
		if (((_vm->_useWith[WITH] == oSAMA33) || (_vm->_useWith[WITH] == oSERRATURA33 && _vm->_obj[oSAMA33]._mode & OBJMODE_OBJSTATUS)) && (_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS)) {
			_vm->_dialogMgr->playDialog(dF331);
			setPosition(10);
			_vm->_obj[oBOTOLAC33]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oSERRATURA33]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oBOTOLAA33]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oBRUCIATURA33]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oSERRATURAF33]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oSAMD33]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oTUBOS33]._mode |= OBJMODE_OBJSTATUS;

			_vm->_obj[oBOTOLAC32]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oBOTOLAB32]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oBOTOLAA32]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPULSANTI32]._anim = 0;

			_vm->_obj[oSIGARO31]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOM31]._anim = a314APREPANNELLO;
			_vm->_obj[oPANNELLOM31]._examine = 713;
			_vm->_obj[oPANNELLOM31]._action = 714;
			_vm->_obj[oPANNELLOM31]._flag |= kObjFlagRoomOut;
			_vm->_obj[oPANNELLON31]._mode |= OBJMODE_OBJSTATUS;

			_vm->_obj[oMANOMETROC34]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oMANOMETRO34]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oMANOMETROC34]._examine = 804;
			_vm->_obj[oVALVOLAC34]._anim = 0;
			_vm->_obj[oVALVOLA34]._anim = 0;
			_vm->_obj[oVALVOLAC34]._action = 1831;
			_vm->_obj[oVALVOLA34]._action = 1831;

			_vm->_obj[oTUBOF34]._examine = 1832;
			_vm->_obj[oTUBOFT34]._examine = 784;

			printSentence = false;
		}
		break;

	case oFILOS31:
		if (_vm->_useWith[WITH] == oCONTATTOP31) {
			_vm->_obj[oFILOS31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCONTATTOP31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oFILOTC31]._mode |= OBJMODE_OBJSTATUS;
			CharacterSay(746);
			RegenRoom();

			printSentence = false;
		}
		break;
	default:
		break;
	}

	return printSentence;
}

void LogicManager::roomOut(uint16 curObj, uint16 *action, uint16 *pos) {
	if (curObj == oSCALA32 && _vm->_obj[oBOTOLAC32]._mode & OBJMODE_OBJSTATUS) {
		CharacterSay(_vm->_obj[curObj]._action);
		_vm->showCursor();
		*action = 0;
		*pos = 0;
	} else {
		*action = _vm->_obj[curObj]._anim;
		*pos = _vm->_obj[curObj]._ninv;
	}
}

bool LogicManager::mouseExamine(uint16 curObj) {
	bool retVal = false;

	switch (curObj) {
	case oMAPPA12:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1211OSSERVAMAPPAPALAZZO, 0, 0, curObj);
		_vm->_dialogMgr->_choice[4]._flag &= ~DLGCHOICE_HIDE;
		_vm->_dialogMgr->_choice[18]._flag &= ~DLGCHOICE_HIDE;
		_vm->_dialogMgr->_choice[33]._flag &= ~DLGCHOICE_HIDE;
		retVal = false;
		break;

	case oDOORA13:
		_vm->_obj[oBOX12]._mode |= OBJMODE_OBJSTATUS;
		retVal = true;
		break;

	case oPANELA12:
	case oFUSIBILE12:
		if (_vm->_obj[oFUSIBILE12]._mode & OBJMODE_OBJSTATUS)
			_vm->_obj[oFUSE12CU]._mode |= OBJMODE_OBJSTATUS;
		else
			_vm->_obj[oFUSE12CU]._mode &= ~OBJMODE_OBJSTATUS;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom12CU, 0, 0, curObj);
		_vm->_closeUpObj = curObj;
		break;

	case oLETTERA13:
	case oPENPADA13:
		if (_vm->_obj[oLETTERA13]._mode & OBJMODE_OBJSTATUS)
			_vm->_obj[oLETTER13CU]._mode |= OBJMODE_OBJSTATUS;
		else
			_vm->_obj[oLETTER13CU]._mode &= ~OBJMODE_OBJSTATUS;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom13CU, 0, 0, curObj);
		_vm->_closeUpObj = curObj;
		break;

	case oCUCININO14:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1413OSSERVAPIANOCOTTURA, 0, 0, curObj);
		retVal = false;
		break;

	case oSCAFFALE14:
		if (!(_vm->_obj[oDOORR14]._mode & OBJMODE_OBJSTATUS))
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a145ESAMINASCAFFALE, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a145CESAMINASCAFFALE, 0, 0, curObj);
		retVal = false;
		break;

	case oTAVOLINOPP14:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1412SPOSTASEDIA, 0, 0, curObj);
		retVal = false;
		break;

	case oBOCCETTE15:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1510TOCCABOCCETTE, 0, 0, curObj);
		retVal = false;
		break;

	case oSPECCHIO15:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1511SISPECCHIA, 0, 0, curObj);
		retVal = false;
		break;

	case oMONITORSA16:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1614GUARDAMONITORS14, 0, 0, curObj);
		retVal = false;
		break;

	case oWINDOWA15:
		if (_vm->_obj[oTAPPARELLAA15]._mode & OBJMODE_OBJSTATUS)
			CharacterSay(1999);
		else
			retVal = true;
		break;

	case oMONITORSP16:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1615GUARDAMONITORS15, 0, 0, curObj);
		retVal = false;
		break;

	case oCARTACCE16:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1613GUARDACARTACCE, 0, 0, curObj);
		retVal = false;
		break;

	case oMAPPA16:
		if (_vm->iconPos(iFOGLIO14) != MAXICON)
			_vm->_obj[oMAPPA16]._flag |= kObjFlagExtra;
		retVal = true;
		break;

	case oSCATOLONE17:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a177SICHINA, 0, 0, curObj);
		retVal = false;
		break;

	case oMURALES17:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a179MUOVETESTA, 0, 0, curObj);
		retVal = false;
		break;

	case oSCHERMO18:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a181ESAMINACARTELLONE, 0, 0, curObj);
		retVal = false;
		break;

	case oVETRINA1A:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1A1ESAMINAVETRINA, 0, 0, curObj);
		retVal = false;
		break;

	case oTESSERA1A:
		if (((_vm->_dialogMgr->_choice[151]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[152]._flag & kObjFlagDone)) && !(_vm->_dialogMgr->_choice[183]._flag & kObjFlagDone))
			_vm->_dialogMgr->_choice[183]._flag &= ~DLGCHOICE_HIDE;
		_vm->_obj[oTESSERA1A]._flag |= kObjFlagExtra;
		retVal = true;
		break;

	case oCARTACCE1B:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B8FRUGACARTACCIE, 0, 0, curObj);
		retVal = false;
		break;

	case oBIDONE1B:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B10GUARDABIDONE, 0, 0, curObj);
		retVal = false;
		break;

	case oGRATA1C:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1C2GUARDAGRATA, 0, 0, curObj);
		retVal = false;
		break;

	case oSCAFFALE1D:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1D8SALESGABELLO, 0, 0, curObj);
		retVal = false;
		break;

	case oBARILOTTO1D:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1D7SPINGEBARILOTTO, 0, 0, curObj);
		retVal = false;
		break;

	case oCASSA1D:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1D10ESAMINABOTTIGLIE, 0, 0, curObj);
		retVal = false;
		break;

	case oSCATOLETTA23:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2310, 0, 0, curObj);
		retVal = false;
		break;

	case oPALMA26:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a262, 0, 0, curObj);
		retVal = false;
		break;

	case oINSEGNA26:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a263, 0, 0, curObj);
		retVal = false;
		break;

	case oTEMPIO28:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2810, 0, 0, curObj);
		retVal = false;
		break;

	case oSERPENTET28:
	case oSERPENTEA28:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2811, 0, 0, curObj);
		retVal = false;
		break;

	case oSERPENTE2B:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2B11ESAMINASERPENTE, 0, 0, curObj);
		retVal = false;
		break;

	case oLEOPARDO2B:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2B9ESAMINALEOPARDO, 0, 0, curObj);
		retVal = false;
		break;

	case oPELLICANO2B:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2B10ESAMINAPELLICANO, 0, 0, curObj);
		retVal = false;
		break;

	case oBACHECA2B:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2B13OSSERVAREFARFALLE, 0, 0, curObj);
		retVal = false;
		break;

	case oROBOT2F:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2F6TOCCADINOSAURO, 0, 0, curObj);
		retVal = false;
		break;

	case oCREPACCIO2E:
		if (_vm->_room[kRoom2E]._flag & kObjFlagExtra)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2E7GUARDACREPACCIODILA, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2E6GUARDACREPACCIODIQUA, 0, 0, curObj);
		retVal = false;
		break;

	case oGENERATORE34:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a347ESAMINAGENERATORE, 0, 0, curObj);
		retVal = false;
		break;

	case oTUBOF33:
		if ((_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS) && _vm->_obj[oVALVOLA34]._anim)
			CharacterSay(2000);
		else
			CharacterSay(_vm->_obj[curObj]._examine);
		retVal = false;
		break;

	case oTUBET33:
		if ((_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS) && _vm->_obj[oVALVOLA34]._anim)
			CharacterSay(2001);
		else
			CharacterSay(_vm->_obj[curObj]._examine);
		retVal = false;
		break;

	case oTUBOA34:
		if ((_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS) && _vm->_obj[oVALVOLA34]._anim)
			CharacterSay(2002);
		else
			CharacterSay(_vm->_obj[curObj]._examine);
		retVal = false;
		break;

	case oTUBOF34:
		if ((_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS) && _vm->_obj[oVALVOLA34]._anim)
			CharacterSay(2000);
		else
			CharacterSay(_vm->_obj[curObj]._examine);
		retVal = false;
		break;

	case oTUBOFT34:
		if ((_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS) && _vm->_obj[oVALVOLA34]._anim)
			CharacterSay(2001);
		else
			CharacterSay(_vm->_obj[curObj]._examine);
		retVal = false;
		break;

	case oCASSE35:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a3522ESAMINACASSE, 0, 0, curObj);
		retVal = false;
		break;

	case oSCAFFALE35:
		if (_vm->_room[kRoom35]._flag & kObjFlagExtra)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a3517ESAMINACIANFRUSAGLIE, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a3517AESAMINACIANFRUSAGLIE, 0, 0, curObj);
		retVal = false;
		break;

	case oGIORNALE35:
		if (_vm->_room[kRoom35]._flag & kObjFlagExtra) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a3521LEGGEGIORNALE, 0, 0, curObj);
			retVal = false;
		}
		break;

	case oSCAFFALE36:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[oSCAFFALE36]._anim, 0, 0, curObj);
		retVal = false;
		break;

	case oFESSURA41:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a411, 0, 0, curObj);
		retVal = false;
		break;

	case oCARTELLOV42:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a424, 0, 0, curObj);
		retVal = false;
		break;

	case oCARTELLOF42:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a426, 0, 0, curObj);
		retVal = false;
		break;

	case oCAMPANAT43:
		if (_vm->_obj[oMARTELLOR43]._mode & OBJMODE_OBJSTATUS)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a431R, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a431, 0, 0, curObj);
		retVal = false;
		break;

	case oTAMBURO43:
		if (_vm->_obj[oMARTELLOR43]._mode & OBJMODE_OBJSTATUS)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a432R, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a432, 0, 0, curObj);
		retVal = false;
		break;

	case oRAGNATELA45:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a451, 0, 0, curObj);
		retVal = false;
		break;

	case oQUADROS4A:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a4A5, 0, 0, curObj);
		retVal = false;
		break;

	case oCARTELLO55:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a5511, 0, 0, curObj);
		retVal = false;
		break;

	case oEXIT12CU:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT12CU]._goRoom, 0, 0, curObj);
		break;

	case oEXIT13CU:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT13CU]._goRoom, 0, 0, curObj);
		break;

	case oEXIT2BL:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT2BL]._goRoom, 0, 0, curObj);
		break;

	case oEXIT36F:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT36F]._goRoom, 0, 0, curObj);
		break;

	case oEXIT41D:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT41D]._goRoom, 0, 0, curObj);
		break;

	case oEXIT4CT:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT4CT]._goRoom, 0, 0, curObj);
		break;

	case oEXIT58T:
		_count58 = 0;
		for (int a = 0; a < 6; a++)
			_vm->_obj[oLED158 + a]._mode &= ~OBJMODE_OBJSTATUS;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT58T]._goRoom, 0, 0, curObj);
		break;

	case oEXIT58M:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT58M]._goRoom, 0, 0, curObj);
		break;

	case oEXIT59L:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT59L]._goRoom, 0, 0, curObj);
		break;

	default:
		retVal = true;
		break;
	}

	return retVal;
}

bool LogicManager::mouseOperate(uint16 curObj) {
	bool retVal = false;

	if (!curObj)
		warning("doMouseOperate");

	switch (curObj) {
	case oFAX17:
		if (_vm->_obj[oSCALA16]._anim) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
			_vm->_inventoryObj[iSAM]._action = 1416;
			retVal = false;
		}
		break;

	case ocPOLIZIOTTO16:
	case oSCALA16:
		if (!(_vm->_obj[oSCALA16]._flag & kObjFlagExtra)) {
			_vm->_obj[oSCALA16]._flag |= kObjFlagExtra;
			_vm->_dialogMgr->_choice[61]._flag &= ~DLGCHOICE_HIDE;
			_vm->_dialogMgr->playDialog(dPOLIZIOTTO16);
			_vm->_obj[oSCALA16]._action = 166;
			_vm->_obj[ocPOLIZIOTTO16]._action = 166;
		} else
			retVal = true;
		break;

	case oPANNELLOC12:
		if (_vm->_obj[oPANNELLOC12]._flag & kObjFlagExtra) {
			if (_vm->_obj[oASCENSOREC12]._mode & OBJMODE_OBJSTATUS)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a128RIUSABOTTONE, 0, 0, curObj);
			else
				CharacterSay(24);
		} else {
			_vm->_obj[oPANNELLOC12]._flag |= kObjFlagExtra;
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		}
		break;
	case oPANNELLO13:
		if (_vm->_obj[oASCENSOREA13]._mode & OBJMODE_OBJSTATUS) {
			CharacterSay(48);
			retVal = false;
		} else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);

		break;

	case oPANNELLO16:
		if (_vm->_obj[oASCENSOREA16]._mode & OBJMODE_OBJSTATUS) {
			CharacterSay(48);
			retVal = false;
		} else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		break;

	case oLATTINA13:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a132PRENDELATTINA, 0, 0, curObj);
		_vm->addIcon(iLATTINA13);
		break;

	case oDOORA13:
		if (_vm->_room[kRoom14]._flag & kObjFlagDone) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1312METTELETTERARICALCA, kRoom14, 14, _vm->_useWith[WITH]);
			retVal = false;
		} else
			retVal = true;
		break;

	case oCESTINO14:
		if (_vm->_obj[curObj]._anim) {
			if (!(_vm->_obj[oDOORR14]._mode & OBJMODE_OBJSTATUS))
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
			else
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a143CPRENDECREDITCARD, 0, 0, curObj);
			_vm->_obj[curObj]._anim = NULL;
		} else
			retVal = true;
		break;
	case oTASTOB15:
		if (_vm->_obj[oTAPPARELLAA15]._mode & OBJMODE_OBJSTATUS) {
			CharacterSay(_vm->_obj[oTASTOB15]._action);
			retVal = false;
		} else {
			if (!(_vm->_obj[oNASTRO15]._flag & kObjFlagExtra))
				_vm->_obj[oNASTRO15]._mode |= OBJMODE_OBJSTATUS;
			if (_vm->_obj[curObj]._anim)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
			retVal = false;
		}
		break;

	case oTASTOA15:
		if (!(_vm->_obj[oTAPPARELLAA15]._mode & OBJMODE_OBJSTATUS)) {
			CharacterSay(_vm->_obj[oTASTOA15]._action);
			retVal = false;
		} else {
			_vm->_obj[oNASTRO15]._mode &= ~OBJMODE_OBJSTATUS;
			if (_vm->_obj[curObj]._anim)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
			retVal = false;
		}
		break;

	case oFINGERPADP16:
		retVal = true;
		break;

	case oDOORC18:
		if (_vm->_obj[ocGUARD18]._flag & kObjFlagPerson) {
			_vm->_dialogMgr->_choice[151]._flag |= DLGCHOICE_HIDE;
			_vm->_dialogMgr->_choice[152]._flag &= ~DLGCHOICE_HIDE;
			_vm->_dialogMgr->playDialog(dGUARDIAN18);
			_vm->_obj[ocGUARD18]._flag &= ~kObjFlagPerson;
			_vm->_obj[ocGUARD18]._action = 227;
			_vm->_obj[oDOORC18]._action = 220;
		} else
			retVal = true;
		break;

	case oGRATA1C:
		if (_vm->_obj[oFAX17]._flag & kObjFlagExtra)
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom21, 0, 10, curObj);
		else
			retVal = true;
		break;

	case oBOTOLAC1B:
		if ((_vm->_obj[oBOTOLAC1B]._anim == a1B3APREBOTOLA) && (_vm->_obj[oTOMBINOA1B]._mode & OBJMODE_OBJSTATUS))
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B3AAPREBOTOLA, 0, 0, curObj);
		else if (_vm->_obj[oBOTOLAC1B]._anim == a1B3APREBOTOLA)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a1B3APREBOTOLA, 0, 0, curObj);
		else
			retVal = true;
		break;

	case oARMADIETTORC22:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		_vm->_obj[oMANIGLIONE22]._anim = a227A;
		_vm->_obj[oMANIGLIONEO22]._anim = a229A;
		_vm->_obj[od22TO29]._anim = a2214A;
		_vm->_obj[od22TO29I]._anim = a2215A;
		break;

	case oARMADIETTORA22:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		_vm->_obj[oMANIGLIONE22]._anim = a227;
		_vm->_obj[oMANIGLIONEO22]._anim = a229;
		_vm->_obj[od22TO29]._anim = a2214;
		_vm->_obj[od22TO29I]._anim = a2215;
		break;

	case oCATENAT21:
		if ((_vm->iconPos(iSBARRA21) != MAXICON) && ((_vm->_dialogMgr->_choice[436]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[466]._flag & kObjFlagDone))) {
			if (_vm->_room[_vm->_curRoom]._flag & kObjFlagExtra) // Go right
				_vm->_dialogMgr->playDialog(dF212);                             // 436
			else                                                 // Go left
				_vm->_dialogMgr->playDialog(dF213);                             // 466
			retVal = false;
		} else if ((_vm->_dialogMgr->_choice[451]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[481]._flag & kObjFlagDone)) {
			if (_vm->_room[_vm->_curRoom]._flag & kObjFlagExtra) // Go right
				_vm->_dialogMgr->playDialog(dF212B);                            // 451
			else                                                 // Go left
				_vm->_dialogMgr->playDialog(dF213B);                            // 481
			retVal = false;
		} else
			retVal = true;
		break;

	case oPULSANTEACS2D:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		_vm->_obj[oPULSANTEBC2D]._anim = a2D7SCHIACCIATASTO6V;
		break;

	case oPULSANTEACA2D:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		_vm->_obj[oPULSANTEBC2D]._anim = a2D7SCHIACCIATASTO6R;
		break;

	case oSWITCH29:
		if (_vm->_curRoom == kRoom29L)
			retVal = true;
		else if ((_vm->_obj[oLAMPADINAS29]._mode & OBJMODE_OBJSTATUS)) {
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom29L, 0, 0, curObj);
			retVal = false;
		} else if (!(_vm->_obj[_vm->_curObj]._flag & kObjFlagExtra)) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a291USAINTERRUTTORELUCE, 0, 0, curObj);
			_vm->_obj[_vm->_curObj]._flag |= kObjFlagExtra;
			retVal = false;
		} else
			retVal = true;
		break;

	case oLEVAS23:
		if (_vm->_obj[oCAVI23]._mode & OBJMODE_OBJSTATUS)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a238, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a234, 0, 0, curObj);
		break;

	case oLEVAG23:
		if (_vm->_obj[oCAVIE23]._mode & OBJMODE_OBJSTATUS)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a239, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a235, 0, 0, curObj);
		break;

	case oBOTOLAC25:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		_vm->_obj[oTRONCHESE25]._anim = a254B;
		break;

	case oBOTOLAA25:
		doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		_vm->_obj[oTRONCHESE25]._anim = a254;
		break;

	case oPASSAGE24:
		if (_vm->_room[kRoom24]._flag & kObjFlagExtra) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a244, 0, 14, curObj);
			_vm->setRoom(kRoom24, false);
			retVal = false;
		} else {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a243, 0, 13, curObj);
			_vm->setRoom(kRoom24, true);
			retVal = false;
		}
		break;

	case oDOOR26:
		if (_vm->_obj[curObj]._anim)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 4, curObj);
		break;

	case oRUBINETTOC28:
		if (_vm->_obj[curObj]._anim) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
			_vm->_obj[oBRACIERES28]._examine = 455;
			_vm->_obj[oBRACIERES28]._flag |= kObjFlagExtra;
		} else
			retVal = true;
		break;

	case oEXIT12CU:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT12CU]._goRoom, 0, 0, curObj);
		break;

	case oEXIT13CU:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT13CU]._goRoom, 0, 0, curObj);
		break;

	case oEXIT2BL:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT2BL]._goRoom, 0, 0, curObj);
		break;

	case oEXIT36F:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT36F]._goRoom, 0, 0, curObj);
		break;

	case oEXIT41D:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT41D]._goRoom, 0, 0, curObj);
		break;

	case oEXIT4CT:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT4CT]._goRoom, 0, 0, curObj);
		break;

	case oEXIT58T:
		_count58 = 0;
		for (uint8 a = 0; a < 6; a++)
			_vm->_obj[oLED158 + a]._mode &= ~OBJMODE_OBJSTATUS;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT58T]._goRoom, 0, 0, curObj);
		break;

	case oEXIT58M:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT58M]._goRoom, 0, 0, curObj);
		break;

	case oEXIT59L:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT59L]._goRoom, 0, 0, curObj);
		break;

	case oPANELM2G:
		if (!(_vm->_obj[oPANELM2G]._flag & kObjFlagExtra)) {
			_vm->_dialogMgr->playDialog(dF2G1);
			_vm->_obj[oCOPERCHIO2G]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oSERBATOIOC2G]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oRAGAZZOP2G]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oRAGAZZOS2G]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oSERBATOIOA2G]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOE2G]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPANELM2G]._flag |= kObjFlagExtra;
			_vm->_animMgr->_animTab[aBKG2G]._flag |= SMKANIM_OFF1;
			retVal = false;
		} else
			retVal = true;

		break;

	case oWHEELS2C:
		if (!(_vm->_obj[od2CALLA2D]._mode & OBJMODE_OBJSTATUS)) {
			_vm->_animMgr->smkStop(kSmackerBackground);
			_vm->_animMgr->_animTab[aBKG2C]._flag |= SMKANIM_OFF1;
			_vm->_obj[oBASEWHEELS2C]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[omWHEELS2C]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPULSANTE2C]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[_wheelPos[0] * 3 + 0 + oWHEEL1A2C]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[_wheelPos[1] * 3 + 1 + oWHEEL1A2C]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[_wheelPos[2] * 3 + 2 + oWHEEL1A2C]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oCAMPO2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oTEMPIO2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oLEONE2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[od2CALLA2D]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oSFINGE2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oSTATUA2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oWHEELS2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[od2CALLA2E]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCARTELLOS2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oCARTELLOA2C]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[od2CALLA26]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_flagShowCharacter = false;
			ReadExtraObj2C();
			RegenRoom();
		} else
			retVal = true;
		break;

	case oCATWALKA2E:
		if (!(_vm->_obj[oCATWALKA2E]._flag & kObjFlagExtra)) {
			_vm->_dialogMgr->playDialog(dF2E1);
			_vm->_obj[oDINOSAURO2E]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oCATWALKA2E]._flag |= kObjFlagExtra;
			_vm->_animMgr->_animTab[aBKG2E]._flag &= ~SMKANIM_OFF2;
			retVal = false;
		} else if (_vm->_obj[curObj]._anim) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
			retVal = false;
		} else
			retVal = true;
		break;

	case oBORSA22:
	case oPORTALAMPADE2B:
	case oMAPPAMONDO2B:
		if (_vm->_obj[curObj]._anim) {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
			_vm->_obj[curObj]._anim = 0;
		} else
			retVal = true;
		break;

	case oTUBOF34:
		if (!(_vm->_obj[oTUBOFT34]._mode & OBJMODE_OBJSTATUS))
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		else
			retVal = true;
		break;

	case oFILOT31:
		_vm->_obj[oFILOT31]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oFILOS31]._mode |= OBJMODE_OBJSTATUS;
		RegenRoom();
		break;

	case oCOPERCHIOA31:
		if (_vm->_obj[oFILOTC31]._mode & OBJMODE_OBJSTATUS) {
			_vm->_soundMgr->play(wCOVER31);
			_vm->_obj[oPANNELLOM31]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOMA31]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oPANNELLOM31]._anim = 0;
			_vm->_obj[oPANNELLOM31]._examine = 715;
			_vm->_obj[oPANNELLOM31]._action = 716;
			_vm->_obj[oPANNELLOM31]._flag &= ~kObjFlagRoomOut;
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom31, a3118CHIUDEPANNELLO, 3, curObj);
		} else
			retVal = true;
		break;

	case oVALVOLAC34:
	case oVALVOLA34:
		if (_vm->_obj[curObj]._anim)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		else
			retVal = true;
		break;

	case oPROIETTORE35:
		_vm->_room[kRoom35]._flag |= kObjFlagExtra;
		read3D("352.3d"); // After the shock

		_vm->_obj[oRIBELLEA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oDOORC35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[omDOORC35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oPRESA35]._mode &= ~OBJMODE_OBJSTATUS;

		_vm->_obj[oDOORA35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[omDOORA35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oRIBELLES35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oSEDIA35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oMONITOR35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[omPIANO35]._mode |= OBJMODE_OBJSTATUS;

		_vm->_obj[oFRONTOFFICEC35]._anim = a356PROVASPORTELLO;
		_vm->_obj[oASCENSORE35]._flag |= kObjFlagRoomOut;
		_vm->_obj[oASCENSORE35]._anim = a3514ENTRAASCENSORE;

		_vm->_animMgr->_animTab[aBKG35]._flag |= SMKANIM_OFF1;
		_vm->_dialogMgr->playDialog(dF351);
		setPosition(7);
		break;

	case oCOMPUTER36:
		if (!(_vm->_dialogMgr->_choice[646]._flag & kObjFlagDone)) {
			_vm->_dialogMgr->playDialog(dF361);
			_vm->_obj[oCOMPUTER36]._action = 2004;
			retVal = false;
		} else
			retVal = true;
		break;

	case oPULSANTEA35:
	case oPULSANTEB35:
	case oPULSANTEC35:
	case oPULSANTED35:
	case oPULSANTEE35:
	case oPULSANTEF35:
	case oPULSANTEG35:
		_vm->_obj[curObj]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[curObj + 7]._mode |= OBJMODE_OBJSTATUS;
		_comb35[_count35++] = curObj;
		_vm->_soundMgr->play(wPAD5);
		if (_count35 == 7) {
			if (((_comb35[0] == oPULSANTEF35) && (_comb35[1] == oPULSANTED35) && (_comb35[2] == oPULSANTEC35) &&
				 (_comb35[3] == oPULSANTEG35) && (_comb35[4] == oPULSANTEB35) && (_comb35[5] == oPULSANTEA35) &&
				 (_comb35[6] == oPULSANTEE35)) ||
				((_comb35[0] == oPULSANTEE35) &&
				 (_comb35[1] == oPULSANTEA35) && (_comb35[2] == oPULSANTEB35) && (_comb35[3] == oPULSANTEG35) &&
				 (_comb35[4] == oPULSANTEC35) && (_comb35[5] == oPULSANTED35) && (_comb35[6] == oPULSANTEF35))) {
				_vm->_obj[oPULSANTEAA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEBA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTECA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEDA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEEA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEFA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEGA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTIV35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oLEDS35]._mode &= ~OBJMODE_OBJSTATUS;

				_vm->_obj[oFRONTOFFICEA35]._anim = 0;
				_vm->_obj[oFRONTOFFICEA35]._action = 1844;
				_vm->_obj[oFRONTOFFICEA35]._flag |= kObjFlagExtra;
				_vm->_obj[oDOORMC36]._flag |= kObjFlagRoomOut;
				_vm->_obj[oDOORMC36]._anim = a3610APREPORTA;
				_vm->_obj[oSCAFFALE36]._anim = a3615APRENDESCAFFALE;

				_vm->_animMgr->_animTab[aBKG36]._flag |= SMKANIM_OFF2;
				_vm->_animMgr->_animTab[aBKG36]._flag |= SMKANIM_OFF3;
				_vm->_obj[oSCANNERLA36]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oSCANNERLS36]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oSCANNERMA36]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oSCANNERMS36]._mode |= OBJMODE_OBJSTATUS;

				_vm->_soundMgr->play(wWIN35);
			} else {
				_vm->_obj[oPULSANTEA35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEB35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEC35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTED35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEE35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEF35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEG35]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEAA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEBA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTECA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEDA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEEA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEFA35]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTEGA35]._mode &= ~OBJMODE_OBJSTATUS;
			}
			_count35 = 0;
			_comb35[0] = 0;
			_comb35[1] = 0;
			_comb35[2] = 0;
			_comb35[3] = 0;
			_comb35[4] = 0;
			_comb35[5] = 0;
			_comb35[6] = 0;
		}
		_vm->_curObj += 7;
		RegenRoom();
		break;

	case oCARD35:
		_vm->_obj[oPULSANTEA35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEB35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEC35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTED35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEE35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEF35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEG35]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEAA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEBA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTECA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEDA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEEA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEFA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oPULSANTEGA35]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->addIcon(iCARD36);

		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom35, a359RITIRACARD, 6, curObj);
		break;

	case oSCAFFALE36:
		retVal = true;
		break;

	case oFOROC49:
	case oFORO849:
	case oFORO949:
	case oFORO1049:
	case oFORO1149:
	case oFORO1249:
	case oFORO149:
	case oFORO249:
	case oFORO349:
	case oFORO449:
	case oFORO549:
	case oFORO649:
	case oFORO749:
		for (int a = oASTAC49; a <= oASTA749; a++)
			_vm->_obj[a]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oASTAC49 + curObj - oFOROC49]._mode |= OBJMODE_OBJSTATUS;
		_comb49[3] = _comb49[2];
		_comb49[2] = _comb49[1];
		_comb49[1] = _comb49[0];
		_comb49[0] = curObj;
		_vm->_soundMgr->play(wASTA49);
		RegenRoom();
		if ((_comb49[3] == oFORO749) && (_comb49[2] == oFORO849) && (_comb49[1] == oFORO449) && (_comb49[0] == oFORO549)) {
			PaintScreen(0);
			_vm->NlDelay(60);
			_vm->_obj[oOMBRAS49]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oSCOMPARTO49]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oAGENDA49]._mode |= OBJMODE_OBJSTATUS;
			_vm->_obj[oSUNDIAL49]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[oAGENDA49]._examine = 1099;
			_vm->_obj[oAGENDA49]._action = 1100;
			_vm->_flagCharacterExists = true;
			_vm->_curObj = oAGENDA49;
			_vm->playScript(s49SUNDIAL);
		}
		retVal = false;
		break;

	case oASTAC49:
	case oASTA849:
	case oASTA949:
	case oASTA1049:
	case oASTA1149:
	case oASTA1249:
	case oASTA149:
	case oASTA249:
	case oASTA349:
	case oASTA449:
	case oASTA549:
	case oASTA649:
	case oASTA749:
		for (int a = oASTAC49; a <= oASTA749; a++)
			_vm->_obj[a]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[oASTAC49]._mode |= OBJMODE_OBJSTATUS;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom49, a496, 1, curObj);
		retVal = false;
		break;

	case oNUMERO14C:
	case oNUMERO24C:
	case oNUMERO34C:
	case oNUMERO44C:
	case oNUMERO54C:
	case oNUMERO64C:
	case oNUMERO74C:
	case oNUMERO84C:
	case oNUMERO94C:
	case oNUMERO04C: {
		int a;
		for (a = 0; a < 6; a++) {
			if (_comb4CT[a] == 0) {
				_vm->_obj[a + oAST14C]._mode |= OBJMODE_OBJSTATUS;
				_comb4CT[a] = curObj - oNUMERO14C + 1;
				break;
			}
		}
		_vm->_soundMgr->play(wPAD1 + curObj - oNUMERO14C);
		RegenRoom();
		if (a < 5)
			break;
		PaintScreen(0);
		_vm->NlDelay(60);
		if ((_comb4CT[0] == 5) && (_comb4CT[1] == 6) && (_comb4CT[2] == 2) &&
			(_comb4CT[3] == 3) && (_comb4CT[4] == 9) && (_comb4CT[5] == 6)) {
			for (a = 0; a < 6; a++) {
				_comb4CT[a] = 0;
				_vm->_obj[oAST14C + a]._mode &= ~OBJMODE_OBJSTATUS;
			}
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom51, 0, 1, curObj);
			_vm->_flagCharacterExists = true;
		} else {
			for (a = 0; a < 6; a++) {
				_comb4CT[a] = 0;
				_vm->_obj[oAST14C + a]._mode &= ~OBJMODE_OBJSTATUS;
			}
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom4C, 0, 4, curObj);
			_vm->_flagCharacterExists = true;
		}
		retVal = false;
		break;
		}
	case oDOORC4A:
		if (!(_vm->_dialogMgr->_choice[245]._flag & kObjFlagDone) && !(_vm->_dialogMgr->_choice[766]._flag & kObjFlagDone)) {
			_vm->_dialogMgr->_choice[245]._flag &= ~DLGCHOICE_HIDE;
			_vm->_dialogMgr->playDialog(dC4A1);
			setPosition(14);
			_vm->_obj[oDOORC4A]._action = 1117;
			_vm->_obj[oDOORC4A]._anim = 0;
			retVal = false;
		} else
			retVal = true;
		break;

	case oPULSANTE4A:
		if (_vm->_obj[curObj]._anim)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		else if (!(_vm->_dialogMgr->_choice[244]._flag & kObjFlagDone)) {
			_vm->_dialogMgr->_choice[244]._flag &= ~DLGCHOICE_HIDE;
			_vm->_dialogMgr->playDialog(dC4A1);
			_vm->_obj[oPULSANTE4A]._examine = 1108;
			_vm->_obj[oPULSANTE4A]._action = 1109;
			retVal = false;
		} else
			retVal = true;
		break;

	case oWINDOW56:
		if (_vm->_obj[oPANNELLOC56]._mode & OBJMODE_OBJSTATUS)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a5614, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a5614P, 0, 0, curObj);
		break;

	case oPULSANTECD:
		for (int a = oPULSANTE1AD; a <= oPULSANTE33AD; a++) {
			if ((_vm->_obj[a]._goRoom == _vm->_obj[oEXIT41D]._goRoom) ||
				((_vm->_obj[a]._goRoom == kRoom45) && (_vm->_obj[oEXIT41D]._goRoom == kRoom45S))) {
				CharacterSay(903);
				break;
			}

			if (_vm->_obj[a]._goRoom == 0) {
				if (_vm->_obj[oEXIT41D]._goRoom == kRoom45S)
					_vm->_obj[a]._goRoom = kRoom45;
				else
					_vm->_obj[a]._goRoom = _vm->_obj[oEXIT41D]._goRoom;
				_vm->_obj[a]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[a - 40]._mode &= ~OBJMODE_OBJSTATUS;
				RegenRoom();
				break;
			}
		}
		retVal = false;
		break;

	case oDOORC54:
		if (!(_vm->_dialogMgr->_choice[826]._flag & kObjFlagDone)) {
			_vm->_dialogMgr->playDialog(dF541);
			retVal = false;
		} else
			retVal = true;
		break;

	case oLAVATRICEL54:
		if ((_vm->_obj[curObj]._anim) && (_vm->_obj[oSECCHIOS54]._flag & kObjFlagExtra) && (_vm->_obj[oGRATAC54]._mode & OBJMODE_OBJSTATUS) && !(_vm->_dialogMgr->_choice[841]._flag & kObjFlagDone))
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		else
			retVal = true;
		break;

	case oSECCHIOS54:
		if (_vm->_obj[oGRATAC54]._mode & OBJMODE_OBJSTATUS)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a544G, 0, 0, curObj);
		else
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		retVal = false;
		break;

	case oTASTIERA56:
		if (_vm->_dialogMgr->_choice[262]._flag & kObjFlagDone) {
			if (_vm->_obj[od56ALLA59]._mode & OBJMODE_OBJSTATUS)
				CharacterSay(_vm->_obj[curObj]._action);
			else
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a567, 0, 0, curObj);
			retVal = false;
		} else {
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a564, 0, 0, curObj);
			retVal = false;
		}
		break;

	case oLIBRIEG2B:
		if (_vm->_room[kRoom2C]._flag & kObjFlagDone) { // If room 2C has been visited before, take the book
			retVal = false;
			if (_vm->_obj[curObj]._anim)
				doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2B4TAKEBOOK, 0, 0, curObj);
			else
				retVal = true;
		} else { // If room 2C hasn't been visited before, he tells it's useless
			CharacterSay(2014);
			retVal = false;
		}
		break;

	case oTASTIERA58:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom58T, 0, 0, curObj);
		break;

	case oLAVAGNA59:
	case oSIMBOLI59:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom59L, 0, 0, curObj);
		break;

	case oWINDOWA5A:
		if ((_vm->_dialogMgr->_choice[871]._flag & kObjFlagDone) && !(_vm->_dialogMgr->_choice[286]._flag & kObjFlagDone)) {
			_vm->_dialogMgr->playDialog(dC5A1);
			retVal = false;
		} else
			retVal = true;
		break;

	case oWINDOWB5A:
		if (!(_vm->_dialogMgr->_choice[256]._flag & kObjFlagDone)) {
			CharacterSay(1999);
			retVal = false;
		} else
			retVal = true;
		break;

	case oTASTO158:
	case oTASTO258:
	case oTASTO358:
	case oTASTO458:
	case oTASTO558:
	case oTASTO658:
	case oTASTO758:
	case oTASTO858:
	case oTASTO958:
	case oTASTO058:
		retVal = false;
		_comb58[5] = _comb58[4];
		_comb58[4] = _comb58[3];
		_comb58[3] = _comb58[2];
		_comb58[2] = _comb58[1];
		_comb58[1] = _comb58[0];
		_comb58[0] = curObj;

		_vm->_soundMgr->play(wPAD1 + curObj - oTASTO158);
		_vm->_obj[oLED158 + _count58]._mode |= OBJMODE_OBJSTATUS;
		_count58++;
		RegenRoom();
		if (_count58 < 6)
			break;

		PaintScreen(0);
		_vm->NlDelay(60);
		_count58 = 0;
		for (int a = 0; a < 6; a++)
			_vm->_obj[oLED158 + a]._mode &= ~OBJMODE_OBJSTATUS;

		if ((_comb58[0] == oTASTO058) && (_comb58[1] == oTASTO258) && (_comb58[2] == oTASTO358) &&
			(_comb58[3] == oTASTO858) && (_comb58[4] == oTASTO558) && (_comb58[5] == oTASTO958)) {
			_vm->_soundMgr->fadeOut();
			_vm->_dialogMgr->playDialog(dF582);
		} else
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom58, 0, 2, curObj);

		for (int i = 0; i < 6; ++i)
			_comb58[i] = 0;
		break;

	default:
		if (_vm->_obj[curObj]._anim)
			doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, _vm->_obj[curObj]._anim, 0, 0, curObj);
		else
			retVal = true;
		break;
	}

	return retVal;
}

bool LogicManager::mouseTake(uint16 curObj) {
	bool retVal;

	switch (curObj) {
	case oTINFOIL11:
		retVal = false;
		break;
	case oNASTRO15:
		_vm->_obj[oNASTRO15]._flag |= kObjFlagExtra;
		retVal = false;
		break;
	case oMONETA13:
		if (!(_vm->_obj[oLATTINA13]._mode & OBJMODE_OBJSTATUS))
			_vm->_obj[curObj]._anim = a133CPRENDEMONETA;
		retVal = true;
		break;
	case oFOGLIETTO14:
		_vm->_obj[oFOGLIETTO14]._flag |= kObjFlagExtra;
		_vm->_obj[oMAPPA16]._examine = 152;
		retVal = false;
		break;
	case oPOSTERC22:
		_vm->_obj[oARMADIETTOCC22]._anim = a221;
		_vm->_obj[oARMADIETTOCA22]._anim = a222;
		retVal = true;
		break;
	case oKEY22:
		_vm->_obj[oARMADIETTORA22]._examine = 2013;
		retVal = true;
		break;
	default:
		retVal = true;
		break;
	}

	return retVal;
}

bool LogicManager::mouseTalk(uint16 curObj) {
	bool retVal = true;

	switch (curObj) {
	case oTICKETOFFICE16:
		if ((_vm->_obj[oFINGERPADP16]._flag & kObjFlagRoomOut) && (_vm->_dialogMgr->_choice[50]._flag & kObjFlagDone)) {
			CharacterSay(147);
			retVal = false;
			break;
		}

		if ((_vm->_dialogMgr->_choice[49]._flag & DLGCHOICE_HIDE) && (_vm->_dialogMgr->_choice[50]._flag & DLGCHOICE_HIDE)) {
			if (_vm->_obj[oMAPPA16]._flag & kObjFlagExtra) {
				_vm->_dialogMgr->_choice[46]._flag &= ~DLGCHOICE_HIDE;
				_vm->_dialogMgr->_choice[48]._flag &= ~DLGCHOICE_HIDE;
				_vm->_obj[oTICKETOFFICE16]._flag |= kObjFlagExtra;
			}
			else {
				if (_vm->_dialogMgr->_choice[46]._flag & kObjFlagDone) {
					CharacterSay(_vm->_obj[oTICKETOFFICE16]._action);
					retVal = false;
					break;
				}

				_vm->_dialogMgr->_choice[46]._flag &= ~DLGCHOICE_HIDE;
				_vm->_dialogMgr->_choice[47]._flag &= ~DLGCHOICE_HIDE;
			}
		}
		break;

	case ocGUARD18:
		_vm->_obj[ocGUARD18]._flag &= ~kObjFlagPerson;
		_vm->_obj[ocGUARD18]._action = 227;
		_vm->_obj[oDOORC18]._action = 220;
		break;

	case ocNEGOZIANTE1A:
		for (int c = _vm->_dialogMgr->_dialog[dSHOPKEEPER1A]._firstChoice; c < (_vm->_dialogMgr->_dialog[dSHOPKEEPER1A]._firstChoice + _vm->_dialogMgr->_dialog[dSHOPKEEPER1A]._choiceNumb); c++) {
			if (!(_vm->_dialogMgr->_choice[c]._flag & DLGCHOICE_HIDE)) {
				_vm->_dialogMgr->playDialog(_vm->_obj[curObj]._goRoom);
				retVal = false;
				return retVal;
			}
		}

		if (_vm->_obj[ocNEGOZIANTE1A]._action) {
			CharacterSay(_vm->_obj[ocNEGOZIANTE1A]._action);
			retVal = false;
		}
		break;

	case ocEVA19:
		_vm->_inventoryObj[iSAM]._action = 1415;
		break;

	default:
		break;
	}

	return retVal;
}

bool LogicManager::mouseClick(uint16 curObj) {
	bool retVal;
	if ((_vm->_curRoom == kRoom1D) && !(_vm->_room[kRoom1D]._flag & kObjFlagExtra) && (curObj != oSCALA1D)) {
		_vm->_curObj = oDONNA1D;
		goToPosition(_vm->_obj[oDONNA1D]._position);
		retVal = true;
	} else if ((_vm->_curRoom == kRoom2B) && (_vm->_room[kRoom2B]._flag & kObjFlagExtra) && (curObj != oCARTELLO2B) && (curObj != od2BALLA28)) {
		_vm->_curObj = oDOOR2B;
		goToPosition(_vm->_obj[oCARTELLO2B]._position);
		retVal = true;
	} else {
		switch (curObj) {
		case oDOORA13:
			if (_vm->_mouseRightBtn && (_vm->_room[kRoom14]._flag & kObjFlagDone)) {
				if (_characterGoToPosition != 4)
					goToPosition(4);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oDIVANO14:
			if (_vm->_mouseLeftBtn) {
				if (_characterGoToPosition != 2)
					goToPosition(2);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oSCAFFALE1D:
			if (_vm->_mouseRightBtn) {
				if (_characterGoToPosition != 9)
					goToPosition(9);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oDIVANOR4A:
			if (_vm->_mouseRightBtn) {
				if (_characterGoToPosition != 1)
					goToPosition(1);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oDOORC21:
			if ((_vm->_useWith[USED] == iPISTOLA15) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 1)
					goToPosition(1);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oTUBO21:
			if ((_vm->_useWith[USED] == oRAMPINO21) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 4)
					goToPosition(4);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oCAMPO23:
			if ((_vm->_useWith[USED] == oCAVIE23) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 2)
					goToPosition(2);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oTASTO2F:
			if ((_vm->_useWith[USED] == iTELECOMANDO2G) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 9)
					goToPosition(9);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oSAMA33:
		case oSERRATURA33:
			if ((_vm->_useWith[USED] == oTUBET33) && (_vm->_obj[oVALVOLA34]._mode & OBJMODE_OBJSTATUS)
			&& (_vm->_obj[oSAMA33]._mode & OBJMODE_OBJSTATUS) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 4)
					goToPosition(4);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oWINDOW33:
			if (_vm->_mouseLeftBtn) {
				if (_characterGoToPosition != 7)
					goToPosition(7);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oPRESA35:
			if (!_vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 2)
					goToPosition(2);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oTRIPLA35:
			if (!_vm->_flagUseWithStarted && _vm->_mouseLeftBtn) {
				if (_characterGoToPosition != 2)
					goToPosition(2);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oPORTALC36:
			if ((_vm->_useWith[USED] == iSTETOSCOPIO) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 8)
					goToPosition(8);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oSERBATOIOA2G:
			if ((_vm->_useWith[USED] == iCANDELOTTO) && (_vm->_inventoryObj[iBOMBOLA]._flag & kObjFlagExtra) && (_vm->_inventoryObj[iLATTINA28]._flag & kObjFlagExtra) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 6)
					goToPosition(6);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oRAGNO41:
			if ((_vm->_useWith[USED] == iMARTELLO) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 1)
					goToPosition(1);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oTAMBURO43:
			if ((_vm->_useWith[USED] == iMAZZA) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 5)
					goToPosition(5);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oLUCCHETTO53:
			if ((_vm->_useWith[USED] == iLASER35) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 2)
					goToPosition(2);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		case oDOOR58C55:
			if ((_vm->_useWith[USED] == iCHIAVI) && _vm->_flagUseWithStarted) {
				if (_characterGoToPosition != 2)
					goToPosition(2);
			} else if (_characterGoToPosition != _vm->_obj[curObj]._position)
				goToPosition(_vm->_obj[curObj]._position);

			retVal = true;
			break;

		default:
			if (_vm->_obj[curObj]._position == -1) {
				_characterGoToPosition = -1;
				retVal = false;
			} else {
				if (_characterGoToPosition != _vm->_obj[curObj]._position)
					goToPosition(_vm->_obj[curObj]._position);
				retVal = true;
			}
			break;
		}

		if (_vm->_room[_vm->_curRoom]._flag & kObjFlagExtra) {
			if ((curObj == oTUBO21) || (curObj == oCARTELLONE21) || (curObj == oESSE21)
			|| (curObj == oRAMPINO21) || (curObj == oCATENA21) || (curObj == od21TO22)
			|| (curObj == oDOORC21) || (curObj == oDOORA21) || (curObj == oCUNICOLO21)
			|| (curObj == od24TO23) || (curObj == od2ETO2C) || (curObj == od2GVALLA26)) {
				_characterGoToPosition = -1;
				retVal = true;
			}
		} else if ((curObj == od21TO23) || (curObj == od24TO26) || (curObj == oENTRANCE2E)
		|| (curObj == oCARTELLO2B) || (curObj == oFRONTOFFICEC35) || (curObj == oFRONTOFFICEA35)
		|| (curObj == oASCENSORE35) || (curObj == oGIORNALE35)) {
			_characterGoToPosition = -1;
			retVal = true;
		}
	}
	return retVal;
}

bool LogicManager::operateInventory() {
	bool printSentence = true;

	switch (_vm->_curInventory) {
	case iSAM:
		if ((_vm->_dialogMgr->_choice[166]._flag & kObjFlagDone) && ((_vm->_curRoom == kRoom17) || (_vm->_curRoom == kRoom1B) || (_vm->_curRoom == kRoom1C) || (_vm->_curRoom == kRoom1D))) {
			if (_vm->_obj[oNUMERO17]._mode & OBJMODE_OBJSTATUS) {
				if (!(_vm->_dialogMgr->_choice[196]._flag & kObjFlagDone)) {
					if (_vm->_curRoom == kRoom17) {
						if (_vm->_dialogMgr->_choice[198]._flag & kObjFlagDone) {
							_vm->_inventoryObj[iSAM]._action = 1787;
							printSentence = true;
						} else {
							_vm->_dialogMgr->_choice[197]._flag |= DLGCHOICE_HIDE;
							_vm->_dialogMgr->_choice[198]._flag &= ~DLGCHOICE_HIDE;
							_vm->_dialogMgr->playDialog(dSAM17);
							printSentence = false;
							_vm->_obj[oFAX17]._mode |= OBJMODE_OBJSTATUS;
						}
					} else {
						if (_vm->_dialogMgr->_choice[199]._flag & kObjFlagDone) {
							_vm->_inventoryObj[iSAM]._action = 1787;
							printSentence = true;
						} else {
							_vm->_dialogMgr->_choice[197]._flag |= DLGCHOICE_HIDE;
							_vm->_dialogMgr->_choice[199]._flag &= ~DLGCHOICE_HIDE;
							_vm->_dialogMgr->playDialog(dSAM17);
							printSentence = false;
							_vm->_obj[oFAX17]._mode |= OBJMODE_OBJSTATUS;
						}
					}
				} else {
					if ((_vm->_dialogMgr->_choice[198]._flag & kObjFlagDone) || (_vm->_dialogMgr->_choice[199]._flag & kObjFlagDone)) {
						_vm->_inventoryObj[iSAM]._action = 1787;
						printSentence = true;
					} else if (_vm->_curRoom == kRoom17) {
						if (_vm->_dialogMgr->_choice[201]._flag & kObjFlagDone) {
							_vm->_inventoryObj[iSAM]._action = 1787;
							printSentence = true;
						} else {
							_vm->_dialogMgr->_choice[201]._flag &= ~DLGCHOICE_HIDE;
							_vm->_dialogMgr->playDialog(dSAM17);
							printSentence = false;
							_vm->_obj[oFAX17]._mode |= OBJMODE_OBJSTATUS;
						}
					} else {
						if (_vm->_dialogMgr->_choice[200]._flag & kObjFlagDone) {
							_vm->_inventoryObj[iSAM]._action = 1787;
							printSentence = true;
						} else {
							_vm->_dialogMgr->_choice[200]._flag &= ~DLGCHOICE_HIDE;
							_vm->_dialogMgr->playDialog(dSAM17);
							printSentence = false;
							_vm->_obj[oFAX17]._mode |= OBJMODE_OBJSTATUS;
						}
					}
				}
			} else if (_vm->_dialogMgr->_choice[197]._flag & kObjFlagDone) {
				_vm->_inventoryObj[iSAM]._action = 1786;
				printSentence = true;
			} else {
				_vm->_dialogMgr->playDialog(dSAM17);
				printSentence = false;
			}
		}
		break;

	case iMAPPA17:
		if (_vm->_curRoom == kRoom23A) {
			CharacterSay(361);
			printSentence = false;
		} else
			printSentence = true;
		break;

	case iLIBRO:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom2BL, 0, 0, _vm->_useWith[WITH]);
		_vm->_obj[oEXIT2BL]._goRoom = _vm->_curRoom;
		actorStop();
		nextStep();
		printSentence = false;
		break;

	case iFOGLIO36:
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom36F, 0, 0, _vm->_useWith[WITH]);
		_vm->_obj[oEXIT36F]._goRoom = _vm->_curRoom;
		actorStop();
		nextStep();
		printSentence = false;
		break;

	case iDISLOCATORE:
		for (int a = oROOM41; a <= oROOM45B; a++)
			_vm->_obj[a]._mode &= ~OBJMODE_OBJSTATUS;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom41D, 0, 0, _vm->_useWith[WITH]);
		_vm->_obj[oEXIT41D]._goRoom = _vm->_curRoom;
		_vm->_inventoryObj[iDISLOCATORE]._flag &= ~kObjFlagExtra;
		actorStop();
		nextStep();
		printSentence = false;
		break;

	case iCODICE:
		_vm->_obj[oEXIT58M]._goRoom = _vm->_curRoom;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom58M, 0, 0, _vm->_useWith[WITH]);
		actorStop();
		nextStep();
		printSentence = false;
		break;

	case iTELECOMANDO44:
		if ((_vm->_actor->_px < 5057.6) && (_vm->_obj[oPUPAZZO44]._mode & OBJMODE_OBJSTATUS) && (_vm->_curRoom == kRoom43)) {
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom46, 0, 7, _vm->_useWith[WITH]);
			printSentence = false;
		}
		break;

	case iMAPPA50:
		if ((_vm->_curRoom >= kRoom51) && (_vm->_curRoom <= kRoom5A))
			_vm->_inventoryObj[iMAPPA50]._action = 1725 + (_vm->_curRoom - kRoom51);
		printSentence = true;
		break;
	default:
		break;
	}

	return printSentence;
}

void LogicManager::doMouseGame() {
	// For the wheel in 2C
	if ((_vm->_curObj >= oWHEEL1A2C) && (_vm->_curObj <= oWHEEL12C2C))
		ShowObjName((oWHEEL1A2C % 3) + oWHEELA2C, true);
	// For the displacer
	else if (_vm->_curRoom == kRoom41D) {
		if ((_vm->_curObj >= oPULSANTE1AD) && (_vm->_curObj <= oPULSANTE33AD)) {
			if (!(_vm->_obj[oROOM41 + _vm->_obj[_vm->_curObj]._goRoom - kRoom41]._mode & OBJMODE_OBJSTATUS)) {
				for (int a = oROOM41; a <= oROOM4X; a++) {
					if (_vm->_obj[a]._mode & OBJMODE_OBJSTATUS)
						_vm->_obj[a]._mode &= ~OBJMODE_OBJSTATUS;
				}
				_vm->_obj[oROOM45B]._mode &= ~OBJMODE_OBJSTATUS;

				if ((oROOM41 + _vm->_obj[_vm->_curObj]._goRoom - kRoom41 == oROOM45) && (_vm->_obj[od44ALLA45]._goRoom == kRoom45S))
					_vm->_obj[oROOM45B]._mode |= OBJMODE_OBJSTATUS;
				else
					_vm->_obj[oROOM41 + _vm->_obj[_vm->_curObj]._goRoom - kRoom41]._mode |= OBJMODE_OBJSTATUS;
				RegenRoom();
			}
		} else {
			for (int a = oROOM41; a <= oROOM4X; a++) {
				if (_vm->_obj[a]._mode & OBJMODE_OBJSTATUS)
					_vm->_obj[a]._mode &= ~OBJMODE_OBJSTATUS;
			}
			_vm->_obj[oROOM45B]._mode &= ~OBJMODE_OBJSTATUS;

			RegenRoom();
		}
		ShowObjName(_vm->_curObj, true);
	} else
		// not a wheel nor the displacer
		ShowObjName(_vm->_curObj, true);

	if (_vm->_inventoryStatus == INV_INACTION)
		doEvent(MC_INVENTORY, ME_CLOSE, MP_DEFAULT, 0, 0, 0, 0);
}

bool LogicManager::doMouseInventory() {
	bool retVal = false;
	// Inventory area
	if (!_vm->_flagCharacterExists && ((_vm->_curRoom != kRoom31P) && (_vm->_curRoom != kRoom35P)))
		retVal = true; // When it's in a room without a character, such as the map
	return retVal;
}

void LogicManager::doMouseLeftRight() {
	//  for the displacer
	if ((_vm->_curObj >= oPULSANTE1AD) && (_vm->_curObj <= oPULSANTE33AD)) {
		if ((_vm->_obj[_vm->_curObj]._goRoom == kRoom45) && (_vm->_obj[od44ALLA45]._goRoom == kRoom45S) &&
			(_vm->_obj[oEXIT41D]._goRoom == kRoom45S) && (_vm->_curMessage->_event == ME_MRIGHT))
			doEvent(MC_ACTION, ME_MOUSEOPERATE, MP_DEFAULT, 0, 0, 0, _vm->_curObj);
		else if ((_vm->_obj[_vm->_curObj]._goRoom == kRoom45) && (_vm->_obj[od44ALLA45]._goRoom == kRoom45S) &&
				 (_vm->_obj[oEXIT41D]._goRoom != kRoom45S) && (_vm->_curMessage->_event == ME_MRIGHT)) {
			_vm->_obj[oEXIT41D]._goRoom = kRoom45S;
			_vm->_inventoryObj[iDISLOCATORE]._flag |= kObjFlagExtra;
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, kRoom45S, 0, 0, _vm->_curObj);
		} else if (_vm->_obj[oEXIT41D]._goRoom != _vm->_obj[_vm->_curObj]._goRoom && (_vm->_curMessage->_event == ME_MRIGHT)) {
			_vm->_obj[oEXIT41D]._goRoom = _vm->_obj[_vm->_curObj]._goRoom;
			_vm->_inventoryObj[iDISLOCATORE]._flag |= kObjFlagExtra;
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[oEXIT41D]._goRoom, 0, 0, _vm->_curObj);
		} else if ((_vm->_curMessage->_event == ME_MLEFT) && _vm->_curObj)
			doEvent(MC_ACTION, ME_MOUSEEXAMINE, MP_DEFAULT, 0, 0, 0, _vm->_curObj);
		else if ((_vm->_curMessage->_event == ME_MRIGHT) && _vm->_curObj)
			doEvent(MC_ACTION, ME_MOUSEOPERATE, MP_DEFAULT, 0, 0, 0, _vm->_curObj);
		return;
	}
	// end of displacer

	if (_vm->_curRoom == kRoom52) {
		// snake escape 52
		if (_vm->_obj[oSNAKEU52]._mode & OBJMODE_OBJSTATUS) {
			if (GAMEAREA(_vm->_curMessage->_u16Param2) && !_vm->_flagUseWithStarted && (_vm->_curObj != oSNAKEU52)) {
				StartCharacterAction(a526, 0, 1, 0);
				_vm->_obj[oSCAVO51]._anim = a516;
				_vm->_snake52.set(_vm->_curMessage);
				return;
			}
		}
	} else if (_vm->_curRoom == kRoomControlPanel) {
		// Sys
		_vm->CheckMask(_vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2);
		DoSys(_vm->_curObj);
		return;
	}

	// If it's in a room without a character, like a map or a book
	if (!_vm->_flagCharacterExists) {
		if ((isInventoryArea(_vm->_curMessage->_u16Param2)) && ((_vm->_curRoom == kRoom31P) || (_vm->_curRoom == kRoom35P))) {
			if (ICONAREA(_vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2)
			&& (_vm->whatIcon(_vm->_curMessage->_u16Param1)) && (_vm->_inventoryStatus == INV_INACTION)) {
				_vm->_useWith[WITH] = 0;
				_vm->_curObj = 0;
				_vm->_lightIcon = 0xFF;
				_vm->setInventoryStart(_vm->_iconBase, INVENTORY_SHOW);
				if (_vm->_curMessage->_event == ME_MRIGHT || _vm->_flagUseWithStarted)
					doEvent(MC_INVENTORY, ME_OPERATEICON, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
				else
					doEvent(MC_INVENTORY, ME_EXAMINEICON, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
			}
			return;
		}

		if ((_vm->_curMessage->_event == ME_MLEFT) && _vm->_curObj)
			doEvent(MC_ACTION, ME_MOUSEEXAMINE, MP_DEFAULT, 0, 0, 0, _vm->_curObj);
		else if ((_vm->_curMessage->_event == ME_MRIGHT) && _vm->_curObj)
			doEvent(MC_ACTION, ME_MOUSEOPERATE, MP_DEFAULT, 0, 0, 0, _vm->_curObj);

		return;
	}

	// Special management for 2C wheels
	if ((_vm->_obj[oBASEWHEELS2C]._mode & OBJMODE_OBJSTATUS) && (_vm->_curRoom == kRoom2C)) {
		if (_vm->CheckMask(_vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2)) {
			if ((_vm->_curObj >= oWHEEL1A2C) && (_vm->_curObj <= oWHEEL12C2C))
				_wheel = (_vm->_curObj - oWHEEL1A2C) % 3;
			else if (_vm->_curObj == oPULSANTE2C) {
				if (_vm->_curMessage->_event == ME_MLEFT) {
					doEvent(MC_ACTION, ME_MOUSEEXAMINE, MP_DEFAULT, 0, 0, 0, _vm->_curObj);
					return;
				}
				_vm->_animMgr->_animTab[aBKG2C]._flag &= ~SMKANIM_OFF1;
				_vm->_obj[oBASEWHEELS2C]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[omWHEELS2C]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[oPULSANTE2C]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[_wheelPos[0] * 3 + 0 + oWHEEL1A2C]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[_wheelPos[1] * 3 + 1 + oWHEEL1A2C]._mode &= ~OBJMODE_OBJSTATUS;
				_vm->_obj[_wheelPos[2] * 3 + 2 + oWHEEL1A2C]._mode &= ~OBJMODE_OBJSTATUS;

				_vm->_obj[oCAMPO2C]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oTEMPIO2C]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oLEONE2C]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oSFINGE2C]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oSTATUA2C]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[od2CALLA2E]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oCARTELLOA2C]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[od2CALLA26]._mode |= OBJMODE_OBJSTATUS;
				_vm->_obj[oWHEELS2C]._mode |= OBJMODE_OBJSTATUS;
				_vm->_flagShowCharacter = true;
				RegenRoom();
				_vm->_animMgr->startSmkAnim(_vm->_room[_vm->_curRoom]._bkgAnim);

				// right combination
				if ((_wheelPos[0] == 7) && (_wheelPos[1] == 5) && (_wheelPos[2] == 11)) {
					doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2C6PREMEPULSANTEAPERTURA, 0, 0, _vm->_curObj);
					_vm->_obj[oSFINGE2C]._flag &= ~kObjFlagPerson;
				} else
					doEvent(MC_CHARACTER, ME_CHARACTERACTION, MP_DEFAULT, a2C6PREMEPULSANTE, 0, 0, _vm->_curObj);

				return;
			} else
				return;

			if (_vm->_curMessage->_event == ME_MLEFT)
				_wheelPos[_wheel] = (_wheelPos[_wheel] > 10) ? 0 : _wheelPos[_wheel] + 1;
			if (_vm->_curMessage->_event == ME_MRIGHT)
				_wheelPos[_wheel] = (_wheelPos[_wheel] < 1) ? 11 : _wheelPos[_wheel] - 1;

			_vm->_soundMgr->play(wWHEELS2C);
			_vm->_obj[_vm->_curObj]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[_wheelPos[_wheel] * 3 + _wheel + oWHEEL1A2C]._mode |= OBJMODE_OBJSTATUS;
			RegenRoom();
		}
		return;
	}

	//	Game area
	if (GAMEAREA(_vm->_curMessage->_u16Param2) && !_vm->_animMgr->_playingAnims[kSmackerAction]) {
		if (_vm->_flagscriptactive)
			_vm->_curObj = _vm->_curMessage->_u32Param;

		int pmousex = _vm->_curMessage->_u16Param1;
		int pmousey = _vm->_curMessage->_u16Param2;
		if (!_vm->_logicMgr->mouseClick(_vm->_curObj)) {
			if (_vm->CheckMask(_vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2)) {
				if ((_vm->_obj[_vm->_curObj]._lim.right - _vm->_obj[_vm->_curObj]._lim.left) < MAXX / 7) {
					pmousex = (_vm->_obj[_vm->_curObj]._lim.left + _vm->_obj[_vm->_curObj]._lim.right) / 2;
					pmousey = ((_vm->_obj[_vm->_curObj]._lim.top + _vm->_obj[_vm->_curObj]._lim.bottom) / 2) + TOP;
				}
			}
			whereIs(pmousex, pmousey);
			findPath();
		}
		_vm->_characterQueue.initQueue();

		if (_vm->CheckMask(_vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2) && !_vm->_flagDialogActive) {
			if ((_vm->_curRoom == kRoom1D) && !(_vm->_room[kRoom1D]._flag & kObjFlagExtra) && (_vm->_curObj != oSCALA1D))
				_vm->_curObj = oDONNA1D;
			else if ((_vm->_curRoom == kRoom2B) && (_vm->_room[kRoom2B]._flag & kObjFlagExtra) && (_vm->_curObj != oCARTELLO2B) && (_vm->_curObj != od2BALLA28)) {
				_vm->clearText();
				_vm->_curObj = oDOOR2B;
				StartCharacterAction(a2B1PROVAAPRIREPORTA, 0, 0, 0);
				if (_vm->_flagUseWithStarted) {
					if (_vm->_useWithInv[USED]) {
						_vm->_lightIcon = 0xFF;
						_vm->_animMgr->smkStop(kSmackerIcon);
						_vm->setInventoryStart(_vm->_inventoryRefreshStartIcon, INVENTORY_HIDE);
						_vm->_flagInventoryLocked = false;
					}
					_vm->_useWith[USED] = 0;
					_vm->_useWith[WITH] = 0;
					_vm->_useWithInv[USED] = false;
					_vm->_useWithInv[WITH] = false;
					_vm->_flagUseWithStarted = false;
					_vm->clearText();
				}
				return;
			} else if ((_vm->_curRoom == kRoom35) && !(_vm->_room[kRoom35]._flag & kObjFlagExtra) && ((_vm->_curObj == oFRONTOFFICEC35)
				|| (_vm->_curObj == oFRONTOFFICEA35) || (_vm->_curObj == oASCENSORE35) || (_vm->_curObj == oMONITOR35)
				|| (_vm->_curObj == oSEDIA35) || (_vm->_curObj == oRIBELLEA35) || (_vm->_curObj == oCOMPUTER35) || (_vm->_curObj == oGIORNALE35))) {
				_vm->_curObj = oLASTLEV5;
				doEvent(MC_CHARACTER, ME_CHARACTERGOTOEXAMINE, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, _vm->_curObj);
				if (_vm->_flagUseWithStarted) {
					if (_vm->_useWithInv[USED]) {
						_vm->_lightIcon = 0xFF;
						_vm->_animMgr->smkStop(kSmackerIcon);
						_vm->setInventoryStart(_vm->_inventoryRefreshStartIcon, INVENTORY_HIDE);
						_vm->_flagInventoryLocked = false;
					}
					_vm->_useWith[USED] = 0;
					_vm->_useWith[WITH] = 0;
					_vm->_useWithInv[USED] = false;
					_vm->_useWithInv[WITH] = false;
					_vm->_flagUseWithStarted = false;
					_vm->clearText();
				}
				return;
			} else if ((_vm->_curMessage->_event == ME_MLEFT) &&
					   ((!(_vm->_room[_vm->_curRoom]._flag & kObjFlagExtra) && ((_vm->_curObj == oENTRANCE2E) || (_vm->_curObj == od24TO26) || (_vm->_curObj == od21TO23 && !(_vm->_obj[_vm->_curObj]._flag & kObjFlagExamine)))) ||
						((_vm->_room[_vm->_curRoom]._flag & kObjFlagExtra) && ((_vm->_curObj == od2ETO2C) || (_vm->_curObj == od24TO23) || (_vm->_curObj == od21TO22 && !(_vm->_obj[_vm->_curObj]._flag & kObjFlagExamine)) || (_vm->_curObj == od2GVALLA26))))) {
				doEvent(MC_CHARACTER, ME_CHARACTERGOTO, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
				return;
			}

			if (_vm->_curMessage->_event == ME_MRIGHT) {
				if (!(_vm->_obj[_vm->_curObj]._flag & kObjFlagExamine) && (_vm->_curObj != 0)) {
					if (_vm->_flagUseWithStarted) {
						doEvent(MC_CHARACTER, ME_CHARACTERGOTO, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
						return;
					}
					if (_vm->_obj[_vm->_curObj]._flag & kObjFlagRoomIn)
						doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[_vm->_curObj]._goRoom, _vm->_obj[_vm->_curObj]._anim, _vm->_obj[_vm->_curObj]._ninv, _vm->_curObj);
					else if (_vm->_obj[_vm->_curObj]._flag & kObjFlagRoomOut)
						doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[_vm->_curObj]._goRoom, 0, _vm->_obj[_vm->_curObj]._ninv, _vm->_curObj);
					actorStop();
					nextStep();
					_vm->_obj[_vm->_curObj]._flag |= kObjFlagDone;
				} else if (_vm->_obj[_vm->_curObj]._flag & kObjFlagUseWith) {
					_characterGoToPosition = -1;
					actorStop();
					nextStep();
					doEvent(MC_ACTION, ME_MOUSEOPERATE, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, _vm->_curObj);
				} else
					doEvent(MC_CHARACTER, ME_CHARACTERGOTOACTION, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, _vm->_curObj);
			} else
				doEvent(MC_CHARACTER, ME_CHARACTERGOTOEXAMINE, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, _vm->_curObj);
		} else
			doEvent(MC_CHARACTER, ME_CHARACTERGOTO, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
	} else if (isInventoryArea(_vm->_curMessage->_u16Param2)) {
		// Inventory area
		if (_vm->_animMgr->_playingAnims[kSmackerAction] || _vm->_flagDialogActive || _vm->_curRoom == kRoomControlPanel)
			return;

		if (ICONAREA(_vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2) && _vm->whatIcon(_vm->_curMessage->_u16Param1) && (_vm->_inventoryStatus == INV_INACTION)) {
			_vm->_characterQueue.initQueue();
			actorStop();
			nextStep();
			doEvent(MC_CHARACTER, ME_CHARACTERGOTOACTION, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
			_vm->_useWith[WITH] = 0;
			_vm->_curObj = 0;
			_vm->_lightIcon = 0xFF;
			_vm->setInventoryStart(_vm->_iconBase, INVENTORY_SHOW);
			if (_vm->_curMessage->_event == ME_MRIGHT || _vm->_flagUseWithStarted)
				doEvent(MC_INVENTORY, ME_OPERATEICON, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
			else
				doEvent(MC_INVENTORY, ME_EXAMINEICON, MP_DEFAULT, _vm->_curMessage->_u16Param1, _vm->_curMessage->_u16Param2, 0, 0);
		}
	}
}

void LogicManager::doSystemChangeRoom() {
	if ((_vm->_curRoom == kRoom41D) && (_vm->_oldRoom != _vm->_curMessage->_u16Param1))
		_vm->_graphicsMgr->NlDissolve(30);

	_vm->_oldRoom = _vm->_curRoom;
	_vm->_curRoom = _vm->_curMessage->_u16Param1;
	_vm->_gameQueue.initQueue();
	_vm->_animQueue.initQueue();
	_vm->_characterQueue.initQueue();
	_vm->_lastCurInventory = 0;
	_vm->_lastLightIcon = 0xFF;
	_vm->_inventoryStatus = INV_OFF;
	_vm->_lightIcon = 0xFF;
	_vm->_flagInventoryLocked = false;
	_vm->_inventoryRefreshStartLine = INVENTORY_HIDE;
	_vm->_inventoryCounter = INVENTORY_HIDE;
	_vm->setInventoryStart(_vm->_inventoryRefreshStartIcon, INVENTORY_HIDE);
	_vm->_flagCharacterExists = true;
	_vm->_flagShowCharacter = true;
	_vm->_animMgr->smkStop(kSmackerIcon);
	_vm->_useWith[USED] = 0;
	_vm->_useWith[WITH] = 0;
	_vm->_useWithInv[USED] = false;
	_vm->_useWithInv[WITH] = false;
	_vm->_flagUseWithStarted = false;
	_vm->_lightIcon = 0xFF;
	_vm->_flagCharacterSpeak = false;
	_vm->_flagSomeoneSpeaks = false;
	actorStop();
	nextStep();

	// Handle exit velocity in dual rooms level 2
	if (_vm->_room[_vm->_oldRoom]._flag & kObjFlagExtra) {
		switch (_vm->_curObj) {
		case od2ETO2C:
			_vm->setRoom(kRoom2E, false);
			break;
		case od24TO23:
			_vm->setRoom(kRoom24, false);
			break;
		case od21TO22:
			_vm->setRoom(kRoom21, false);
			break;
		case od2GVALLA26:
			_vm->setRoom(kRoom2GV, false);
			break;
		default:
			break;
		}
	} else {
		switch (_vm->_curObj) {
		case oENTRANCE2E:
			_vm->setRoom(kRoom2E, true);
			break;
		case od24TO26:
			_vm->setRoom(kRoom24, true);
			break;
		case od21TO23:
			_vm->setRoom(kRoom21, true);
			break;
		default:
			break;
		}
	}

	if (_vm->_curRoom == kRoom12 && _vm->_oldRoom == kRoom11)
		_vm->_animMgr->_animTab[aBKG11]._flag |= SMKANIM_OFF1;
	else if (_vm->_oldRoom == kRoom2BL || _vm->_oldRoom == kRoom36F)
		_vm->_oldRoom = _vm->_curRoom;
	else if (_vm->_curRoom == kRoomControlPanel) {
		bool speechON = !ConfMan.getBool("speech_mute");
		bool textON = ConfMan.getBool("subtitles");
		int speechVol = ConfMan.getInt("speech_volume");
		int musicVol = ConfMan.getInt("music_volume");
		int sfxVol = ConfMan.getInt("sfx_volume");

		if (speechON)
			_vm->_obj[o00SPEECHON]._mode |= OBJMODE_OBJSTATUS;
		else
			_vm->_obj[o00SPEECHOFF]._mode |= OBJMODE_OBJSTATUS;

		if (textON)
			_vm->_obj[o00TEXTON]._mode |= OBJMODE_OBJSTATUS;
		else
			_vm->_obj[o00TEXTOFF]._mode |= OBJMODE_OBJSTATUS;

		_vm->_obj[o00SPEECH1D + (speechVol / 51) * 2]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[o00MUSIC1D + (musicVol) / 51 * 2]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[o00SOUND1D + (sfxVol / 51) * 2]._mode |= OBJMODE_OBJSTATUS;

		if (speechVol < 256)
			_vm->_obj[o00SPEECH1D + (speechVol / 51) * 2 + 1]._mode |= OBJMODE_OBJSTATUS;
		if (musicVol < 256)
			_vm->_obj[o00MUSIC1D + (musicVol) / 51 * 2 + 1]._mode |= OBJMODE_OBJSTATUS;
		if (sfxVol < 256)
			_vm->_obj[o00SOUND1D + (sfxVol / 51) * 2 + 1]._mode |= OBJMODE_OBJSTATUS;
	}

	ReadLoc();
	_vm->showCursor();

	if (_vm->_curRoom == kRoom21) {
		switch (_vm->_oldRoom) {
		case kRoom22:
			_vm->setRoom(kRoom21, false);
			break;
		case kRoom23A:
		case kRoom23B:
			_vm->setRoom(kRoom21, true);
			break;
		}
	} else if (_vm->_curRoom == kRoom24) {
		switch (_vm->_oldRoom) {
		case kRoom23A:
		case kRoom23B:
			_vm->setRoom(kRoom24, false);
			break;
		case kRoom26:
			_vm->setRoom(kRoom24, true);
			break;
		}
	} else if (_vm->_curRoom == kRoom2A) {
		switch (_vm->_oldRoom) {
		case kRoom25:
			_vm->setRoom(kRoom2A, true);
			break;
		case kRoom2B:
		case kRoom29:
		case kRoom29L:
			_vm->setRoom(kRoom2A, false);
			break;
		}
	} else if (_vm->_curRoom == kRoom2B) {
		switch (_vm->_oldRoom) {
		case kRoom28:
			_vm->setRoom(kRoom2B, true);
			break;
		case kRoom2A:
			_vm->setRoom(kRoom2B, false);
			break;
		}
	}
	//			for save/load
	else if (_vm->_room[_vm->_curRoom]._flag & kObjFlagExtra) {
		switch (_vm->_curRoom) {
		case kRoom15: read3D("152.3d"); break;
		case kRoom17: read3D("172.3d"); break;
		case kRoom1D: read3D("1d2.3d"); break;
		case kRoom21: read3D("212.3d"); break;
		case kRoom24: read3D("242.3d"); break;
		case kRoom28: read3D("282.3d"); break;
		case kRoom2A: read3D("2A2.3d"); break;
		case kRoom2B: read3D("2B2.3d"); break;
		case kRoom2E: read3D("2E2.3d"); break;
		case kRoom2GV: read3D("2GV2.3d"); break;
		case kRoom35: read3D("352.3d"); break;
		case kRoom37: read3D("372.3d"); break;
		case kRoom4P: read3D("4P2.3d"); break;
		default:
			break;
		}
	}
}

void LogicManager::DoSys(uint16 curObj) {
	switch (curObj) {
	case o00QUIT:
		if (_vm->QuitGame())
			doEvent(MC_SYSTEM, ME_QUIT, MP_SYSTEM, 0, 0, 0, 0);
		break;

	case o00EXIT:
		if (_vm->_oldRoom == kRoomControlPanel)
			break;
		doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[o00EXIT]._goRoom, 0, 0, 0);
		break;

	case o00SAVE:
		if (_vm->_oldRoom == kRoomControlPanel)
			break;
		_vm->_curRoom = _vm->_obj[o00EXIT]._goRoom;
		if (!_vm->DataSave()) {
			_vm->showInventoryName(NO_OBJECTS, false);
			doEvent(MC_INVENTORY, ME_SHOWICONNAME, MP_DEFAULT, _vm->_mouseX, _vm->_mouseY, 0, 0);
			doEvent(MC_SYSTEM, ME_CHANGEROOM, MP_SYSTEM, _vm->_obj[o00EXIT]._goRoom, 0, 0, 0);
		}
		_vm->_curRoom = kRoomControlPanel;
		break;

	case o00LOAD:
		if (!_vm->DataLoad()) {
			_vm->showInventoryName(NO_OBJECTS, false);
			doEvent(MC_INVENTORY, ME_SHOWICONNAME, MP_DEFAULT, _vm->_mouseX, _vm->_mouseY, 0, 0);
		}
		break;

	case o00SPEECHON:
		if (ConfMan.getBool("subtitles")) {
			_vm->_obj[o00SPEECHON]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[o00SPEECHOFF]._mode |= OBJMODE_OBJSTATUS;
			ConfMan.setBool("speech_mute", true);
			_vm->_curObj = o00SPEECHOFF;
			RegenRoom();
			ShowObjName(_vm->_curObj, true);
		}
		break;

	case o00SPEECHOFF:
		_vm->_obj[o00SPEECHOFF]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[o00SPEECHON]._mode |= OBJMODE_OBJSTATUS;
		ConfMan.setBool("speech_mute", false);
		_vm->_curObj = o00SPEECHON;
		RegenRoom();
		ShowObjName(_vm->_curObj, true);
		break;

	case o00TEXTON:
		if (!ConfMan.getBool("speech_mute")) {
			_vm->_obj[o00TEXTON]._mode &= ~OBJMODE_OBJSTATUS;
			_vm->_obj[o00TEXTOFF]._mode |= OBJMODE_OBJSTATUS;
			ConfMan.setBool("subtitles", false);
			_vm->_curObj = o00TEXTOFF;
			RegenRoom();
			ShowObjName(_vm->_curObj, true);
		}
		break;

	case o00TEXTOFF:
		_vm->_obj[o00TEXTOFF]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[o00TEXTON]._mode |= OBJMODE_OBJSTATUS;
		ConfMan.setBool("subtitles", true);
		_vm->_curObj = o00TEXTON;
		RegenRoom();
		ShowObjName(_vm->_curObj, true);
		break;

	case o00SPEECH1D:
	case o00SPEECH2D:
	case o00SPEECH3D:
	case o00SPEECH4D:
	case o00SPEECH5D:
	case o00SPEECH6D:
	case o00MUSIC1D:
	case o00MUSIC2D:
	case o00MUSIC3D:
	case o00MUSIC4D:
	case o00MUSIC5D:
	case o00MUSIC6D:
	case o00SOUND1D:
	case o00SOUND2D:
	case o00SOUND3D:
	case o00SOUND4D:
	case o00SOUND5D:
	case o00SOUND6D:
		_vm->_obj[curObj]._mode &= ~OBJMODE_OBJSTATUS;
		if ((curObj != o00SPEECH6D) && (curObj != o00MUSIC6D) && (curObj != o00SOUND6D))
			_vm->_obj[curObj + 1]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[curObj - 1]._mode |= OBJMODE_OBJSTATUS;
		_vm->_obj[curObj - 2]._mode |= OBJMODE_OBJSTATUS;
		RegenRoom();
		if (curObj < o00MUSIC1D)
			ConfMan.setInt("speech_volume", ((curObj - 2 - o00SPEECH1D) / 2) * 51);
		else if (curObj > o00MUSIC6D)
			ConfMan.setInt("sfx_volume", ((curObj - 2 - o00SOUND1D) / 2) * 51);
		else
			ConfMan.setInt("music_volume", ((curObj - 2 - o00MUSIC1D) / 2) * 51);
		break;

	case o00SPEECH1U:
	case o00SPEECH2U:
	case o00SPEECH3U:
	case o00SPEECH4U:
	case o00SPEECH5U:
	case o00MUSIC1U:
	case o00MUSIC2U:
	case o00MUSIC3U:
	case o00MUSIC4U:
	case o00MUSIC5U:
	case o00SOUND1U:
	case o00SOUND2U:
	case o00SOUND3U:
	case o00SOUND4U:
	case o00SOUND5U:
		_vm->_obj[curObj]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[curObj - 1]._mode &= ~OBJMODE_OBJSTATUS;
		_vm->_obj[curObj + 1]._mode |= OBJMODE_OBJSTATUS;
		if ((curObj != o00SPEECH5U) && (curObj != o00MUSIC5U) && (curObj != o00SOUND5U))
			_vm->_obj[curObj + 2]._mode |= OBJMODE_OBJSTATUS;
		RegenRoom();
		if (curObj < o00MUSIC1D)
			ConfMan.setInt("speech_volume", ((curObj + 1 - o00SPEECH1D) / 2) * 51);
		else if (curObj > o00MUSIC6D)
			ConfMan.setInt("sfx_volume", ((curObj + 1 - o00SOUND1D) / 2) * 51);
		else
			ConfMan.setInt("music_volume", ((curObj + 1 - o00MUSIC1D) / 2) * 51);
		break;
	default:
		break;
	}

	g_engine->syncSoundSettings();
	ConfMan.flushToDisk();
}

} // End of namespace Trecision
