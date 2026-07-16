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

std::map<std::string, PreToggleSetting> g_preToggles;
std::map<std::string, MidToggleSetting> g_midToggles;
std::map<std::string, EditorToggleSetting> g_editToggles;

$execute {
// $on_mod(Loaded) {
	// new EventListener<EventFilter<AddPreToggleEvent>>(+[](AddPreToggleEvent* ev) {
	auto preToggleListener = AddPreToggleEvent().listen([](std::string_view name, std::string_view modID, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod) {
			g_preToggles[fmt::format("{}/{}", modID, name)] = PreToggleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers()[0], mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback,
				initialValue,
				fmt::format("{}", desc)
			};
		}
		return ListenerResult::Stop;
	});
	preToggleListener.leak();
	// new EventListener<EventFilter<AddMidToggleEvent>>(+[](AddMidToggleEvent* ev) {
	auto midToggleListener = AddMidToggleEvent().listen([](std::string_view name, std::string_view modID, std::function<void(GJBaseGameLayer*)> callback, std::function<bool(GJBaseGameLayer*)> initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod) {
			g_midToggles[fmt::format("{}/{}", modID, name)] = MidToggleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers()[0], mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback,
				initialValue,
				fmt::format("{}", desc)
			};
		}
		return ListenerResult::Stop;
	});
	midToggleListener.leak();
	// new EventListener<EventFilter<AddEditToggleEvent>>(+[](AddEditToggleEvent* ev) {
	auto editToggleListener = AddEditToggleEvent().listen([](std::string_view name, std::string_view modID, std::function<void()> callback, std::function<bool()> initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod) {
			g_editToggles[fmt::format("{}/{}", modID, name)] = EditorToggleSetting{
				fmt::format("{}", name),
				fmt::format("{} by {}{}", mod->getName(), mod->getDevelopers()[0], mod->getDevelopers().size() > 1 ? " and More" : ""),
				callback,
				initialValue,
				fmt::format("{}", desc)
			};
		}
		return ListenerResult::Stop;
	});
	editToggleListener.leak();
}

#include <Geode/modify/GameLevelOptionsLayer.hpp>
class $modify(GameLevelOptionsLayer) {
	static void onModify(auto& self) {
		if (!self.setHookPriority("GameLevelOptionsLayer::setupOptions", 4000)) {
			// nin i'm so sorry, i want -9999999 prio as well but alk will yell at you if you kept -9999999 prio --raydeeux
			geode::log::warn("Failed to set hook priority for GameLevelOptionsLayer::setupOptions");
		}
	}

	void setupOptions() {
		auto winSize = CCDirector::get()->getWinSize();

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

		int index = GEODE_DESKTOP(3) GEODE_MOBILE(5); // remove ifdefs once desktop also gets CBF overrides --raydeeux

		for (auto [k, v] : g_preToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(m_level), fmt::format("{}", v.m_description).c_str());
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
				return std::next(g_preToggles.begin(), opt - GEODE_DESKTOP(3) GEODE_MOBILE(5))->second.m_callback(m_level); // this might be stupid idk
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
			// nin i'm so sorry, i want -9999999 prio as well but alk will yell at you if you kept -9999999 prio --raydeeux
			geode::log::warn("Failed to set hook priority for GameOptionsLayer::setupOptions");
		}
	}

	void onIgnoreDamage(CCObject* obj) {
		GameManager::get()->toggleGameVariable("0173");
		if (auto pl = typeinfo_cast<PlayLayer*>(this->m_baseGameLayer)) pl->toggleIgnoreDamage(GameManager::get()->getGameVariable("0173"));
	}

	CCPoint findPositionFor(int index) {
		auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
		cocos2d::CCPoint pos = winSize * .5f + cocos2d::CCPoint { index % 2 == 0 ? -160.f : 80.f, m_offset + 80.f };
		if (index > 1) pos.y -= floorf(index / 2.f) * m_gap;
		return pos;
	}

	void setupOptions() {
		this->setTag(20260219);
		this->setUserObject("options-api"_spr, CCBool::create(true));
		this->setUserFlag("modified-by-options-api"_spr);

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

		int index = 12;

		for (auto [k, v] : g_midToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(m_baseGameLayer), fmt::format("{}", v.m_description).c_str());
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
				return std::next(g_midToggles.begin(), opt - 12)->second.m_callback(m_baseGameLayer); // this might be stupid idk
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
};

#include <Geode/modify/EditorOptionsLayer.hpp>
class $modify(EditorOptionsLayer) {
	static void onModify(auto& self) {
		if (!self.setHookPriority("EditorOptionsLayer::setupOptions", 4000)) {
			// nin i'm so sorry, i want -9999999 prio as well but alk will yell at you if you kept -9999999 prio --raydeeux
			geode::log::warn("Failed to set hook priority for EditorOptionsLayer::setupOptions");
		}
	}

	void setupOptions() {
		// no recreation needed here! everything is well done in EditorOptionsLayer
		EditorOptionsLayer::setupOptions();

		int index = 26; // bump this by 1 because rob added "Static Trace Arrows", "0181" --raydeeux

		for (auto [k, v] : g_editToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(), fmt::format("{}", v.m_description).c_str());
			index++;
		}
	}

	void didToggle(int opt) {
		switch (opt) {
			case 1: case 2: case 3: case 4: case 5:
			case 6: case 7: case 8: case 9: case 10:
			case 11: case 12: case 13: case 14: case 15:
			case 16: case 17: case 18: case 19: case 20:
			case 21: case 22: case 23: case 24: case 25: // highkey i think rob only added 23 toggles in 2.2082, but anything for consistency, i guess... --raydeeux
				return EditorOptionsLayer::didToggle(opt);
			default:
				return std::next(g_editToggles.begin(), opt - 26)->second.m_callback(); // this might be stupid idk
		}
	}
};