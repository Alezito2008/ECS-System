#include "ComponentRegistry.h"
#include <dlfcn.h>

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

bool ComponentRegistry::LoadLibrary(const std::string &path, bool clear /*= true*/)
{
    using RegisterFunc = void(*)();

    if (clear) Clear();

    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cout << "[ERROR] Cannot load library: " << path << "\n" << dlerror() << std::endl;
        return false;
    }    
    dlerror();

    RegisterFunc registerComponents = reinterpret_cast<RegisterFunc>(
        dlsym(handle, "RegisterComponents")
    );

    if (!registerComponents) {
        std::cout << "[ERROR] Failed to find RegisterComponents function on " << path << " not found" << std::endl;
        dlclose(handle);
        return false;
    }

    registerComponents();
    return true;
}
