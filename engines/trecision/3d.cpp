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

#include "trecision/3d.h"
#include "trecision/anim.h"
#include "trecision/sound.h"
#include "trecision/text.h"
#include "trecision/actor.h"
#include "trecision/graphics.h"
#include "trecision/trecision.h"

namespace Trecision {
#define SHADOWVERTSNUM 42

static int16 _shadowVerts[SHADOWVERTSNUM] = {
	6, 15, 23,
	24, 32, 78,
	80, 81, 83,
	86, 90, 99,
	107, 108, 116,
	155, 157, 158,
	160, 164, 168,
	169, 173, 174,
	187, 188, 192,
	193, 213, 215,
	227, 229, 235,
	238, 249, 250,
	252, 253, 299,
	306, 330, 336
};
#define SHADOWFACESNUM 48

int16 _shadowFaces[SHADOWFACESNUM][3] = {
	22, 21, 5,
	7, 5, 22,
	7, 19, 5,
	5, 2, 19,
	27, 24, 16,
	27, 16, 18,
	18, 16, 9,
	18, 13, 9,
	13, 9, 2,
	3, 19, 12,
	25, 26, 17,
	17, 15, 25,
	17, 19, 15,
	15, 12, 19,
	20, 23, 8,
	8, 6, 20,
	6, 9, 3,
	3, 8, 6,
	12, 3, 4,
	4, 11, 12,
	35, 4, 11,
	13, 2, 1,
	1, 14, 13,
	14, 37, 1,
	1, 34, 37,
	31, 36, 37,
	37, 30, 31,
	29, 34, 35,
	35, 29, 28,
	36, 11, 31,
	30, 37, 14,
	29, 1, 34,
	28, 4, 35,
	36, 10, 35,
	35, 32, 10,
	37, 0, 34,
	37, 33, 0,
	0, 33, 39,
	39, 40, 0,
	10, 38, 32,
	32, 41, 38,
	36, 35, 34,
	36, 37, 35,
	11, 36, 35,
	38, 40, 41,
	41, 38, 39,
	2, 19, 13,
	3, 9, 12
};

Renderer3D::Renderer3D(TrecisionEngine *vm) : _vm(vm) {
	_zBuffer = new int16[ZBUFFERSIZE / 2];
	_curPage = nullptr;

	_minXClip = 0;
	_minYClip = 0;
	_maxXClip = 0;
	_maxYClip = 0;
	_zBufStartX = 0;
	_zBufStartY = 0;
	_zBufWid = 0;
	_shadowLightNum = 0;
	_totalShadowVerts = 0;

	// data for the triangle routines
	for (int i = 0; i < 480; ++i) {
		_lEdge[i] = 0;
		_rEdge[i] = 0;
		_lColor[i] = 0;
		_rColor[i] = 0;
		_lZ[i] = 0;
		_rZ[i] = 0;
		_lTextX[i] = 0;
		_rTextX[i] = 0;
		_lTextY[i] = 0;
		_rTextY[i] = 0;
	}

	for (int i = 0; i < 10; ++i)
		_shadowIntens[i] = 0;

	for (int i = 0; i < MAXVERTEX; ++i) {
		_vVertex[i].clear();
		_shVertex[i].clear();
	}

	DObj.rect = Common::Rect(0, 0, 0, 0);
	DObj.l = Common::Rect(0, 0, 0, 0);
}

Renderer3D::~Renderer3D() {
	delete[] _zBuffer;
}

void Renderer3D::textureTriangle(int32 x1, int32 y1, int32 z1, int32 c1, int32 tx1, int32 ty1,
								 int32 x2, int32 y2, int32 z2, int32 c2, int32 tx2, int32 ty2,
								 int32 x3, int32 y3, int32 z3, int32 c3, int32 tx3, int32 ty3,
								 STexture *t) {
	int32 cl;  // color of left edge of horizontal scanline
	int32 zl;  // zbuffer of left edge of horizontal scanline
	int32 olx; // texture x of left edge of horizontal scanline
	int32 oly; // texture y of left edge of horizontal scanline
	int16 y;   // looping variable

	if (y1 > _maxYClip)
		y1 = _maxYClip;
	if (y1 < _minYClip)
		y1 = _minYClip;

	int16 yBottom = y1;
	int16 yTop = y1;
	uint8 *texture = t->_texture;

	if (yBottom > y2) {
		if (y2 < _minYClip)
			y2 = _minYClip;
		yBottom = y2;
	}
	if (yTop < y2) {
		if (y2 > _maxYClip)
			y2 = _maxYClip;
		yTop = y2;
	}
	if (yBottom > y3) {
		if (y3 < _minYClip)
			y3 = _minYClip;
		yBottom = y3;
	}
	if (yTop < y3) {
		if (y3 > _maxYClip)
			y3 = _maxYClip;
		yTop = y3;
	}
	for (y = yBottom; y < yTop; y++) {
		_lEdge[y] = _maxXClip;
		_rEdge[y] = _minXClip;
	}

	// scan the edges of the triangle
	textureScanEdge(x1, y1, z1, c1, tx1, ty1, x2, y2, z2, c2, tx2, ty2);
	textureScanEdge(x2, y2, z2, c2, tx2, ty2, x3, y3, z3, c3, tx3, ty3);
	textureScanEdge(x3, y3, z3, c3, tx3, ty3, x1, y1, z1, c1, tx1, ty1);

	// Gouraud fill the horizontal scanlines
	for (y = yBottom; y < yTop; y++) {
		int32 el = _lEdge[y];
		if (el < _minXClip)
			el = _minXClip;
		int32 er = _rEdge[y];
		if (er > _maxXClip)
			er = _maxXClip;

		// edge right - edge left
		int16 dx = er - el;

		if (!(dx <= 0)) {
			// slope dc/_dx
			int32 mc = ((int16)(_rColor[y] - (cl = _lColor[y])) << 8) / dx;
			// slope _dz/_dx
			int32 mz = ((int32)(_rZ[y] - (zl = _lZ[y])) << 16) / dx;
			// slope dty/_dx
			int32 mtx = ((int32)(_rTextX[y] - (olx = _lTextX[y])) << 16) / dx;
			// slope dty/_dx
			int32 mty = ((int32)(_rTextY[y] - (oly = _lTextY[y])) << 16) / dx;
			// screen offset
			int32 sl = el + MAXX * y;
			// pointer to zbuffer
			int16 *z = _zBuffer + (y - _zBufStartY) * _zBufWid + (el - _zBufStartX);
			uint16 *screenPtr = _curPage + sl;

			zl <<= 16;
			cl <<= 8;
			olx <<= 16;
			oly <<= 16;
			// loop through every pixel in horizontal scanline
			while (dx) {
				sl = zl >> 16;
				if (*z > sl) {
					*screenPtr = (uint16)(_vm->_actor->_textureMat[texture[(olx >> 16) + t->_dx * (oly >> 16)]][cl >> 9]);
					*z = (int16)sl;
				}
				screenPtr++; // increase screen x
				z++;         // increase zbuffer
				zl += mz;    // increase the zbuffer by _dz/_dx
				cl += mc;    // increase the color by dc/_dx
				olx += mtx;
				oly += mty;
				dx--; // pixel to do --
			}
		}
	}
}

void Renderer3D::textureScanEdge(int32 x1, int32 y1, int32 z1, int32 c1, int32 tx1, int32 ty1, int32 x2, int32 y2, int32 z2, int32 c2, int32 tx2, int32 ty2) {
	// make sure that edge goes from top to bottom
	int16 dy = y2 - y1;
	if (dy < 0) {
		SWAP(y1, y2);
		SWAP(x1, x2);
		SWAP(c1, c2);
		SWAP(z1, z2);
		SWAP(tx1, tx2);
		SWAP(ty1, ty2);

		dy = -dy;
	}

	if (dy == 0)
		dy = 1;

	// initialize for stepping
	int32 mx = ((x2 - x1) << 16) / dy; // dx/dy
	int32 mz = ((z2 - z1) << 16) / dy; // dz/dy
	int32 mc = ((c2 - c1) << 8) / dy;  // dc/dy
	int32 mtx = ((tx2 - tx1) << 16) / dy;
	int32 mty = ((ty2 - ty1) << 16) / dy;

	x1 <<= 16; // starting x coordinate
	z1 <<= 16; // starting z coordinate
	c1 <<= 8;  // starting c color

	tx1 <<= 16;
	ty1 <<= 16;

	// step through edge and record color values along the way
	for (int32 count = y1; count < y2; count++) {
		int16 x = (uint16)(x1 >> 16);
		if (x < _lEdge[count]) {
			_lEdge[count] = x;
			_lZ[count] = (int16)(z1 >> 16);
			_lTextX[count] = (uint16)(tx1 >> 16);
			_lTextY[count] = (uint16)(ty1 >> 16);
			_lColor[count] = (uint8)(c1 >> 8);
		}
		if (x > _rEdge[count]) {
			_rEdge[count] = x;
			_rZ[count] = (int16)(z1 >> 16);
			_rTextX[count] = (uint16)(tx1 >> 16);
			_rTextY[count] = (uint16)(ty1 >> 16);
			_rColor[count] = (uint8)(c1 >> 8);
		}

		x1 += mx; // x = x + dx/dy
		c1 += mc; // c = c + dc/dy
		z1 += mz; // z = z + dz/dy

		tx1 += mtx;
		ty1 += mty;
	}
}

void Renderer3D::shadowTriangle(int32 x1, int32 y1, int32 x2, int32 y2,
								int32 x3, int32 y3, uint8 cv, int32 zv) {
	if (y1 > _maxYClip)
		y1 = _maxYClip;
	if (y1 < _minYClip)
		y1 = _minYClip;

	int16 yBottom = y1;
	int16 yTop = y1;

	if (yBottom > y2) {
		if (y2 < _minYClip)
			y2 = _minYClip;
		yBottom = y2;
	}
	if (yTop < y2) {
		if (y2 > _maxYClip)
			y2 = _maxYClip;
		yTop = y2;
	}
	if (yBottom > y3) {
		if (y3 < _minYClip)
			y3 = _minYClip;
		yBottom = y3;
	}
	if (yTop < y3) {
		if (y3 > _maxYClip)
			y3 = _maxYClip;
		yTop = y3;
	}

	for (int16 y = yBottom; y < yTop; y++) {
		_lEdge[y] = _maxXClip;
		_rEdge[y] = _minXClip;
	}

	// scan the edges of the triangle
	shadowScanEdge(x1, y1, x2, y2);
	shadowScanEdge(x2, y2, x3, y3);
	shadowScanEdge(x3, y3, x1, y1);

	// gouraud fill the horizontal scanlines
	for (int16 y = yBottom; y < yTop; y++) {
		// coordinate of left edge of horizontal scanline
		int32 el = _lEdge[y];
		if (el < _minXClip)
			el = _minXClip;
		// coordinate of right edge of horizontal scanline
		int32 er = _rEdge[y];
		if (er > _maxXClip)
			er = _maxXClip;

		// edge right - edge left
		int16 dx = er - el;

		if (!(dx <= 0)) {
			// screen offset
			int32 sl = el + MAXX * y;

			int16 *zBufferPtr = _zBuffer + (y - _zBufStartY) * _zBufWid + (el - _zBufStartX);
			uint16 *screenPtr = _curPage + sl;

			// loop through every pixel in horizontal scanline
			while (dx) {
				if (*zBufferPtr != zv) {
					*screenPtr = _vm->_graphicsMgr->shadow(*screenPtr, cv);
					*zBufferPtr = zv;
				}
				screenPtr++;  // increase screen x
				zBufferPtr++; // increase zbuffer
				dx--;         // pixel to do --
			}
		}
	}
}

void Renderer3D::shadowScanEdge(int32 x1, int32 y1, int32 x2, int32 y2) {
	// make sure that edge goes from top to bottom
	int16 dy = y2 - y1;
	if (dy < 0) {
		SWAP(y1, y2);
		SWAP(x1, x2);

		dy = -dy;
	}

	if (dy == 0)
		dy = 1;

	// initialize for stepping
	int32 mx = ((x2 - x1) << 16) / dy; // slope dx/dy

	x1 <<= 16; // starting x coordinate

	// step through edge and record color values along the way
	for (int32 count = y1; count < y2; count++) {
		int16 x = (int16)(x1 >> 16);
		if (x < _lEdge[count])
			_lEdge[count] = x;

		if (x > _rEdge[count])
			_rEdge[count] = x;

		x1 += mx; // x = x + dx/dy
	}
}

/*------------------------------------------------
	Initialize a 3D Room
--------------------------------------------------*/
void Renderer3D::init3DRoom(uint16 *destBuffer) {
	_curPage = destBuffer;
	_vm->_cx = (MAXX - 1) / 2;
	_vm->_cy = (MAXY - 1) / 2;

	for (int c = 0; c < ZBUFFERSIZE / 2; ++c)
		_zBuffer[c] = 0x7FFF;
}

void Renderer3D::resetZBuffer(int x1, int y1, int x2, int y2) {
	if (x1 > x2 || y1 > y2)
		return;

	int size = (x2 - x1) * (y2 - y1);
	if (size * 2 > ZBUFFERSIZE)
		warning("Warning: _zBuffer size %d!\n", size * 2);

	int16 *d = _zBuffer;
	for (int i = 0; i < size; ++i)
		*d++ = 0x7FFF;
}

/*------------------------------------------------
	Change the clipping area
--------------------------------------------------*/
void Renderer3D::setClipping(int16 x1, int16 y1, int16 x2, int16 y2) {
	_minXClip = x1;
	_minYClip = y1;
	_maxXClip = x2;
	_maxYClip = y2;
}

void Renderer3D::setZBufferRegion(int16 sx, int16 sy, int16 dx) {
	_zBufStartX = sx;
	_zBufStartY = sy;
	_zBufWid = dx;
}

/*------------------------------------------------
	Determines whether a triangle has clockwise
	or counterclockwise vertices
--------------------------------------------------*/
int8 Renderer3D::clockWise(int16 x1, int16 y1, int16 x2, int16 y2, int16 x3, int16 y3) {
	x2 -= x1;
	y2 -= y1;

	x3 -= x1;
	y3 -= y1;

	int32 a1 = ((int32)x2) * y3;
	int32 a2 = ((int32)y2) * x3;

	if (a1 > a2)
		return 1; // clockwise
	if (a1 < a2)
		return -1; // counterclockwise

	a1 = ((int32)x2) * x3;
	a2 = ((int32)y2) * y3;
	if (a1 < 0 || a2 < 0)
		return -1;

	a1 = ((int32)x2) * x2 + ((int32)y2) * y2;
	a2 = ((int32)x3) * x3 + ((int32)y3) * y3;
	if (a1 < a2)
		return 1;

	return 0;
}

/*------------------------------------------------
	Draw the character
--------------------------------------------------*/
void Renderer3D::drawCharacter(uint8 flag) {
	Actor *actor = _vm->_actor;

	// Compute pointer to frame
	if (flag & CALCPOINTS) {
		if (actor->_curAction > hLAST)
			error("Error in drawCharacter() - _curAction > hLAST");

		int cfp = 0;
		int cur = 0;
		while (cur < actor->_curAction)
			cfp += _vm->_defActionLen[cur++];

		if (actor->_curAction == hWALKOUT)
			cfp = 1;

		cfp += actor->_curFrame;

		if (actor->_curAction == hLAST)
			cfp = 0;

		actor->_vertex = &actor->_characterArea[cfp * actor->_vertexNum];
	}

	SCamera *_curCamera = actor->_camera;
	SLight *_curLight = actor->_light;
	STexture *_curTexture = actor->_texture;
	SVertex *_curVertex = actor->_vertex;
	SFace *_curFace = actor->_face;

	int vertexNum = actor->_vertexNum;

	if (flag & CALCPOINTS) {
		_shadowLightNum = 0;
		_totalShadowVerts = 0;

		// camera matrix
		float e10 = _curCamera->_e1[0];
		float e11 = _curCamera->_e1[1];
		float e12 = _curCamera->_e1[2];

		float e20 = _curCamera->_e2[0];
		float e21 = _curCamera->_e2[1];
		float e22 = _curCamera->_e2[2];

		float e30 = _curCamera->_e3[0];
		float e31 = _curCamera->_e3[1];
		float e32 = _curCamera->_e3[2];

		// Light directions
		float l0 = 0.0;
		float l1 = 0.0;
		float l2 = 0.0;

		actor->_lim[0] = 32000;
		actor->_lim[1] = -32000;
		actor->_lim[2] = 32000;
		actor->_lim[3] = -32000;
		actor->_lim[4] = 32000;
		actor->_lim[5] = -32000;

		float t = (actor->_theta * PI2) / 360.0;
		float cost = cos(t);
		float sint = sin(t);

		// Put all vertices in dark color
		for (int i = 0; i < MAXVERTEX; ++i)
			_vVertex[i]._angle = 180;

		float dist;
		float tx = 0;
		float ty = 0;
		float tz = 0;
		float pa0, pa1, pa2;

		for (uint32 b = 0; b < actor->_lightNum; b++) {
			// if off                lint == 0
			// if it has a shadow    lint & 0x80

			int lint = _curLight->_inten & 0x7F;
			if (lint) {                                       // if it's not turned off
				tx = _curLight->_x - actor->_px - actor->_dx; // computes direction vector
				tz = _curLight->_z - actor->_pz - actor->_dz; // between light and actor
				ty = _curLight->_y;

				if (_curLight->_position) {                   // if it's attenuated
					dist = sqrt(tx * tx + ty * ty + tz * tz); // Distance light <--> actor

					// adjust light intensity due to the distance
					if (dist > _curLight->_outr) // if it's out of range it's off
						lint = 0;
					else if (dist > _curLight->_inr) // if it's inside the circle it's decreased
						lint = (int)((float)lint * (_curLight->_outr - dist) / (_curLight->_outr - _curLight->_inr));
				}
			}

			if (lint) { // If it's still on
				// Light rotates around the actor
				l0 = tx * cost - tz * sint;
				l2 = tx * sint + tz * cost;
				l1 = ty;
				t = sqrt(l0 * l0 + l1 * l1 + l2 * l2);
				l0 /= t;
				l1 /= t;
				l2 /= t;

				// Adjust light intensity according to the spot
				tx = (float)_curLight->_fallOff;
				if (tx) { // for light spot only
					ty = (float)_curLight->_hotspot;

					pa0 = _curLight->_dx * cost - _curLight->_dz * sint;
					pa1 = _curLight->_dy;
					pa2 = _curLight->_dx * sint + _curLight->_dz * cost;

					t = sqrt(pa0 * pa0 + pa1 * pa1 + pa2 * pa2);
					pa0 /= t;
					pa1 /= t;
					pa2 /= t;

					tz = acos((pa0 * l0) + (pa1 * l1) + (pa2 * l2)) * 360.0 / PI2;
					tz = CLIP(tz, 0.f, 180.f);

					// tx falloff
					// ty hotspot
					// tz current angle

					_shadowIntens[_shadowLightNum] = SHADOWAMBIENT;

					if (tz > tx) { // if it's out of the falloff
						lint = 0;
						_shadowIntens[_shadowLightNum] = 0;
					} else if (tz > ty) { // if it's between the falloff and the hotspot
						lint = (int)((float)lint * (tx - tz) / (tx - ty));
						_shadowIntens[_shadowLightNum] = (int)((float)_shadowIntens[_shadowLightNum] * (tx - tz) / (tx - ty));
					}
				}
			}

			if ((_curLight->_inten & 0x80) && lint) { // if it's shadowed and still on
				_curVertex = actor->_vertex;

				// casts shadow vertices
				for (int a = 0; a < SHADOWVERTSNUM; a++) {
					pa0 = _curVertex[_shadowVerts[a]]._x;
					pa1 = _curVertex[_shadowVerts[a]]._y;
					pa2 = _curVertex[_shadowVerts[a]]._z;

					_shVertex[vertexNum + _totalShadowVerts + a]._x = pa0 - (pa1 * l0);
					_shVertex[vertexNum + _totalShadowVerts + a]._z = pa2 - (pa1 * l2);
					_shVertex[vertexNum + _totalShadowVerts + a]._y = 0;
				}

				// per default all shadows are equally faint
				// _shadowIntens[_shadowLightNum] = SHADOWAMBIENT;

				_shadowLightNum++;
				_totalShadowVerts += SHADOWVERTSNUM;
			}

			if (lint) { // if still on
				// adapts the light vector o its intensity
				t = (float)(lint) / 127.0;
				l0 = l0 * t;
				l1 = l1 * t;
				l2 = l2 * t;

				_curVertex = actor->_vertex;
				for (int a = 0; a < vertexNum; a++) {
					pa0 = _curVertex->_nx;
					pa1 = _curVertex->_ny;
					pa2 = _curVertex->_nz;

					lint = (int)((acos(pa0 * l0 + pa1 * l1 + pa2 * l2) * 360.0) / PI);
					lint = CLIP(lint, 0, 180);

					_vVertex[a]._angle -= (180 - lint);
					_curVertex++;
				}
			}

			_curLight++;
		}

		// rearranged light values so they can be viewed
		for (int a = 0; a < vertexNum; a++)
			_vVertex[a]._angle = CLIP(_vVertex[a]._angle, 0, 180);

		_curVertex = actor->_vertex;

		// Calculate the distance of the character from the room
		tx = _curCamera->_ex - actor->_px;
		ty = _curCamera->_ey;
		tz = _curCamera->_ez - actor->_pz;

		dist = tx * e30 + ty * e31 + tz * e32;

		for (int a = 0; a < vertexNum + _totalShadowVerts; a++) {
			if (a < vertexNum) {
				l0 = _curVertex->_x;
				l1 = _curVertex->_z;
				pa1 = ty - _curVertex->_y;
			} else {
				l0 = _shVertex[a]._x;
				l1 = _shVertex[a]._z;
				pa1 = ty - _shVertex[a]._y;
			}

			pa0 = tx - (l0 * cost + l1 * sint); // rotate _curVertex
			pa2 = tz - (-l0 * sint + l1 * cost);

			l0 = pa0 * e10 + pa1 * e11 + pa2 * e12; // project _curVertex
			l1 = pa0 * e20 + pa1 * e21 + pa2 * e22;
			l2 = pa0 * e30 + pa1 * e31 + pa2 * e32;

			int _x2d = _vm->_cx + (int)((l0 * _curCamera->_fovX) / l2);
			int _y2d = _vm->_cy + (int)((l1 * _curCamera->_fovY) / l2);

			_vVertex[a]._x = _x2d;
			_vVertex[a]._y = _y2d;
			_vVertex[a]._z = (int32)((dist - l2) * 128.0);

			actor->_lim[0] = MIN(_x2d, actor->_lim[0]);
			actor->_lim[1] = MAX(_x2d, actor->_lim[1]);
			actor->_lim[2] = MIN(_y2d, actor->_lim[2]);
			actor->_lim[3] = MAX(_y2d, actor->_lim[3]);

			actor->_lim[4] = MIN(_vVertex[a]._z, actor->_lim[4]);
			actor->_lim[5] = MAX(_vVertex[a]._z, actor->_lim[5]);

			_curVertex++;
		}
		actor->_lim[4] = (int)dist;
		actor->_lim[5] = (int)dist;

		// vertex clipping
		actor->_lim[0] = (actor->_lim[0] <= _minXClip + 1) ? _minXClip : actor->_lim[0]--;
		actor->_lim[1] = (actor->_lim[1] >= _maxXClip - 1) ? _maxXClip : actor->_lim[1]++;
		actor->_lim[2] = (actor->_lim[2] <= _minYClip + 1) ? _minYClip : actor->_lim[2]--;
		actor->_lim[3] = (actor->_lim[3] >= _maxYClip - 1) ? _maxYClip : actor->_lim[3]++;

		if (actor->_curAction == hLAST) // exit displacer
			actor->_lim[2] = actor->_lim[3] - (((actor->_lim[3] - actor->_lim[2]) * actor->_curFrame) / _vm->_defActionLen[hLAST]);

		// set zbuffer vars
		setZBufferRegion(actor->_lim[0], actor->_lim[2], actor->_lim[1] - actor->_lim[0]);
	}

	if (flag & DRAWFACES) {
		if (actor->_curAction == hLAST)
			setClipping(0, actor->_lim[2], MAXX, actor->_lim[3]);

		for (int b = 0; b < _shadowLightNum; b++) {
			for (int a = 0; a < SHADOWFACESNUM; a++) {
				int p0 = _shadowFaces[a][0] + vertexNum + b * SHADOWVERTSNUM;
				int p1 = _shadowFaces[a][1] + vertexNum + b * SHADOWVERTSNUM;
				int p2 = _shadowFaces[a][2] + vertexNum + b * SHADOWVERTSNUM;

				int px0 = _vVertex[p0]._x;
				int py0 = _vVertex[p0]._y;
				int px1 = _vVertex[p1]._x;
				int py1 = _vVertex[p1]._y;
				int px2 = _vVertex[p2]._x;
				int py2 = _vVertex[p2]._y;

				shadowTriangle(px0, py0, px1, py1, px2, py2, 127 - _shadowIntens[b], (int16)(0x7FF0 + b));
			}
		}

		for (uint a = 0; a < actor->_faceNum; ++a) {
			int p0 = _curFace->_a;
			int p1 = _curFace->_b;
			int p2 = _curFace->_c;

			int px0 = _vVertex[p0]._x;
			int py0 = _vVertex[p0]._y;
			int px1 = _vVertex[p1]._x;
			int py1 = _vVertex[p1]._y;
			int px2 = _vVertex[p2]._x;
			int py2 = _vVertex[p2]._y;

			if (clockWise(px0, py0, px1, py1, px2, py2) > 0) {
				uint16 b = _curFace->_mat;
				if (_curTexture[b]._flag & TEXTUREACTIVE) {
					textureTriangle(px0, py0, _vVertex[p0]._z, _vVertex[p0]._angle, actor->_textureCoord[a][0][0], actor->_textureCoord[a][0][1],
									px1, py1, _vVertex[p1]._z, _vVertex[p1]._angle, actor->_textureCoord[a][1][0], actor->_textureCoord[a][1][1],
									px2, py2, _vVertex[p2]._z, _vVertex[p2]._angle, actor->_textureCoord[a][2][0], actor->_textureCoord[a][2][1],
									&_curTexture[b]);
				}
			}

			_curFace++;
		}

		int p0 = 0;
		for (int b = _zBufStartY; b < actor->_lim[3]; b++) {
			int px0 = b * MAXX + _zBufStartX;
			for (int a = 1; a < _zBufWid; a++) {
				// CHECKME: These are always 0
				//bool _shadowSplit;
				int py1 = 0; //(_zBuf[p0]   >= 0x7FF0) * 0x8000 * _shadowSplit;
				int py2 = 0; //(_zBuf[p0 + 1] >= 0x7FF0) * 0x8000 * _shadowSplit;

				int p1 = _zBuffer[p0] < 0x7FFF;
				int p2 = _zBuffer[p0 + 1] < 0x7FFF;

				if (p1 != p2) {
					int px1 = _curPage[px0 + a - 1];
					int px2 = _curPage[px0 + a];

					_curPage[px0 + a - 1] = _vm->_graphicsMgr->aliasing(px1, px2, 6); // 75% 25%
					_curPage[px0 + a] = _vm->_graphicsMgr->aliasing(px1, px2, 2);     // 25% 75%

					// if the first is the character
					if (p1)
						_zBuffer[p0] = 0x00BF | py1;
					else
						_zBuffer[p0] = 0x003F | py2;

					if (a + 1 < _zBufWid) {
						p0++;
						a++;

						// if the second is the character
						if (p2)
							_zBuffer[p0] = 0x00BF | py2;
						else
							_zBuffer[p0] = 0x003F | py1;
					}
				} else {
					// set value alpha max
					if (p1)
						_zBuffer[p0] = 0x00FF | py1;
					else
						_zBuffer[p0] = 0x0000 | py1;
				}

				p0++;

				// if it's the last of the line
				if (a == _zBufWid - 1) {
					if (p2)
						_zBuffer[p0] = 0x00FF | py2;
					else
						_zBuffer[p0] = 0x0000 | py2;
				}
			}
			p0++;
		}
		if (actor->_curAction == hLAST)
			setClipping(0, TOP, MAXX, AREA + TOP);
	}
}

void Renderer3D::paintScreen(bool flag) {
	_vm->_animTypeMgr->next();

	_vm->_actorRect = nullptr;
	_vm->_dirtyRects.clear();
	_vm->_flagPaintCharacter = true; // always redraws the character

	int x1 = _vm->_actor->_lim[0];
	int y1 = _vm->_actor->_lim[2] - TOP;
	int x2 = _vm->_actor->_lim[1];
	int y2 = _vm->_actor->_lim[3] - TOP;

	// erase character
	if (_vm->_flagShowCharacter && x2 > x1 && y2 > y1) { // if a description exists
		DObj.rect = Common::Rect(0, TOP, MAXX, AREA + TOP);
		DObj.l = Common::Rect(x1, y1, x2, y2);
		DObj.objIndex = -1;
		DObj.drawMask = false;
		_vm->_graphicsMgr->DrawObj(DObj);

		_vm->addDirtyRect(DObj.l);
		_vm->_actorRect = &_vm->_dirtyRects.back();
	} else if (_vm->_animMgr->_animRect.left != MAXX) {
		DObj.rect = Common::Rect(0, TOP, MAXX, AREA + TOP);
		DObj.l = _vm->_animMgr->_animRect;
		DObj.objIndex = -1;
		DObj.drawMask = false;
		_vm->_graphicsMgr->DrawObj(DObj);

		_vm->addDirtyRect(DObj.l);
		_vm->_actorRect = &_vm->_dirtyRects.back();
	}

	// If there's text to remove
	if (_vm->_textStatus & TEXT_DEL) {
		// remove text
		DObj.rect = Common::Rect(0, TOP, MAXX, MAXY + TOP);
		DObj.l = _vm->_textMgr->getOldTextRect();
		DObj.l.translate(0, -TOP);
		DObj.objIndex = -1;
		DObj.drawMask = false;

		if (DObj.l.top >= 0 && DObj.l.bottom < AREA) {
			_vm->_graphicsMgr->DrawObj(DObj);
		} else {
			_vm->_graphicsMgr->EraseObj(DObj);
		}
		_vm->_textMgr->clearOldText();
		_vm->addDirtyRect(DObj.l);

		if (!(_vm->_textStatus & TEXT_DRAW)) // if there's no new text
			_vm->_textStatus = TEXT_OFF;     // stop updating text
	}

	// Suppress all the objects you removed
	for (Common::List<SSortTable>::iterator i = _vm->_sortTable.begin(); i != _vm->_sortTable.end(); ++i) {
		if (i->_remove) {
			DObj.rect = Common::Rect(0, TOP, MAXX, AREA + TOP);

			DObj.l = _vm->_obj[i->_objectId]._rect;
			DObj.objIndex = -1;
			DObj.drawMask = false;
			_vm->_graphicsMgr->DrawObj(DObj);
			_vm->addDirtyRect(DObj.l);
		}
	}

	// Find the position of the character
	_vm->_pathFind->actorOrder();

	// For every box from the horizon forward...
	// Copy per level
	for (int liv = _vm->_pathFind->_numSortPan; liv >= 0; liv--) {
		uint16 curBox = _vm->_pathFind->_sortPan[liv]._num;

		// draws all objects and animations that intersect the boundaries and refer to the current box
		paintObjAnm(curBox);
	}

	if (_vm->_textStatus & TEXT_DRAW) {
		_vm->_textMgr->drawCurString();
		_vm->_textStatus = TEXT_DRAW; // Activate text update
	}

	_vm->_soundMgr->SoundPasso((_vm->_actor->_lim[1] + _vm->_actor->_lim[0]) / 2, (_vm->_actor->_lim[5] + _vm->_actor->_lim[4]) / 2, _vm->_actor->_curAction, _vm->_actor->_curFrame, _vm->_room[_vm->_curRoom]._sounds);

	if (!flag && !_vm->_flagDialogActive) {
		_vm->_graphicsMgr->copyToScreen(0, 0, MAXX, MAXY);
	}

	_vm->_sortTable.clear();

	_vm->_flagPaintCharacter = false;
	_vm->_flagWaitRegen = false;

	// Handle papaverine delayed action
	if ((_vm->_curRoom == kRoom4A) && (_vm->_obj[oCHOCOLATES4A]._flag & kObjFlagExtra)) {
		if (_vm->_animMgr->smkCurFrame(kSmackerBackground) > 480) {
			_vm->playScript(s4AHELLEN);
			_vm->_obj[oCHOCOLATES4A]._flag &= ~kObjFlagExtra;
		}
	}
	//
}

/* -------------------------------------------------
    Draw all objects and animations that intersect
         boundaries belonging to curbox
 --------------------------------------------------*/
void Renderer3D::paintObjAnm(uint16 curBox) {
	_vm->_animMgr->refreshAnim(curBox);

	// draws new cards belonging to the current box
	for (Common::List<SSortTable>::iterator i = _vm->_sortTable.begin(); i != _vm->_sortTable.end(); ++i) {
		if (!i->_remove && _vm->_obj[i->_objectId]._nbox == curBox) {
			// the bitmap object at the desired level
			SObject obj = _vm->_obj[i->_objectId];
			DObj.rect = obj._rect;
			DObj.rect.translate(0, TOP);
			DObj.l = Common::Rect(DObj.rect.width(), DObj.rect.height());
			DObj.objIndex = _vm->getRoomObjectIndex(i->_objectId);
			DObj.drawMask = obj._mode & OBJMODE_MASK;
			_vm->_graphicsMgr->DrawObj(DObj);
			_vm->_dirtyRects.push_back(DObj.rect);
		}
	}

	for (DirtyRectsIterator d = _vm->_dirtyRects.begin(); d != _vm->_dirtyRects.end(); ++d) {
		for (int b = 0; b < MAXOBJINROOM; b++) {
			const uint16 curObject = _vm->_room[_vm->_curRoom]._object[b];
			if (!curObject)
				break;

			SObject obj = _vm->_obj[curObject];

			if ((obj._mode & (OBJMODE_FULL | OBJMODE_MASK)) && _vm->isObjectVisible(curObject) && (obj._nbox == curBox)) {
				Common::Rect r = *d;
				Common::Rect r2 = obj._rect;

				r2.translate(0, TOP);

				// Include the bottom right of the rect in the intersects() check
				r2.bottom++;
				r2.right++;

				if (r.intersects(r2)) {
					DObj.rect = obj._rect;
					DObj.rect.translate(0, TOP);

					// Restore the bottom right of the rect
					r2.bottom--;
					r2.right--;

					// TODO: Simplify this?
					const int16 xr1 = (r2.left > r.left) ? 0 : r.left - r2.left;
					const int16 yr1 = (r2.top > r.top) ? 0 : r.top - r2.top;
					const int16 xr2 = MIN<int16>(r.right, r2.right) - r2.left;
					const int16 yr2 = MIN<int16>(r.bottom, r2.bottom) - r2.top;
					DObj.l = Common::Rect(xr1, yr1, xr2, yr2);
					DObj.objIndex = b;
					DObj.drawMask = obj._mode & OBJMODE_MASK;

					_vm->_graphicsMgr->DrawObj(DObj);
				}
			}
		}
	}

	if (_vm->_actorPos == curBox && _vm->_flagShowCharacter && _vm->_flagCharacterExists) {
		drawCharacter(CALCPOINTS);

		int x1 = _vm->_actor->_lim[0];
		int y1 = _vm->_actor->_lim[2];
		int x2 = _vm->_actor->_lim[1];
		int y2 = _vm->_actor->_lim[3];

		if (x2 > x1 && y2 > y1) {
			// enlarge the rectangle of the character
			Common::Rect l(x1, y1, x2, y2);
			if (_vm->_actorRect)
				_vm->_actorRect->extend(l);

			resetZBuffer(x1, y1, x2, y2);
		}

		drawCharacter(DRAWFACES);

	} else if (_vm->_actorPos == curBox && !_vm->_flagDialogActive) {
		_vm->_animMgr->refreshSmkAnim(_vm->_animMgr->_playingAnims[kSmackerAction]);
	}
}

// Path Finding
PathFinding3D::PathFinding3D(TrecisionEngine *vm) : _vm(vm) {
	_lookX = 0.0f;
	_lookZ = 0.0f;
	_curStep = 0;
	_lastStep = 0;

	_characterInMovement = false;
	_characterGoToPosition = -1;

	_panelNum = 0;

	for (int i = 0; i < MAXPATHNODES; ++i)
		_pathNode[i].clear();

	_curPanel = -1;
	_oldPanel = -1;

	_numPathNodes = 0;
	_numSortPan = 0;
	_x3d = 0.0f;
	_y3d = 0.0f;
	_z3d = 0.0f;

	_curX = 0.0f;
	_curZ = 0.0f;

	for (int i = 0; i < 3; ++i) {
		_invP[i][0] = 0.0f;
		_invP[i][1] = 0.0f;
		_invP[i][2] = 0.0f;
	}

	for (int i = 0; i < MAXPANELSINROOM; ++i)
		_panel[i].clear();

	for (int i = 0; i < 32; ++i) {
		_sortPan[i]._num = 0;
		_sortPan[i]._min = 0.0f;
	}

	for (int i = 0; i < MAXSTEP; ++i)
		_step[i].clear();
}

PathFinding3D::~PathFinding3D() {
}

void PathFinding3D::findPath() {
	int b;

	Actor *actor = _vm->_actor;
	actor->_px += actor->_dx;
	actor->_pz += actor->_dz;

	int inters = 0;
	_numPathNodes = 0;

	// if you have clicked behind the starting panel or the corner it's not possible to walk
	if ((_curPanel < 0) && (_oldPanel >= 0) &&
		// behind the starting panel
		(pointInside(b = _oldPanel, _curX, _curZ) ||
		 // behind the panel corner1
		 ((_vm->dist2D(_panel[_oldPanel]._x1, _panel[_oldPanel]._z1, actor->_px, actor->_pz) < EPSILON) &&
		  (pointInside(b = _panel[_oldPanel]._near1, _curX, _curZ) ||
		   pointInside(b = _panel[_oldPanel]._near2, _curX, _curZ))) ||
		 // behind the panel corner2
		 ((_vm->dist2D(_panel[_oldPanel]._x2, _panel[_oldPanel]._z2, actor->_px, actor->_pz) < EPSILON) &&
		  (pointInside(b = _panel[_oldPanel]._near2, _curX, _curZ) ||
		   pointInside(b = _panel[_oldPanel]._near1, _curX, _curZ))))) {
		_curX = actor->_px;
		_curZ = actor->_pz;
		actor->_px -= actor->_dx;
		actor->_pz -= actor->_dz;
		_curPanel = b;
		_numPathNodes = 0;
		lookAt(_lookX, _lookZ);
		return;
	}

	float dist = _vm->dist2D(actor->_px, actor->_pz, _curX, _curZ);

	for (b = 0; b < _panelNum; b++) {
		if (_panel[b]._flags & 0x80000000) { // it must be a wide panel
			if (intersectLineLine(_panel[b]._x1, _panel[b]._z1,
								  _panel[b]._x2, _panel[b]._z2,
								  actor->_px, actor->_pz, _curX, _curZ)) {
				inters++;

				_pathNode[_numPathNodes]._x = _x3d;
				_pathNode[_numPathNodes]._z = _z3d;
				_pathNode[_numPathNodes]._dist = _vm->dist2D(actor->_px, actor->_pz, _x3d, _z3d);
				_pathNode[_numPathNodes]._oldPanel = b;
				_pathNode[_numPathNodes]._curPanel = b;
				_numPathNodes++;

				// CORNERS - lever intersections in corners
				if ((b == _panel[_oldPanel]._near1) || (b == _panel[_oldPanel]._near2)) {
					// otherwise if it's near the starting panel
					if ((_pathNode[_numPathNodes - 1]._dist < EPSILON) &&
						(b != _oldPanel) && (b != _curPanel)) {
						// and the distance is very small to the intersection
						inters--;
						_numPathNodes--;

						// If the click is inside the nearby panel
						if ((_curPanel < 0) && (pointInside(b, _curX, _curZ))) {
							_curX = actor->_px;
							_curZ = actor->_pz;
							actor->_px -= actor->_dx;
							actor->_pz -= actor->_dz;

							_curPanel = b;
							lookAt(_lookX, _lookZ);
							return;
						}
					}
				} else if ((b == _panel[_curPanel]._near1) || (b == _panel[_curPanel]._near2)) {
					// otherwise if it is near the finish panel
					if ((fabs(_pathNode[_numPathNodes - 1]._dist - dist) < EPSILON) &&
						(b != _oldPanel) && (b != _curPanel)) {
						// and the distance is very small to the intersection
						inters--;
						_numPathNodes--;
					}
				}

			} else if (b == _oldPanel) {
				// always adds start and finish node only in on a panel
				inters++;

				_pathNode[_numPathNodes]._x = actor->_px;
				_pathNode[_numPathNodes]._z = actor->_pz;
				_pathNode[_numPathNodes]._dist = 0.0;
				_pathNode[_numPathNodes]._oldPanel = _oldPanel;
				_pathNode[_numPathNodes]._curPanel = _oldPanel;
				_numPathNodes++;
			} else if (b == _curPanel) {
				inters++;

				_pathNode[_numPathNodes]._x = _curX;
				_pathNode[_numPathNodes]._z = _curZ;
				_pathNode[_numPathNodes]._dist = dist;
				_pathNode[_numPathNodes]._oldPanel = _curPanel;
				_pathNode[_numPathNodes]._curPanel = _curPanel;
				_numPathNodes++;
			}
		}
	}

	// the path is defined by:
	// start        _actor._px, _actor._pz
	// _numPathNodes _pathNode
	// end          _curX, _curZ

	// if it collides with any panel
	if (inters) {
		sortPath();

		// if odd and I go to the floor but I did not start from the panel
		// if it arrives on the floor and the last two nodes are not on the same block
		// if outside the last panel it moves the last node

		if (((inters & 1) && (_curPanel < 0) && (_oldPanel < 0)) ||
			((inters - 1 & 1) && (_curPanel < 0) &&
			 (!findAttachedPanel(_pathNode[_numPathNodes - 2]._curPanel, _pathNode[_numPathNodes - 1]._curPanel) ||
			  pointInside(_pathNode[_numPathNodes - 1]._curPanel, _curX, _curZ)))) {

			_curPanel = _pathNode[_numPathNodes - 1]._curPanel;

			pointOut(); // remove the point found

			_pathNode[_numPathNodes]._x = _curX;
			_pathNode[_numPathNodes]._z = _curZ;
			_pathNode[_numPathNodes]._oldPanel = _curPanel;
			_pathNode[_numPathNodes]._curPanel = _curPanel;

			_numPathNodes++;
		}

		// if it arrives on the floor
		inters = 0;

		// Count the intersections with narrow panels
		// and with the union of large panels and small panels
		for (b = 0; b < _panelNum; b++) {
			if (!(_panel[b]._flags & 0x80000000)) {
				if (intersectLineLine(_panel[b]._x1, _panel[b]._z1,
									  _panel[b]._x2, _panel[b]._z2,
									  _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z,
									  _curX, _curZ))
					inters++;
			} else {
				if (_panel[b]._col1 & 0x80) {
					if (intersectLineLine(_panel[b]._x1, _panel[b]._z1,
										  _panel[_panel[b]._col1 & 0x7F]._x2, _panel[_panel[b]._col1 & 0x7F]._z2,
										  _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z,
										  _curX, _curZ))
						if ((_vm->dist2D(_x3d, _z3d, _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z) > EPSILON) &&
							(_vm->dist2D(_x3d, _z3d, _curX, _curZ) > EPSILON))
							inters++;
				} else {
					if (intersectLineLine(_panel[b]._x1, _panel[b]._z1,
										  _panel[_panel[b]._col1 & 0x7F]._x1, _panel[_panel[b]._col1 & 0x7F]._z1,
										  _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z,
										  _curX, _curZ))
						if ((_vm->dist2D(_x3d, _z3d, _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z) > EPSILON) &&
							(_vm->dist2D(_x3d, _z3d, _curX, _curZ) > EPSILON))
							inters++;
				}

				if (_panel[b]._col2 & 0x80) {
					if (intersectLineLine(_panel[b]._x2, _panel[b]._z2,
										  _panel[_panel[b]._col2 & 0x7F]._x2, _panel[_panel[b]._col2 & 0x7F]._z2,
										  _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z,
										  _curX, _curZ))
						if ((_vm->dist2D(_x3d, _z3d, _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z) > EPSILON) &&
							(_vm->dist2D(_x3d, _z3d, _curX, _curZ) > EPSILON))
							inters++;
				} else {
					if (intersectLineLine(_panel[b]._x2, _panel[b]._z2,
										  _panel[_panel[b]._col2 & 0x7F]._x1, _panel[_panel[b]._col2 & 0x7F]._z1,
										  _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z,
										  _curX, _curZ))
						if ((_vm->dist2D(_x3d, _z3d, _pathNode[_numPathNodes - 1]._x, _pathNode[_numPathNodes - 1]._z) > EPSILON) &&
							(_vm->dist2D(_x3d, _z3d, _curX, _curZ) > EPSILON))
							inters++;
				}
			}

			if (inters)
				break;
		}

		// If in the last line there's an obstacle, remove the first node
		if (inters) {
			_curPanel = _pathNode[_numPathNodes - 1]._curPanel;

			pointOut(); // take out the point found

			_pathNode[_numPathNodes]._x = _curX;
			_pathNode[_numPathNodes]._z = _curZ;
			_pathNode[_numPathNodes]._oldPanel = _curPanel;
			_pathNode[_numPathNodes]._curPanel = _curPanel;

			_numPathNodes++;
		}

		_pathNode[_numPathNodes]._x = _curX;
		_pathNode[_numPathNodes]._z = _curZ;
		_pathNode[_numPathNodes]._dist = _vm->dist2D(actor->_px, actor->_pz, _curX, _curZ);
		_pathNode[_numPathNodes]._oldPanel = _curPanel;
		_pathNode[_numPathNodes]._curPanel = _curPanel;
		_numPathNodes++;

		findShortPath();
		displayPath();
	} else { // otherwise if it's direct
		_pathNode[_numPathNodes]._x = actor->_px;
		_pathNode[_numPathNodes]._z = actor->_pz;
		_pathNode[_numPathNodes]._dist = 0.0;
		_pathNode[_numPathNodes]._oldPanel = _oldPanel;
		_pathNode[_numPathNodes]._curPanel = _oldPanel;
		_numPathNodes++;

		_pathNode[_numPathNodes]._x = _curX;
		_pathNode[_numPathNodes]._z = _curZ;
		_pathNode[_numPathNodes]._dist = _vm->dist2D(actor->_px, actor->_pz, _curX, _curZ);
		_pathNode[_numPathNodes]._oldPanel = _curPanel;
		_pathNode[_numPathNodes]._curPanel = _curPanel;
		_numPathNodes++;

		displayPath();
	}

	actor->_px -= actor->_dx;
	actor->_pz -= actor->_dz;
}
/*------------------------------------------------
  Look for the shorter route avoiding obstacle
--------------------------------------------------*/
void PathFinding3D::findShortPath() {
	SPathNode TempPath[MAXPATHNODES];
	float len1, len2;
	int curp, nearp, oldp;
	float destx, destz;
	signed int a, b, c, fail = 0;

	int count = 0;
	// Add departure
	TempPath[count]._x = _vm->_actor->_px;
	TempPath[count]._z = _vm->_actor->_pz;
	TempPath[count]._dist = 0.0;
	TempPath[count]._oldPanel = _oldPanel;
	TempPath[count]._curPanel = _oldPanel;
	count++;

	// for every obstacle, try to go around it by the right and the left
	// then take the sorter path
	for (a = 0; a < _numPathNodes - 1; a++) {
		memcpy(&TempPath[count], &_pathNode[a], sizeof(SPathNode));
		count++;
		if (count >= MAXPATHNODES - 2)
			count = MAXPATHNODES - 2;

		curp = _pathNode[a]._curPanel;

		// if source and destination panel are on the same block
		if (!findAttachedPanel(curp, _pathNode[a + 1]._curPanel))
			continue;

		// go around obstacle starting with _near1
		len1 = evalPath(a, _panel[curp]._x1, _panel[curp]._z1, _panel[curp]._near1) + _vm->dist2D(_pathNode[a]._x, _pathNode[a]._z, _panel[curp]._x1, _panel[curp]._z1);

		// go around obstacle starting with _near2
		len2 = evalPath(a, _panel[curp]._x2, _panel[curp]._z2, _panel[curp]._near2) + _vm->dist2D(_pathNode[a]._x, _pathNode[a]._z, _panel[curp]._x2, _panel[curp]._z2);

		// Check which route was shorter
		if ((len1 < 32000.0) && (len2 < 32000.0)) {
			if (len1 < len2) {
				destx = _panel[curp]._x1;
				destz = _panel[curp]._z1;
				nearp = _panel[curp]._near1;
			} else {
				destx = _panel[curp]._x2;
				destz = _panel[curp]._z2;
				nearp = _panel[curp]._near2;
			}

			float curx = _pathNode[a]._x;
			float curz = _pathNode[a]._z;
			oldp = curp;

			b = 0;

			// Save the shorter path
			for (;;) {
				TempPath[count]._x = curx;
				TempPath[count]._z = curz;
				TempPath[count]._oldPanel = oldp;
				TempPath[count]._curPanel = curp;
				count++;
				if (count >= MAXPATHNODES - 2)
					count = MAXPATHNODES - 2;

				// if it reaches the point, exit the loop
				if (curp == _pathNode[a + 1]._curPanel) {
					memcpy(&TempPath[count], &_pathNode[a + 1], sizeof(SPathNode));
					count++;
					if (count >= MAXPATHNODES - 2)
						count = MAXPATHNODES - 2;
					break;
				}

				// If it's back to the starting panel, it didn't find a route
				if (((curp == _pathNode[a]._curPanel) && b) || (b > _panelNum)) {
					fail = 1; // stop at the edge first
					break;    // and stop walking
				}

				// otherwise go to the next panel

				if (_panel[nearp]._near1 == curp) {
					// go to summit 2 next time
					curx = destx;
					curz = destz;

					destx = _panel[nearp]._x2;
					destz = _panel[nearp]._z2;

					oldp = curp;
					curp = nearp;
					nearp = _panel[curp]._near2;
				} else {
					// go to summit 1 next time
					curx = destx;
					curz = destz;

					destx = _panel[nearp]._x1;
					destz = _panel[nearp]._z1;

					oldp = curp;
					curp = nearp;
					nearp = _panel[curp]._near1;
				}

				b++;
			}
		} else {
			fail = 1;
		}

		if (fail) // if it failed to go around the obstacle, stop
			break;
	}

	// adds arrival
	TempPath[count]._x = _curX;
	TempPath[count]._z = _curZ;
	TempPath[count]._dist = 0.0;
	TempPath[count]._oldPanel = _curPanel;
	TempPath[count]._curPanel = _curPanel;
	count++;

	// after walking around all obstacles, optimize
	_numPathNodes = 0;
	for (a = 0; a < count; a++) {
		if (_numPathNodes > MAXPATHNODES - 2)
			_numPathNodes = MAXPATHNODES - 2;

		// remove all the attached nodes
		for (b = count - 1; b >= a; b--) {
			if (_vm->dist2D(TempPath[b]._x, TempPath[b]._z, TempPath[a]._x, TempPath[a]._z) < EPSILON)
				break;
		}

		a = b;

		memcpy(&_pathNode[_numPathNodes], &TempPath[a], sizeof(SPathNode));
		_numPathNodes++;

		for (b = count - 1; b > a + 1; b--) {
			int inters = 0;
			for (c = 0; c < _panelNum; c++) {
				// it must never intersect the small panel
				if (!(_panel[c]._flags & 0x80000000)) {
					if (intersectLineLine(_panel[c]._x1, _panel[c]._z1,
										  _panel[c]._x2, _panel[c]._z2,
										  TempPath[a]._x, TempPath[a]._z,
										  TempPath[b]._x, TempPath[b]._z))
						inters++;

					if (_panel[c]._col1 & 0x80) {
						if (intersectLineLine(_panel[c]._x1, _panel[c]._z1,
											  _panel[_panel[c]._col1 & 0x7F]._x2, _panel[_panel[c]._col1 & 0x7F]._z2,
											  TempPath[a]._x, TempPath[a]._z,
											  TempPath[b]._x, TempPath[b]._z)) {
							len2 = _vm->dist2D(_x3d, _z3d, TempPath[a]._x, TempPath[a]._z);
							len1 = _vm->dist2D(_x3d, _z3d, TempPath[b]._x, TempPath[b]._z);

							// intersect at a point distant from the start and the finish
							if ((len1 > EPSILON) && (len2 > EPSILON))
								inters++;
						}
					} else {
						if (intersectLineLine(_panel[c]._x1, _panel[c]._z1,
											  _panel[_panel[c]._col1 & 0x7F]._x1, _panel[_panel[c]._col1 & 0x7F]._z1,
											  TempPath[a]._x, TempPath[a]._z,
											  TempPath[b]._x, TempPath[b]._z)) {
							len2 = _vm->dist2D(_x3d, _z3d, TempPath[a]._x, TempPath[a]._z);
							len1 = _vm->dist2D(_x3d, _z3d, TempPath[b]._x, TempPath[b]._z);

							// intersect at a point distant from the start and the finish
							if ((len1 > EPSILON) && (len2 > EPSILON))
								inters++;
						}
					}

					if (_panel[c]._col2 & 0x80) {
						if (intersectLineLine(_panel[c]._x2, _panel[c]._z2,
											  _panel[_panel[c]._col2 & 0x7F]._x2, _panel[_panel[c]._col2 & 0x7F]._z2,
											  TempPath[a]._x, TempPath[a]._z,
											  TempPath[b]._x, TempPath[b]._z)) {
							len2 = _vm->dist2D(_x3d, _z3d, TempPath[a]._x, TempPath[a]._z);
							len1 = _vm->dist2D(_x3d, _z3d, TempPath[b]._x, TempPath[b]._z);

							// intersect at a point distant from the start and the finish
							if ((len1 > EPSILON) && (len2 > EPSILON))
								inters++;
						}
					} else {
						if (intersectLineLine(_panel[c]._x2, _panel[c]._z2,
											  _panel[_panel[c]._col2 & 0x7F]._x1, _panel[_panel[c]._col2 & 0x7F]._z1,
											  TempPath[a]._x, TempPath[a]._z,
											  TempPath[b]._x, TempPath[b]._z)) {
							len2 = _vm->dist2D(_x3d, _z3d, TempPath[a]._x, TempPath[a]._z);
							len1 = _vm->dist2D(_x3d, _z3d, TempPath[b]._x, TempPath[b]._z);

							// intersect at a point distant from the start and the finish
							if ((len1 > EPSILON) && (len2 > EPSILON))
								inters++;
						}
					}

					if (inters)
						break;
				}
			}

			// if from A it's possible to reach B directly
			if (!inters) {
				curp = _pathNode[_numPathNodes - 1]._curPanel;
				oldp = TempPath[b]._oldPanel;

				for (c = a; c <= b; c++) {
					if ((TempPath[c]._oldPanel == curp) && (TempPath[c]._curPanel == oldp))
						break;
				}

				// if they weren't connected it means it went through the floor
				if (c > b) {
					_pathNode[_numPathNodes - 1]._curPanel = -1; // start
					TempPath[b]._oldPanel = -1;                  // destination
				}
				a = b - 1;
				break;
			}
		}
	}
}

/*------------------------------------------------
			Evaluate path length
--------------------------------------------------*/
float PathFinding3D::evalPath(int a, float destX, float destZ, int nearP) {
	int b = 0;
	float len = 0.0f;

	int curPanel = _pathNode[a]._curPanel;
	float curX = _pathNode[a]._x;
	float curZ = _pathNode[a]._z;

	for (;;) {
		// if the point is reached, stop
		if (curPanel == _pathNode[a + 1]._curPanel) {
			len += _vm->dist2D(curX, curZ, _pathNode[a + 1]._x, _pathNode[a + 1]._z);
			break;
		}

		// if it's back to the starting plane, there's no route
		if (((curPanel == _pathNode[a]._curPanel) && b) || (b > _panelNum)) {
			len += 32000.0; // Absurd length
			break;
		}

		// Otherwise it goes to the next plane

		// if nearP is attached to curp via vertex1
		if (_panel[nearP]._near1 == curPanel) {
			// go to vertex 2 next time
			len += _vm->dist2D(curX, curZ, destX, destZ);

			curX = destX;
			curZ = destZ;

			destX = _panel[nearP]._x2;
			destZ = _panel[nearP]._z2;

			curPanel = nearP;
			nearP = _panel[curPanel]._near2;
		} else {
			// go to vertex 1 newt time
			len += _vm->dist2D(curX, curZ, destX, destZ);

			curX = destX;
			curZ = destZ;

			destX = _panel[nearP]._x1;
			destZ = _panel[nearP]._z1;

			curPanel = nearP;
			nearP = _panel[curPanel]._near1;
		}

		b++;
	}

	return len;
}

/*------------------------------------------------
	Check if a point is inside a panel
--------------------------------------------------*/
bool PathFinding3D::pointInside(int pan, float x, float z) {
	if (pan < 0)
		return false;

	if (!(_panel[pan]._flags & 0x80000000))
		return true;

	double pgon[4][2];
	pgon[0][0] = (double)_panel[pan]._x1;
	pgon[0][1] = (double)_panel[pan]._z1;
	pgon[3][0] = (double)_panel[pan]._x2;
	pgon[3][1] = (double)_panel[pan]._z2;

	uint8 idx = _panel[pan]._col1 & 0x7F;
	if (_panel[pan]._col1 & 0x80) {
		pgon[1][0] = (double)_panel[idx]._x2;
		pgon[1][1] = (double)_panel[idx]._z2;
	} else {
		pgon[1][0] = (double)_panel[idx]._x1;
		pgon[1][1] = (double)_panel[idx]._z1;
	}

	idx = _panel[pan]._col2 & 0x7F;
	if (_panel[pan]._col2 & 0x80) {
		pgon[2][0] = (double)_panel[idx]._x2;
		pgon[2][1] = (double)_panel[idx]._z2;
	} else {
		pgon[2][0] = (double)_panel[idx]._x1;
		pgon[2][1] = (double)_panel[idx]._z1;
	}

	double ox = pgon[3][0] - pgon[0][0];
	double oz = pgon[3][1] - pgon[0][1];
	double s = sqrt(ox * ox + oz * oz);
	ox /= s;
	oz /= s;
	pgon[0][0] -= EPSILON * ox;
	pgon[0][1] -= EPSILON * oz;
	pgon[3][0] += EPSILON * ox;
	pgon[3][1] += EPSILON * oz;

	ox = pgon[2][0] - pgon[1][0];
	oz = pgon[2][1] - pgon[1][1];
	s = sqrt(ox * ox + oz * oz);
	ox /= s;
	oz /= s;
	pgon[1][0] -= EPSILON * ox;
	pgon[1][1] -= EPSILON * oz;
	pgon[2][0] += EPSILON * ox;
	pgon[2][1] += EPSILON * oz;

	// Crossing-Multiply algorithm
	double *vtx0 = pgon[3];
	// get test bit for above/below X axis
	bool yflag0 = (vtx0[1] >= z);
	double *vtx1 = pgon[0];

	int counter = 0;
	for (int j = 5; --j;) {
		bool yflag1 = (vtx1[1] >= z);
		if (yflag0 != yflag1) {
			bool xflag0 = (vtx0[0] >= x);
			if ((xflag0 == (vtx1[0] >= x)) && (xflag0))
				counter += (yflag0 ? -1 : 1);
			else if ((vtx1[0] - (vtx1[1] - z) * (vtx0[0] - vtx1[0]) / (vtx0[1] - vtx1[1])) >= x)
				counter += (yflag0 ? -1 : 1);
		}

		// Move to the next pair of vertices, retaining info as possible.
		yflag0 = yflag1;
		vtx0 = vtx1;
		vtx1 += 2;
	}

	return (counter != 0);
}

void PathFinding3D::setPosition(int num) {
	SLight *curLight = _vm->_actor->_light;

	for (uint32 a = 0; a < _vm->_actor->_lightNum; a++) {
		// If it's off
		if (curLight->_inten == 0) {
			// If it's the required position
			if (curLight->_position == num) {
				_vm->_actor->_px = curLight->_x;
				_vm->_actor->_pz = curLight->_z;
				_vm->_actor->_dx = 0.0;
				_vm->_actor->_dz = 0.0;

				float ox = curLight->_dx;
				float oz = curLight->_dz;

				// If it's a null light
				if ((ox == 0.0) && (oz == 0.0))
					warning("setPosition: Unknown error : null light");

				float t = sqrt(ox * ox + oz * oz);
				ox /= t;
				oz /= t;

				float theta = _vm->sinCosAngle(ox, oz) * 180.0f / PI;
				if (theta >= 360.0)
					theta -= 360.0;
				if (theta < 0.0)
					theta += 360.0;

				_vm->_actor->_theta = theta;

				_curStep = 0;
				_lastStep = 0;
				_curPanel = -1;
				_oldPanel = -1;

				reset(0, _vm->_actor->_px + _vm->_actor->_dx, _vm->_actor->_pz + _vm->_actor->_dz, _vm->_actor->_theta);

				_characterGoToPosition = num;
				return;
			}
		}

		curLight++;
	}
}

void PathFinding3D::goToPosition(int num) {
	SLight *_curLight = _vm->_actor->_light;

	for (uint32 a = 0; a < _vm->_actor->_lightNum; a++) {
		// If it's off and if it's a position
		if (_curLight->_inten == 0) {
			// If it's the right position
			if (_curLight->_position == num) {
				_curX = _curLight->_x;
				_curZ = _curLight->_z;
				_lookX = _curX - _curLight->_dx;
				_lookZ = _curZ - _curLight->_dz;

				_curStep = 0;
				_lastStep = 0;

				reset(0, _vm->_actor->_px + _vm->_actor->_dx, _vm->_actor->_pz + _vm->_actor->_dz, _vm->_actor->_theta);

				_oldPanel = _curPanel;
				_curPanel = -1;

				findPath();

				_characterGoToPosition = num;
				break;
			}
		}

		_curLight++;
	}
}

void PathFinding3D::lookAt(float x, float z) {
	float ox = _step[_lastStep]._px - x;
	float oz = _step[_lastStep]._pz - z;

	// If the light is null
	if ((ox == 0.0) && (oz == 0.0)) {
		memcpy(&_step[_lastStep + 1], &_step[_lastStep], sizeof(SStep));
		memcpy(&_step[_lastStep + 2], &_step[_lastStep + 1], sizeof(SStep));
		_lastStep += 2;

		return;
	}

	float t = sqrt(ox * ox + oz * oz);
	ox /= t;
	oz /= t;

	float theta = _vm->sinCosAngle(ox, oz) * 180.0f / PI;
	if (theta >= 360.0f)
		theta -= 360.0f;
	if (theta < 0.0f)
		theta += 360.0f;

	float approx = theta - _step[_lastStep]._theta;

	if ((approx < 30.0f) && (approx > -30.0f))
		approx = 0.0f;
	else if (approx > 180.0f)
		approx = -360.0f + approx;
	else if (approx < -180.0)
		approx = 360.0f + approx;

	approx /= 3.0;

	// Antepenultimate 1/3
	_step[_lastStep]._theta += approx;
	_step[_lastStep]._theta = (_step[_lastStep]._theta > 360.0) ? _step[_lastStep]._theta - 360.0 : (_step[_lastStep]._theta < 0.0) ? _step[_lastStep]._theta + 360.0 : _step[_lastStep]._theta;

	// Penultimate 2/3
	memcpy(&_step[_lastStep + 1], &_step[_lastStep], sizeof(SStep));
	_lastStep++;
	_step[_lastStep]._theta += approx;
	_step[_lastStep]._theta = (_step[_lastStep]._theta > 360.0) ? _step[_lastStep]._theta - 360.0 : (_step[_lastStep]._theta < 0.0) ? _step[_lastStep]._theta + 360.0 : _step[_lastStep]._theta;

	// Last right step
	memcpy(&_step[_lastStep + 1], &_step[_lastStep], sizeof(SStep));
	_lastStep++;
	_step[_lastStep]._theta = theta;

	//	????
	memcpy(&_step[_lastStep + 1], &_step[_lastStep], sizeof(SStep));
	_lastStep++;
	_step[_lastStep]._theta = theta;
}

/*------------------------------------------------
		Build list containing all the frames
--------------------------------------------------*/
void PathFinding3D::buildFramelist() {
	// check that it never crosses or touches a narrow panel
	for (int a = 1; a < _numPathNodes; a++) {
		for (int c = 0; c < _panelNum; c++) {
			// it must never intersect narrow panel
			if (!(_panel[c]._flags & 0x80000000)) {
				if (intersectLineLine(_panel[c]._x1, _panel[c]._z1,
									  _panel[c]._x2, _panel[c]._z2,
									  _pathNode[a - 1]._x, _pathNode[a - 1]._z,
									  _pathNode[a]._x, _pathNode[a]._z)) {
					_numPathNodes = a;
					break;
				}
			}
		}
	}

	float len = 0.0;
	float curLen = 0.0;

	float ox = _pathNode[0]._x;
	float oz = _pathNode[0]._z;

	for (int a = 1; a < _numPathNodes; a++) {
		len += _vm->dist3D(_pathNode[a]._x, 0.0, _pathNode[a]._z, ox, 0.0, oz);

		ox = _pathNode[a]._x;
		oz = _pathNode[a]._z;
	}
	// total route length calculated - if too small, returns
	if (len < 2.0) {
		lookAt(_lookX, _lookZ);
		return;
	}

	int a = 0;
	// compute offset
	SVertex *v = _vm->_actor->_characterArea;
	float firstFrame = _vm->_actor->frameCenter(v);
	float startPos = 0.0;

	// if he was already walking
	int curAction, curFrame, cfp;
	if (_vm->_actor->_curAction == hWALK) {
		// compute current frame
		cfp = _vm->_defActionLen[hSTART] + 1 + _vm->_actor->_curFrame;
		v += cfp * _vm->_actor->_vertexNum;

		curAction = hWALK;
		curFrame = _vm->_actor->_curFrame;

		// if it wasn't the last frame, take the next step
		if (_vm->_actor->_curFrame < _vm->_defActionLen[hWALK] - 1) {
			cfp++;
			curFrame++;
			v += _vm->_actor->_vertexNum;
		}
	} else if ((_vm->_actor->_curAction >= hSTOP0) && (_vm->_actor->_curAction <= hSTOP9)) {
		// if he was stopped, starts moving again

		// compute current frame
		curAction = hWALK;
		//o		CurF = _vm->_actor->_curAction - hSTOP1;
		curFrame = _vm->_actor->_curAction - hSTOP0;

		cfp = _vm->_defActionLen[hSTART] + 1 + curFrame;
		v += cfp * _vm->_actor->_vertexNum;
	} else {
		// if he was standing, start working or turn
		oz = 0.0;
		cfp = 1;

		curAction = hSTART;
		curFrame = 0;

		// start from the first frame
		v += _vm->_actor->_vertexNum;
	}
	oz = -_vm->_actor->frameCenter(v) + firstFrame;

	// at this point, CurA / _curAction is either hSTART or hWALK

	// until it arrives at the destination
	while (((curLen = oz + _vm->_actor->frameCenter(v) - firstFrame) < len) || (!a)) {
		_step[a]._pz = oz - firstFrame; // where to render
		_step[a]._dz = curLen;          // where it is
		_step[a]._curAction = curAction;
		_step[a]._curFrame = curFrame;

		a++;
		v += _vm->_actor->_vertexNum;

		curFrame++;
		cfp++;

		if (curFrame >= _vm->_defActionLen[curAction]) {
			if (curAction == hSTART) {
				curAction = hWALK;
				curFrame = 0;
				cfp = _vm->_defActionLen[hSTART] + 1;

				ox = 0.0;
			} else if (curAction == hWALK) {
				curAction = hWALK;
				curFrame = 0;
				cfp = _vm->_defActionLen[hSTART] + 1;

				// end walk frame
				ox = _vm->_actor->frameCenter(v) - firstFrame;

				v = &_vm->_actor->_characterArea[cfp * _vm->_actor->_vertexNum];
				ox -= _vm->_actor->frameCenter(v);
			}

			v = &_vm->_actor->_characterArea[cfp * _vm->_actor->_vertexNum];

			// only if it doesn't end
			if ((oz + ox + _vm->_actor->frameCenter(v) - firstFrame) < len)
				oz += ox;
			else
				break;
		}
	}

	if (!a)
		warning("buildFramelist - Unknown error: step number = 0");

	// After the destination, add the stop frame

	// if he was walking
	if (_step[a - 1]._curAction == hWALK)
		curAction = _step[a - 1]._curFrame + hSTOP0; // stop previous step.
	else
		curAction = hSTOP0; // stop step 01

	assert(curAction <= hLAST); // _defActionLen below has a size of hLAST + 1

	curFrame = 0;

	int b = 0;
	cfp = 0;
	while (b != curAction)
		cfp += _vm->_defActionLen[b++];

	v = &_vm->_actor->_characterArea[cfp * _vm->_actor->_vertexNum];

	for (b = 0; b < _vm->_defActionLen[curAction]; b++) {
		curLen = oz + _vm->_actor->frameCenter(v) - firstFrame;
		_step[a]._pz = oz - firstFrame; // where to render
		_step[a]._dz = curLen;          // where it is
		_step[a]._curAction = curAction;
		_step[a]._curFrame = curFrame;

		a++;
		curFrame++;
		v += _vm->_actor->_vertexNum;
	}

	// how far is it from the destination?
	float approx = (len - curLen - EPSILON) / (a - 2);
	float theta = 0.0;
	// Adjust all the steps so it arrives exactly where clicked 
	for (b = 1; b < a; b++) {
		// verify there's no reverse step
		if ((_step[b - 1]._dz > (_step[b]._dz + approx * b)) || ((_step[b]._dz + approx * b + EPSILON) >= len)) {
			theta = _step[b]._dz - _step[b]._pz;
			_step[b]._dz = _step[b - 1]._dz;
			_step[b]._pz = _step[b]._dz - theta;
		} else {
			_step[b]._pz += (approx * b);
			_step[b]._dz += (approx * b);
		}
	}
	float cx = _step[b - 1]._dz;

	_lastStep = b; // last step
	_curStep = 0;  // current step

	// now insert exact directions and start and destination points
	b = 0;

	len = 0.0;
	startPos = 0.0;
	for (a = 0; a < _numPathNodes - 1; a++) {
		curLen = 0.0;
		len += _vm->dist3D(_pathNode[a]._x, 0.0, _pathNode[a]._z,
					  _pathNode[a + 1]._x, 0.0, _pathNode[a + 1]._z);

		// determine the direction
		ox = _pathNode[a + 1]._x - _pathNode[a]._x;
		oz = _pathNode[a + 1]._z - _pathNode[a]._z;
		// if it's a useless node, remove it
		if ((ox == 0.0) && (oz == 0.0)) {
			continue;
		}

		approx = sqrt(ox * ox + oz * oz);
		ox /= approx;
		oz /= approx;

		theta = _vm->sinCosAngle(ox, oz) * 180.0f / PI + 180.0f;
		if (theta >= 360.0)
			theta -= 360.0;
		if (theta < 0.0)
			theta += 360.0;

		while ((b < _lastStep) && (_step[b]._dz <= len)) {
			curLen = (_step[b]._dz - _step[b]._pz);

			_step[b]._px = _pathNode[a]._x + (_step[b]._pz - startPos) * ox;
			_step[b]._pz = _pathNode[a]._z + (_step[b]._pz - startPos) * oz;
			_step[b]._dx = curLen * ox;
			_step[b]._dz = curLen * oz;
			_step[b]._theta = theta;

			_step[b]._curPanel = _pathNode[a]._curPanel;

			b++;
		}
		startPos = len;
	}

	reset(b, _curX, _curZ, theta);

	_lastStep = b; // last step
	_curStep = 0;  // current step

	// starting angle
	float oldTheta = _vm->_actor->_theta;
	// first angle walk
	theta = _step[0]._theta;

	// if he starts from standstill position
	if ((_step[0]._curAction == hSTART) && (_step[0]._curFrame == 0) && (_lastStep > 4) && (_step[0]._theta == _step[1]._theta)) {
		approx = theta - oldTheta;

		if (approx > 180.0)
			approx = -360.0 + approx;
		else if (approx < -180.0)
			approx = 360.0 + approx;

		approx /= 3.0;

		for (b = 0; b < 2; b++) {
			_step[b]._theta = oldTheta + (float)(b + 1) * approx;
			_step[b]._theta = (_step[b]._theta > 360.0) ? _step[b]._theta - 360.0 : (_step[b]._theta < 0.0) ? _step[b]._theta + 360.0 : _step[b]._theta;

			theta = _step[b]._theta;

			curLen = sqrt(_step[b]._dx * _step[b]._dx + _step[b]._dz * _step[b]._dz);

			theta = ((270.0 - theta) * PI) / 180.0;
			ox = cos(theta) * curLen;
			oz = sin(theta) * curLen;

			cx = _step[b]._px + _step[b]._dx;
			float cz = _step[b]._pz + _step[b]._dz;

			_step[b]._px += _step[b]._dx - ox;
			_step[b]._pz += _step[b]._dz - oz;

			_step[b]._dx = cx - _step[b]._px;
			_step[b]._dz = cz - _step[b]._pz;
		}
	}

	// makes the curve
	oldTheta = _step[2]._theta;
	for (b = 3; b <= _lastStep; b++) {
		theta = _step[b]._theta;

		// if it made a curve
		if (oldTheta != theta) {
			approx = theta - oldTheta;

			if (approx > 180.0)
				approx = -360.0 + approx;
			else if (approx < -180.0)
				approx = 360.0 + approx;

			approx /= 3.0;

			// for the previous one
			_step[b - 1]._theta += approx;
			_step[b - 1]._theta = (_step[b - 1]._theta > 360.0) ? _step[b - 1]._theta - 360.0 : (_step[b - 1]._theta < 0.0) ? _step[b - 1]._theta + 360.0 : _step[b - 1]._theta;

			oldTheta = _step[b - 1]._theta;
			startPos = oldTheta;

			curLen = sqrt(_step[b - 1]._dx * _step[b - 1]._dx + _step[b - 1]._dz * _step[b - 1]._dz);

			oldTheta = ((270.0 - oldTheta) * PI) / 180.0;
			ox = cos(oldTheta) * curLen;
			oz = sin(oldTheta) * curLen;

			cx = _step[b - 1]._px + _step[b - 1]._dx;
			float cz = _step[b - 1]._pz + _step[b - 1]._dz;

			_step[b - 1]._px += _step[b - 1]._dx - ox;
			_step[b - 1]._pz += _step[b - 1]._dz - oz;

			_step[b - 1]._dx = cx - _step[b - 1]._px;
			_step[b - 1]._dz = cz - _step[b - 1]._pz;

			// for the next one
			_step[b]._theta -= approx;
			_step[b]._theta = (_step[b]._theta > 360.0) ? _step[b]._theta - 360.0 : (_step[b]._theta < 0.0) ? _step[b]._theta + 360.0 : _step[b]._theta;

			oldTheta = theta;
			theta = _step[b]._theta;

			curLen = sqrt(_step[b]._dx * _step[b]._dx + _step[b]._dz * _step[b]._dz);

			theta = ((270.0 - theta) * PI) / 180.0;
			ox = cos(theta) * curLen;
			oz = sin(theta) * curLen;

			cx = _step[b]._px + _step[b]._dx;
			cz = _step[b]._pz + _step[b]._dz;

			_step[b]._px += _step[b]._dx - ox;
			_step[b]._pz += _step[b]._dz - oz;

			_step[b]._dx = cx - _step[b]._px;
			_step[b]._dz = cz - _step[b]._pz;

		} else
			oldTheta = theta;
	}

	lookAt(_lookX, _lookZ);
}

/*------------------------------------------------
			Take the next frame walk
--------------------------------------------------*/
int PathFinding3D::nextStep() {
	Actor *actor = _vm->_actor;
	actor->_px = _step[_curStep]._px;
	actor->_pz = _step[_curStep]._pz;
	actor->_dx = _step[_curStep]._dx;
	actor->_dz = _step[_curStep]._dz;
	actor->_theta = _step[_curStep]._theta;
	actor->_curAction = _step[_curStep]._curAction;
	actor->_curFrame = _step[_curStep]._curFrame;
	_curPanel = _step[_curStep]._curPanel;

	// increase the current step if it's not the last frame
	if (_curStep < _lastStep) {
		_curStep++;
		return false;
	}

	if (_characterGoToPosition != -1)
		setPosition(_characterGoToPosition);

	return true;
}
/*------------------------------------------------
				View route
--------------------------------------------------*/
void PathFinding3D::displayPath() {
	buildFramelist();
}

/*------------------------------------------------
	Check if two panels are in the same block
--------------------------------------------------*/
bool PathFinding3D::findAttachedPanel(int srcPanel, int destPanel) {
	// if at least one is on the floor, return false
	if (srcPanel < 0 || destPanel < 0)
		return false;

	// if they are equal, return true
	if (srcPanel == destPanel)
		return true;

	int curPanel = srcPanel;
	int nearPanel = _panel[srcPanel]._near1;

	for (int b = 0;; b++) {
		// if they are attached, return true
		if (curPanel == destPanel)
			return true;

		// if it has returned to the starting panel, return false
		if (srcPanel == curPanel && b)
			return false;

		if (b > _panelNum)
			return false;

		// if they are attached to vertex 1, take 2
		if (_panel[nearPanel]._near1 == curPanel) {
			curPanel = nearPanel;
			nearPanel = _panel[curPanel]._near2;
		} else {
			curPanel = nearPanel;
			nearPanel = _panel[curPanel]._near1;
		}
	}
}

/*------------------------------------------------
		Compare route distance (qsort)
--------------------------------------------------*/
int pathCompare(const void *arg1, const void *arg2) {
	SPathNode *p1 = (SPathNode *)arg1;
	SPathNode *p2 = (SPathNode *)arg2;

	if (p1->_dist < p2->_dist)
		return -1;

	if (p1->_dist > p2->_dist)
		return 1;

	return 0;
}

/*------------------------------------------------
		sort the nodes of the path found
--------------------------------------------------*/
void PathFinding3D::sortPath() {
	qsort(&_pathNode[0], _numPathNodes, sizeof(SPathNode), pathCompare);
}

/*------------------------------------------------
			Initializes sort panel
--------------------------------------------------*/
void PathFinding3D::initSortPan() {
	_numSortPan = 31;

	for (int a = 1; a < _numSortPan - 1; ++a) {
		_sortPan[a]._min = 32000.0f;
		_sortPan[a]._num = a;
	}

	// First panel is behind everything and is not sorted
	_sortPan[0]._min = 30000.0f;
	_sortPan[0]._num = BOX_BACKGROUND;

	// Last panel is in front of everything and is not sorted
	_sortPan[30]._min = 0.0f;
	_sortPan[30]._num = BOX_FOREGROUND;

	Actor *actor = _vm->_actor;
	// Sort panel blocks by increasing distance from the camera
	for (int b = 0; b < _panelNum; ++b) {
		if (!(_panel[b]._flags & 0x80000000)) {
			float dist1 = _vm->dist3D(actor->_camera->_ex, 0.0, actor->_camera->_ez, _panel[b]._x1, 0.0, _panel[b]._z1);
			float dist2 = _vm->dist3D(actor->_camera->_ex, 0.0, actor->_camera->_ez, _panel[b]._x2, 0.0, _panel[b]._z2);

			float min = MIN(dist1, dist2);

			for (int a = 0; a < _numSortPan; ++a) {
				if (_panel[b]._flags & (1 << a)) {
					if (_sortPan[a + 1]._min > min)
						_sortPan[a + 1]._min = min;
				}
			}
		}
	}

	sortPanel();

	for (int b = 0; b < _numSortPan; ++b) {
		if (_sortPan[b]._num == BOX_BACKGROUND) {
			// now the panels go from 0 (foreground) to _numSortPan (background)
			_numSortPan = b;
			break;
		}
	}
}

void PathFinding3D::read3D(Common::SeekableReadStream *ff) {
	// read panels
	_panelNum = ff->readSint32LE();
	if (_panelNum > MAXPANELSINROOM)
		error("read3D(): Too many panels");

	for (int i = 0; i < _panelNum; ++i) {
		_panel[i]._x1 = ff->readFloatLE();
		_panel[i]._z1 = ff->readFloatLE();
		_panel[i]._x2 = ff->readFloatLE();
		_panel[i]._z2 = ff->readFloatLE();
		_panel[i]._h = ff->readFloatLE();
		_panel[i]._flags = ff->readUint32LE();

		_panel[i]._near1 = ff->readSByte();
		_panel[i]._near2 = ff->readSByte();
		_panel[i]._col1 = ff->readSByte();
		_panel[i]._col2 = ff->readSByte();
	}

		// projection matrix
	float _proj[3][3];
	_proj[0][0] = _vm->_actor->_camera->_e1[0];
	_proj[0][1] = _vm->_actor->_camera->_e1[1];
	_proj[0][2] = _vm->_actor->_camera->_e1[2];
	_proj[1][0] = _vm->_actor->_camera->_e2[0];
	_proj[1][1] = _vm->_actor->_camera->_e2[1];
	_proj[1][2] = _vm->_actor->_camera->_e2[2];
	_proj[2][0] = _vm->_actor->_camera->_e3[0];
	_proj[2][1] = _vm->_actor->_camera->_e3[1];
	_proj[2][2] = _vm->_actor->_camera->_e3[2];

	// Compute 3x3 inverse matrix for 2D points on 3D
	float det = _proj[0][0] * _proj[1][1] * _proj[2][2] +
				_proj[0][1] * _proj[1][2] * _proj[2][0] +
				_proj[0][2] * _proj[1][0] * _proj[2][1] -
				_proj[2][0] * _proj[1][1] * _proj[0][2] -
				_proj[2][1] * _proj[1][2] * _proj[2][0] -
				_proj[2][2] * _proj[1][0] * _proj[2][1];

	if (det == 0.0)
		error("read3D : Unexpected data error while computing inverse matrix");

	_invP[0][0] = (_proj[1][1] * _proj[2][2] - _proj[1][2] * _proj[2][1]) / det;
	_invP[0][1] = (_proj[0][1] * _proj[2][2] - _proj[0][2] * _proj[2][1]) / (-det);
	_invP[0][2] = (_proj[0][1] * _proj[1][2] - _proj[0][2] * _proj[1][1]) / det;
	_invP[1][0] = (_proj[1][0] * _proj[2][2] - _proj[1][2] * _proj[2][0]) / (-det);
	_invP[1][1] = (_proj[0][0] * _proj[2][2] - _proj[0][2] * _proj[2][0]) / det;
	_invP[1][2] = (_proj[0][0] * _proj[1][2] - _proj[0][2] * _proj[1][0]) / (-det);
	_invP[2][0] = (_proj[1][0] * _proj[2][1] - _proj[1][1] * _proj[2][0]) / det;
	_invP[2][1] = (_proj[0][0] * _proj[2][1] - _proj[0][1] * _proj[2][0]) / (-det);
	_invP[2][2] = (_proj[0][0] * _proj[1][1] - _proj[0][1] * _proj[1][0]) / det;
}

void PathFinding3D::reset(uint16 idx,float px, float pz, float theta) {
	_step[idx]._px = px;
	_step[idx]._pz = pz;
	_step[idx]._dx = 0.0f;
	_step[idx]._dz = 0.0f;

	_step[idx]._theta = theta;
	_step[idx]._curAction = hSTAND;
	_step[idx]._curFrame = 0;
	_step[idx]._curPanel = _curPanel;
}

/*------------------------------------------------
		Compare panel distance (qsort)
--------------------------------------------------*/
int panelCompare(const void *arg1, const void *arg2) {
	SSortPan *p1 = (SSortPan *)arg1;
	SSortPan *p2 = (SSortPan *)arg2;

	if (p1->_min > p2->_min)
		return 1;

	if (p1->_min < p2->_min)
		return -1;

	return 0;
}

/*------------------------------------------------
				Sort the panels
--------------------------------------------------*/
void PathFinding3D::sortPanel() {
	qsort(&_sortPan[0], _numSortPan, sizeof(SSortPan), panelCompare);
}

/*------------------------------------------------
  Find the 3D point corresponding to the 2D point
--------------------------------------------------*/
void PathFinding3D::whereIs(int px, int py) {
	float inters = 32000.0;

	_vm->_actor->_px += _vm->_actor->_dx;
	_vm->_actor->_pz += _vm->_actor->_dz;

	_oldPanel = _curPanel;
	_curPanel = -2;

	invPointProject(px, py);
	float x = _x3d;
	float y = _y3d;
	float z = _z3d;

	// Try to intersect with the floor
	if (intersectLineFloor(x, y, z)) {
		_curPanel = -1;
		_curX = _x3d;
		_curZ = _z3d;
	}

	// try all the panels and choose the closest one
	for (int b = 0; b < _panelNum; b++) {
		if (intersectLinePanel(&_panel[b], x, y, z)) {
			float temp = _vm->dist3D(_vm->_actor->_camera->_ex, _vm->_actor->_camera->_ey, _vm->_actor->_camera->_ez, _x3d, _y3d, _z3d);

			if (temp < inters) {
				inters = temp;
				_curPanel = b;
				_curX = _x3d;
				_curZ = _z3d;
			}
		}
	}

	_lookX = _curX;
	_lookZ = _curZ;

	pointOut();

	_vm->_actor->_px -= _vm->_actor->_dx;
	_vm->_actor->_pz -= _vm->_actor->_dz;
}

/*------------------------------------------------
  Brings out point from inner panel
--------------------------------------------------*/
void PathFinding3D::pointOut() {
#define LARGEVAL 60.0 // 30 cm = 15 enlarge * 2

	float x = 0.0, z = 0.0;
	float inters = 32000.0;

	// TODO: ask an italian speaker the meaning of this comment :)
	// se ho beccato il pavimento devo contare quante volte interseca
	// i box larghi la retta omino pto
	if (_curPanel < 0)
		return;

	SPan *panel = &_panel[_curPanel];
	float nx = panel->_z1 - panel->_z2;
	float nz = panel->_x2 - panel->_x1;
	float temp = sqrt(nx * nx + nz * nz);
	nx /= temp;
	nz /= temp;

	// move the point on the wide panel
	for (int b = 0; b < _panelNum; b++) {
		panel = &_panel[b];
		// Only check the external panels with the same flag
		if ((panel->_flags & 0x80000000) && (panel->_flags & (_panel[_curPanel]._flags & 0x7FFFFFFF))) {
			// check point 1
			temp = _vm->dist2D(_curX, _curZ, panel->_x1, panel->_z1);

			if (temp < inters) {
				inters = temp;
				_curPanel = b;
				x = panel->_x1;
				z = panel->_z1;
			}

			// check point 2
			temp = _vm->dist2D(_curX, _curZ, panel->_x2, panel->_z2);

			if (temp < inters) {
				inters = temp;
				_curPanel = b;
				x = panel->_x2;
				z = panel->_z2;
			}

			// check point a 1/3
			temp = _vm->dist2D(_curX, _curZ, (panel->_x1 * 2.0 + panel->_x2) / 3.0, (panel->_z1 * 2.0 + panel->_z2) / 3.0);

			if (temp < inters) {
				inters = temp;
				_curPanel = b;
				x = (panel->_x1 * 2.0 + panel->_x2) / 3.0;
				z = (panel->_z1 * 2.0 + panel->_z2) / 3.0;
			}

			// check point a 2/3
			temp = _vm->dist2D(_curX, _curZ, (panel->_x1 + panel->_x2 * 2.0) / 3.0, (panel->_z1 + panel->_z2 * 2.0) / 3.0);

			if (temp < inters) {
				inters = temp;
				_curPanel = b;
				x = (panel->_x1 + panel->_x2 * 2.0) / 3.0;
				z = (panel->_z1 + panel->_z2 * 2.0) / 3.0;
			}

			// check intersection with camera
			if (intersectLineLine(panel->_x1, panel->_z1, panel->_x2, panel->_z2, _vm->_actor->_camera->_ex, _vm->_actor->_camera->_ez, _curX, _curZ)) {
				temp = _vm->dist2D(_curX, _curZ, _x3d, _z3d);

				if (temp < inters) {
					inters = temp;
					_curPanel = b;
					x = _x3d;
					z = _z3d;
				}
			}

			// check intersection with character
			if (intersectLineLine(panel->_x1, panel->_z1, panel->_x2, panel->_z2, _vm->_actor->_px, _vm->_actor->_pz, _curX, _curZ)) {
				temp = _vm->dist2D(_curX, _curZ, _x3d, _z3d);

				if (temp < inters) {
					inters = temp;
					_curPanel = b;
					x = _x3d;
					z = _z3d;
				}
			}

			// check intersection with normal panel
			if (intersectLineLine(panel->_x1, panel->_z1, panel->_x2, panel->_z2,
								  _curX + nx * LARGEVAL, _curZ + nz * LARGEVAL, _curX - nx * LARGEVAL, _curZ - nz * LARGEVAL)) {
				temp = _vm->dist2D(_curX, _curZ, _x3d, _z3d);

				if (temp < inters) {
					inters = temp;
					_curPanel = b;
					x = _x3d;
					z = _z3d;
				}
			}
		}
	}

	_curX = x;
	_curZ = z;

#undef LARGEVAL
}

/*------------------------------------------------
		Projects 2D point in a 3D world
--------------------------------------------------*/
void PathFinding3D::invPointProject(int x, int y) {
	float px = (float)(x - _vm->_cx) / _vm->_actor->_camera->_fovX;
	float py = (float)(y - _vm->_cy) / _vm->_actor->_camera->_fovY;

	_x3d = (float)(px * _invP[0][0] + py * _invP[0][1] + _invP[0][2]);
	_y3d = (float)(px * _invP[1][0] + py * _invP[1][1] + _invP[1][2]);
	_z3d = (float)(px * _invP[2][0] + py * _invP[2][1] + _invP[2][2]);

	_x3d += _vm->_actor->_camera->_ex;
	_y3d += _vm->_actor->_camera->_ey;
	_z3d += _vm->_actor->_camera->_ez;
}

/*------------------------------------------------
		Intersects a 3D line with the panel
--------------------------------------------------*/
bool PathFinding3D::intersectLinePanel(SPan *p, float x, float y, float z) {
	// If it's an enlarged panel
	if (p->_flags & 0x80000000)
		return false;

	float x1 = _vm->_actor->_camera->_ex;
	float y1 = _vm->_actor->_camera->_ey;
	float z1 = _vm->_actor->_camera->_ez;

	float dx = (x - x1);
	float dy = (y - y1);
	float dz = (z - z1);
	float t = sqrt(dx * dx + dy * dy + dz * dz);
	dx /= t;
	dy /= t;
	dz /= t;

	float nx = p->_z1 - p->_z2;
	float nz = p->_x2 - p->_x1;
	t = sqrt(nx * nx + nz * nz);
	nx /= t;
	nz /= t;
	// ny is always equal to zero for panels

	float n = nx * p->_x1 + nz * p->_z1 - nx * x - nz * z;
	float d = dx * nx + dz * nz;

	if (d != 0.0) {
		t = n / d;

		if (t <= 0.0)
			return false;

		_x3d = x1 + dx * t;
		_y3d = y1 + dy * t;
		_z3d = z1 + dz * t;

		float minx = MIN(p->_x1, p->_x2) - 1.5;
		float maxx = MAX(p->_x1, p->_x2) + 1.5;
		float minz = MIN(p->_z1, p->_z2) - 1.5;
		float maxz = MAX(p->_z1, p->_z2) + 1.5;

		// check if it fits inside the panel
		if ((_x3d >= minx) && (_x3d <= maxx) && (_y3d >= 0.0) && (_y3d <= p->_h) && (_z3d >= minz) && (_z3d <= maxz))
			return true;

		return false;
	}

	return false;
}

/*------------------------------------------------
		Intersects 3D line with the floor
--------------------------------------------------*/
bool PathFinding3D::intersectLineFloor(float x, float y, float z) {
	float x1 = _vm->_actor->_camera->_ex;
	float y1 = _vm->_actor->_camera->_ey;
	float z1 = _vm->_actor->_camera->_ez;

	float dx = (x - x1);
	float dy = (y - y1);
	float dz = (z - z1);
	float t = sqrt(dx * dx + dy * dy + dz * dz);
	dx /= t;
	dy /= t;
	dz /= t;

	// ny is always equal to 1 for the floor

	if (dy != 0.0) {
		t = -y / dy;

		if (t <= 0.0)
			return false;

		_x3d = x1 + dx * t;
		_y3d = y1 + dy * t;
		_z3d = z1 + dz * t;

		return true;
	}

	return false;
}

/*------------------------------------------------
		Intersects a 2D line with a 2D line
--------------------------------------------------*/
bool PathFinding3D::intersectLineLine(float xa, float ya, float xb, float yb, float xc, float yc, float xd, float yd) {
	float divisor = (float)((xb - xa) * (yd - yc) - (yb - ya) * (xd - xc));
	if (divisor == 0.0)
		return false;

	float r = (float)((ya - yc) * (xd - xc) - (xa - xc) * (yd - yc)) / divisor;
	float s = (float)((ya - yc) * (xb - xa) - (xa - xc) * (yb - ya)) / divisor;
	if ((r < 0) || (r > 1) || (s < 0) || (s > 1))
		return false;

	_x3d = xa + r * (xb - xa);
	_y3d = 0.0;
	_z3d = ya + r * (yb - ya);

	return true;
}

/*------------------------------------------------
  Tells after which panel the character stands
--------------------------------------------------*/
void PathFinding3D::actorOrder() {
#define LARGEVAL 15.0 // 30 cm (max)
	Actor *actor = _vm->_actor;

	if (_vm->_forcedActorPos != BOX_NORMAL) {
		_vm->_actorPos = _vm->_forcedActorPos;
		return;
	}

	float ox = actor->_px + actor->_dx - actor->_camera->_ex;
	float oz = actor->_pz + actor->_dz - actor->_camera->_ez;
	float dist = sqrt(ox * ox + oz * oz);
	float lx = (-oz / dist) * LARGEVAL;
	float lz = (ox / dist) * LARGEVAL;

	ox = actor->_px + actor->_dx;
	oz = actor->_pz + actor->_dz;

	// It must be copied in front of the nearest box
	_vm->_actorPos = _sortPan[1]._num;
	// from closest to farthest
	for (int b = 1; b < _numSortPan; b++) {
		for (int a = 0; a < _panelNum; a++) {
			// If it's not wide and belongs to this level
			if (!(_panel[a]._flags & 0x80000000) && (_panel[a]._flags & (1 << (_sortPan[b]._num - 1)))) {
				// If it intersects the center of the character camera
				if (intersectLineLine(_panel[a]._x1, _panel[a]._z1, _panel[a]._x2, _panel[a]._z2, actor->_camera->_ex, actor->_camera->_ez, ox, oz) || intersectLineLine(_panel[a]._x1, _panel[a]._z1, _panel[a]._x2, _panel[a]._z2, actor->_camera->_ex, actor->_camera->_ez, ox + lx, oz + lz) || intersectLineLine(_panel[a]._x1, _panel[a]._z1, _panel[a]._x2, _panel[a]._z2, actor->_camera->_ex, actor->_camera->_ez, ox - lx, oz - lz)) {
					// If it intersects it must be copied after the next box
					_vm->_actorPos = _sortPan[b + 1]._num;
				}
			}
		}
	}
}

} // End of namespace Trecision
