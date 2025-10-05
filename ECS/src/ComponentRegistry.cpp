#include "ComponentRegistry.h"

void ComponentRegistry::Register(const std::string &name, ComponentRegistry::CreatorFunc creator)
{
    auto it = s_Creators.find(name);
    assert(it == s_Creators.end() && "The component is already registered");
    s_Creators[name] = creator;
}

std::unique_ptr<Component> ComponentRegistry::Create(const std::string& name, GameObject* owner)
{
    auto it = s_Creators.find(name);
    assert(it != s_Creators.end() && "The component isn't registered");
    return it->second(owner);
}

const std::unordered_map<std::string, ComponentRegistry::CreatorFunc> &ComponentRegistry::GetComponents()
{
    return s_Creators;
}
