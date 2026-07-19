#include <Geode/Geode.hpp>
#include <API.hpp>

using namespace geode::prelude;

struct PreToggleSetting {
	std::string m_name;
	std::string m_modID;
	PreToggleCallback m_callback;
	PreInitialCallback m_initial;
	std::string m_description;
};

struct MidToggleSetting {
	std::string m_name;
	std::string m_modID;
	MidToggleCallback m_callback;
	MidInitialCallback m_initial;
	std::string m_description;
};

struct EditorToggleSetting {
	std::string m_name;
	std::string m_modID;
	EditToggleCallback m_callback;
	EditInitialCallback m_initial;
	std::string m_description;
};

struct PreDoubleSetting {
	std::string m_name;
	std::string m_modID;
	PreDoubleCallback m_callback;
	PreInitialCallbackDouble m_initial;
	double m_min;
	double m_max;
	std::string m_description;
};

struct MidDoubleSetting {
	std::string m_name;
	std::string m_modID;
	MidDoubleCallback m_callback;
	MidInitialCallbackDouble m_initial;
	double m_min;
	double m_max;
	std::string m_description;
};

struct EditorDoubleSetting {
	std::string m_name;
	std::string m_modID;
	EditDoubleCallback m_callback;
	EditInitialCallbackDouble m_initial;
	double m_min;
	double m_max;
	std::string m_description;
};

struct PreLongSetting {
	std::string m_name;
	std::string m_modID;
	PreLongCallback m_callback;
	PreInitialCallbackLong m_initial;
	long m_min;
	long m_max;
	std::string m_description;
};

struct MidLongSetting {
	std::string m_name;
	std::string m_modID;
	MidLongCallback m_callback;
	MidInitialCallbackLong m_initial;
	long m_min;
	long m_max;
	std::string m_description;
};

struct EditorLongSetting {
	std::string m_name;
	std::string m_modID;
	EditLongCallback m_callback;
	EditInitialCallbackLong m_initial;
	long m_min;
	long m_max;
	std::string m_description;
};

struct PreStringSetting {
	std::string m_name;
	std::string m_modID;
	PreStringCallback m_callback;
	PreInitialCallbackString m_initial;
	std::string m_description;
};

struct MidStringSetting {
	std::string m_name;
	std::string m_modID;
	MidStringCallback m_callback;
	MidInitialCallbackString m_initial;
	std::string m_description;
};

struct EditorStringSetting {
	std::string m_name;
	std::string m_modID;
	EditStringCallback m_callback;
	EditInitialCallbackString m_initial;
	std::string m_description;
};

struct PreLabeledButtonSetting {
	std::string m_name;
	std::string m_modID;
	PreLabeledButtonCallback m_callback;
	PreInitialCallbackLabeledButton m_initial;
	std::string m_description;
};

struct MidLabeledButtonSetting {
	std::string m_name;
	std::string m_modID;
	MidLabeledButtonCallback m_callback;
	MidInitialCallbackLabeledButton m_initial;
	std::string m_description;
};

struct EditorLabeledButtonSetting {
	std::string m_name;
	std::string m_modID;
	EditLabeledButtonCallback m_callback;
	EditInitialCallbackLabeledButton m_initial;
	std::string m_description;
};

struct PreGeodeButtonWithLabelSetting {
	std::string m_name;
	std::string m_modID;
	PreGeodeButtonWithLabelCallback m_callback;
	PreInitialCallbackGeodeButtonWithLabel m_initial;
	geode::Ref<geode::Button> m_button;
	std::string m_description;
};

struct MidGeodeButtonWithLabelSetting {
	std::string m_name;
	std::string m_modID;
	MidGeodeButtonWithLabelCallback m_callback;
	MidInitialCallbackGeodeButtonWithLabel m_initial;
	geode::Ref<geode::Button> m_button;
	std::string m_description;
};

struct EditorGeodeButtonWithLabelSetting {
	std::string m_name;
	std::string m_modID;
	EditGeodeButtonWithLabelCallback m_callback;
	EditInitialCallbackGeodeButtonWithLabel m_initial;
	geode::Ref<geode::Button> m_button;
	std::string m_description;
};

std::map<std::string, PreToggleSetting> g_preToggles;
std::map<std::string, MidToggleSetting> g_midToggles;
std::map<std::string, EditorToggleSetting> g_editToggles;

std::map<std::string, PreDoubleSetting> g_preDoubles;
std::map<std::string, MidDoubleSetting> g_midDoubles;
std::map<std::string, EditorDoubleSetting> g_editDoubles;

std::map<std::string, PreLongSetting> g_preLongs;
std::map<std::string, MidLongSetting> g_midLongs;
std::map<std::string, EditorLongSetting> g_editLongs;

std::map<std::string, PreStringSetting> g_preStrings;
std::map<std::string, MidStringSetting> g_midStrings;
std::map<std::string, EditorStringSetting> g_editStrings;

std::map<std::string, PreLabeledButtonSetting> g_preLabeledButtons;
std::map<std::string, MidLabeledButtonSetting> g_midLabeledButtons;
std::map<std::string, EditorLabeledButtonSetting> g_editLabeledButtons;

std::map<std::string, PreGeodeButtonWithLabelSetting> g_preGeodeButtonWithLabels;
std::map<std::string, MidGeodeButtonWithLabelSetting> g_midGeodeButtonWithLabels;
std::map<std::string, EditorGeodeButtonWithLabelSetting> g_editGeodeButtonWithLabels;

