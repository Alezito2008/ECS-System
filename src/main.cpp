#include <iostream>

#include "ComponentManager.h"
#include "GameObject.h"
#include "Scene.h"

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
