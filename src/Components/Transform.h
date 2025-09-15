#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

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

    glm::mat4 GetLocalMatrix() const {
        glm::mat4 model(1.0f);
        model = glm::translate(model, position);

        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::scale(model, scale);

        return model;
    }

    void UpdateWorldMatrix() {
        GameObject* parent = m_Owner->GetParent();
        if (parent) {
            Transform& parentTransform = parent->transform;
            worldMatrix = parentTransform.GetLocalMatrix();
        } else {
            worldMatrix = GetLocalMatrix();
        }

        for (auto* child : m_Owner->GetChilds()) {
            child->transform.UpdateWorldMatrix();
        }
    }

    void Update() override {
        UpdateWorldMatrix();
    }

};
