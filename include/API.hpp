#pragma once

#include <Geode/Geode.hpp>

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
class Add##evname##DoubleEvent : public Event<Add##evname##ToggleEvent, bool(std::string_view name, std::string_view id, changeInDouble callback, call initialValue, std::string_view desc, geode::Mod* mod)> { \
public: \
    using Event::Event; \
    std::string m_name; \
    std::string m_id; \
    changeInDouble m_callback; \
    call m_initialValue; \
    std::string m_description; \
    geode::Mod* m_mod; \
 \
    Add##evname##DoubleEvent(std::string_view name, std::string_view id, changeInDouble callback, call initialValue, std::string_view desc, geode::Mod* mod) : m_name(name), m_id(id), m_callback(callback), m_initialValue(initialValue), m_description(desc), m_mod(mod) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, changeInDouble); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_description, Desc, std::string); \
    READONLY(m_mod, Mod, geode::Mod*); \
};

DOUBLEEVENT(Pre, PreDoubleCallback, PreInitialCallbackDouble)
DOUBLEEVENT(Mid, MidDoubleCallback, MidInitialCallbackDouble)
DOUBLEEVENT(Edit, EditDoubleCallback, EditInitialCallbackDouble)

namespace OptionsAPI { // TODO: expand to double, long, and std::string
    template <typename T>
    void addPreLevelSetting(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<T(GJGameLevel*)> initialValue, std::string_view desc);

    template <typename T>
    void addMidLevelSetting(std::string_view name, std::string_view id, std::function<void(GJBaseGameLayer*)> callback, std::function<T(GJBaseGameLayer*)> initialValue, std::string_view desc);

    template <typename T>
    void addEditorLevelSetting(std::string_view name, std::string_view id, std::function<void()> callback, std::function<T()> initialValue, std::string_view desc);

    template <typename T>
    void addPreLevelSettingReactive(std::string_view name, std::string_view id, std::function<void(GJGameLevel*, T)> callback, std::function<T(GJGameLevel*)> initialValue, std::string_view desc);

    template <typename T>
    void addMidLevelSettingReactive(std::string_view name, std::string_view id, std::function<void(GJBaseGameLayer*, T)> callback, std::function<T(GJBaseGameLayer*)> initialValue, std::string_view desc);

    template <typename T>
    void addEditorLevelSettingReactive(std::string_view name, std::string_view id, std::function<void(T)> callback, std::function<T()> initialValue, std::string_view desc);

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
    void addPreLevelSettingReactive<double>(std::string_view name, std::string_view id, PreDoubleCallback callback, PreInitialCallbackDouble initialValue, std::string_view desc) {
        AddPreDoubleEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    template <>
    void addMidLevelSettingReactive<double>(std::string_view name, std::string_view id, MidDoubleCallback callback, MidInitialCallbackDouble initialValue, std::string_view desc) {
        AddMidDoubleEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }

    template <>
    void addEditorLevelSettingReactive<double>(std::string_view name, std::string_view id, EditDoubleCallback callback, EditInitialCallbackDouble initialValue, std::string_view desc) {
        AddEditDoubleEvent().send(name, id, callback, initialValue, desc, geode::getMod());
    }
}