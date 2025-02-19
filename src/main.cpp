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
	new EventListener<EventFilter<AddPreToggleEvent>>(+[](AddPreToggleEvent* ev) {
		g_preToggles[fmt::format("{}", ev->getID())] = PreToggleSetting{
			ev->getName(), 
			fmt::format("{} by {}{}", ev->sender->getName(), ev->sender->getDevelopers()[0], ev->sender->getDevelopers().size() > 1 ? " and More" : ""), 
			ev->getCallback(), 
			ev->getInitialVal(),
			ev->getDesc()
		};
        return ListenerResult::Stop;
    });
	new EventListener<EventFilter<AddMidToggleEvent>>(+[](AddMidToggleEvent* ev) {
		g_midToggles[fmt::format("{}", ev->getID())] = MidToggleSetting{
			ev->getName(), 
			fmt::format("{} by {}{}", ev->sender->getName(), ev->sender->getDevelopers()[0], ev->sender->getDevelopers().size() > 1 ? " and More" : ""), 
			ev->getCallback(), 
			ev->getInitialVal(),
			ev->getDesc()
		};
        return ListenerResult::Stop;
    });
	new EventListener<EventFilter<AddEditToggleEvent>>(+[](AddEditToggleEvent* ev) {
		g_editToggles[fmt::format("{}", ev->getID())] = EditorToggleSetting{
			ev->getName(), 
			fmt::format("{} by {}{}", ev->sender->getName(), ev->sender->getDevelopers()[0], ev->sender->getDevelopers().size() > 1 ? " and More" : ""), 
			ev->getCallback(), 
			ev->getInitialVal(),
			ev->getDesc()
		};
        return ListenerResult::Stop;
    });
}

#include <Geode/modify/GameLevelOptionsLayer.hpp>
class $modify(GameLevelOptionsLayer) {
	static void onModify(auto& self) {
        if (!self.setHookPriority("GameLevelOptionsLayer::setupOptions", -9999999)) {
            geode::log::warn("Failed to set hook priority for GameLevelOptionsLayer::setupOptions");
        }
    }

	void setupOptions() {
		auto winSize = CCDirector::get()->getWinSize();

		// do this to add descriptions to low detail mode and disable shake
		addToggle("Low Detail Mode", 1, m_level->m_lowDetailModeToggled, "Toggles off all objects marked as High Detail.");
		addToggle("Disable Shake", 2, m_level->m_disableShakeToggled, "Disables all shake triggers in the level.");

		int index = 3;

		for (auto [k, v] : g_preToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(m_level), fmt::format("{}", v.m_description).c_str());
			index++;
		}
	}

	void didToggle(int opt) {
		switch (opt) {
			case 1: case 2:
				return GameLevelOptionsLayer::didToggle(opt);
			default:
				return std::next(g_preToggles.begin(), opt - 3)->second.m_callback(m_level); // this might be stupid idk
		}
	}
};

#include <Geode/modify/GameOptionsLayer.hpp>
class $modify(OAPIGameOptionsLayer, GameOptionsLayer) {
	static void onModify(auto& self) {
        if (!self.setHookPriority("GameOptionsLayer::setupOptions", -9999999)) {
            geode::log::warn("Failed to set hook priority for GameOptionsLayer::setupOptions");
        }
    }

	void onIgnoreDamage(CCObject* obj) {
		CCMenuItemToggler* toggle = typeinfo_cast<CCMenuItemToggler*>(obj);
		GameManager::get()->toggleGameVariable("0173");
		if (auto pl = typeinfo_cast<PlayLayer*>(this->m_baseGameLayer)) pl->toggleIgnoreDamage(GameManager::get()->getGameVariable("0173"));
	}

	void setupOptions() {
		auto winSize = CCDirector::get()->getWinSize();

		// TODO: full recreation to add descriptions and fix the stupid Practice Music Sync toggle
		addToggle("Auto-Retry", 1, GameManager::get()->getGameVariable("0026"), "Instantly start a new attempt instead of showing the restart menu.");
		addToggle("Auto-Checkpoints", 2, GameManager::get()->getGameVariable("0027"), "Automatically place checkpoints occasionally.");
		addToggle("Show Progress Bar", 3, GameManager::get()->m_showProgressBar, "Show the progress bar at the top of the screen.");
		addToggle("Show Percentage", 4, GameManager::get()->getGameVariable("0040"), "Show the current percentage at the top of the screen. (Classic Mode only)");
		addToggle("Show Time", 7, GameManager::get()->getGameVariable("0145"), "Show the current time at the top of the screen. (Platformer Mode only)");
		addToggle("Audio Visualizer", 5, GameManager::get()->getGameVariable("0144"), "Enables an audio visualizer on the side of the screen.");
		addToggle("Show Info Label", 6, GameManager::get()->getGameVariable("0109"), "Show a label containing info about the level.");
		addToggle("Disable Checkpoints", 8, GameManager::get()->getGameVariable("0146"), "Disable platformer mode checkpoints and always respawn from the beginning. (Platformer Mode only)");
		addToggle("Practice Music Sync", 10, m_baseGameLayer->m_practiceMusicSync, "Use the level's song instead of the normal practice mode song.");
		addToggle("Show Hitboxes", 9, GameManager::get()->getGameVariable("0166"), "Shows hitboxes while in practice mode.");

		if (m_baseGameLayer->m_level->m_levelType == GJLevelType::Editor) {
			GameToolbox::createToggleButton(
				"Ignore Damage", 
				menu_selector(OAPIGameOptionsLayer::onIgnoreDamage), 
				// in reality this should be GJOptionsLayer::onToggle with some extra stuff but it's easier to just recreate it
				GameManager::get()->getGameVariable("0173"), 
				m_buttonMenu, ccp(235, 280), this, 
				this, 0.7f, 0.5f, 
				m_maxLabelWidth, ccp(7, 0), 
				"goldFont.fnt", false, 0, 
				nullptr
			);
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

		int index = 11;

		for (auto [k, v] : g_midToggles) {
			addToggle(v.m_name.c_str(), index, v.m_initial(m_baseGameLayer), fmt::format("{}", v.m_description).c_str());
			index++;
		}
	}

	void didToggle(int opt) {
		switch (opt) {
			case 1: case 2: case 3: case 4: case 5:
			case 6: case 7: case 8: case 9:
				return GameOptionsLayer::didToggle(opt);
			case 10:
				return onPracticeMusicSync(nullptr);
			default:
				return std::next(g_midToggles.begin(), opt - 11)->second.m_callback(m_baseGameLayer); // this might be stupid idk
		}
	}
};

#include <Geode/modify/EditorOptionsLayer.hpp>
class $modify(EditorOptionsLayer) {
	static void onModify(auto& self) {
        if (!self.setHookPriority("EditorOptionsLayer::setupOptions", -9999999)) {
            geode::log::warn("Failed to set hook priority for EditorOptionsLayer::setupOptions");
        }
    }

	void setupOptions() {
		// no recreation needed here! everything is well done in EditorOptionsLayer
		EditorOptionsLayer::setupOptions();

		int index = 25;

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
				return EditorOptionsLayer::didToggle(opt);
			default:
				return std::next(g_editToggles.begin(), opt - 25)->second.m_callback(); // this might be stupid idk
		}
	}
};