#define MOD_NAME_DEVS_OTHERS mod->getName(), mod->getDevelopers().at(0), mod->getDevelopers().size() > 1 ? " and others" : ""
#define FORMATTED_MOD_INFO fmt::format("{} by {}{}", MOD_NAME_DEVS_OTHERS)
#define FORMATTED_DESC desc.empty() ? fmt::format("<cl>(From {} by {}{})</c>\n[No description provided! It's anyone's guess as to what editing this option does. Go ask <co>{}</c> to fill in this description, maybe?]", MOD_NAME_DEVS_OTHERS, mod->getDevelopers().at(0)) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {} by {}{})</c>\n", MOD_NAME_DEVS_OTHERS)) ? fmt::format("{}", desc) : geode::utils::string::startsWith(desc, fmt::format("<cl>(From {})</c>\n", mod->getName())) ? fmt::format("<cl>(From {} by {}{})</c>\n{}", MOD_NAME_DEVS_OTHERS, geode::utils::string::replace(desc.data(), fmt::format("<cl>(From {})</c>\n", mod->getName()), "")) : fmt::format("<cl>(From {} by {}{})</c>\n{}", MOD_NAME_DEVS_OTHERS, desc)

$execute {
	auto preToggleListener = AddPreToggleEvent().listen([](std::string_view name, std::string_view modID, PreToggleCallback callback, PreInitialCallback initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_preToggles[fmt::format("{}/{}-pre-toggle", modID, name)] = PreToggleSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback,
				initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	preToggleListener.leak();

	auto midToggleListener = AddMidToggleEvent().listen([](std::string_view name, std::string_view modID, MidToggleCallback callback, MidInitialCallback initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_midToggles[fmt::format("{}/{}-mid-toggle", modID, name)] = MidToggleSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback,
				initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	midToggleListener.leak();

	auto editToggleListener = AddEditToggleEvent().listen([](std::string_view name, std::string_view modID, EditToggleCallback callback, EditInitialCallback initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_editToggles[fmt::format("{}/{}-edit-toggle", modID, name)] = EditorToggleSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback,
				initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("a setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	editToggleListener.leak();

	auto preDoubleListener = AddPreDoubleEvent().listen([](std::string_view name, std::string_view modID, PreDoubleCallback callback, PreInitialCallbackDouble initialValue, double min, double max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && min < max) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_preDoubles[fmt::format("{}/{}-pre-double", modID, name)] = PreDoubleSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		else if (mod && min >= max) log::error("UH-OH! One of the developers of {} mixed up their minimums and maximums! (attempted min: {}, attempted max: {})", mod->getName(), min, max);
		return ListenerResult::Stop;
	});
	preDoubleListener.leak();

	auto midDoubleListener = AddMidDoubleEvent().listen([](std::string_view name, std::string_view modID, MidDoubleCallback callback, MidInitialCallbackDouble initialValue, double min, double max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && min < max) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_midDoubles[fmt::format("{}/{}-mid-double", modID, name)] = MidDoubleSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		else if (mod && min >= max) log::error("UH-OH! One of the developers of {} mixed up their minimums and maximums! (attempted min: {}, attempted max: {})", mod->getName(), min, max);
		return ListenerResult::Stop;
	});
	midDoubleListener.leak();

	auto editDoubleListener = AddEditDoubleEvent().listen([](std::string_view name, std::string_view modID, EditDoubleCallback callback, EditInitialCallbackDouble initialValue, double min, double max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && min < max) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_editDoubles[fmt::format("{}/{}-edit-double", modID, name)] = EditorDoubleSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		else if (mod && min >= max) log::error("UH-OH! One of the developers of {} mixed up their minimums and maximums! (attempted min: {}, attempted max: {})", mod->getName(), min, max);
		return ListenerResult::Stop;
	});
	editDoubleListener.leak();

	auto preLongListener = AddPreLongEvent().listen([](std::string_view name, std::string_view modID, PreLongCallback callback, PreInitialCallbackLong initialValue, long min, long max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && min < max) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_preLongs[fmt::format("{}/{}-pre-long", modID, name)] = PreLongSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		else if (mod && min >= max) log::error("UH-OH! One of the developers of {} mixed up their minimums and maximums! (attempted min: {}, attempted max: {})", mod->getName(), min, max);
		return ListenerResult::Stop;
	});
	preLongListener.leak();

	auto midLongListener = AddMidLongEvent().listen([](std::string_view name, std::string_view modID, MidLongCallback callback, MidInitialCallbackLong initialValue, long min, long max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && min < max) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_midLongs[fmt::format("{}/{}-mid-long", modID, name)] = MidLongSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		else if (mod && min >= max) log::error("UH-OH! One of the developers of {} mixed up their minimums and maximums! (attempted min: {}, attempted max: {})", mod->getName(), min, max);
		return ListenerResult::Stop;
	});
	midLongListener.leak();

	auto editLongListener = AddEditLongEvent().listen([](std::string_view name, std::string_view modID, EditLongCallback callback, EditInitialCallbackLong initialValue, long min, long max, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && min < max) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_editLongs[fmt::format("{}/{}-edit-long", modID, name)] = EditorLongSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				min, max,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		else if (mod && min >= max) log::error("UH-OH! One of the developers of {} mixed up their minimums and maximums! (attempted min: {}, attempted max: {})", mod->getName(), min, max);
		return ListenerResult::Stop;
	});
	editLongListener.leak();

	auto preStringListener = AddPreStringEvent().listen([](std::string_view name, std::string_view modID, PreStringCallback callback, PreInitialCallbackString initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_preStrings[fmt::format("{}/{}-pre-string", modID, name)] = PreStringSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	preStringListener.leak();

	auto midStringListener = AddMidStringEvent().listen([](std::string_view name, std::string_view modID, MidStringCallback callback, MidInitialCallbackString initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_midStrings[fmt::format("{}/{}-mid-string", modID, name)] = MidStringSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	midStringListener.leak();

	auto editStringListener = AddEditStringEvent().listen([](std::string_view name, std::string_view modID, EditStringCallback callback, EditInitialCallbackString initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_editStrings[fmt::format("{}/{}-edit-string", modID, name)] = EditorStringSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	editStringListener.leak();

	auto preLabeledButtonListener = AddPreLabeledButtonEvent().listen([](std::string_view name, std::string_view modID, PreLabeledButtonCallback callback, PreInitialCallbackLabeledButton initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_preLabeledButtons[fmt::format("{}/{}-pre-labeled-button", modID, name)] = PreLabeledButtonSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	preLabeledButtonListener.leak();

	auto midLabeledButtonListener = AddMidLabeledButtonEvent().listen([](std::string_view name, std::string_view modID, MidLabeledButtonCallback callback, MidInitialCallbackLabeledButton initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_midLabeledButtons[fmt::format("{}/{}-mid-labeled-button", modID, name)] = MidLabeledButtonSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	midLabeledButtonListener.leak();

	auto editLabeledButtonListener = AddEditLabeledButtonEvent().listen([](std::string_view name, std::string_view modID, EditLabeledButtonCallback callback, EditInitialCallbackLabeledButton initialValue, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_editLabeledButtons[fmt::format("{}/{}-edit-labeled-button", modID, name)] = EditorLabeledButtonSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		return ListenerResult::Stop;
	});
	editLabeledButtonListener.leak();

	auto preGeodeButtonWithLabelListener = AddPreGeodeButtonWithLabelEvent().listen([](std::string_view name, std::string_view modID, PreGeodeButtonWithLabelCallback callback, PreInitialCallbackGeodeButtonWithLabel initialValue, geode::Ref<geode::Button> button, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && button && button.data()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_preGeodeButtonWithLabels[fmt::format("{}/{}-pre-geode-button-with-label", modID, name)] = PreGeodeButtonWithLabelSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue, button,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		 else if (mod && (!button || !button.data())) log::error("UH-OH! A setting from {} was provided without a valid button node!", mod->getName());
		return ListenerResult::Stop;
	});
	preGeodeButtonWithLabelListener.leak();

	auto midGeodeButtonWithLabelListener = AddMidGeodeButtonWithLabelEvent().listen([](std::string_view name, std::string_view modID, MidGeodeButtonWithLabelCallback callback, MidInitialCallbackGeodeButtonWithLabel initialValue, geode::Ref<geode::Button> button, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && button && button.data()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_midGeodeButtonWithLabels[fmt::format("{}/{}-mid-geode-button-with-label", modID, name)] = MidGeodeButtonWithLabelSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue, button,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		 else if (mod && (!button || !button.data())) log::error("UH-OH! A setting from {} was provided without a valid button node!", mod->getName());
		return ListenerResult::Stop;
	});
	midGeodeButtonWithLabelListener.leak();

	auto editGeodeButtonWithLabelListener = AddEditGeodeButtonWithLabelEvent().listen([](std::string_view name, std::string_view modID, EditGeodeButtonWithLabelCallback callback, EditInitialCallbackGeodeButtonWithLabel initialValue, geode::Ref<geode::Button> button, std::string_view desc, geode::Mod* mod) {
		if (mod && !name.empty() && button && button.data()) {
			const std::string& lockedInDesc = FORMATTED_DESC;
			g_editGeodeButtonWithLabels[fmt::format("{}/{}-edit-geode-button-with-label", modID, name)] = EditorGeodeButtonWithLabelSetting{
				fmt::format("{}", name),
				FORMATTED_MOD_INFO,
				callback, initialValue, button,
				lockedInDesc
			};
		} else if (mod && name.empty()) log::error("UH-OH! A setting from {} was provided without a name!", mod->getName());
		 else if (mod && (!button || !button.data())) log::error("UH-OH! A setting from {} was provided without a valid button node!", mod->getName());
		return ListenerResult::Stop;
	});
	editGeodeButtonWithLabelListener.leak();
}

// keep for debugging
double dummyValue = 150.;
long otherDummy = 5000;
std::string strDummy = "shane hollander";
$on_game(Loaded) {
	Mod* mod = Mod::get();
	std::string desc;
	const std::string& trueDesc = FORMATTED_DESC;
	for (int i = 0; i < 20; i++) {
		g_midDoubles[fmt::format("dummy-double-setting-double-{}"_spr, i)] = MidDoubleSetting{
			fmt::format("dummy double setting #{}", i),
			FORMATTED_MOD_INFO,
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
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_preDoubles[fmt::format("dummy-double-setting-double-{}"_spr, i)] = PreDoubleSetting{
			fmt::format("dummy double setting #{}", i),
			FORMATTED_MOD_INFO,
			[](GJGameLevel* gjlvl, double value) {
				log::info("gjbgl: {}", gjlvl != nullptr);
				log::info("value: {}", value);
				dummyValue = value;
			},
			[](GJGameLevel* gjlvl) {
				log::info("gjbgl: {}", gjlvl != nullptr);
				return dummyValue;
			},
			-200.f, 200.f,
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_editDoubles[fmt::format("dummy-double-setting-double-{}"_spr, i)] = EditorDoubleSetting{
			fmt::format("dummy double setting #{}", i),
			FORMATTED_MOD_INFO,
			[](double value) {
				log::info("value: {}", value);
				dummyValue = value;
			},
			[]() {
				return dummyValue;
			},
			-200.f, 200.f,
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_midLongs[fmt::format("dummy-double-setting-long-{}"_spr, i)] = MidLongSetting{
			fmt::format("dummy long setting #{}", i),
			FORMATTED_MOD_INFO,
			[](GJBaseGameLayer* gjbgl, long value) {
				log::info("gjbgl: {}", gjbgl != nullptr);
				log::info("value: {}", value);
				otherDummy = value;
			},
			[](GJBaseGameLayer* gjbgl) {
				log::info("gjbgl: {}", gjbgl != nullptr);
				return otherDummy;
			},
			-1000, 1000,
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_preLongs[fmt::format("dummy-double-setting-long-{}"_spr, i)] = PreLongSetting{
			fmt::format("dummy long setting #{}", i),
			FORMATTED_MOD_INFO,
			[](GJGameLevel* gjlvl, long value) {
				log::info("gjbgl: {}", gjlvl != nullptr);
				log::info("value: {}", value);
				otherDummy = value;
			},
			[](GJGameLevel* gjlvl) {
				log::info("gjbgl: {}", gjlvl != nullptr);
				return otherDummy;
			},
			-1000, 1000,
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_editLongs[fmt::format("dummy-double-setting-long-{}"_spr, i)] = EditorLongSetting{
			fmt::format("dummy long setting #{}", i),
			FORMATTED_MOD_INFO,
			[](long value) {
				log::info("value: {}", value);
				dummyValue = value;
			},
			[]() {
				return otherDummy;
			},
			-1000, 1000,
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_midStrings[fmt::format("dummy-string-setting-string-{}"_spr, i)] = MidStringSetting{
			fmt::format("dummy string setting #{}", i),
			FORMATTED_MOD_INFO,
			[](GJBaseGameLayer* gjbgl, std::string value) {
				log::info("gjbgl: {}", gjbgl != nullptr);
				log::info("value: {}", value);
				strDummy = value;
			},
			[](GJBaseGameLayer* gjbgl) {
				log::info("gjbgl: {}", gjbgl != nullptr);
				return strDummy;
			},
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_preStrings[fmt::format("dummy-string-setting-string-{}"_spr, i)] = PreStringSetting{
			fmt::format("dummy string setting #{}", i),
			FORMATTED_MOD_INFO,
			[](GJGameLevel* gjlvl, std::string value) {
				log::info("gjbgl: {}", gjlvl != nullptr);
				log::info("value: {}", value);
				strDummy = value;
			},
			[](GJGameLevel* gjlvl) {
				log::info("gjbgl: {}", gjlvl != nullptr);
				return strDummy;
			},
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_editStrings[fmt::format("dummy-string-setting-string-{}"_spr, i)] = EditorStringSetting{
			fmt::format("dummy string setting #{}", i),
			FORMATTED_MOD_INFO,
			[](std::string value) {
				log::info("value: {}", value);
				strDummy = value;
			},
			[]() {
				return strDummy;
			},
			fmt::format("#{}\n{}", i, trueDesc)
		};
		// ask self: should lambda take ccmise as param?
		g_midLabeledButtons[fmt::format("dummy-labeled-button-{}"_spr, i)] = MidLabeledButtonSetting{
			fmt::format("dummy labeled button setting #{}", i),
			FORMATTED_MOD_INFO,
			[](GJBaseGameLayer* gjbgl) {
				Notification::create(fmt::format("gjbgl != nullptr: {}", gjbgl != nullptr), gjbgl != nullptr ? NotificationIcon::Success : NotificationIcon::Error, .25f)->show();
			},
			[](GJBaseGameLayer* gjbgl) {},
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_preLabeledButtons[fmt::format("dummy-labeled-button-{}"_spr, i)] = PreLabeledButtonSetting{
			fmt::format("dummy labeled button setting #{}", i),
			FORMATTED_MOD_INFO,
			[](GJGameLevel* level) {
				Notification::create(fmt::format("gjbgl != nullptr: {}", level != nullptr), level != nullptr ? NotificationIcon::Success : NotificationIcon::Error, .25f)->show();
			},
			[](GJGameLevel* level) {},
			fmt::format("#{}\n{}", i, trueDesc)
		};
		g_editLabeledButtons[fmt::format("dummy-labeled-button-{}"_spr, i)] = EditorLabeledButtonSetting{
			fmt::format("dummy labeled button setting #{}", i),
			FORMATTED_MOD_INFO,
			[]() {
				Notification::create("hello world", NotificationIcon::Success, .25f)->show();
			},
			[](){},
			fmt::format("#{}\n{}", i, trueDesc)
		};
	}
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
// EDIT_TOGGLES_START is for the toggler's individual tags
// ACTUAL_EDITOR_TOGGLER_COUNT is the # of togglers rob added (plus two invisible ones)
#define EDIT_TOGGLES_START 200
#define ACTUAL_EDITOR_TOGGLER_COUNT 25

#define DECLARE_DUMMY_CHECKBOX_FUNCTION\
	CCMenuItemToggler* addDummyCheckboxWithDescription(const int tag, const std::string_view desc, const int offsetBecauseOfStupidNoclipToggleOrOtherStupidReason = 0) {\
		if (!this->m_buttonMenu) return nullptr;\
		addToggle(" ", tag, false, desc.data());\
		const int stupidSum = tag + offsetBecauseOfStupidNoclipToggleOrOtherStupidReason + (this->getUserFlag("use-edittoggles"_spr) ? 1 : 0);\
		int page = (stupidSum / this->m_togglesPerPage);\
		if ((stupidSum % this->m_togglesPerPage) != 0) page++;\
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
			placeholder->setUserObject("page-number"_spr, CCInteger::create(page));\
			return placeholder;\
		}\
		return nullptr;\
	}

#define MAKE_LABEL(someValue)\
	CCLabelBMFont* label = CCLabelBMFont::create(someValue.m_name.c_str(), "bigFont.fnt");\
	label->limitLabelWidth(idealWidth * .125f, .125f, .00001f);\
	container->addChild(label);\
	container->updateLayout();

#define POSITION_AND_SETUP_CONTAINER(someKey, someValue)\
	container->addChild(primaryElement);\
	container->setLayout(RowLayout::create()->setAutoScale(true)->setDefaultScaleLimits(.0001f, 1.f)->setGap(15.f)->setCrossAxisOverflow(true));\
	this->m_buttonMenu->addChild(container);\
	container->setID(fmt::format("{}"_spr, geode::utils::string::replace(someKey, "/", "-")));\
	container->setPosition(dummyCheckbox->getPosition() - (dummyCheckbox->getContentSize() / 2.f));\
	container->setPositionY(dummyCheckbox->getPositionY() - 5.f);\
	container->ignoreAnchorPointForPosition(true);\
	container->setUserObject("page-number"_spr, CCInteger::create(static_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))->getValue()));\
	container->setUserFlag("not-a-toggle"_spr, true);

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

		constexpr float idealWidth = 165.f;
		for (const auto& [l, w] : g_preDoubles) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameLevelOptionsLayer::addDummyCheckboxWithDescription(index, w.m_description);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(w.m_initial(this->m_level));
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Float);
			primaryElement->setCallback([me = primaryElement, gjlvl = this->m_level, callback = w.m_callback, min = w.m_min, max = w.m_max](const std::string& input) {
				const double clamped = std::clamp<double>(geode::utils::numFromString<double>(input).unwrapOr((min + max) / 2.), min, max);
				if (clamped == min || clamped == max) me->setString(geode::utils::numToString(clamped), false);
				callback(gjlvl, clamped);
			});

			POSITION_AND_SETUP_CONTAINER(l, w)
			MAKE_LABEL(w)

			index++;
		}

		for (const auto& [m, x] : g_preLongs) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameLevelOptionsLayer::addDummyCheckboxWithDescription(index, x.m_description);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(x.m_initial(this->m_level));
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Int);
			primaryElement->setCallback([me = primaryElement, gjlvl = this->m_level, callback = x.m_callback, min = x.m_min, max = x.m_max](const std::string& input) {
				const long clamped = std::clamp<long>(geode::utils::numFromString<long>(input).unwrapOr((min + max) / 2.), min, max);
				if (clamped == min || clamped == max) me->setString(geode::utils::numToString(clamped), false);
				callback(gjlvl, clamped);
			});

			POSITION_AND_SETUP_CONTAINER(m, x)
			MAKE_LABEL(x)

			index++;
		}

		for (const auto& [n, y] : g_preStrings) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameLevelOptionsLayer::addDummyCheckboxWithDescription(index, y.m_description);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(y.m_initial(this->m_level));
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Any);
			primaryElement->setCallback([gjlvl = this->m_level, callback = y.m_callback](const std::string& input) {
				callback(gjlvl, input);
			});

			POSITION_AND_SETUP_CONTAINER(n, y)
			MAKE_LABEL(y)

			index++;
		}

		for (const auto& [o, z] : g_preLabeledButtons) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameLevelOptionsLayer::addDummyCheckboxWithDescription(index, z.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			ButtonSprite* btnSprite = ButtonSprite::create(z.m_name.c_str(), "bigFont.fnt", "GJ_button_01.png");
			CCMenuItemSpriteExtra* primaryElement = geode::cocos::CCMenuItemExt::createSpriteExtra(btnSprite, [callback = z.m_callback, this](CCMenuItemSpriteExtra* btn) {
				callback(this->m_level);
			});
			primaryElement->setID(fmt::format("{}"_spr, geode::utils::string::replace(o, "/", "-")));
			z.m_initial(this->m_level);

			POSITION_AND_SETUP_CONTAINER(o, z)

			index++;
		}

		for (const auto& [p, a] : g_preGeodeButtonWithLabels) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameLevelOptionsLayer::addDummyCheckboxWithDescription(index, a.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			geode::Button* primaryElement = a.m_button.data();
			primaryElement->setActivateCallback([callback = a.m_callback, this](geode::Button*) {
				callback(this->m_level);
			});
			primaryElement->setID(fmt::format("{}"_spr, geode::utils::string::replace(p, "/", "-")));
			a.m_initial(this->m_level);

			POSITION_AND_SETUP_CONTAINER(p, a)
			MAKE_LABEL(a)

			index++;
		}
	}

	void didToggle(int opt) {
		if (opt > PRE_TOGGLES_START - 1) return std::next(g_preToggles.begin(), opt - PRE_TOGGLES_START)->second.m_callback(m_level);
		GameLevelOptionsLayer::didToggle(opt);
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
			CCMenuItemToggler* dummyCheckbox = OAPIGameOptionsLayer::addDummyCheckboxWithDescription(index, w.m_description, this->m_baseGameLayer->m_level && this->m_baseGameLayer->m_level->m_levelType == GJLevelType::Editor ? 1 : 0);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(w.m_initial(this->m_baseGameLayer));
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Float);
			primaryElement->setCallback([me = primaryElement, gjbgl = this->m_baseGameLayer, callback = w.m_callback, min = w.m_min, max = w.m_max](const std::string& input) {
				const double clamped = std::clamp<double>(geode::utils::numFromString<double>(input).unwrapOr((min + max) / 2.), min, max);
				if (clamped == min || clamped == max) me->setString(geode::utils::numToString(clamped), false);
				callback(gjbgl, clamped);
			});

			POSITION_AND_SETUP_CONTAINER(l, w)
			MAKE_LABEL(w)

			index++;
		}

		for (const auto& [m, x] : g_midLongs) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameOptionsLayer::addDummyCheckboxWithDescription(index, x.m_description, this->m_baseGameLayer->m_level && this->m_baseGameLayer->m_level->m_levelType == GJLevelType::Editor ? 1 : 0);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(x.m_initial(this->m_baseGameLayer));
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Int);
			primaryElement->setCallback([me = primaryElement, gjbgl = this->m_baseGameLayer, callback = x.m_callback, min = x.m_min, max = x.m_max](const std::string& input) {
				const long clamped = std::clamp<long>(geode::utils::numFromString<long>(input).unwrapOr((min + max) / 2), min, max);
				if (clamped == min || clamped == max) me->setString(geode::utils::numToString(clamped), false);
				callback(gjbgl, clamped);
			});

			POSITION_AND_SETUP_CONTAINER(m, x)
			MAKE_LABEL(x)

			index++;
		}

		for (const auto& [n, y] : g_midStrings) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameOptionsLayer::addDummyCheckboxWithDescription(index, y.m_description, this->m_baseGameLayer->m_level && this->m_baseGameLayer->m_level->m_levelType == GJLevelType::Editor ? 1 : 0);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(y.m_initial(this->m_baseGameLayer));
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Any);
			primaryElement->setCallback([gjbgl = this->m_baseGameLayer, callback = y.m_callback](const std::string& input) {
				callback(gjbgl, input);
			});

			POSITION_AND_SETUP_CONTAINER(n, y)
			MAKE_LABEL(y)

			index++;
		}

		for (const auto& [o, z] : g_midLabeledButtons) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameOptionsLayer::addDummyCheckboxWithDescription(index, z.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			ButtonSprite* btnSprite = ButtonSprite::create(z.m_name.c_str(), "bigFont.fnt", "GJ_button_01.png");
			CCMenuItemSpriteExtra* primaryElement = geode::cocos::CCMenuItemExt::createSpriteExtra(btnSprite, [callback = z.m_callback, this](CCMenuItemSpriteExtra* btn) {
				callback(this->m_baseGameLayer);
			});
			primaryElement->setID(fmt::format("{}"_spr, geode::utils::string::replace(o, "/", "-")));
			z.m_initial(this->m_baseGameLayer);

			POSITION_AND_SETUP_CONTAINER(o, z)

			index++;
		}

		for (const auto& [p, a] : g_midGeodeButtonWithLabels) {
			CCMenuItemToggler* dummyCheckbox = OAPIGameOptionsLayer::addDummyCheckboxWithDescription(index, a.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			geode::Button* primaryElement = a.m_button.data();
			primaryElement->setActivateCallback([callback = a.m_callback, this](geode::Button*) {
				callback(this->m_baseGameLayer);
			});
			primaryElement->setID(fmt::format("{}"_spr, geode::utils::string::replace(p, "/", "-")));
			a.m_initial(this->m_baseGameLayer);

			POSITION_AND_SETUP_CONTAINER(p, a)
			MAKE_LABEL(a)

			index++;
		}
	}

	void didToggle(int opt) {
		if (opt > MID_TOGGLES_START - 1) return std::next(g_midToggles.begin(), opt - MID_TOGGLES_START)->second.m_callback(m_baseGameLayer); // this might be stupid idk
		switch (opt) {
			default: return;
			case 1: case 2: case 3: case 4: case 5:
			case 6: case 7: case 8: case 9: case 11:
				return GameOptionsLayer::didToggle(opt);
			case 10: return GameOptionsLayer::onPracticeMusicSync(nullptr);
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

		if (this->getUserFlag("use-edittoggles"_spr) || this->getUserFlag("use-midtoggles"_spr) || this->getUserFlag("use-pretoggles"_spr)) {
			for (CCNode* child : this->m_buttonMenu->getChildrenExt()) {
				if (!child || !child->getUserFlag("not-a-toggle"_spr) || child->getTag() > -1 || !child->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(child->getUserObject("page-number"_spr))) continue;
				// log::info("child object name: {}", geode::cocos::getObjectName(child));
				// log::info("static_cast<CCInteger*>(child->getUserObject(\"page-number\"_spr))->getValue(): {}", static_cast<CCInteger*>(child->getUserObject("page-number"_spr))->getValue());
				// log::info("page: {}", page);
				child->setVisible(static_cast<CCInteger*>(child->getUserObject("page-number"_spr))->getValue() == page + 1);
			}
		}

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
			// log::info("g_editToggles.size() + EDIT_TOGGLES_START: {}", g_editToggles.size() + EDIT_TOGGLES_START);
			std::string name, desc;
			const size_t editTogglesCount = g_editToggles.size(), editDoublesCount = g_editDoubles.size(), editLongsCount = g_editLongs.size(), editStringsCount = g_editStrings.size(), editLabeledButtonsCount = g_editLabeledButtons.size(), editGeodeButtonsWithLabelsCount = g_editGeodeButtonWithLabels.size();
			if (senderTag < editTogglesCount + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - EDIT_TOGGLES_START);
				const auto& information = std::next(g_editToggles.begin(), senderTag - EDIT_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < editDoublesCount + editTogglesCount + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - editTogglesCount - EDIT_TOGGLES_START);
				const auto& information = std::next(g_editDoubles.begin(), senderTag - editTogglesCount - EDIT_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < editLongsCount + editDoublesCount + editTogglesCount + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START);
				const auto& information = std::next(g_editLongs.begin(), senderTag - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < editStringsCount + editLongsCount + editDoublesCount + editTogglesCount + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - editLongsCount - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START);
				const auto& information = std::next(g_editStrings.begin(), senderTag - editLongsCount - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < editLabeledButtonsCount + editStringsCount + editLongsCount + editDoublesCount + editTogglesCount + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - editStringsCount - editLongsCount - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START);
				const auto& information = std::next(g_editLabeledButtons.begin(), senderTag - editStringsCount - editLongsCount - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < editGeodeButtonsWithLabelsCount + editLabeledButtonsCount + editStringsCount + editLongsCount + editDoublesCount + editTogglesCount + EDIT_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - editLabeledButtonsCount - editStringsCount - editLongsCount - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START);
				const auto& information = std::next(g_editGeodeButtonWithLabels.begin(), senderTag - editLabeledButtonsCount - editStringsCount - editLongsCount - editDoublesCount - editTogglesCount - EDIT_TOGGLES_START)->second;
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
			const size_t midTogglesCount = g_midToggles.size(), midDoublesCount = g_midDoubles.size(), midLongsCount = g_midLongs.size(), midStringsCount = g_midStrings.size(), midLabeledButtonsCount = g_midLabeledButtons.size(), midGeodeButtonsWithLabelsCount = g_midGeodeButtonWithLabels.size();
			if (senderTag < midTogglesCount + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - MID_TOGGLES_START);
				const auto& information = std::next(g_midToggles.begin(), senderTag - MID_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < midDoublesCount + midTogglesCount + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - midTogglesCount - MID_TOGGLES_START);
				const auto& information = std::next(g_midDoubles.begin(), senderTag - midTogglesCount - MID_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < midLongsCount + midDoublesCount + midTogglesCount + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - midDoublesCount - midTogglesCount - MID_TOGGLES_START);
				const auto& information = std::next(g_midLongs.begin(), senderTag - midDoublesCount - midTogglesCount - MID_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < midStringsCount + midLongsCount + midDoublesCount + midTogglesCount + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - midLongsCount - midDoublesCount - midTogglesCount - MID_TOGGLES_START);
				const auto& information = std::next(g_midStrings.begin(), senderTag - midLongsCount - midDoublesCount - midTogglesCount - MID_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < midLabeledButtonsCount + midStringsCount + midLongsCount + midDoublesCount + midTogglesCount + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - midStringsCount - midLongsCount - midDoublesCount - midTogglesCount - MID_TOGGLES_START);
				const auto& information = std::next(g_midLabeledButtons.begin(), senderTag - midStringsCount - midLongsCount - midDoublesCount - midTogglesCount - MID_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < midGeodeButtonsWithLabelsCount + midLabeledButtonsCount + midStringsCount + midLongsCount + midDoublesCount + midTogglesCount + MID_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - midLabeledButtonsCount - midStringsCount - midLongsCount - midDoublesCount - midTogglesCount - MID_TOGGLES_START);
				const auto& information = std::next(g_midGeodeButtonWithLabels.begin(), senderTag - midLabeledButtonsCount - midStringsCount - midLongsCount - midDoublesCount - midTogglesCount - MID_TOGGLES_START)->second;
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
			// log::info("g_preToggles.size() + PRE_TOGGLES_START: {}", g_preToggles.size() + PRE_TOGGLES_START);
			std::string name, desc;
			const size_t preTogglesCount = g_preToggles.size(), preDoublesCount = g_preDoubles.size(), preLongsCount = g_preLongs.size(), preStringsCount = g_preStrings.size(), preLabeledButtonsCount = g_preLabeledButtons.size(), preGeodeButtonsWithLabelsCount = g_preGeodeButtonWithLabels.size();
			if (senderTag < preTogglesCount + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - PRE_TOGGLES_START);
				const auto& information = std::next(g_preToggles.begin(), senderTag - PRE_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < preDoublesCount + preTogglesCount + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - preTogglesCount - PRE_TOGGLES_START);
				const auto& information = std::next(g_preDoubles.begin(), senderTag - preTogglesCount - PRE_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < preLongsCount + preDoublesCount + preTogglesCount + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - preDoublesCount - preTogglesCount - PRE_TOGGLES_START);
				const auto& information = std::next(g_preLongs.begin(), senderTag - preDoublesCount - preTogglesCount - PRE_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < preStringsCount + preLongsCount + preDoublesCount + preTogglesCount + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - preLongsCount - preDoublesCount - preTogglesCount - PRE_TOGGLES_START);
				const auto& information = std::next(g_preStrings.begin(), senderTag - preLongsCount - preDoublesCount - preTogglesCount - PRE_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < preLabeledButtonsCount + preStringsCount + preLongsCount + preDoublesCount + preTogglesCount + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - preStringsCount - preLongsCount - preDoublesCount - preTogglesCount - PRE_TOGGLES_START);
				const auto& information = std::next(g_preLabeledButtons.begin(), senderTag - preStringsCount - preLongsCount - preDoublesCount - preTogglesCount - PRE_TOGGLES_START)->second;
				name = information.m_name;
				desc = information.m_description;
			} else if (senderTag < preGeodeButtonsWithLabelsCount + preLabeledButtonsCount + preStringsCount + preLongsCount + preDoublesCount + preTogglesCount + PRE_TOGGLES_START) {
				// log::info("index should be 0: {}", senderTag - preLabeledButtonsCount - preStringsCount - preLongsCount - preDoublesCount - preTogglesCount - PRE_TOGGLES_START);
				const auto& information = std::next(g_preGeodeButtonWithLabels.begin(), senderTag - preLabeledButtonsCount - preStringsCount - preLongsCount - preDoublesCount - preTogglesCount - PRE_TOGGLES_START)->second;
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

		constexpr float idealWidth = 165.f;
		for (const auto& [l, w] : g_editDoubles) {
			CCMenuItemToggler* dummyCheckbox = OAIPEditorOptionsLayer::addDummyCheckboxWithDescription(index, w.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(w.m_initial());
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Float);
			primaryElement->setCallback([me = primaryElement, callback = w.m_callback, min = w.m_min, max = w.m_max](const std::string& input) {
				const double clamped = std::clamp<double>(geode::utils::numFromString<double>(input).unwrapOr((min + max) / 2.), min, max);
				if (clamped == min || clamped == max) me->setString(geode::utils::numToString(clamped), false);
				callback(clamped);
			});

			POSITION_AND_SETUP_CONTAINER(l, w)
			MAKE_LABEL(w)

			index++;
		}

		for (const auto& [m, x] : g_editLongs) {
			CCMenuItemToggler* dummyCheckbox = OAIPEditorOptionsLayer::addDummyCheckboxWithDescription(index, x.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(x.m_initial());
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Int);
			primaryElement->setCallback([me = primaryElement, callback = x.m_callback, min = x.m_min, max = x.m_max](const std::string& input) {
				const long clamped = std::clamp<long>(geode::utils::numFromString<long>(input).unwrapOr((min + max) / 2), min, max);
				if (clamped == min || clamped == max) me->setString(geode::utils::numToString(clamped), false);
				callback(clamped);
			});

			POSITION_AND_SETUP_CONTAINER(m, x)
			MAKE_LABEL(x)

			index++;
		}

		for (const auto& [n, y] : g_editStrings) {
			CCMenuItemToggler* dummyCheckbox = OAIPEditorOptionsLayer::addDummyCheckboxWithDescription(index, y.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			const std::string& stupidPlaceholder = geode::utils::numToString(y.m_initial());
			geode::TextInput* primaryElement = geode::TextInput::create(idealWidth * 1.5f, stupidPlaceholder);
			primaryElement->setString(stupidPlaceholder, false);
			primaryElement->setCommonFilter(CommonFilter::Any);
			primaryElement->setCallback([callback = y.m_callback](const std::string& input) {
				callback(input);
			});

			POSITION_AND_SETUP_CONTAINER(n, y)
			MAKE_LABEL(y)

			index++;
		}

		for (const auto& [o, z] : g_editLabeledButtons) {
			CCMenuItemToggler* dummyCheckbox = OAIPEditorOptionsLayer::addDummyCheckboxWithDescription(index, z.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			ButtonSprite* btnSprite = ButtonSprite::create(z.m_name.c_str(), "bigFont.fnt", "GJ_button_01.png");
			CCMenuItemSpriteExtra* primaryElement = geode::cocos::CCMenuItemExt::createSpriteExtra(btnSprite, [callback = z.m_callback](CCMenuItemSpriteExtra* btn) {
				callback();
			});
			primaryElement->setID(fmt::format("{}"_spr, geode::utils::string::replace(o, "/", "-")));
			z.m_initial();

			POSITION_AND_SETUP_CONTAINER(o, z)

			index++;
		}

		for (const auto& [p, a] : g_editGeodeButtonWithLabels) {
			CCMenuItemToggler* dummyCheckbox = OAIPEditorOptionsLayer::addDummyCheckboxWithDescription(index, a.m_description, ACTUAL_EDITOR_TOGGLER_COUNT - EDIT_TOGGLES_START);
			if (!dummyCheckbox || !dummyCheckbox->getUserObject("page-number"_spr) || !typeinfo_cast<CCInteger*>(dummyCheckbox->getUserObject("page-number"_spr))) continue;
			CCMenu* container = CCMenu::create();
			container->setContentWidth(idealWidth);

			geode::Button* primaryElement = a.m_button.data();
			primaryElement->setActivateCallback([callback = a.m_callback](geode::Button*) {
				callback();
			});
			primaryElement->setID(fmt::format("{}"_spr, geode::utils::string::replace(p, "/", "-")));
			a.m_initial();

			POSITION_AND_SETUP_CONTAINER(p, a)
			MAKE_LABEL(a)

			index++;
		}
	}

	void didToggle(int opt) {
		if (opt > EDIT_TOGGLES_START - 1) return std::next(g_editToggles.begin(), opt - EDIT_TOGGLES_START)->second.m_callback(); // this might be stupid idk
		EditorOptionsLayer::didToggle(opt);
	}
};