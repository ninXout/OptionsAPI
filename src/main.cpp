#include <Geode/Geode.hpp>
#include <API.hpp>

using namespace geode::prelude;

struct PreToggleSetting {
	std::string m_name;
	std::string m_modID;
	std::function<void(GJGameLevel*)> m_callback;
	std::function<bool(GJGameLevel*)> m_initial;
	std::string m_description;
};

struct MidToggleSetting {
	std::string m_name;
	std::string m_modID;
	std::function<void(GJBaseGameLayer*)> m_callback;
	std::function<bool(GJBaseGameLayer*)> m_initial;
	std::string m_description;
};

struct EditorToggleSetting {
	std::string m_name;
	std::string m_modID;
	std::function<void()> m_callback;
	std::function<bool()> m_initial;
	std::string m_description;
};

struct PreDoubleSetting {
	std::string m_name;
	std::string m_modID;
	std::function<void(GJGameLevel*, double)> m_callback;
	std::function<double(GJGameLevel*)> m_initial;
	double m_min;
	double m_max;
	std::string m_description;
};

struct MidDoubleSetting {
	std::string m_name;
	std::string m_modID;
	std::function<void(GJBaseGameLayer*, double)> m_callback;
	std::function<double(GJBaseGameLayer*)> m_initial;
	double m_min;
	double m_max;
	std::string m_description;
};

struct EditorDoubleSetting {
	std::string m_name;
	std::string m_modID;
	std::function<void(double)> m_callback;
	std::function<double()> m_initial;
	double m_min;
	double m_max;
	std::string m_description;
};

struct NameDesc {
	std::string m_name;
	std::string m_description;
};

std::map<std::string, PreToggleSetting> g_preToggles;
std::map<std::string, MidToggleSetting> g_midToggles;
std::map<std::string, EditorToggleSetting> g_editToggles;

std::map<std::string, PreDoubleSetting> g_preDoubles;
std::map<std::string, MidDoubleSetting> g_midDoubles;
std::map<std::string, EditorDoubleSetting> g_editDoubles;

