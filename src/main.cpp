#include <iostream>

#include "ComponentManager.h"
#include "GameObject.h"
#include "Scene.h"

class Transform : public Component {
public:
    Transform(GameObject* parent = nullptr) : Component(parent) {};

    const std::string& GetName() const override {
        static const std::string name = "Transform";
        return name;
    }

    void Start() override {
        std::cout << "Iniciado" << std::endl;
    }

    void Update() override {
        std::cout << "Actualizado" << std::endl;
    }

    void OnDestroy() override {
        std::cout << "Destruido" << std::endl;
    }
};

int main() {
    Scene scene;

    GameObject& cubo = scene.CreateGameObject("Cubo");
    GameObject& circulo = scene.CreateGameObject("Circulo");

    for (const auto& obj : scene.GetGameObjects()) {
        std::cout << *obj << std::endl;
    }

    cubo.AddChild(circulo);

    std::cout << "-------------------------------" << std::endl;

    for (const auto& obj : scene.GetGameObjects()) {
        std::cout << *obj << std::endl;
    }
}
