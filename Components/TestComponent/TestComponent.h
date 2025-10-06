#pragma once
#include "Component.h"

class TestComponent : public Component {
public:
    int vida = 100;

    TestComponent(GameObject* owner) : Component(owner) {
        SERIALIZED_FIELD(vida);
    }

    inline const std::string& GetName() const override {
        static const std::string name = "TestComponent";
        return name; 
    };
};
