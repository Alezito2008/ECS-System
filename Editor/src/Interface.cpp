#include "Interface.h"
#include "imgui_internal.h"
#include "console/console.h"

#include <iostream>

#include "DockLayout.h"

static DockLayout layout;

static bool firstTime = true;

void ShowInterface() {
    if (firstTime) {
        firstTime = false;
        Console::AddLog(LOGTYPE::INFO, "Hola");
        Console::AddLog(LOGTYPE::INFO, "Chau");
        Console::AddLog(LOGTYPE::INFO, "Manzana");
        Console::AddLog(LOGTYPE::INFO, "Hola");
        Console::AddLog(LOGTYPE::INFO, "Banana");
        Console::AddLog(LOGTYPE::INFO, "Hola");
        Console::AddLog(LOGTYPE::INFO, "Hola");
        Console::AddLog(LOGTYPE::INFO, "Chau");
        Console::AddLog(LOGTYPE::INFO, "Manzana");
        Console::AddLog(LOGTYPE::INFO, "Hola");
        Console::AddLog(LOGTYPE::INFO, "Banana");
        Console::AddLog(LOGTYPE::INFO, "Hola");
    }

    SplitList splitList{
        { "root", ImGuiDir_Down, "Console", "Up", 0.25 },
        { "Up", ImGuiDir_Left, "Tree", "Right", 0.3 }
    };

    layout.Setup(splitList);

    Console::Render();

    ImGui::Begin("Tree");
    ImGui::Text("Es un tree");
    ImGui::End();
    
}
