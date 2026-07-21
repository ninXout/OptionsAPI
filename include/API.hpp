#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Button.hpp>

using namespace geode::prelude;

using PreToggleCallback = std::function<void(GJGameLevel*)>;
using PreInitialCallback = std::function<bool(GJGameLevel*)>;

using MidToggleCallback = std::function<void(GJBaseGameLayer*)>;
using MidInitialCallback = std::function<bool(GJBaseGameLayer*)>;

using EditToggleCallback = std::function<void()>;
using EditInitialCallback = std::function<bool()>;

#define READONLY(mem, name, type) type get##name() const { return mem; };

#define TOGGLEEVENT(evname, toggle, call) \
class Add##evname##ToggleEvent : public Event<Add##evname##ToggleEvent, bool(std::string_view name, std::string_view id, toggle callback, call initialValue, std::string_view desc, geode::Mod* mod)> { \
public: \
    using Event::Event; \
    std::string m_name; \
    std::string m_id; \
    toggle m_callback; \
    call m_initialValue; \
    std::string m_description; \
    geode::Mod* m_mod; \
 \
    Add##evname##ToggleEvent(std::string_view name, std::string_view id, toggle callback, call initialValue, std::string_view desc, geode::Mod* mod) : m_name(name), m_id(id), m_callback(callback), m_initialValue(initialValue), m_description(desc), m_mod(mod) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, toggle); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_description, Desc, std::string); \
    READONLY(m_mod, Mod, geode::Mod*); \
};

TOGGLEEVENT(Pre, PreToggleCallback, PreInitialCallback)
TOGGLEEVENT(Mid, MidToggleCallback, MidInitialCallback)
TOGGLEEVENT(Edit, EditToggleCallback, EditInitialCallback)

using PreDoubleCallback = std::function<void(GJGameLevel*, double)>;
using PreInitialCallbackDouble = std::function<double(GJGameLevel*)>;

using MidDoubleCallback = std::function<void(GJBaseGameLayer*, double)>;
using MidInitialCallbackDouble = std::function<double(GJBaseGameLayer*)>;

using EditDoubleCallback = std::function<void(double)>;
using EditInitialCallbackDouble = std::function<double()>;

#define DOUBLEEVENT(evname, changeInDouble, call) \
class Add##evname##DoubleEvent : public Event<Add##evname##DoubleEvent, bool(std::string_view name, std::string_view id, changeInDouble callback, call initialValue, double min, double max, std::string_view desc, geode::Mod* mod)> { \
public: \
    using Event::Event; \
    std::string m_name; \
    std::string m_id; \
    changeInDouble m_callback; \
    call m_initialValue; \
    double m_min; \
    double m_max; \
    std::string m_description; \
    geode::Mod* m_mod; \
 \
    Add##evname##DoubleEvent(std::string_view name, std::string_view id, changeInDouble callback, call initialValue, double min, double max, std::string_view desc, geode::Mod* mod) : m_name(name), m_id(id), m_callback(callback), m_initialValue(initialValue), m_min(min), m_max(max), m_description(desc), m_mod(mod) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, changeInDouble); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_description, Desc, std::string); \
    READONLY(m_mod, Mod, geode::Mod*); \
    READONLY(m_min, Min, double); \
    READONLY(m_max, Max, double); \
};

DOUBLEEVENT(Pre, PreDoubleCallback, PreInitialCallbackDouble)
DOUBLEEVENT(Mid, MidDoubleCallback, MidInitialCallbackDouble)
DOUBLEEVENT(Edit, EditDoubleCallback, EditInitialCallbackDouble)

using PreLongCallback = std::function<void(GJGameLevel*, long)>;
using PreInitialCallbackLong = std::function<long(GJGameLevel*)>;

using MidLongCallback = std::function<void(GJBaseGameLayer*, long)>;
using MidInitialCallbackLong = std::function<long(GJBaseGameLayer*)>;

using EditLongCallback = std::function<void(long)>;
using EditInitialCallbackLong = std::function<long()>;

