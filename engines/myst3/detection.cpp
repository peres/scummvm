/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
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

#include "engines/advancedDetector.h"

#include "engines/myst3/database.h"
#include "engines/myst3/state.h"

#include "common/config-manager.h"
#include "common/savefile.h"
#include "common/translation.h"

#include "graphics/scaler.h"

namespace Myst3 {

struct Myst3GameDescription {
	ADGameDescription desc;
	uint32 localizationType;
};

static const PlainGameDescriptor myst3Games[] = {
	{ "myst3", "Myst III Exile" },
	{ 0, 0 }
};

static const char *directoryGlobs[] = {
	"bin",
	"M3Data",
	"MYST3BIN",
	"TEXT",
	0
};

#define MYST3ENTRY(lang, langFile, md5lang, extra, flags)                       \
{                                                                               \
	{                                                                           \
		"myst3",                                                                \
		extra,                                                                  \
		{                                                                       \
			{ "RSRC.m3r", 0, "a2c8ed69800f60bf5667e5c76a88e481", 1223862 },     \
			{ langFile, 0, md5lang, -1 },                                       \
		},                                                                      \
		lang,                                                                   \
		Common::kPlatformWindows,                                               \
		ADGF_NO_FLAGS,                                                          \
		GUIO_NONE                                                               \
	},                                                                          \
	flags                                                                       \
},

#define MYST3ENTRY_XBOX(lang, langFile, md5lang) 								\
{																				\
	{																			\
		"myst3",																\
		0,																		\
		{																		\
			{ "RSRC.m3r", 0, "3de23eb5a036a62819186105478f9dde", 1226192 },		\
			{ langFile, 0, md5lang, -1 },										\
		},																		\
		lang,																	\
		Common::kPlatformXbox,													\
		ADGF_UNSTABLE,															\
		GUIO_NONE																\
	},																			\
	kLocMulti6																	\
},


static const Myst3GameDescription gameDescriptions[] = {
	// Initial US release (English only)
	MYST3ENTRY(Common::EN_ANY, "ENGLISH.m3t",  "3ca92b097c4319a2ace7fd6e911d6b0f", 0, kLocMonolingual)

	// European releases (Country language + English) (1.2)
	MYST3ENTRY(Common::NL_NLD, "DUTCH.m3u",    "0e8019cfaeb58c2de00ac114cf122220", 0, kLocMulti2)
	MYST3ENTRY(Common::FR_FRA, "FRENCH.m3u",   "3a7e270c686806dfc31c2091e09c03ec", 0, kLocMulti2)
	MYST3ENTRY(Common::DE_DEU, "GERMAN.m3u",   "1b2fa162a951fa4ed65617dd3f0c8a53", 0, kLocMulti2) // #1323, andrews05
	MYST3ENTRY(Common::IT_ITA, "ITALIAN.m3u",  "906645a87ac1cbbd2b88c277c2b4fda2", 0, kLocMulti2) // #1323, andrews05
	MYST3ENTRY(Common::ES_ESP, "SPANISH.m3u",  "28003569d9536cbdf6020aee8e9bcd15", 0, kLocMulti2) // #1323, goodoldgeorge
	MYST3ENTRY(Common::PL_POL, "POLISH.m3u",   "00000000000000000000000000000000", 0, kLocMulti2)

	// Russian release (Russian only) (1.2)
	MYST3ENTRY(Common::RU_RUS, "ENGLISH.m3t",  "57d36d8610043fda554a0708d71d2681", 0, kLocMonolingual)

	// Japanese release (1.2)
	MYST3ENTRY(Common::JA_JPN, "JAPANESE.m3u", "21bbd040bcfadd13b9dc84360c3de01d", 0, kLocMulti2)
	MYST3ENTRY(Common::JA_JPN, "JAPANESE.m3u", "1e7c3156417978a1187fa6bc0e2cfafc", "Subtitles only", kLocMulti2)

	// Multilingual CD release (1.21)
	MYST3ENTRY(Common::EN_ANY, "ENGLISH.m3u",  "b62ca55aa17724cddbbcc78cba988337", 0, kLocMulti6)
	MYST3ENTRY(Common::FR_FRA, "FRENCH.m3u",   "73519070cba1c7bea599adbddeae304f", 0, kLocMulti6)
	MYST3ENTRY(Common::NL_NLD, "DUTCH.m3u",    "c4a8d8fb0eb3fecb9c435a8517bc1f9a", 0, kLocMulti6)
	MYST3ENTRY(Common::DE_DEU, "GERMAN.m3u",   "5b3be343dd20f03ebdf16381b873f035", 0, kLocMulti6)
	MYST3ENTRY(Common::IT_ITA, "ITALIAN.m3u",  "73db43aac3fe8671e2c4e227977fbb61", 0, kLocMulti6)
	MYST3ENTRY(Common::ES_ESP, "SPANISH.m3u",  "55ceb165dad02211ef2d25946c3aac8e", 0, kLocMulti6)

	// DVD releases (1.27)
	MYST3ENTRY(Common::EN_ANY, "ENGLISH.m3u",  "e200b416f43e70fee76148a80d195d5c", "DVD", kLocMulti6)
	MYST3ENTRY(Common::FR_FRA, "FRENCH.m3u",   "5679ce65c5e9af8899835ef9af398f1a", "DVD", kLocMulti6)
	MYST3ENTRY(Common::NL_NLD, "DUTCH.m3u",    "2997afdb4306c573153fdbb391ed2fff", "DVD", kLocMulti6)
	MYST3ENTRY(Common::DE_DEU, "GERMAN.m3u",   "09f32e6ceb414463e8fc22ca1a9564d3", "DVD", kLocMulti6)
	MYST3ENTRY(Common::IT_ITA, "ITALIAN.m3u",  "51fb02f6bf37dde811d7cde648365260", "DVD", kLocMulti6)
	MYST3ENTRY(Common::ES_ESP, "SPANISH.m3u",  "e27e610fe8ce35223a3239ff170a85ec", "DVD", kLocMulti6)

	// Myst 3 Xbox (PAL)
	MYST3ENTRY_XBOX(Common::EN_ANY, "ENGLISHX.m3t", "c4d012ab02b8ca7d0c7e79f4dbd4e676")
	MYST3ENTRY_XBOX(Common::FR_FRA, "FRENCHX.m3t",  "94c9dcdec8794751e4d773776552751a")
	MYST3ENTRY_XBOX(Common::DE_DEU, "GERMANX.m3t",  "b9b66fcd5d4fbb95ac2d7157577991a5")
	MYST3ENTRY_XBOX(Common::IT_ITA, "ITALIANX.m3t", "3ca266019eba68123f6b7cae57cfc200")
	MYST3ENTRY_XBOX(Common::ES_ESP, "SPANISHX.m3t", "a9aca36ccf6709164249f3fb6b1ef148")

	// Myst 3 Xbox (RUS)
	MYST3ENTRY_XBOX(Common::RU_RUS, "ENGLISHX.m3t", "18cb50f5c5317586a128ca9eb3e03279")

//	{
//		// Myst 3 PS2 (NTSC-U/C)
//		{
//			"myst3",
//			0,
//			AD_ENTRY1s("RSRC.m3r", "c60d37bfd3bb8b0bee143018447bb460", 346618151),
//			Common::UNK_LANG,
//			Common::kPlatformPS2,
//			ADGF_UNSTABLE,
//			GUIO_NONE
//		},
//		kFlagDVD
//	},
//
//	{
//		// Myst 3 PS2 (PAL)
//		{
//			"myst3",
//			0,
//			AD_ENTRY1s("RSRC.m3r", "f0e0c502f77157e6b5272686c661ea75", 91371793),
//			Common::UNK_LANG,
//			Common::kPlatformPS2,
//			ADGF_UNSTABLE,
//			GUIO_NONE
//		},
//		kFlagDVD
//	},

	{ AD_TABLE_END_MARKER, 0 }
};

#define GAMEOPTION_WIDESCREEN_MOD GUIO_GAMEOPTIONS1

static const ADExtraGuiOptionsMap optionsList[] = {
	{
		GAMEOPTION_WIDESCREEN_MOD,
		{
			_s("Widescreen mod"),
			_s("Enable enable widescreen rendering in fullscreen mode."),
			"widescreen_mod",
			false
		}
	},

	AD_EXTRA_GUI_OPTIONS_TERMINATOR
};

class Myst3MetaEngine : public AdvancedMetaEngine {
public:
	Myst3MetaEngine() : AdvancedMetaEngine(gameDescriptions, sizeof(Myst3GameDescription), myst3Games, optionsList) {
		_singleId = "myst3";
		_guiOptions = GUIO5(GUIO_NOMIDI, GUIO_NOSFX, GUIO_NOSPEECH, GUIO_NOSUBTITLES, GAMEOPTION_WIDESCREEN_MOD);
		_maxScanDepth = 3;
		_directoryGlobs = directoryGlobs;
	}

