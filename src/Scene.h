#pragma once

#include <memory>
#include <vector>

#include "GameObject.h"

class Scene {
public:
    Scene();
    ~Scene();

    GameObject& CreateGameObject(const std::string& name) {
        auto gameObject = std::make_unique<GameObject>(name);
        GameObject& ref = *gameObject;
        m_GameObjects.push_back(std::move(gameObject));
        return ref;
    }
private:
    static unsigned int s_NextID;
    unsigned int m_ID;
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
};
