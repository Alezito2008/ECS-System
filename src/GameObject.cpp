#include "GameObject.h"

unsigned int GameObject::s_NextID = 0;

GameObject::GameObject(const std::string& name) : transform(this) {
    m_ID = ++s_NextID;

    if (name.empty()) {
        m_Name = "GameObject_" + std::to_string(m_ID);
    } else {
        m_Name = name;
    }
}