	virtual const char *getName() const {
		return "Myst III Engine";
	}

	virtual const char *getOriginalCopyright() const {
		return "Myst III Exile (C) Presto Studios";
	}

	virtual bool hasFeature(MetaEngineFeature f) const {
		return
			(f == kSupportsListSaves) ||
			(f == kSupportsDeleteSave) ||
			(f == kSupportsLoadingDuringStartup) ||
			(f == kSavesSupportMetaInfo) ||
			(f == kSavesSupportThumbnail) ||
			(f == kSavesSupportCreationDate) ||
			(f == kSavesSupportPlayTime);
	}

	virtual SaveStateList listSaves(const char *target) const {
		Common::Platform platform = Common::parsePlatform(ConfMan.get("platform", target));
		Common::String searchPattern = buildSaveName("*", platform);

		SaveStateList saveList;
		Common::StringArray filenames = g_system->getSavefileManager()->listSavefiles(searchPattern);

		for (uint32 i = 0; i < filenames.size(); i++)
			saveList.push_back(SaveStateDescriptor(i, filenames[i]));

		return saveList;
	}

	Common::String buildSaveName(const char *name, Common::Platform platform) const {
		const char *format;

		if (platform == Common::kPlatformXbox) {
			format = "%s.m3x";
		} else {
			format = "%s.m3s";
		}

		return Common::String::format(format, name);
	}

