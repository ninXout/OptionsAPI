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
class Add##evname##ToggleEvent : public Event { \
protected: \
    std::string m_name; \
    std::string m_id; \
    toggle m_callback; \
    call m_initialValue; \
    std::string m_description; \
 \
public: \
    Add##evname##ToggleEvent(std::string_view name, std::string_view id,  toggle callback,  call initialValue, std::string_view desc) : m_name(name), m_id(id), m_callback(callback), m_initialValue(initialValue), m_description(desc) {}; \
 \
    READONLY(m_name, Name, std::string); \
    READONLY(m_id, ID, std::string); \
    READONLY(m_callback, Callback, toggle); \
    READONLY(m_initialValue, InitialVal, call); \
    READONLY(m_description, Desc, std::string); \
};

TOGGLEEVENT(Pre, PreToggleCallback, PreInitialCallback)
TOGGLEEVENT(Mid, MidToggleCallback, MidInitialCallback)
TOGGLEEVENT(Edit, EditToggleCallback, EditInitialCallback)

namespace OptionsAPI { // TODO: expand to float, int, and std::string
    template <typename T>
    void addPreLevelSetting(std::string_view name, std::string_view id, std::function<void(GJGameLevel*)> callback, std::function<T(GJGameLevel*)> initialValue, std::string_view desc);

    template <typename T>
    void addMidLevelSetting(std::string_view name, std::string_view id, std::function<void(GJBaseGameLayer*)> callback, std::function<T(GJBaseGameLayer*)> initialValue, std::string_view desc);

    template <typename T>
    void addEditorLevelSetting(std::string_view name, std::string_view id, std::function<void()> callback, std::function<T()> initialValue, std::string_view desc);

    template <>
    void addPreLevelSetting<bool>(std::string_view name, std::string_view id, PreToggleCallback callback, PreInitialCallback initialValue, std::string_view desc) {
        AddPreToggleEvent(name, id, callback, initialValue, desc).post();
    }

    template <>
    void addMidLevelSetting<bool>(std::string_view name, std::string_view id, MidToggleCallback callback, MidInitialCallback initialValue, std::string_view desc) {
        AddMidToggleEvent(name, id, callback, initialValue, desc).post();
    }

    template <>
    void addEditorLevelSetting<bool>(std::string_view name, std::string_view id, EditToggleCallback callback, EditInitialCallback initialValue, std::string_view desc) {
        AddEditToggleEvent(name, id, callback, initialValue, desc).post();
    }
}