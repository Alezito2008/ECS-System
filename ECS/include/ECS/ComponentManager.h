#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "Component.h"

class GameObject;
class Component;

class ComponentManager {
public:
    static ComponentManager& GetInstance() {
        static ComponentManager componentManager;
        return componentManager;
    }

    template <typename T>
    T* CreateComponent(GameObject* owner) {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component class");
        
        std::unique_ptr<T> comp = std::make_unique<T>(owner);
        T* raw = comp.get();

        auto& componentsVec = components[typeid(T).hash_code()];
        componentsVec.push_back(std::move(comp));
        
        componentsOwners[owner].push_back(raw);
        
        return raw;
    };

    const std::vector<Component*>& GetComponents(const GameObject* owner) const {
        static const std::vector<Component*> empty;
        auto it = componentsOwners.find(const_cast<GameObject*>(owner));
        if (it != componentsOwners.end()) return it->second;
        return empty;
    }

    template <typename T>
    T* FindComponent(GameObject* owner) {
        auto it = componentsOwners.find(owner);
        if (it != componentsOwners.end()) {
            for (auto comp : it->second) {
                if (auto casted = dynamic_cast<T*>(comp)) return casted;
            }
        }
        return nullptr;
    };

    template <typename T>
    bool RemoveComponent(GameObject* owner) {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component class");

        auto findOwner = componentsOwners.find(owner);
        if (findOwner == componentsOwners.end()) {
            // No se enontró el owner
            return false;
        }

        size_t typeID = typeid(T).hash_code();
        auto& componentsOfOwner = findOwner->second;

        // Chequear que el tipo de componente se haya usado
        auto findComponentType = components.find(typeID);
        if (findComponentType == components.end()) {
            // No hay component1es de este tipo
            return false;
        }

        std::vector<std::unique_ptr<Component>>& componentsOfType = findComponentType->second;

        // Ciclado por unique_ptr de components
        for (auto compIt = componentsOfType.begin(); compIt != componentsOfType.end(); ++compIt) {
            if (auto casted = dynamic_cast<T*>(compIt->get())) {
                casted->Destroy();

                // Eliminar de owner
                for (auto ownerIt = componentsOfOwner.begin(); ownerIt < componentsOfOwner.end(); ++ownerIt) {
                    if (*ownerIt == casted) {
                        componentsOfOwner.erase(ownerIt);
                        break;
                    }
                }

                componentsOfType.erase(compIt);

                return true;
            }
        }

        return false;
    }

private:
    ComponentManager() = default;

    // guarda pointers a componentes
    std::unordered_map<size_t, std::vector<std::unique_ptr<Component>>> components;
    // relaciona cada GameObject con uno de los componentes
    std::unordered_map<GameObject*, std::vector<Component*>> componentsOwners;
};