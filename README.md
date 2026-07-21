# Options API

API mod that allows developers to add their own settings to some of the settings menus in game.

## Usage

There are 3 menus you can add settings to:

```cpp
/*
Type definitions listed as std::function<T> in this code snippet *can and will* be different in API.hpp. They are shown here in their more conventional C++ equivalent for ease of reference. Nontheless, the underlying syntax and functionality remains the same.
*/
// To add a toggle setting to the LevelInfoLayer settings
OptionsAPI::addPreLevelSetting<bool>(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc);

// To add a toggle setting to the PauseLayer settings
OptionsAPI::addMidLevelSetting<bool>(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc);

// To add a toggle setting to the EditorPauseLayer settings
OptionsAPI::addEditorSetting<bool>(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc);
```

Basic usage (Adding a toggle setting to LevelInfoLayer settings):
```cpp
#include <ninxout.options_api/include/API.hpp>

bool myBoolSetting = false;

$on_mod(Loaded) {
    OptionsAPI::addPreLevelSetting<bool>(
		"My Crazy Setting",                                                // name
		"my-setting"_spr,                                                  // id
		[](GJGameLevel*) { myBoolSetting = !myBoolSetting; },  // toggle callback
		[](GJGameLevel*) { return myBoolSetting; },            // initial value callback
		"My Crazy Description!"                                            // description
	);
}
```

Slightly more advanced usage examples:
```cpp
#include <ninxout.options_api/include/API.hpp>

double myDoubleValue = 7.27;
long myLongValue = 727;
std::string myStringValue = "WYSI";

$on_mod(Loaded) {
	// "Floats? Where we're going, we don't need floats."
    OptionsAPI::addMidLevelSettingReactiveNumeric<double>(
		"My Double/Float Setting",						// name
		"my-double-or-float-setting"_spr,				// id
		[](GJBaseGameLayer*, double newDoubleValue) {
			myDoubleValue = newDoubleValue;
		},												// callback on value change, INCLUDING when the input gets clamped to min/max values.
		[](GJBaseGameLayer*) {
			// this is the value that will appear in the input box for this setting.
			return myDoubleValue;
		},												// initial value callback
		-50, 50,										// setting min and max values. Both min *AND* max values *ARE* required. When in doubt, just use  std::numeric_limits::<double>::min() and std::numeric_limits::<double>::max().
		"My Crazy Desc For My Double/Float Setting!"	// description
	);

	// "Ints? Where we're going, we don't need ints."
    OptionsAPI::addEditorLevelSettingReactiveNumeric<long>(
		"My Long/Int Setting",							// name
		"my-long-or-int-setting"_spr,					// id
		[](long newLongValue) {
			myLongValue = newLongValue;
		},												// callback on value change, INCLUDING when the input gets clamped to min/max values.
		[]() {
			// this is the value that will appear in the input box for this setting.
			return myLongValue;
		},												// initial value callback
		-5000, 5000,									// setting min and max values. Both min *AND* max values *ARE* required. When in doubt, just use  std::numeric_limits::<long>::min() and std::numeric_limits::<long>::max().
		"My Crazy Desc For My Long/Int Setting!"		// description
	);

	// You really shouldn't be using this to link to a mod's string settings, especially a string setting with the "one-of" property or regex filter.
	// This is because Options API hasn't gone as far as accomodating custom dropdown menus or parsing regex filters yet.
	// Although defining a string setting type for Options API and supplying a non-regex character filter *is* feasible, this option is not yet available as of v1.1.0.
    OptionsAPI::addPreLevelSettingReactiveNonNumeric<std::string>(
		"My String Setting",							// name
		"my-string-setting"_spr,						// id
		[](GJGameLevel*, std::string newStringValue) {
			myStringValue = newStringValue;
		},												// callback on value change
		[](GJGameLevel*) {
			// this is the value that will appear in the input box for this setting.
			return myStringValue;
		},												// initial value callback
		"My Crazy Desc For My String Setting!"			// description
	);

	// Adds a button with custom label text.
	// No, Options API will *NEVER* let you set the font of the label for the button.
	OptionsAPI::addMidLevelLabeledButtonSetting(
		"My Labeled Button",							// name (will be inside the button)
		"my-labeled-button"_spr,						// id
		[](GJBaseGameLayer* gjbgl) {
			Notification::create(fmt::format("gjbgl != nullptr: {}", gjbgl != nullptr), gjbgl != nullptr ? NotificationIcon::Success : NotificationIcon::Error, .25f)->show();
		},												// callback on button press
		[](GJBaseGameLayer* gjbgl) {
			// anything you want to do when the button first gets initalized.
			// you might find this useless, and that's totally fine!
			// but you still need to include it.
		},												// button initalization callback
		"My Crazy Desc For My Labeled Button Setting!"	// description
	);

	// Adds a button with companion label text next to it (like the vanilla RobTop toggles).
	// DO NOT SET A CALLBACK FOR THE GEODE::BUTTON NODE. IT **WILL** BE OVERWRITTEN!!!
	OptionsAPI::addEditorLevelGeodeButtonWithCallbackSetting(
		"My Geode Button With Label",					// name
		"my-geode-button-with-label"_spr,				// id
		[]() {
			// callback on button press.
			// THIS takes priority over whatever callback you might set for your geode::Button.
			// this caveat might be worthless for an Editor setting, but is CRUCIAL
			// for MidSettings and PreSettings, which pass GJBaseGameLayer/GJGameLevel pointer variables.
			Notification::create("hello world", NotificationIcon::Success, .25f)->show();
		},												// callback on button press
		[]() {
			// anything you want to do when the button first gets initalized.
			// you might find this useless, and that's totally fine!
			// but you still need to include it.
		},												// button initalization callback
		// geode::Button creation.
		// DO NOT SET A CALLBACK ON THE GEODE::BUTTON. IT WILL BE OVERWRITTEN BY THE CALLBACK ON BUTTON PRESS.
		// this caveat might be worthless for an Editor setting, but is CRUCIAL
		// for MidSettings and PreSettings, which pass GJBaseGameLayer/GJGameLevel pointer variables.
		// anything goes for a geode::Button, just PLEASE pass it through a geode::Ref.
		geode::Ref(
			geode::Button::createWithLabel(
				fmt::format("gjbgl #{}", 727), "chatFont.fnt"
			)
		),												// geode::Button creation.
		"My Crazy Desc For My Geode Button With Label!"	// description
	);
```