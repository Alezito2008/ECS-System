#include "Interface.h"
#include "imgui_internal.h"
#include "DockLayout.h"
#include "Themes.h"

#include "Console/Console.h"
#include "Tree/Tree.h"

#include "SceneManager.h"
#include "GameObject.h"


static DockLayout layout;

static SceneManager& sceneManager = SceneManager::GetInstance();

static bool firstTime = true;

void ShowInterface() {
    if (firstTime) {
        Themes::SetBessDarkColors();

        SceneManager& sceneManager = SceneManager::GetInstance();
        Scene& scene = sceneManager.CreateScene("Escena 1");
        GameObject& cubo1 = scene.CreateGameObject("Cubo 1");
        GameObject& cubo2 = scene.CreateGameObject("Cubo 2");
        GameObject& cubo3 = scene.CreateGameObject("Cubo 3");

        Scene& scene2 = sceneManager.CreateScene("Escena 2");

        GameObject& esfera1 = scene.CreateGameObject("Esfera 1");
        GameObject& esfera2 = scene.CreateGameObject("Esfera 2");
        cubo1.AddChild(esfera1);
        cubo1.AddChild(esfera2);

        GameObject& triangulo1 = scene.CreateGameObject("Triangulo 1");
        esfera2.AddChild(triangulo1);

        firstTime = false;
        ConsolePanel::AddLog(LOGTYPE::INFO, "Hola");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Chau");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Manzana");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Hola");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Banana");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Hola");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Hola");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Chau");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Manzana");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Hola");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Banana");
        ConsolePanel::AddLog(LOGTYPE::INFO, "Hola");
    }

    SplitList splitList{
        { "root", ImGuiDir_Down, "Console", "Up", 0.25 },
        { "Up", ImGuiDir_Left, "Tree", "Right", 0.3 },
        { "Up", ImGuiDir_Right, "Inspector", nullptr, 0.25 }
    };

    layout.Setup(splitList);

    ConsolePanel::Render();
    TreePanel::Render(sceneManager.GetScenes());

    ImGui::Begin("Inspector");
    ImGui::End();
}