#define LONGEVENT(evname, changeInLong, call) \
class Add##evname##LongEvent : public Event<Add##evname##LongEvent, bool(std::string_view name, std::string_view id, changeInLong callback, call initialValue, long min, long max, std::string_view desc, geode::Mod* mod)> { \
public: \
    using Event::Event; \
    std::string m_name; \
    std::string m_id; \
    changeInLong m_callback; \
    call m_initialValue; \
    long m_min; \
    long m_max; \
    std::string m_description; \
    geode::Mod* m_mod; \
 \
    Add##evname##LongEvent(std::string_view name, std::string_view id, changeInLong callback, call initialValue, long min, long max, std::string_view desc, geode::Mod* mod) : m_name(name), m_id(id), m_callback(callback), m_initialValue(initialValue), m_min(min), m_max(max), m_description(desc), m_mod(mod) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, changeInLong); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_description, Desc, std::string); \
    READONLY(m_mod, Mod, geode::Mod*); \
    READONLY(m_min, Min, long); \
    READONLY(m_max, Max, long); \
};

LONGEVENT(Pre, PreLongCallback, PreInitialCallbackLong)
LONGEVENT(Mid, MidLongCallback, MidInitialCallbackLong)
LONGEVENT(Edit, EditLongCallback, EditInitialCallbackLong)

using PreStringCallback = std::function<void(GJGameLevel*, std::string)>;
using PreInitialCallbackString = std::function<std::string(GJGameLevel*)>;

using MidStringCallback = std::function<void(GJBaseGameLayer*, std::string)>;
using MidInitialCallbackString = std::function<std::string(GJBaseGameLayer*)>;

using EditStringCallback = std::function<void(std::string)>;
using EditInitialCallbackString = std::function<std::string()>;

#define STRINGEVENT(evname, changeInString, call) \
class Add##evname##StringEvent : public Event<Add##evname##StringEvent, bool(std::string_view name, std::string_view id, changeInString callback, call initialValue, std::string_view desc, geode::Mod* mod)> { \
public: \
    using Event::Event; \
    std::string m_name; \
    std::string m_id; \
    changeInString m_callback; \
    call m_initialValue; \
    std::string m_description; \
    geode::Mod* m_mod; \
 \
    Add##evname##StringEvent(std::string_view name, std::string_view id, changeInString callback, call initialValue, std::string_view desc, geode::Mod* mod) : m_name(name), m_id(id), m_callback(callback), m_initialValue(initialValue), m_description(desc), m_mod(mod) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, changeInString); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_description, Desc, std::string); \
    READONLY(m_mod, Mod, geode::Mod*); \
};

STRINGEVENT(Pre, PreStringCallback, PreInitialCallbackString)
STRINGEVENT(Mid, MidStringCallback, MidInitialCallbackString)
STRINGEVENT(Edit, EditStringCallback, EditInitialCallbackString)

using PreLabeledButtonCallback = std::function<void(GJGameLevel*)>;
using PreInitialCallbackLabeledButton = std::function<void(GJGameLevel*)>;

using MidLabeledButtonCallback = std::function<void(GJBaseGameLayer*)>;
using MidInitialCallbackLabeledButton = std::function<void(GJBaseGameLayer*)>;

using EditLabeledButtonCallback = std::function<void()>;
using EditInitialCallbackLabeledButton = std::function<void()>;

#define LABELEDBUTTONEVENT(evname, onButtonPress, call) \
class Add##evname##LabeledButtonEvent : public Event<Add##evname##LabeledButtonEvent, bool(std::string_view name, std::string_view id, onButtonPress callback, call initialValue, std::string_view desc, geode::Mod* mod)> { \
public: \
    using Event::Event; \
    std::string m_name; \
    std::string m_id; \
    onButtonPress m_callback; \
    call m_initialValue; \
    std::string m_description; \
    geode::Mod* m_mod; \
 \
    Add##evname##LabeledButtonEvent(std::string_view name, std::string_view id, onButtonPress callback, call initialValue, std::string_view desc, geode::Mod* mod) : m_name(name), m_id(id), m_callback(callback), m_initialValue(initialValue), m_description(desc), m_mod(mod) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, onButtonPress); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_description, Desc, std::string); \
    READONLY(m_mod, Mod, geode::Mod*); \
};

LABELEDBUTTONEVENT(Pre, PreLabeledButtonCallback, PreInitialCallbackLabeledButton)
LABELEDBUTTONEVENT(Mid, MidLabeledButtonCallback, MidInitialCallbackLabeledButton)
LABELEDBUTTONEVENT(Edit, EditLabeledButtonCallback, EditInitialCallbackLabeledButton)

using PreGeodeButtonWithLabelCallback = std::function<void(GJGameLevel*)>;
using PreInitialCallbackGeodeButtonWithLabel = std::function<void(GJGameLevel*)>;

using MidGeodeButtonWithLabelCallback = std::function<void(GJBaseGameLayer*)>;
using MidInitialCallbackGeodeButtonWithLabel = std::function<void(GJBaseGameLayer*)>;

