#include <iostream>

#include "ComponentManager.h"
#include "GameObject.h"
#include "SceneManager.h"

int main() {
    SceneManager& sceneManager = SceneManager::GetInstance();

    Scene& scene = sceneManager.CreateScene("Escena 1");

    GameObject& cubo = scene.CreateGameObject("Cubo");
    GameObject& circulo = scene.CreateGameObject("Circulo");

    cubo.AddComponent<Transform>();

    for (const auto& obj : scene.GetGameObjects()) {
        std::cout << *obj << std::endl;
    }

    cubo.AddChild(circulo);

    std::cout << "-------------------------------" << std::endl;

    for (const auto& obj : scene.GetGameObjects()) {
        std::cout << *obj << std::endl;
    }
}
