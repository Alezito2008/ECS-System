#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

class GameObject;

class Transform : public Component {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 worldMatrix;

    Transform(GameObject* parent)
        : Component(parent), position(0.0f), rotation(0.0f), scale(0.0f) {}

    const std::string& GetName() const override {
        static const std::string name = "Transform";
        return name;
    }

    glm::mat4 GetLocalMatrix() const;

    void UpdateWorldMatrix();

    void Update() override {
        UpdateWorldMatrix();
    }

};