using EditGeodeButtonWithLabelCallback = std::function<void()>;
using EditInitialCallbackGeodeButtonWithLabel = std::function<void()>;

#define GEODEBUTTONWITHLABELEVENT(evname, onButtonPress, call) \
class Add##evname##GeodeButtonWithLabelEvent : public Event<Add##evname##GeodeButtonWithLabelEvent, bool(std::string_view name, std::string_view id, onButtonPress callback, call initialValue, geode::Ref<geode::Button> button, std::string_view desc, geode::Mod* mod)> { \
public: \
    using Event::Event; \
    std::string m_name; \
    std::string m_id; \
    onButtonPress m_callback; \
    call m_initialValue; \
    geode::Ref<geode::Button> m_button; \
    std::string m_description; \
    geode::Mod* m_mod; \
 \
    Add##evname##GeodeButtonWithLabelEvent(std::string_view name, std::string_view id, onButtonPress callback, call initialValue, geode::Ref<geode::Button> button, std::string_view desc, geode::Mod* mod) : m_name(name), m_id(id), m_callback(callback), m_button(button), m_initialValue(initialValue), m_description(desc), m_mod(mod) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, onButtonPress); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_button, Button, geode::Ref<geode::Button>); \
    READONLY(m_description, Desc, std::string); \
    READONLY(m_mod, Mod, geode::Mod*); \
};

GEODEBUTTONWITHLABELEVENT(Pre, PreGeodeButtonWithLabelCallback, PreInitialCallbackGeodeButtonWithLabel)
GEODEBUTTONWITHLABELEVENT(Mid, MidGeodeButtonWithLabelCallback, MidInitialCallbackGeodeButtonWithLabel)
GEODEBUTTONWITHLABELEVENT(Edit, EditGeodeButtonWithLabelCallback, EditInitialCallbackGeodeButtonWithLabel)

namespace OptionsAPI {
    template <typename T>
    void addPreLevelSetting(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<T(GJGameLevel*)> initialValue, std::string_view desc);

    template <typename T>
    void addMidLevelSetting(std::string_view name, std::string_view id, std::function<void(GJBaseGameLayer*)> callback, std::function<T(GJBaseGameLayer*)> initialValue, std::string_view desc);

    template <typename T>
    void addEditorLevelSetting(std::string_view name, std::string_view id, std::function<void()> callback, std::function<T()> initialValue, std::string_view desc);

    template <typename T>
    void addPreLevelSettingReactiveNumeric(std::string_view name, std::string_view id, std::function<void(GJGameLevel*, T)> callback, std::function<T(GJGameLevel*)> initialValue, T min, T max, std::string_view desc);

    template <typename T>
    void addMidLevelSettingReactiveNumeric(std::string_view name, std::string_view id, std::function<void(GJBaseGameLayer*, T)> callback, std::function<T(GJBaseGameLayer*)> initialValue, T min, T max, std::string_view desc);

    template <typename T>
    void addEditorLevelSettingReactiveNumeric(std::string_view name, std::string_view id, std::function<void(T)> callback, std::function<T()> initialValue, T min, T max, std::string_view desc);

    template <typename T>
    void addPreLevelSettingReactiveNonNumeric(std::string_view name, std::string_view id, std::function<void(GJGameLevel*, T)> callback, std::function<T(GJGameLevel*)> initialValue, std::string_view desc);

    template <typename T>
    void addMidLevelSettingReactiveNonNumeric(std::string_view name, std::string_view id, std::function<void(GJBaseGameLayer*, T)> callback, std::function<T(GJBaseGameLayer*)> initialValue, std::string_view desc);

    template <typename T>
    void addEditorLevelSettingReactiveNonNumeric(std::string_view name, std::string_view id, std::function<void(T)> callback, std::function<T()> initialValue, std::string_view desc);

