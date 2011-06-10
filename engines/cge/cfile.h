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

/*
 * This code is based on original Soltys source code
 * Copyright (c) 1994-1995 Janus B. Wisniewski and L.K. Avalon
 */

#ifndef		__CFILE__
#define		__CFILE__

#include	"cge/general.h"
#include	<io.h>


#define		LINE_MAX	512

#ifndef		IOBUF_SIZE
  #define	IOBUF_SIZE	K(2)
#endif

#define		CFREAD(x)	Read((byte *)(x),sizeof(*(x)))




class IOBUF : public IOHAND
{
protected:
  byte * Buff;
  word Ptr, Lim;
  long BufMark;
  word Seed;
  CRYPT * Crypt;
  virtual void ReadBuff (void);
  virtual void WriteBuff (void);
public:
  IOBUF (IOMODE mode, CRYPT * crpt = NULL);
  IOBUF (const char * name, IOMODE mode, CRYPT * crpt = NULL);
  virtual ~IOBUF (void);
  word Read (void * buf, word len);
  word Read (char * buf);
  int Read (void);
  word Write (void * buf, word len);
  word Write (byte * buf);
  void Write (byte b);
};



class CFILE : public IOBUF
{
public:
  static word MaxLineLen;
  CFILE (const char * name, IOMODE mode = REA, CRYPT * crpt = NULL);
  virtual ~CFILE (void);
  void Flush (void);
  long Mark (void);
  long Seek (long pos);
  void Append (CFILE& f);
};


#endif
