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

#ifndef KYRA_KYRA_HOF_H
#define KYRA_KYRA_HOF_H

#include "kyra/kyra_v2.h"
#include "kyra/script.h"
#include "kyra/script_tim.h"
#include "kyra/screen_hof.h"
#include "kyra/text_hof.h"
#include "kyra/gui_hof.h"

#include "common/list.h"
#include "common/func.h"

namespace Kyra {

enum kSequences {
	kSequenceVirgin = 0,
	kSequenceWestwood,
	kSequenceTitle,
	kSequenceOverview,
	kSequenceLibrary,
	kSequenceHand,
	kSequencePoint,
	kSequenceZanfaun,

	kSequenceFunters,
	kSequenceFerb,
	kSequenceFish,
	kSequenceFheep,
	kSequenceFarmer,
	kSequenceFuards,
	kSequenceFirates,
	kSequenceFrash,

	kSequenceArraySize
};

enum kNestedSequences {
	kSequenceFiggle = 0,
	kSequenceOver1,
	kSequenceOver2,
	kSequenceForest,
	kSequenceDragon,
	kSequenceDarm,
	kSequenceLibrary2,
	kSequenceLibrary3,
	kSequenceMarco,
	kSequenceHand1a,
	kSequenceHand1b,
	kSequenceHand1c,
	kSequenceHand2,
	kSequenceHand3,
	kSequenceHand4
};

enum kSequencesDemo {
	kSequenceDemoVirgin = 0,
	kSequenceDemoWestwood,
	kSequenceDemoTitle,
	kSequenceDemoHill,
	kSequenceDemoOuthome,
	kSequenceDemoWharf,
	kSequenceDemoDinob,
	kSequenceDemoFisher
};

enum kNestedSequencesDemo {
	kSequenceDemoWharf2 = 0,
	kSequenceDemoDinob2,
	kSequenceDemoWater,
	kSequenceDemoBail,
	kSequenceDemoDig
};

class WSAMovieV2;
class KyraEngine_HoF;
class TextDisplayer_HoF;

struct TIM;

typedef int (KyraEngine_HoF::*SeqProc)(WSAMovieV2*, int, int, int);

struct FrameControl {
	uint16 index;
	uint16 delay;
};

struct ActiveWSA {
	int16 flags;
	WSAMovieV2 *movie;
	uint16 startFrame;
	uint16 endFrame;
	uint16 frameDelay;
	SeqProc callback;
	uint32 nextFrame;
	uint16 currentFrame;
	uint16 lastFrame;
	uint16 x;
	uint16 y;
	const FrameControl *control;
	uint16 startupCommand;
	uint16 finalCommand;
};

struct ActiveText {
	uint16 strIndex;
	uint16 x;
	uint16 y;
	int duration;
	uint16 width;
	uint32 startTime;
	int16 textcolor;
};

struct Sequence {
	uint16 flags;
	const char * wsaFile;
	const char * cpsFile;
	uint8 startupCommand;
	uint8 finalCommand;
	int16 stringIndex1;
	int16 stringIndex2;
	uint16 startFrame;
	uint16 numFrames;
	uint16 frameDelay;
	uint16 xPos;
	uint16 yPos;
	uint16 duration;
};

struct NestedSequence {
	uint16 flags;
	const char * wsaFile;
	uint16 startframe;
	uint16 endFrame;
	uint16 frameDelay;
	uint16 x;
	uint16 y;
	const FrameControl *wsaControl;
	uint16 startupCommand;
	uint16 finalCommand;
};

struct HofSeqData {
	const Sequence *seq;
	int numSeq;
	const NestedSequence *seqn;
	int numSeqn;
};

struct ItemAnimData_v1 {
	int16 itemIndex;
	uint16 y;
	const uint16 *frames;
};

struct ItemAnimData_v2 {
	int16 itemIndex;
	uint8 numFrames;
	const FrameControl *frames;
};

struct ActiveItemAnim {
	uint16 currentFrame;
	uint32 nextFrame;
};

class KyraEngine_HoF : public KyraEngine_v2 {
friend class Debugger_HoF;
friend class TextDisplayer_HoF;
friend class GUI_HoF;
public:
	KyraEngine_HoF(OSystem *system, const GameFlags &flags);
	~KyraEngine_HoF();

