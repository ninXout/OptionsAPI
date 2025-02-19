# Options API

API mod that allows developers to add their own settings to some of the settings menus in game.

## Usage

There is 3 menus you can add settings to for now, and at the moment, only bool toggles can be added. Buttons with callbacks and text inputs are soon to come.

```cpp
// To add a setting to the LevelInfoLayer settings
OptionsAPI::addPreLevelSetting<bool>(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc);

// To add a setting to the PauseLayer settings
OptionsAPI::addMidLevelSetting<bool>(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc);

// To add a setting to the EditorPauseLayer settings
OptionsAPI::addEditorSetting<bool>(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<bool(GJGameLevel*)> initialValue, std::string_view desc);
```

Basic usage (Adding setting to LevelInfoLayer settings):
```cpp
#include <ninxout.options_api/include/API.hpp>

bool myBoolSetting = false;

$on_mod(Loaded) {
    OptionsAPI::addPreLevelSetting<bool>(
		"My Crazy Setting",                                                // name
		"my-setting"_spr,                                                  // id
		[myBoolSetting](GJGameLevel*) { myBoolSetting = !myBoolSetting },  // toggle callback
		[myBoolSetting](GJGameLevel*) { return myBoolSetting },            // initial value callback
		"My Crazy Description!"                                            // description
	);
}
```