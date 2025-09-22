#include "Interface.h"

#include "imgui_internal.h"

#include <iostream>

#include "DockLayout.h"

static DockLayout layout;

void ShowInterface() {
    SplitList splitList{
        { "root", ImGuiDir_Down, "Console", "Up", 0.25 },
        { "Up", ImGuiDir_Left, "Tree", "Right", 0.3 }
    };

    layout.Setup(splitList);

    ImGui::Begin("Console");
    ImGui::Text("> Console");
    ImGui::End();

    ImGui::Begin("Tree");
    ImGui::Text("Es un tree");
    ImGui::End();
    
}
