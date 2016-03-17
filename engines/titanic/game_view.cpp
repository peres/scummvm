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

#include "titanic/game_view.h"
#include "titanic/game_manager.h"
#include "titanic/main_game_window.h"
#include "titanic/screen_manager.h"

namespace Titanic {

CGameView::CGameView() : _gameManager(nullptr), _surface(nullptr) {
}

void CGameView::setGameManager(CGameManager *gameManager) {
	_gameManager = gameManager;
}

void CGameView::postLoad() {
	delete _surface;
	_surface = nullptr;
}

void CGameView::deleteView(int roomNumber, int nodeNumber, int viewNumber) {
	CViewItem *view = _gameManager->_project->findView(roomNumber, nodeNumber, viewNumber);
	if (view)
		delete view;
}

void CGameView::createSurface(const CResourceKey &key) {
	// Reset any current view surface
	_gameManager->initBounds();
	delete _surface;
	_surface = nullptr;
	
	// Create a fresh surface
	CScreenManager::setCurrent();
	_surface = CScreenManager::_currentScreenManagerPtr->createSurface(key);
	_surface->_field3C = true;
}

/*------------------------------------------------------------------------*/

CSTGameView::CSTGameView(CMainGameWindow *gameWindow) :
		CGameView(), _gameWindow(gameWindow) {
}

void CSTGameView::setView(CViewItem *view) {
	_gameWindow->setActiveView(view);
}

void CSTGameView::proc4() {
	_gameWindow->fn2();
}

} // End of namespace Titanic
