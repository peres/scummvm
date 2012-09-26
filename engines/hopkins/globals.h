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

#ifndef HOPKINS_GLOBALS_H
#define HOPKINS_GLOBALS_H

#include "common/scummsys.h"
#include "common/str.h"

namespace Hopkins {

struct ZonePItem {
	int field0;
	int field2;
	int field4;
};

struct LigneItem {
	int field0;
	int field2;
	int field4;
	int field6;
	int field8;
	byte *field12;
};

struct LigneZoneItem {
	int field0;
	int field2;
	byte *field4;
};

struct CarreZoneItem {
	int field0;
};

struct BqeAnimItem {
	byte *data;
	int field4;
};

struct BankItem {
	byte *data;
	int8 field4;
	Common::String filename1;
	int fileHeader;
	int field1A;
	uint32 field1C;
	Common::String filename2;
};

struct ListeItem {
	int field0;
	int field2;
	int field4;
	int x2;
	int y2;
};

struct BobItem {
	int field0;
	byte *field4;
	int field8;
	int fieldA;
	int fieldC;
	int fieldE;
	int field10;
	int field12;
	int field14;
	int field16;
	byte *field18;
	int field1A;
	int field1C;
	int field1E;
	int field20;
	int field22;
	int field24;
	int field26;
	int field28;
	int field2A;
	int field2C;
	byte *field30;
	int field34;
	int field36;
	int field38;
	int field3A;
	int field3C;
	int field3E;
	int field40;
	int field42;
	int field44;
	int field46;
	int field48;
	int field4A;
};

struct Liste2Item {
	int field0;
	int field2;
	int field4;
	int field6;
	int field8;
};

struct BlAnimItem {
	uint32 v1;
	uint32 v2;
};

struct VBobItem {
	byte *field0;
	int field4;
	int field6;
	int field8;
	int fieldA;
	int fieldC;
	int fieldE;
	byte *field10;
	int field14;
	int field16;
	int field18;
	byte *field1C;
};

struct ObjetWItem {
	byte field0;
	byte field1;
	byte field2;
	byte field3;
	byte field4;
	byte field5;
	byte field6;
	byte field7;
};

struct BlocItem {
	uint16 field0;
	int x1;
	int y1;
	int x2;
	int y2;
};

struct TriItem {
	int field0;
	int field2;
	int field4;
	int field6;
};

struct CacheItem {
	int field0;
	int field2;
	int field4;
	int field6;
	int field8;
	int fieldA;
	int field10;
	int field14;
};

// Note: Fields decimal based for now
struct Sauvegarde {
	int field4;
	int field353;
	int field354;
	int field355;
	int field356;
	int field357;
};

class HopkinsEngine;

/**
 * Engine Globals
 */
class Globals {
private:
	HopkinsEngine *_vm;
public:
	int FR;
	int SVGA;
	int internet;
	int PUBEXIT;
	bool XFULLSCREEN;
	int XSETMODE;
	int XZOOM;
	bool XFORCE16;
	bool XFORCE8;
	bool CARD_SB;
	int PERSO_TYPE;
	int vitesse;
	int INSTALL_TYPE;
	Common::String HOPIMAGE;
	Common::String HOPANIM;
	Common::String HOPLINK;
	Common::String HOPSAVE;
	Common::String HOPSOUND;
	Common::String HOPMUSIC;
	Common::String HOPVOICE;
	Common::String HOPANM;
	Common::String HOPSEQ;
	Common::String FICH_ZONE;
	Common::String FICH_TEXTE;
	Common::String NFICHIER;
	Common::String REP_SPR;
	int SOUNDVOL;
	int MUSICVOL;
	int VOICEVOL;
	bool SOUNDOFF;
	bool MUSICOFF;
	bool VOICEOFF;
	bool CENSURE;
	int lItCounter;
	int lOldItCounter;
	int g_old_anim;
	int g_old_sens;
	int HopkinsArr[140];
	byte *police;
	int police_l;
	int police_h;
	byte *TETE;
	byte *ICONE;
	byte *BUF_ZONE;
	byte *CACHE_BANQUE[6];
	ZonePItem ZoneP[105];
	LigneItem Ligne[400];
	LigneZoneItem LigneZone[400];
	CarreZoneItem CarreZone[100];
	BqeAnimItem Bqe_Anim[35];
	BankItem Bank[8];
	BobItem Bob[36];
	Liste2Item Liste2[35];
	BlAnimItem BL_ANIM[30];
	VBobItem VBob[35];
	ObjetWItem ObjetW[300];
	BlocItem BLOC[250];
	ListeItem Liste[7];
	CacheItem Cache[25];
	byte *Winventaire;
	byte *texte_tmp;
	int texte_long;
	int TEXTE_FORMATE;
	byte *SPRITE_ECRAN;
	Sauvegarde *SAUVEGARDE;
	byte *BUFFERTAPE;
	byte *essai0;
	byte *essai1;
	byte *essai2;
	byte *Bufferobjet;
	int INVENTAIRE[36];
	TriItem Tri[51];
	byte *inventaire2;
	byte *GESTE;
	int OBJET_EN_COURS;
	int NUM_FICHIER_OBJ;
	int nbrligne;
	int largeur_boite;
	byte *INVENTAIRE_OBJET;
	int hauteur_boite;
	bool GESTE_FLAG;
	byte *FORETSPR;
	int FORET;
	byte *COUCOU;
	byte *chemin;
	byte *cache_souris;
	byte *BufLig;
	byte *Bufferdecor;
	byte *ADR_FICHIER_OBJ;
	byte *PERSO;
	bool redraw;
	int OBJL, OBJH;
	int Nouv_objet;
	int HELICO;
	uint32 CAT_POSI;
	uint32 CAT_TAILLE;
	int iRegul;
	bool BPP_NOAFF;
	int SORTIE;
	int PLANX, PLANY;
	int PASSWORD;
	int NOSPRECRAN;
	int ECRAN;
	int OLD_ECRAN;
	int Max_Propre;
	int Max_Propre_Gen;
	int Max_Ligne_Long;
	int Max_Perso_Y;
	bool DESACTIVE_INVENT;
	bool FLAG_VISIBLE;
	bool netscape;
	bool NOMARCHE;
	int NBBLOC;
	bool NO_VISU;
	byte *OPTION_SPR;
	bool OPTION_FLAG;
	int opt_anm;
	int opt_vitesse;
	int opt_scrtype;
	int opt_scrspeed;
	int opt_sound;
	int opt_voice;
	int opt_music;
	int opt_txt;
	int NBTRI;
	bool CACHEFLAG;
	int AFFINVEN;
	bool NOPARLE;

	Globals();
	~Globals();
	void setParent(HopkinsEngine *vm);

	void setConfig();
	void clearAll();
	void HOPKINS_DATA();
	void INIT_ANIM();
	void INIT_VBOB();
	void CHARGE_OBJET();
	byte *dos_malloc2(int count);
	byte *dos_free2(byte *p);
	byte *LIBERE_FICHIER(byte *p);
};

#define PTRNUL (byte *)NULL

} // End of namespace Hopkins

#endif /* HOPKINS_GLOBALS_H */