$execute {
	auto preToggleListener = AddPreToggleEvent().listen([](std::string_view name, std::string_view modID, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = desc.empty() ? fmt::format("<cl>(From {})</c>\n[No description provided! It's anyone's guess as to what toggling this option does. Go ask <co>{}</c> to fill in this description, maybe?]", mod->getName(), mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("{}", desc) : fmt::format("<cl>(From {})</c>\n{}", mod->getName(), desc);
			g_preToggles[fmt::format("{}/{}-toggle", modID, name)] = PreToggleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback,
				initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	preToggleListener.leak();

	auto midToggleListener = AddMidToggleEvent().listen([](std::string_view name, std::string_view modID, std::function<void(GJBaseGameLayer*)> callback, std::function<bool(GJBaseGameLayer*)> initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = desc.empty() ? fmt::format("<cl>(From {})</c>\n[No description provided! It's anyone's guess as to what toggling this option does. Go ask <co>{}</c> to fill in this description, maybe?]", mod->getName(), mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("{}", desc) : fmt::format("<cl>(From {})</c>\n{}", mod->getName(), desc);
			g_midToggles[fmt::format("{}/{}-toggle", modID, name)] = MidToggleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback,
				initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	midToggleListener.leak();

	auto editToggleListener = AddEditToggleEvent().listen([](std::string_view name, std::string_view modID, std::function<void()> callback, std::function<bool()> initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = desc.empty() ? fmt::format("<cl>(From {})</c>\n[No description provided! It's anyone's guess as to what toggling this option does. Go ask <co>{}</c> to fill in this description, maybe?]", mod->getName(), mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("{}", desc) : fmt::format("<cl>(From {})</c>\n{}", mod->getName(), desc);
			g_editToggles[fmt::format("{}/{}-toggle", modID, name)] = EditorToggleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback,
				initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	editToggleListener.leak();

	auto preDoubleListener = AddPreDoubleEvent().listen([](std::string_view name, std::string_view modID, std::function<void(GJGameLevel*, double)> callback, std::function<double(GJGameLevel*)> initialValue, double min, double max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = desc.empty() ? fmt::format("<cl>(From {})</c>\n[No description provided! It's anyone's guess as to what toggling this option does. Go ask <co>{}</c> to fill in this description, maybe?]", mod->getName(), mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("{}", desc) : fmt::format("<cl>(From {})</c>\n{}", mod->getName(), desc);
			g_preDoubles[fmt::format("{}/{}-double", modID, name)] = PreDoubleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	preDoubleListener.leak();

	auto midDoubleListener = AddMidDoubleEvent().listen([](std::string_view name, std::string_view modID, std::function<void(GJBaseGameLayer*, double)> callback, std::function<double(GJBaseGameLayer*)> initialValue, double min, double max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = desc.empty() ? fmt::format("<cl>(From {})</c>\n[No description provided! It's anyone's guess as to what toggling this option does. Go ask <co>{}</c> to fill in this description, maybe?]", mod->getName(), mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("{}", desc) : fmt::format("<cl>(From {})</c>\n{}", mod->getName(), desc);
			g_midDoubles[fmt::format("{}/{}-double", modID, name)] = MidDoubleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	midDoubleListener.leak();

	auto editDoubleListener = AddEditDoubleEvent().listen([](std::string_view name, std::string_view modID, std::function<void(double)> callback, std::function<double()> initialValue, double min, double max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = desc.empty() ? fmt::format("<cl>(From {})</c>\n[No description provided! It's anyone's guess as to what toggling this option does. Go ask <co>{}</c> to fill in this description, maybe?]", mod->getName(), mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("{}", desc) : fmt::format("<cl>(From {})</c>\n{}", mod->getName(), desc);
			g_editDoubles[fmt::format("{}/{}-double", modID, name)] = EditorDoubleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	editDoubleListener.leak();
}

// keep for debugging
double dummyValue = 150.;
$on_game(Loaded) {
	Mod* mod = Mod::get();
	std::string desc;
	const std::string& trueDesc = desc.empty() ? fmt::format("<cl>(From {})</c>\n[No description provided! It's anyone's guess as to what toggling this option does. Go ask <co>{}</c> to fill in this description, maybe?]", mod->getName(), mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("{}", desc) : fmt::format("<cl>(From {})</c>\n{}", mod->getName(), desc);
	g_midDoubles["dummy-double-setting-double"_spr] = MidDoubleSetting{
		"dummy double setting",
		fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and More" : ""),
		[](GJBaseGameLayer* gjbgl, double value) {
			log::info("gjbgl: {}", gjbgl != nullptr);
			log::info("value: {}", value);
			dummyValue = value;
		},
		[](GJBaseGameLayer* gjbgl) {
			log::info("gjbgl: {}", gjbgl != nullptr);
			return dummyValue;
		},
		-200.f, 200.f,
		trueDesc
	};
}

// remove ifdefs once desktop also gets CBF overrides --raydeeux
#ifdef GEODE_IS_DESKTOP
#define PRE_TOGGLES_START 3
#endif
#ifdef GEODE_IS_MOBILE
#define PRE_TOGGLES_START 5
#endif
#define MID_TOGGLES_START 12
// so the tags in editoroptionslayer are all sorts of fucked
#define EDIT_TOGGLES_START 200

#define DECLARE_DUMMY_CHECKBOX_FUNCTION\
	CCMenuItemToggler* addDummyCheckboxWithDescription(const int tag, const std::string& desc) {\
		if (!this->m_buttonMenu) return nullptr;\
		addToggle(" ", tag, false, desc.c_str());\
		if (CCMenuItemToggler* placeholder = typeinfo_cast<CCMenuItemToggler*>(this->m_buttonMenu->getChildByTag(tag))) {\
			placeholder->setID(fmt::format("if-you-activate-me-via-devtools-the-game-will-crash-{}"_spr, tag));\
			placeholder->setScale(0);\
			placeholder->setEnabled(false);\
			placeholder->m_pListener = nullptr;\
			placeholder->m_notClickable = true;\
			placeholder->m_pfnSelector = nullptr;\
			placeholder->m_onButton->removeMeAndCleanup();\
			placeholder->m_onButton = nullptr;\
			placeholder->m_offButton->removeMeAndCleanup();\
			placeholder->m_offButton = nullptr;\
			placeholder->removeAllChildrenWithCleanup(true);\
			return placeholder;\
		}\
		return nullptr;\
	}

#include <Geode/modify/GameLevelOptionsLayer.hpp>
class $modify(OAPIGameLevelOptionsLayer, GameLevelOptionsLayer) {
	static void onModify(auto& self) {
		if (!self.setHookPriority("GameLevelOptionsLayer::setupOptions", 4000)) {
			geode::log::warn("Failed to set hook priority for GameLevelOptionsLayer::setupOptions");
		}
	}

	DECLARE_DUMMY_CHECKBOX_FUNCTION

	void setupOptions() {
		this->setUserFlag("use-pretoggles"_spr, true);

		this->setUserFlag("undefined0.draggable-popups/undraggable-popup", true);
		this->setUserFlag("chs000.customizepopupanimation/dont-animate", true);

		// do this to add descriptions to low detail mode and disable shake
		addToggle("Low Detail Mode", 1, m_level->m_lowDetailModeToggled, "Disables all objects marked as High Detail in the level."); // rewrite desc for consistency with shake trigger toggle. original desc: Toggles off all objects marked as High Detail.
		addToggle("Disable Shake", 2, m_level->m_disableShakeToggled, "Disables all shake triggers in the level.");
		#ifdef GEODE_IS_MOBILE
		// do this to add CBF overrides to mirror vanilla GD vehavior --raydeeux
		addToggle("Enable CBS", 3, m_level->m_cbsOverride == 1, "Force <cg>enable</c> <cy>Click Between Steps</c> on this level regardless of the global setting.");
		addToggle("Disable CBS", 4, m_level->m_cbsOverride == 2, "Force <cr>disable</c> <cy>Click Between Steps</c> on this level regardless of the global setting.");

		// robtop i hate you so FUCKING MUCH right now --raydeeux
		if (auto enableCBF = GJOptionsLayer::getToggleButton(3); enableCBF) enableCBF->m_notClickable = 1;
		else if (auto enableCBF = typeinfo_cast<CCMenuItemToggler*>(this->m_buttonMenu->getChildByTag(3))) enableCBF->m_notClickable = 1;

		if (auto disableCBF = GJOptionsLayer::getToggleButton(4); disableCBF) disableCBF->m_notClickable = 1;
		else if (auto disableCBF = typeinfo_cast<CCMenuItemToggler*>(this->m_buttonMenu->getChildByTag(4))) disableCBF->m_notClickable = 1;
		#endif

		int index = PRE_TOGGLES_START;

		for (const auto& [k, v] : g_preToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(m_level), fmt::format("{}", v.m_description).c_str());
			index++;
		}

		for (const auto& [l, w] : g_preDoubles) {
			CCMenuItemToggler* dummyCheckboxPosition = OAPIGameLevelOptionsLayer::addDummyCheckboxWithDescription(index, fmt::format("{}", w.m_description).c_str());
			CCMenu* container = CCMenu::create();
			// impl custom node perhaps
			index++;
		}
	}

	void didToggle(int opt) {
		switch (opt) {
			case 1: case 2:
				return GameLevelOptionsLayer::didToggle(opt);
			#ifdef GEODE_IS_MOBILE // remove ifdefs once desktop also gets CBF overrides --raydeeux
			case 3: case 4:
				return GameLevelOptionsLayer::didToggle(opt);
			#endif
			default:
				return std::next(g_preToggles.begin(), opt - PRE_TOGGLES_START)->second.m_callback(m_level); // this might be stupid idk
		}
	}
};

#include <Geode/modify/GameOptionsLayer.hpp>
class $modify(OAPIGameOptionsLayer, GameOptionsLayer) {
	// sorry for swearing in source code nin, you know how it is with me seeing rob fumble harder than the average NFL player --raydeeux
	struct Fields {
		CCMenuItemToggler* fuckingStupidIgnoreDamageToggle = nullptr;
		CCMenuItemToggler* fuckingStupidPlaceholderToggle = nullptr;
		CCMenuItemToggler* fuckingStupidPracticeMusicSyncToggle = nullptr;
		CCMenuItemToggler* yetAnotherFuckingStupidPlaceholderToggle = nullptr;
	};

	static void onModify(auto& self) {
		if (!self.setHookPriority("GameOptionsLayer::setupOptions", 4000)) {
			geode::log::warn("Failed to set hook priority for GameOptionsLayer::setupOptions");
		}
	}

	void onIgnoreDamage(CCObject* obj) {
		GameManager::get()->toggleGameVariable("0173");
		if (auto pl = typeinfo_cast<PlayLayer*>(this->m_baseGameLayer)) pl->toggleIgnoreDamage(GameManager::get()->getGameVariable("0173"));
	}

	CCPoint findPositionFor(int index) {
		cocos2d::CCPoint pos = (CCDirector::get()->getWinSize() / 2.f) + cocos2d::CCPoint{ index % 2 == 0 ? -160.f : 80.f, this->m_offset + 80.f };
		if (index > 1) pos.y -= floorf(index / 2.f) * this->m_gap;
		return pos;
	}

	DECLARE_DUMMY_CHECKBOX_FUNCTION

	void setupOptions() {
		this->setTag(20260219);
		this->setUserObject("options-api"_spr, CCBool::create(true));
		this->setUserFlag("modified-by-options-api"_spr);
		this->setUserFlag("use-midtoggles"_spr, true);

		this->setUserFlag("undefined0.draggable-popups/undraggable-popup", true);
		this->setUserFlag("chs000.customizepopupanimation/dont-animate", true);

		// robtop i hate you so f!@$%^&*(*&^%$#$%^&*ing much right now --raydeeux
		this->m_togglesPerPage = 12;
		this->m_gap = 37.f;
		this->m_offset = 32.f;

		// full recreation to add descriptions and fix the stupid Practice Music Sync toggle
		// ok so it's dawned onto me that this whole shebang was so nin can add descriptions wtfrick
		addToggle("Auto-Retry", 1, GameManager::get()->getGameVariable("0026"), "Instantly start a new attempt instead of showing the restart menu.");
		addToggle("Auto-Checkpoints", 2, GameManager::get()->getGameVariable("0027"), "Automatically place checkpoints occasionally.");
		addToggle("Show Progress Bar", 3, GameManager::get()->m_showProgressBar, "Show the progress bar at the top of the screen.");
		addToggle("Show Percentage", 4, GameManager::get()->getGameVariable("0040"), "Show the current percentage at the top of the screen. (Classic Mode only)");
		addToggle("Show Time", 7, GameManager::get()->getGameVariable("0145"), "Show the current time at the top of the screen. (Platformer Mode only)");
		addToggle("Audio Visualizer", 5, GameManager::get()->getGameVariable("0144"), "Enables an audio visualizer on the side of the screen.");
		addToggle("Show Info Label", 6, GameManager::get()->getGameVariable("0109"), "Show a label containing info about the level.");
		addToggle("Disable Checkpoints", 8, GameManager::get()->getGameVariable("0146"), "Disable platformer mode checkpoints and always respawn from the beginning. (Platformer Mode only)");
		addToggle("Show Hitboxes", 9, GameManager::get()->getGameVariable("0166"), "Shows hitboxes while in practice mode.");
		addToggle("Hitbox On Death", 11, GameManager::get()->getGameVariable("0179"), "Shows hitboxes upon death in both normal and practice mode.");

		constexpr int yetAnotherPlaceholderToggleTag = 10;
		addToggle(" ", yetAnotherPlaceholderToggleTag, false, "Use the level's song instead of the normal practice mode song."); // add description since that's the most vanilla approach to ensure correct positioning and ninxout wants descriptions for everything!!!!! --raydeeux
		m_fields->yetAnotherFuckingStupidPlaceholderToggle = typeinfo_cast<CCMenuItemToggler*>(this->m_buttonMenu->getChildByTag(yetAnotherPlaceholderToggleTag));
		if (m_fields->yetAnotherFuckingStupidPlaceholderToggle) {
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->setID("if-you-activate-this-placeholder-the-game-will-crash"_spr);
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->setScale(0);
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->setEnabled(false);
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->m_pListener = nullptr;
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->m_notClickable = true;
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->m_pfnSelector = nullptr;
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->m_onButton->removeMeAndCleanup();
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->m_onButton = nullptr;
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->m_offButton->removeMeAndCleanup();
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->m_offButton = nullptr;
			m_fields->yetAnotherFuckingStupidPlaceholderToggle->removeAllChildrenWithCleanup(true);
		}

		// addToggle("Practice Music Sync", 10, m_baseGameLayer->m_practiceMusicSync, "Use the level's song instead of the normal practice mode song.");
		m_fields->fuckingStupidPracticeMusicSyncToggle = GameToolbox::createToggleButton(
			"Practice Music Sync",
			menu_selector(GameOptionsLayer::onPracticeMusicSync),
			// in reality this should be GJOptionsLayer::onToggle with some extra stuff but it's easier to just recreate it
			m_baseGameLayer->m_practiceMusicSync,
			// highkey i eyeballed the CCPoint based on a screenshot cheeseworks sent here: https://discord.com/channels/911701438269386882/911702535373475870/1473814193152069844 [discord, #mod-dev-chat] --raydeeux
			m_buttonMenu, OAPIGameOptionsLayer::findPositionFor(yetAnotherPlaceholderToggleTag), this,
			this->m_mainLayer, 0.8f, this->m_maxLabelScale, this->m_maxLabelWidth,
			ccp(8, 0), "bigFont.fnt", false, 0, nullptr
		);

		if (m_baseGameLayer->m_level->m_levelType == GJLevelType::Editor) {
			// dummy toggle to trick the UI
			constexpr int placeholderToggleTag = 0;
			addToggle(" ", placeholderToggleTag, false, "Noclip.\n\n<c_>This option will break slope physics; please use Noclip from mod menus instead.</c>"); // add description since that's the most vanilla approach to ensure correct positioning and ninxout wants descriptions for everything!!!!! --raydeeux

			m_fields->fuckingStupidPlaceholderToggle = typeinfo_cast<CCMenuItemToggler*>(this->m_buttonMenu->getChildByTag(placeholderToggleTag));
			if (m_fields->fuckingStupidPlaceholderToggle) {
				m_fields->fuckingStupidPlaceholderToggle->setID("if-you-activate-this-other-placeholder-the-game-will-crash"_spr);
				m_fields->fuckingStupidPlaceholderToggle->setScale(0);
				m_fields->fuckingStupidPlaceholderToggle->setEnabled(false);
				m_fields->fuckingStupidPlaceholderToggle->m_pListener = nullptr;
				m_fields->fuckingStupidPlaceholderToggle->m_notClickable = true;
				m_fields->fuckingStupidPlaceholderToggle->m_pfnSelector = nullptr;
				m_fields->fuckingStupidPlaceholderToggle->m_onButton->removeMeAndCleanup();
				m_fields->fuckingStupidPlaceholderToggle->m_onButton = nullptr;
				m_fields->fuckingStupidPlaceholderToggle->m_offButton->removeMeAndCleanup();
				m_fields->fuckingStupidPlaceholderToggle->m_offButton = nullptr;
				m_fields->fuckingStupidPlaceholderToggle->removeAllChildrenWithCleanup(true);
			}

			// lowkey i don't know how the hell we're gonna go about hiding the label. --raydeeux
			m_fields->fuckingStupidIgnoreDamageToggle = GameToolbox::createToggleButton(
				"Ignore Damage",
				menu_selector(OAPIGameOptionsLayer::onIgnoreDamage),
				// in reality this should be GJOptionsLayer::onToggle with some extra stuff but it's easier to just recreate it
				GameManager::get()->getGameVariable("0173"),
				// highkey i eyeballed the CCPoint based on a screenshot cheeseworks sent here: https://discord.com/channels/911701438269386882/911702535373475870/1473814193152069844 [discord, #mod-dev-chat] --raydeeux
				m_buttonMenu, OAPIGameOptionsLayer::findPositionFor(yetAnotherPlaceholderToggleTag + 1) + ccp(-47.f, 0.f), this,
				this->layerForPage(0), 0.7f, 0.5f, this->m_maxLabelWidth,
				ccp(8, 0), "goldFont.fnt", false, 0, nullptr
			);
			// m_fields->fuckingStupidIgnoreDamageToggle->setPositionX(32.f); // brute force!

			// SAVE FOR DEBUGGING PURPOSES --raydeeux
			/*
			addToggle("DON'T PRESS ME!", -1, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -2, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -3, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -4, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -5, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -6, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -7, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -8, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -9, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -10, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -11, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -12, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -13, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -14, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -15, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -16, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -17, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -18, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -19, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -20, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -21, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -22, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -23, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -24, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -25, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -26, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -27, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -28, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -29, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -30, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -31, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -32, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -33, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -34, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -35, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -36, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -37, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -38, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -39, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -40, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -41, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -42, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -43, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -44, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -45, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -46, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -47, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -48, false, "DON'T PRESS ME!");
			addToggle("DON'T PRESS ME!", -49, false, "I WILL CRASH GD");
			addToggle("I WILL CRASH GD", -50, false, "DON'T PRESS ME!");
			*/
			//--raydeeux
		}

		CCMenuItemSpriteExtra* platUI = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Platformer UI", "goldFont.fnt", "GJ_button_01.png"),
			m_buttonMenu,
			menu_selector(GameOptionsLayer::onUIOptions)
		);
		platUI->setPosition(ccp(-80, -115));
		platUI->setScale(0.7f);
		platUI->m_baseScale = 0.7f;
		m_buttonMenu->addChild(platUI);

		CCMenuItemSpriteExtra* pracUI = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Practice UI", "goldFont.fnt", "GJ_button_01.png"),
			m_buttonMenu,
			menu_selector(GameOptionsLayer::onUIPOptions)
		);
		pracUI->setPosition(ccp(80, -115));
		pracUI->setScale(0.7f);
		pracUI->m_baseScale = 0.7f;
		m_buttonMenu->addChild(pracUI);

		int index = MID_TOGGLES_START;

		for (const auto& [k, v] : g_midToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(m_baseGameLayer), fmt::format("{}", v.m_description).c_str());
			index++;
		}

		constexpr float idealWidth = 165.f;
		for (const auto& [l, w] : g_midDoubles) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameOptionsLayer::addDummyCheckboxWithDescription(index, w.m_description.c_str());
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(w.m_initial(this->m_baseGameLayer));
			geode::TextInput* inputBox = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			inputBox->setString(stupidPlaceholder, false);
			inputBox->setCommonFilter(CommonFilter::Float);
			inputBox->setCallback([me = geode::Ref(inputBox), gjbgl = geode::Ref(this->m_baseGameLayer), callback = w.m_callback, min = w.m_min, max = w.m_max](const std::string& input) {
				const double clamped = std::clamp<double>(geode::utils::numFromString<double>(input).unwrapOr((min + max) / 2.), min, max);
				me->setString(geode::utils::numToString(clamped), false);
				callback(gjbgl, clamped);
			});

			CCLabelBMFont* label = CCLabelBMFont::create(fmt::format("{}", w.m_name).c_str(), "bigFont.fnt");
			label->limitLabelWidth(idealWidth * .125f, .125f, .00001f);

			container->addChild(inputBox);
			container->addChild(label);

			container->setLayout(RowLayout::create()->setAutoScale(true)->setDefaultScaleLimits(.0001f, 1.f)->setGap(15.f)->setCrossAxisOverflow(true));

			this->m_buttonMenu->addChild(container);

			container->setID(fmt::format("{}"_spr, geode::utils::string::replace(l, "/", "-")));
			container->setPosition(dummyCheckbox->getPosition() - (dummyCheckbox->getContentSize() / 2.f));
			container->setPositionY(dummyCheckbox->getPositionY() - 5.f); // why do we need to do this????? fuck robtop's stupid disregard for anchor points wtf !!!!!!
			container->ignoreAnchorPointForPosition(true); // fuck you robtop

			index++;
		}
	}

	void didToggle(int opt) {
		switch (opt) {
			case 0: return;
			case 1: case 2: case 3: case 4: case 5:
			case 6: case 7: case 8: case 9: case 11:
				return GameOptionsLayer::didToggle(opt);
			case 10:
				return onPracticeMusicSync(nullptr);
			default:
				return std::next(g_midToggles.begin(), opt - MID_TOGGLES_START)->second.m_callback(m_baseGameLayer); // this might be stupid idk
		}
	}
};

/*
welcome 2.208!
this stupid hook was necessary because robtop did a stupid thing
where the Ignore Damage toggle visually became a part of the page
w/o being a part of the GJOptionsPage pagination system.
so a lot of node tagging and node casting had to happen.
--raydeeux
*/
#include <Geode/modify/GJOptionsLayer.hpp>
class $modify(OAPIGJOptionsLayer, GJOptionsLayer) {
	void stupidSongAndDance(CCNode* parent, int page) {
		if (!parent) return;
		for (CCNode* child : parent->getChildrenExt()) {
			if (!child) continue;
			if (child->getUserFlag("conditionally-hidden-label"_spr)) {
				child->setVisible(page == 0);
				continue;
			}
			CCLabelBMFont* node = typeinfo_cast<CCLabelBMFont*>(child);
			if (!node) continue;
			if ((static_cast<std::string>(node->getString()) == "Ignore Damage" && static_cast<std::string>(node->getFntFile()) == "goldFont.fnt") || (static_cast<std::string>(node->getString()) == "Practice Music Sync" && static_cast<std::string>(node->getFntFile()) == "bigFont.fnt")) {
				if (!node->getUserFlag("conditionally-hidden-label"_spr)) node->setUserFlag("conditionally-hidden-label"_spr);
				node->setVisible(page == 0);
			}
		}
	}
	void goToPage(int page) {
		GJOptionsLayer::goToPage(page);
		if (this->getTag() != 20260219 || !this->getUserFlag("modified-by-options-api"_spr) || !typeinfo_cast<CCBool*>(this->getUserObject("options-api"_spr)) || !static_cast<CCBool*>(this->getUserObject("options-api"_spr))->getValue() || !typeinfo_cast<GameOptionsLayer*>(this)) return;

		OAPIGameOptionsLayer* fooBar = reinterpret_cast<OAPIGameOptionsLayer*>(this);

		auto fields = fooBar->m_fields.self();
		if (!fields) return;

		OAPIGJOptionsLayer::stupidSongAndDance(this->m_mainLayer, page);
		OAPIGJOptionsLayer::stupidSongAndDance(this->layerForPage(0), page);

		if (auto node = fields->fuckingStupidPracticeMusicSyncToggle) node->setScale(page == 0 ? 1 : 0);
		if (auto node = fields->fuckingStupidIgnoreDamageToggle) node->setScale(page == 0 ? 1 : 0);
		if (auto node = fields->yetAnotherFuckingStupidPlaceholderToggle) {
			node->setScale(0);
			node->m_pListener = nullptr;
			node->m_pfnSelector = nullptr;
		}
		if (auto node = fields->fuckingStupidPlaceholderToggle) {
			node->setScale(0);
			node->m_pListener = nullptr;
			node->m_pfnSelector = nullptr;
		}
	}
	void onInfo(CCObject* sender) {
		if (!sender || sender->getTag() < 1) return GJOptionsLayer::onInfo(sender);
		if (!this->getUserFlag("use-edittoggles"_spr) && !this->getUserFlag("use-midtoggles"_spr) && !this->getUserFlag("use-pretoggles"_spr)) return GJOptionsLayer::onInfo(sender);

		const int senderTag = sender->getTag();
		if (this->getUserFlag("use-edittoggles"_spr)) {
			if (senderTag < EDIT_TOGGLES_START) return GJOptionsLayer::onInfo(sender);
			// log::info("senderTag: {}", senderTag);
			// log::info("g_midToggles.size() + EDIT_TOGGLES_START: {}", g_midToggles.size() + EDIT_TOGGLES_START);
			std::string name, desc;
			if (senderTag < g_preToggles.size() + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - EDIT_TOGGLES_START);
				const auto& information = std::next(g_preToggles.begin(), senderTag - EDIT_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < g_preDoubles.size() + g_preToggles.size() + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - g_midToggles.size() - EDIT_TOGGLES_START);
				const auto& information = std::next(g_preDoubles.begin(), senderTag - g_preToggles.size() - EDIT_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			}
			FLAlertLayer* info = FLAlertLayer::create(nullptr, name.c_str(), geode::utils::string::replace(desc, "<c-ff0000>", "<c_>"), "OK", nullptr, 400.f, false, 0, 1.f);
			info->m_noElasticity = true;
			info->setUserFlag("undefined0.draggable-popups/undraggable-popup", true);
			info->setUserFlag("chs000.customizepopupanimation/dont-animate", true);
			info->show();
			return;
		}
		if (this->getUserFlag("use-midtoggles"_spr)) {
			if (senderTag < MID_TOGGLES_START) return GJOptionsLayer::onInfo(sender);
			// log::info("senderTag: {}", senderTag);
			// log::info("g_midToggles.size() + MID_TOGGLES_START: {}", g_midToggles.size() + MID_TOGGLES_START);
			std::string name, desc;
			if (senderTag < g_midToggles.size() + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - MID_TOGGLES_START);
				const auto& information = std::next(g_midToggles.begin(), senderTag - MID_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < g_midDoubles.size() + g_midToggles.size() + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - g_midToggles.size() - MID_TOGGLES_START);
				const auto& information = std::next(g_midDoubles.begin(), senderTag - g_midToggles.size() - MID_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			}
			FLAlertLayer* info = FLAlertLayer::create(nullptr, name.c_str(), geode::utils::string::replace(desc, "<c-ff0000>", "<c_>"), "OK", nullptr, 400.f, false, 0, 1.f);
			info->m_noElasticity = true;
			info->setUserFlag("undefined0.draggable-popups/undraggable-popup", true);
			info->setUserFlag("chs000.customizepopupanimation/dont-animate", true);
			info->show();
			return;
		}
		if (this->getUserFlag("use-pretoggles"_spr)) {
			if (senderTag < PRE_TOGGLES_START) return GJOptionsLayer::onInfo(sender);
			// log::info("senderTag: {}", senderTag);
			// log::info("g_midToggles.size() + PRE_TOGGLES_START: {}", g_midToggles.size() + PRE_TOGGLES_START);
			std::string name, desc;
			if (senderTag < g_preToggles.size() + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - PRE_TOGGLES_START);
				const auto& information = std::next(g_preToggles.begin(), senderTag - PRE_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < g_preDoubles.size() + g_preToggles.size() + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - g_midToggles.size() - PRE_TOGGLES_START);
				const auto& information = std::next(g_preDoubles.begin(), senderTag - g_preToggles.size() - PRE_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			}
			FLAlertLayer* info = FLAlertLayer::create(nullptr, name.c_str(), geode::utils::string::replace(desc, "<c-ff0000>", "<c_>"), "OK", nullptr, 400.f, false, 0, 1.f);
			info->m_noElasticity = true;
			info->setUserFlag("undefined0.draggable-popups/undraggable-popup", true);
			info->setUserFlag("chs000.customizepopupanimation/dont-animate", true);
			info->show();
			return;
		}
	}
};

#include <Geode/modify/EditorOptionsLayer.hpp>
class $modify(OAIPEditorOptionsLayer, EditorOptionsLayer) {
	static void onModify(auto& self) {
		if (!self.setHookPriority("EditorOptionsLayer::setupOptions", 4000)) {
			geode::log::warn("Failed to set hook priority for EditorOptionsLayer::setupOptions");
		}
	}

	DECLARE_DUMMY_CHECKBOX_FUNCTION

	void setupOptions() {
		// no recreation needed here! everything is well done in EditorOptionsLayer
		EditorOptionsLayer::setupOptions();
		this->setUserFlag("use-edittoggles"_spr, true);

		this->setUserFlag("undefined0.draggable-popups/undraggable-popup", true);
		this->setUserFlag("chs000.customizepopupanimation/dont-animate", true);

		int index = EDIT_TOGGLES_START; // bump this by 1 because rob added "Static Trace Arrows", "0181" --raydeeux

		for (const auto& [k, v] : g_editToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(), fmt::format("{}", v.m_description).c_str());
			index++;
		}

		for (const auto& [l, w] : g_editDoubles) {
			CCMenuItemToggler* dummyCheckboxPosition = OAIPEditorOptionsLayer::addDummyCheckboxWithDescription(index, fmt::format("{}", w.m_description).c_str());
			CCMenu* container = CCMenu::create();
			// impl custom node perhaps
			index++;
		}
	}

	void didToggle(int opt) {
		if (opt > EDIT_TOGGLES_START - 1) return std::next(g_editToggles.begin(), opt - EDIT_TOGGLES_START)->second.m_callback(); // this might be stupid idk
		EditorOptionsLayer::didToggle(opt);
	}
};