	Screen *screen() { return _screen; }
	Screen_v2 *screen_v2() const { return _screen; }
	GUI_v2 *gui_v2() const { return _gui; }
	virtual TextDisplayer *text() { return _text; }
	int language() const { return _lang; }
protected:
	static const EngineDesc _hofEngineDesc;

	// intro/outro
	void seq_playSequences(int startSeq, int endSeq = -1);

	int seq_introWestwood(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introTitle(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introOverview(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introLibrary(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introHand(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introPoint(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introZanfaun(WSAMovieV2 *wsaObj, int x, int y, int frm);

	int seq_introOver1(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introOver2(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introForest(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introDragon(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introDarm(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introLibrary2(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introMarco(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introHand1a(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introHand1b(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introHand1c(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introHand2(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_introHand3(WSAMovieV2 *wsaObj, int x, int y, int frm);

	int seq_finaleFunters(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_finaleFerb(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_finaleFish(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_finaleFheep(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_finaleFarmer(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_finaleFuards(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_finaleFirates(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_finaleFrash(WSAMovieV2 *wsaObj, int x, int y, int frm);

	int seq_finaleFiggle(WSAMovieV2 *wsaObj, int x, int y, int frm);

	int seq_demoVirgin(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoWestwood(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoTitle(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoHill(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoOuthome(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoWharf(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoDinob(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoFisher(WSAMovieV2 *wsaObj, int x, int y, int frm);

	int seq_demoWharf2(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoDinob2(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoWater(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoBail(WSAMovieV2 *wsaObj, int x, int y, int frm);
	int seq_demoDig(WSAMovieV2 *wsaObj, int x, int y, int frm);

	void seq_sequenceCommand(int command);
	void seq_loadNestedSequence(int wsaNum, int seqNum);
	void seq_nestedSequenceFrame(int command, int wsaNum);
	void seq_animatedSubFrame(int srcPage, int dstPage, int delaytime,
		int steps, int x, int y, int w, int h, int openClose, int directionFlags);
	bool seq_processNextSubFrame(int wsaNum);
	void seq_resetActiveWSA(int wsaNum);
	void seq_unloadWSA(int wsaNum);
	void seq_processWSAs();
	void seq_cmpFadeFrame(const char *cmpFile);
	void seq_playTalkText(uint8 chatNum);
	void seq_resetAllTextEntries();
	uint32 seq_activeTextsTimeLeft();
	void seq_waitForTextsTimeout();
	int seq_setTextEntry(uint16 strIndex, uint16 posX, uint16 posY, int duration, uint16 width);
	void seq_processText();
	char *seq_preprocessString(const char *str, int width);
	void seq_printCreditsString(uint16 strIndex, int x, int y, const uint8 *colorMap, uint8 textcolor);
	void seq_playWsaSyncDialogue(uint16 strIndex, uint16 vocIndex, int textColor, int x, int y, int width,
		WSAMovieV2 * wsa, int firstframe, int lastframe, int wsaXpos, int wsaYpos);
	void seq_finaleActorScreen();
	void seq_displayScrollText(uint8 *data, const ScreenDim *d, int tempPage1, int tempPage2, int speed, int step, Screen::FontId fid1, Screen::FontId fid2, const uint8 *shapeData = 0, const char *const *specialData = 0);
	void seq_scrollPage();
	void seq_showStarcraftLogo();

	void seq_init();
	void seq_uninit();

	int init();
	int go();

	Screen_HoF *_screen;
	TextDisplayer_HoF *_text;
	TIMInterpreter *_tim;

	uint8 *_mouseSHPBuf;

	static const int8 _dosTrackMap[];
	static const int _dosTrackMapSize;

	const AudioDataStruct *_soundData;

protected:
	// game initialization
	void startup();
	void runLoop();
	void cleanup();

	void registerDefaultSettings();
	void writeSettings();
	void readSettings();
	uint8 _configTextspeed;

	// TODO: get rid of all variables having pointers to the static resources if possible
	// i.e. let them directly use the _staticres functions
	void initStaticResource();

	void setupTimers();
	void setupOpcodeTable();

	void loadMouseShapes();
	void loadItemShapes();

	// run
	void update();
	void updateWithText();

	Common::Functor0Mem<void, KyraEngine_HoF> _updateFunctor;

	void updateMouse();

	void dinoRide();

	int _mouseState;

	void handleInput(int x, int y);
	bool handleInputUnkSub(int x, int y);

	int inputSceneChange(int x, int y, int unk1, int unk2);

	// gfx/animation specific
	bool _inventorySaved;
	void backUpPage0();
	void restorePage0();

	uint8 *_gfxBackUpRect;

	void backUpGfxRect24x24(int x, int y);
	void restoreGfxRect24x24(int x, int y);
	void backUpGfxRect32x32(int x, int y);
	void restoreGfxRect32x32(int x, int y);

	uint8 *_sceneShapeTable[50];

	WSAMovieV2 *_wsaSlots[10];

	void freeSceneShapePtrs();

	struct ShapeDesc {
		uint8 unk0, unk1, unk2, unk3, unk4;
		uint16 width, height;
		int16 xAdd, yAdd;
	};

	ShapeDesc *_shapeDescTable;

	void loadCharacterShapes(int shapes);
	void loadInventoryShapes();

	void resetScaleTable();
	void setScaleTableItem(int item, int data);
	int getScale(int x, int y);
	uint16 _scaleTable[15];

	void setDrawLayerTableEntry(int entry, int data);
	int getDrawLayer(int x, int y);
	int _drawLayerTable[15];

	int _layerFlagTable[16]; // seems to indicate layers where items get destroyed when dropped to (TODO: check this!)

	int initAnimationShapes(uint8 *filedata);
	void uninitAnimationShapes(int count, uint8 *filedata);

	// animator
	uint8 *_gamePlayBuffer;
	void restorePage3();

	void clearAnimObjects();

	void refreshAnimObjects(int force);

	void drawAnimObjects();
	void drawSceneAnimObject(AnimObj *obj, int x, int y, int drawLayer);
	void drawCharacterAnimObject(AnimObj *obj, int x, int y, int drawLayer);

	void updateItemAnimations();

	void updateCharFacing();
	void updateCharacterAnim(int);
	void updateSceneAnim(int anim, int newFrame);

	int _animObj0Width, _animObj0Height;
	void setCharacterAnimDim(int w, int h);
	void resetCharacterAnimDim();

	// scene
	const char *_sceneCommentString;
	uint8 _scenePal[688];

	void enterNewScene(uint16 newScene, int facing, int unk1, int unk2, int unk3);
	void enterNewSceneUnk1(int facing, int unk1, int unk2);
	void enterNewSceneUnk2(int unk1);
	void unloadScene();

	void loadScenePal();
	void loadSceneMsc();

	void fadeScenePal(int srcIndex, int delay);

	void startSceneScript(int unk1);
	void runSceneScript2();
	void runSceneScript4(int unk1);
	void runSceneScript7();

	void initSceneAnims(int unk1);
	void initSceneScreen(int unk1);

	int trySceneChange(int *moveTable, int unk1, int updateChar);
	int checkSceneChange();

	// pathfinder
	bool lineIsPassable(int x, int y);

	// item
	void setMouseCursor(uint16 item);

	uint8 _itemHtDat[176];

	int checkItemCollision(int x, int y);
	void updateWaterFlasks();

	bool dropItem(int unk1, uint16 item, int x, int y, int unk2);
	bool processItemDrop(uint16 sceneId, uint16 item, int x, int y, int unk1, int unk2);
	void itemDropDown(int startX, int startY, int dstX, int dstY, int itemSlot, uint16 item);
	void exchangeMouseItem(int itemPos);
	bool pickUpItem(int x, int y);

	bool isDropable(int x, int y);

	static const byte _itemStringMap[];
	static const int _itemStringMapSize;

	static const int16 _flaskTable[];
	bool itemIsFlask(int item);

	// inventory
	static const int _inventoryX[];
	static const int _inventoryY[];
	static const uint16 _itemMagicTable[];

	int getInventoryItemSlot(uint16 item);
	void removeSlotFromInventory(int slot);
	bool checkInventoryItemExchange(uint16 item, int slot);
	void drawInventoryShape(int page, uint16 item, int slot);
	void clearInventorySlot(int slot, int page);
	void redrawInventory(int page);
	void scrollInventoryWheel();
	int findFreeVisibleInventorySlot();

	ActiveItemAnim _activeItemAnim[15];
	int _nextAnimItem;

	// gui
	bool _menuDirectlyToLoad;
	GUI_HoF *_gui;

	void loadButtonShapes();
	void setupLangButtonShapes();
	uint8 *_buttonShapes[19];

	void initInventoryButtonList();
	Button *_inventoryButtons;
	Button *_buttonList;

	int scrollInventory(Button *button);
	int buttonInventory(Button *button);
	int bookButton(Button *button);
	int cauldronButton(Button *button);
	int cauldronClearButton(Button *button);

	// book
	static const int _bookPageYOffset[];
	static const byte _bookTextColorMap[];

	int _bookMaxPage;
	int _bookNewPage;
	int _bookCurPage;
	int _bookBkgd;
	bool _bookShown;

	void loadBookBkgd();
	void showBookPage();
	void bookLoop();

	void bookDecodeText(uint8 *text);
	void bookPrintText(int dstPage, const uint8 *text, int x, int y, uint8 color);

	int bookPrevPage(Button *button);
	int bookNextPage(Button *button);
	int bookClose(Button *button);

	// cauldron
	uint8 _cauldronState;
	int16 _cauldronUseCount;
	int16 _cauldronTable[25];
	int16 _cauldronStateTables[23][7];

	static const int16 _cauldronProtectedItems[];
	static const int16 _cauldronBowlTable[];
	static const int16 _cauldronMagicTable[];
	static const int16 _cauldronMagicTableScene77[];
	static const uint8 _cauldronStateTable[];

	void resetCauldronStateTable(int idx);
	bool addToCauldronStateTable(int data, int idx);

	void setCauldronState(uint8 state, bool paletteFade);
	void clearCauldronTable();
	void addFrontCauldronTable(int item);
	void cauldronItemAnim(int item);
	void cauldronRndPaletteFade();
	bool updateCauldron();
	void listItemsInCauldron();

	// localization
	void loadCCodeBuffer(const char *file);
	void loadOptionsBuffer(const char *file);
	void loadChapterBuffer(int chapter);
	uint8 *_optionsBuffer;
	uint8 *_cCodeBuffer;

	uint8 *_chapterBuffer;
	int _currentChapter;
	int _newChapterFile;

	uint8 *getTableEntry(uint8 *buffer, int id);
	char *getTableString(int id, uint8 *buffer, int decode);
	const char *getChapterString(int id);
	int decodeString1(const char *src, char *dst);
	void decodeString2(const char *src, char *dst);

	void changeFileExtension(char *buffer);

	// - Just used in French version
	int getItemCommandStringDrop(uint16 item);
	int getItemCommandStringPickUp(uint16 item);
	int getItemCommandStringInv(uint16 item);
	// -

	char _internStringBuf[200];
	static const char *_languageExtension[];
	static const char *_scriptLangExt[];

	// character
	bool _useCharPal;
	int _charPalEntry;
	uint8 _charPalTable[16];
	void updateCharPal(int unk1);
	void setCharPalEntry(int entry, int value);

	int getCharacterWalkspeed() const;
	void updateCharAnimFrame(int num, int *table);

	bool checkCharCollision(int x, int y);

	static const uint8 _characterFrameTable[];

	// text
	void showMessageFromCCode(int id, int16 palIndex, int);
	void showMessage(const char *string, int16 palIndex);
	void showChapterMessage(int id, int16 palIndex);

	void updateCommandLineEx(int str1, int str2, int16 palIndex);

	const char *_shownMessage;

	byte _messagePal[3];
	bool _fadeMessagePalette;
	void fadeMessagePalette();

	// chat
	bool _chatIsNote;

	int chatGetType(const char *text);
	int chatCalcDuration(const char *text);

	void objectChat(const char *text, int object, int vocHigh = -1, int vocLow = -1);
	void objectChatInit(const char *text, int object, int vocHigh = -1, int vocLow = -1);
	void objectChatPrintText(const char *text, int object);
	void objectChatProcess(const char *script);
	void objectChatWaitToFinish();

	void startDialogue(int dlgIndex);

	void zanthSceneStartupChat();
	void randomSceneChat();
	void updateDlgBuffer();
	void loadDlgHeader(int &csEntry, int &vocH, int &scIndex1, int &scIndex2);
	void processDialogue(int dlgOffset, int vocH = 0, int csEntry = 0);
	void npcChatSequence(const char *str, int objectId, int vocHigh = -1, int vocLow = -1);
	void setDlgIndex(int dlgIndex);

	int _npcTalkChpIndex;
	int _npcTalkDlgIndex;
	uint8 _newSceneDlgState[32];
	int8 **_conversationState;
	uint8 *_dlgBuffer;

	// Talk object handling
	void initTalkObject(int index);
	void deinitTalkObject(int index);

	struct TalkObject {
		char filename[13];
		int8 scriptId;
		int16 x, y;
		int8 color;
	};
	TalkObject *_talkObjectList;

	struct TalkSections {
		TIM *STATim;
		TIM *TLKTim;
		TIM *ENDTim;
	};
	TalkSections _currentTalkSections;

	char _TLKFilename[13];

	// tim
	void playTim(const char *filename);

	int t2_initChat(const TIM *tim, const uint16 *param);
	int t2_updateSceneAnim(const TIM *tim, const uint16 *param);
	int t2_resetChat(const TIM *tim, const uint16 *param);
	int t2_playSoundEffect(const TIM *tim, const uint16 *param);

	Common::Array<const TIMOpcode*> _timOpcodes;

	// sound
	int _oldTalkFile;
	int _currentTalkFile;
	void openTalkFile(int newFile);
	int _lastSfxTrack;

	virtual void snd_playVoiceFile(int id);
	void snd_loadSoundFile(int id);

	void playVoice(int high, int low);
	void snd_playSoundEffect(int track, int volume=0xFF);

	// timer
	void timerFadeOutMessage(int);
	void timerCauldronAnimation(int);
	void timerFunc4(int);
	void timerFunc5(int);
	void timerBurnZanthia(int);

	void setTimer1DelaySecs(int secs);

	uint32 _nextIdleAnim;
	int _lastIdleScript;

	void setNextIdleAnimTimer();
	void showIdleAnim();
	void runIdleScript(int script);

	void setWalkspeed(uint8 speed);

	// delay
	void delay(uint32 millis, bool updateGame = false, bool isMainLoop = false);

	// ingame static sequence handling
	void seq_makeBookOrCauldronAppear(int type);
	void seq_makeBookAppear();

	struct InventoryWsa {
		int x, y, x2, y2, w, h;
		int page;
		int curFrame, lastFrame, specialFrame;
		int sfx;
		int delay;
		bool running;
		uint32 timer;
		WSAMovieV2 *wsa;
	} _invWsa;

	// TODO: move inside KyraEngine_HoF::InventoryWsa?
	void loadInvWsa(const char *filename, int run, int delay, int page, int sfx, int sFrame, int flags);
	void closeInvWsa();

	void updateInvWsa();
	void displayInvWsaLastFrame();

	// opcodes
	int o2_setCharacterFacingRefresh(EMCState *script);
	int o2_setCharacterPos(EMCState *script);
	int o2_defineObject(EMCState *script);
	int o2_refreshCharacter(EMCState *script);
	int o2_setSceneComment(EMCState *script);
	int o2_setCharacterAnimFrame(EMCState *script);
	int o2_setCharacterFacing(EMCState *script);
	int o2_customCharacterChat(EMCState *script);
	int o2_soundFadeOut(EMCState *script);
	int o2_showChapterMessage(EMCState *script);
	int o2_restoreTalkTextMessageBkgd(EMCState *script);
	int o2_wsaClose(EMCState *script);
	int o2_meanWhileScene(EMCState *script);
	int o2_backUpScreen(EMCState *script);
	int o2_restoreScreen(EMCState *script);
	int o2_displayWsaFrame(EMCState *script);
	int o2_displayWsaSequentialFramesLooping(EMCState *script);
	int o2_wsaOpen(EMCState *script);
	int o2_displayWsaSequentialFrames(EMCState *script);
	int o2_displayWsaSequence(EMCState *script);
	int o2_addItemToInventory(EMCState *script);
	int o2_drawShape(EMCState *script);	
	int o2_addItemToCurScene(EMCState *script);
	int o2_loadSoundFile(EMCState *script);
	int o2_removeSlotFromInventory(EMCState *script);
	int o2_removeItemFromInventory(EMCState *script);
	int o2_countItemInInventory(EMCState *script);
	int o2_countItemsInScene(EMCState *script);
	int o2_wipeDownMouseItem(EMCState *script);
	int o2_getElapsedSecs(EMCState *script);
	int o2_getTimerDelay(EMCState *script);
	//int o2_playSoundEffect(EMCState *script);
	int o2_delaySecs(EMCState *script);
	int o2_setTimerDelay(EMCState *script);
	int o2_setScaleTableItem(EMCState *script);
	int o2_setDrawLayerTableItem(EMCState *script);
	int o2_setCharPalEntry(EMCState *script);
	int o2_loadZShapes(EMCState *script);
	int o2_drawSceneShape(EMCState *script);
	int o2_drawSceneShapeOnPage(EMCState *script);
	int o2_disableAnimObject(EMCState *script);
	int o2_enableAnimObject(EMCState *script);
	int o2_loadPalette384(EMCState *script);
	int o2_setPalette384(EMCState *script);
	int o2_restoreBackBuffer(EMCState *script);
	int o2_backUpInventoryGfx(EMCState *script);
	int o2_disableSceneAnim(EMCState *script);
	int o2_enableSceneAnim(EMCState *script);
	int o2_restoreInventoryGfx(EMCState *script);
	int o2_setSceneAnimPos2(EMCState *script);
	int o2_fadeScenePal(EMCState *script);
	int o2_enterNewScene(EMCState *script);
	int o2_switchScene(EMCState *script);
	int o2_setPathfinderFlag(EMCState *script);
	int o2_getSceneExitToFacing(EMCState *script);
	int o2_setLayerFlag(EMCState *script);
	int o2_setZanthiaPos(EMCState *script);
	int o2_loadMusicTrack(EMCState *script);
	int o2_playSoundEffect(EMCState *script);
	int o2_setSceneAnimPos(EMCState *script);
	int o2_blockInRegion(EMCState *script);
	int o2_blockOutRegion(EMCState *script);
	int o2_setCauldronState(EMCState *script);
	int o2_showItemString(EMCState *script);
	int o2_isAnySoundPlaying(EMCState *script);
	int o2_setDrawNoShapeFlag(EMCState *script);
	int o2_setRunFlag(EMCState *script);
	int o2_showLetter(EMCState *script);
	int o2_fillRect(EMCState *script);
	int o2_encodeShape(EMCState *script);
	int o2_defineSceneAnim(EMCState *script);
	int o2_updateSceneAnim(EMCState *script);
	int o2_addToSceneAnimPosAndUpdate(EMCState *script);
	int o2_useItemOnMainChar(EMCState *script);
	int o2_startDialogue(EMCState *script);
	int o2_addCauldronStateTableEntry(EMCState *script);
	int o2_setCountDown(EMCState *script);
	int o2_getCountDown(EMCState *script);
	int o2_pressColorKey(EMCState *script);
	int o2_objectChat(EMCState *script);
	int o2_changeChapter(EMCState *script);
	int o2_getColorCodeFlag1(EMCState *script);
	int o2_setColorCodeFlag1(EMCState *script);
	int o2_getColorCodeFlag2(EMCState *script);
	int o2_setColorCodeFlag2(EMCState *script);
	int o2_getColorCodeValue(EMCState *script);
	int o2_setColorCodeValue(EMCState *script);
	int o2_countItemInstances(EMCState *script);
	int o2_removeItemFromScene(EMCState *script);
	int o2_initObject(EMCState *script);
	int o2_npcChat(EMCState *script);
	int o2_deinitObject(EMCState *script);
	int o2_playTimSequence(EMCState *script);
	int o2_makeBookOrCauldronAppear(EMCState *script);
	int o2_resetInputColorCode(EMCState *script);
	int o2_mushroomEffect(EMCState *script);
	int o2_customChat(EMCState *script);
	int o2_customChatFinish(EMCState *script);
	int o2_setupSceneAnimation(EMCState *script);
	int o2_stopSceneAnimation(EMCState *script);
	int o2_processPaletteIndex(EMCState *script);
	int o2_updateTwoSceneAnims(EMCState *script);
	int o2_getRainbowRoomData(EMCState *script);
	int o2_drawSceneShapeEx(EMCState *script);
	int o2_getBoolFromStack(EMCState *script);
	int o2_getSfxDriver(EMCState *script);
	int o2_getVocSupport(EMCState *script);
	int o2_getMusicDriver(EMCState *script);
	int o2_zanthiaChat(EMCState *script);
	int o2_isVoiceEnabled(EMCState *script);
	int o2_isVoicePlaying(EMCState *script);
	int o2_stopVoicePlaying(EMCState *script);
	int o2_getGameLanguage(EMCState *script);
	int o2_demoFinale(EMCState *script);
	int o2_dummy(EMCState *script);

	// animation opcodes
	int o2a_setCharacterFrame(EMCState *script);

	// script
	void runStartScript(int script, int unk1);
	void loadNPCScript();

	bool _noScriptEnter;

	EMCData _npcScriptData;

	// pathfinder
	uint8 *_unkBuf500Bytes;
	uint8 *_unkBuf200kByte;
	bool _chatAltFlag;

	// sequence player
	ActiveWSA *_activeWSA;
	ActiveText *_activeText;

	const char *const *_sequencePakList;
	int _sequencePakListSize;
	const char *const *_ingamePakList;
	int _ingamePakListSize;

	const char *const *_musicFileListIntro;
	int _musicFileListIntroSize;
	const char *const *_musicFileListFinale;
	int _musicFileListFinaleSize;
	const char *const *_musicFileListIngame;
	int _musicFileListIngameSize;
	const uint8 *_cdaTrackTableIntro;
	int _cdaTrackTableIntroSize;
	const uint8 *_cdaTrackTableIngame;
	int _cdaTrackTableIngameSize;
	const uint8 *_cdaTrackTableFinale;
	int _cdaTrackTableFinaleSize;
	const char *const *_sequenceSoundList;
	int _sequenceSoundListSize;
	const char *const *_ingameSoundList;
	int _ingameSoundListSize;
	const uint16 *_ingameSoundIndex;
	int _ingameSoundIndexSize;
	const char *const *_sequenceStrings;
	int _sequenceStringsSize;
	const uint16 *_ingameTalkObjIndex;
	int _ingameTalkObjIndexSize;
	const char *const *_ingameTimJpStr;
	int _ingameTimJpStrSize;	
	const HofSeqData *_sequences;
	const ItemAnimData_v2 *_itemAnimData;
	int _itemAnimDataSize;
	const ItemAnimData_v1 *_demoAnimData;
	int _demoAnimSize;

	int _sequenceStringsDuration[33];

	static const uint8 _seqTextColorPresets[];
	char *_seqProcessedString;
	WSAMovieV2 *_seqWsa;

	bool _abortIntroFlag;
	int _menuChoice;

	uint32 _seqFrameDelay;
	uint32 _seqStartTime;
	uint32 _seqEndTime;
	int _seqFrameCounter;
	int _seqScrollTextCounter;
	int _seqWsaCurrentFrame;
	bool _seqSpecialFlag;
	bool _seqSubframePlaying;
	uint8 _seqTextColor[2];
	uint8 _seqTextColorMap[16];

	const SeqProc *_callbackS;
	const SeqProc *_callbackN;

	static const uint8 _rainbowRoomData[];

	// color code related vars
	int _colorCodeFlag1;
	int _colorCodeFlag2;
	uint8 _presetColorCode[7];
	uint8 _inputColorCode[7];
	uint32 _scriptCountDown;
	int _dbgPass;

	// save/load specific
	void saveGame(const char *fileName, const char *saveName);
	void loadGame(const char *fileName);
};

} // end of namespace Kyra

#endif

