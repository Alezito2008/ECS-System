#include <iostream>

#include "ComponentManager.h"
#include "GameObject.h"

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
    auto object1 = std::make_unique<GameObject>();
    auto object2 = std::make_unique<GameObject>();

    object1->AddComponent<Transform>();

    // Buscar y loguear ANTES de borrar
    if (auto transform = object1->FindComponent<Transform>()) {
        std::cout << transform->GetName() << std::endl;
    }

    // Ahora borrar
    object1->RemoveComponent<Transform>();

    // Buscar otra vez para ver que ya no está
    auto afterDelete = object1->FindComponent<Transform>();
    std::cout << (afterDelete ? afterDelete->GetName() : "null") << std::endl;

    object1->AddChild(std::move(object2));

    std::cout << *object1 << std::endl;
    std::cout << *(object1->FindFirstChild()) << std::endl;
}