	SaveStateDescriptor getSaveDescription(const char *target, int slot) const {
		SaveStateList saves = listSaves(target);

		SaveStateDescriptor description = SaveStateDescriptor();
		for (uint32 i = 0; i < saves.size(); i++) {
			if (saves[i].getSaveSlot() == slot) {
				description = saves[i];
			}
		}

		return description;
	}

	virtual SaveStateDescriptor querySaveMetaInfos(const char *target, int slot) const {
		SaveStateDescriptor saveInfos = getSaveDescription(target, slot);

		if (saveInfos.getDescription().empty()) {
			// Unused slot
			return SaveStateDescriptor();
		}

		// Open save
		Common::InSaveFile *saveFile = g_system->getSavefileManager()->openForLoading(saveInfos.getDescription());

		// Read state data
		Common::Serializer s = Common::Serializer(saveFile, 0);
		GameState::StateData data;
		data.syncWithSaveGame(s);

		// Read and resize the thumbnail
		Graphics::Surface *guiThumb = new Graphics::Surface();
		guiThumb->create(kThumbnailWidth, kThumbnailHeight1, Graphics::PixelFormat(4, 8, 8, 8, 8, 16, 8, 0, 24));
		data.resizeThumbnail(guiThumb);

		// Set metadata
		saveInfos.setThumbnail(guiThumb);
		saveInfos.setPlayTime(data.secondsPlayed * 1000);

		if (data.saveYear != 0) {
			saveInfos.setSaveDate(data.saveYear, data.saveMonth, data.saveDay);
			saveInfos.setSaveTime(data.saveHour, data.saveMinute);
		}

		if (data.saveDescription != "")
			saveInfos.setDescription(data.saveDescription);

		delete saveFile;

		return saveInfos;
	}

	void removeSaveState(const char *target, int slot) const {
		SaveStateDescriptor saveInfos = getSaveDescription(target, slot);
		g_system->getSavefileManager()->removeSavefile(saveInfos.getDescription());
	}

	virtual int getMaximumSaveSlot() const {
		return 999;
	}

	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const;
};

bool Myst3MetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	const Myst3GameDescription *gd = (const Myst3GameDescription *)desc;
	if (gd) {
		*engine = new Myst3Engine(syst, gd);
	}
	return gd != 0;
}

Common::Platform Myst3Engine::getPlatform() const {
	return _gameDescription->desc.platform;
}

Common::Language Myst3Engine::getGameLanguage() const {
	return _gameDescription->desc.language;
}

uint32 Myst3Engine::getGameLocalizationType() const {
	return _gameDescription->localizationType;
}

} // End of namespace Myst3

#if PLUGIN_ENABLED_DYNAMIC(MYST3)
	REGISTER_PLUGIN_DYNAMIC(MYST3, PLUGIN_TYPE_ENGINE, Myst3::Myst3MetaEngine);
#else
	REGISTER_PLUGIN_STATIC(MYST3, PLUGIN_TYPE_ENGINE, Myst3::Myst3MetaEngine);
#endif
