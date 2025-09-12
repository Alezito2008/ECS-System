#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "Component.h"
#include "ComponentManager.h"

class GameObject {
    public:
        GameObject(const std::string& name = "");
        ~GameObject() = default;

        inline unsigned int GetID() const {
            return m_ID;
        };

        inline const std::string& GetName() const {
            return m_Name;
        }
        
        inline const std::vector<std::unique_ptr<Component>>& GetComponents() const {
            return m_Components;
        };

        template <typename T>
        T* FindComponent() {
            T* comp = ComponentManager::GetInstance().FindComponent<T>(this);
            return comp;
        };

        template <typename T>
        bool RemoveComponent() {
            return ComponentManager::GetInstance().RemoveComponent<T>(this);
        };

        template <typename T>
        T* AddComponent() {
            T* comp = ComponentManager::GetInstance().CreateComponent<T>(this);
            return comp;
        };
        
        inline GameObject* GetParent() const {
            return m_Parent;
        };

        inline std::vector<std::unique_ptr<GameObject>>& GetChilds() {
            return m_Childs;
        };

        inline GameObject* FindChild(const std::string& name) const {
            for (const auto& child : m_Childs) {
                if (child->GetName() == name) {
                    return child.get();
                }
            }
            return nullptr;
        };

        inline GameObject* FindChild(const unsigned int index) const {
            if (m_Childs[index]) {
                return m_Childs[index].get();
            }
            return nullptr;
        };

        inline GameObject* FindFirstChild() const {
            return FindChild(0);
        }

        void AddChild(std::unique_ptr<GameObject> child) {
            child->m_Parent = this;
            m_Childs.push_back(std::move(child));
        };
    private:
        unsigned int m_ID;
        static unsigned int s_NextID;

        std::string m_Name;

        std::vector<std::unique_ptr<Component>> m_Components;
        std::vector<std::unique_ptr<GameObject>> m_Childs;
        GameObject* m_Parent = nullptr;
};

inline std::ostream& operator<<(std::ostream& os, const GameObject& obj) {
    os << "Name: " << obj.GetName() <<
        "\nID: " << obj.GetID() <<
            "\nParent: " << (obj.GetParent() ? obj.GetParent()->GetName() : "null") << std::endl;
    return os;
}
