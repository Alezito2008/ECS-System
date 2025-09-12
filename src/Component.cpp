#include "Component.h"

unsigned int Component::m_NextID = 0;

Component::Component(GameObject* parent) {
    m_ID = m_NextID++;
    m_GameObject = parent;
}

void Component::Start() {};
void Component::Update() {};
void Component::OnDestroy() {};

const std::string& Component::GetName() const {
    static const std::string defaultName = "Component";
    return defaultName;
}

void Component::Destroy() {
    OnDestroy();
}

void Component::SetParent(GameObject* newParent) {
    m_GameObject = newParent;
}
