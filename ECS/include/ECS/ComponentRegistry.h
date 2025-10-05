#pragma once
#include "GameObject.h"
#include <functional>
#include <memory>
#include <unordered_map>
#include <string>

class ComponentRegistry {
public:
    using CreatorFunc = std::function<std::unique_ptr<Component>(GameObject* owner)>;

    static void Register(const std::string& name, CreatorFunc creator);
    static std::unique_ptr<Component> Create(const std::string& name, GameObject* owner);
    static const std::unordered_map<std::string,CreatorFunc>& GetComponents();

private:
    inline static std::unordered_map<std::string,CreatorFunc> s_Creators;
};