    template <>
    void addPreLevelSetting<bool>(std::string_view name, std::string_view id, PreToggleCallback callback, PreInitialCallback initialValue, std::string_view desc) {
        AddPreToggleEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    template <>
    void addMidLevelSetting<bool>(std::string_view name, std::string_view id, MidToggleCallback callback, MidInitialCallback initialValue, std::string_view desc) {
        AddMidToggleEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    template <>
    void addEditorLevelSetting<bool>(std::string_view name, std::string_view id, EditToggleCallback callback, EditInitialCallback initialValue, std::string_view desc) {
        AddEditToggleEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    template <>
    void addPreLevelSettingReactiveNumeric<double>(std::string_view name, std::string_view id, PreDoubleCallback callback, PreInitialCallbackDouble initialValue, double min, double max, std::string_view desc) {
        AddPreDoubleEvent().send(name, id, callback, initialValue, min, max, desc, geode::getMod());
    }

    template <>
    void addMidLevelSettingReactiveNumeric<double>(std::string_view name, std::string_view id, MidDoubleCallback callback, MidInitialCallbackDouble initialValue, double min, double max, std::string_view desc) {
        AddMidDoubleEvent().send(name, id, callback, initialValue, min, max, desc, geode::getMod());
    }

    template <>
    void addEditorLevelSettingReactiveNumeric<double>(std::string_view name, std::string_view id, EditDoubleCallback callback, EditInitialCallbackDouble initialValue, double min, double max, std::string_view desc) {
        AddEditDoubleEvent().send(name, id, callback, initialValue, min, max, desc, geode::getMod());
    }

    template <>
    void addPreLevelSettingReactiveNumeric<long>(std::string_view name, std::string_view id, PreLongCallback callback, PreInitialCallbackLong initialValue, long min, long max, std::string_view desc) {
        AddPreLongEvent().send(name, id, callback, initialValue, min, max, desc, geode::getMod());
    }

    template <>
    void addMidLevelSettingReactiveNumeric<long>(std::string_view name, std::string_view id, MidLongCallback callback, MidInitialCallbackLong initialValue, long min, long max, std::string_view desc) {
        AddMidLongEvent().send(name, id, callback, initialValue, min, max, desc, geode::getMod());
    }

    template <>
    void addEditorLevelSettingReactiveNumeric<long>(std::string_view name, std::string_view id, EditLongCallback callback, EditInitialCallbackLong initialValue, long min, long max, std::string_view desc) {
        AddEditLongEvent().send(name, id, callback, initialValue, min, max, desc, geode::getMod());
    }

    template <>
    void addPreLevelSettingReactiveNonNumeric<std::string>(std::string_view name, std::string_view id, PreStringCallback callback, PreInitialCallbackString initialValue, std::string_view desc) {
        AddPreStringEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    template <>
    void addMidLevelSettingReactiveNonNumeric<std::string>(std::string_view name, std::string_view id, MidStringCallback callback, MidInitialCallbackString initialValue, std::string_view desc) {
        AddMidStringEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    template <>
    void addEditorLevelSettingReactiveNonNumeric<std::string>(std::string_view name, std::string_view id, EditStringCallback callback, EditInitialCallbackString initialValue, std::string_view desc) {
        AddEditStringEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    void addPreLevelLabeledButtonSetting(std::string_view name, std::string_view id, PreLabeledButtonCallback callback, PreInitialCallbackLabeledButton initialValue, std::string_view desc) {
        AddPreLabeledButtonEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    void addMidLevelLabeledButtonSetting(std::string_view name, std::string_view id, MidLabeledButtonCallback callback, MidInitialCallbackLabeledButton initialValue, std::string_view desc) {
        AddMidLabeledButtonEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    void addEditorLevelLabeledButtonSetting(std::string_view name, std::string_view id, EditLabeledButtonCallback callback, EditInitialCallbackLabeledButton initialValue, std::string_view desc) {
        AddEditLabeledButtonEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    void addPreLevelGeodeButtonWithCallbackSetting(std::string_view name, std::string_view id, PreGeodeButtonWithLabelCallback callback, PreInitialCallbackGeodeButtonWithLabel initialValue, geode::Ref<geode::Button> button, std::string_view desc) {
        AddPreGeodeButtonWithLabelEvent().send(name, id, callback, initialValue, button, desc, geode::getMod());
    }

    void addMidLevelGeodeButtonWithCallbackSetting(std::string_view name, std::string_view id, MidGeodeButtonWithLabelCallback callback, MidInitialCallbackGeodeButtonWithLabel initialValue, geode::Ref<geode::Button> button, std::string_view desc) {
        AddMidGeodeButtonWithLabelEvent().send(name, id, callback, initialValue, button, desc, geode::getMod());
    }

    void addEditorLevelGeodeButtonWithCallbackSetting(std::string_view name, std::string_view id, EditGeodeButtonWithLabelCallback callback, EditInitialCallbackGeodeButtonWithLabel initialValue, geode::Ref<geode::Button> button, std::string_view desc) {
        AddEditGeodeButtonWithLabelEvent().send(name, id, callback, initialValue, button, desc, geode::getMod());
    }
}