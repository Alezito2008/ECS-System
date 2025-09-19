#include "Interface.h"

#include "imgui_internal.h"

#include <iostream>


static bool first_time = true;
void SetupDockspace() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

    // Ventana invisible para DockSpace
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus |
                                    ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDocking;

    ImGui::Begin("DockSpaceWindow", nullptr, window_flags);
    ImGui::DockSpace(dockspace_id, ImVec2(0,0), ImGuiDockNodeFlags_None);
    ImGui::End();

    if (first_time) {
        first_time = false;

        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

        ImGuiID dock_id_bottom, dock_id_top;
        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, &dock_id_bottom, &dock_id_top);

        std::cout << "Top: " << dock_id_top << "\n" << "Bottom: " << dock_id_bottom << std::endl;

        ImGui::DockBuilderDockWindow("Console", dock_id_bottom);
        ImGui::DockBuilderDockWindow("Manzana", dock_id_top);

        ImGuiID sceneTree;
        ImGui::DockBuilderSplitNode(dock_id_top, ImGuiDir_Left, 0.25f, &sceneTree, nullptr);
        ImGui::DockBuilderDockWindow("SceneTree", sceneTree);

        ImGui::DockBuilderFinish(dockspace_id);
    }
}

void ShowInterface() {
    SetupDockspace();

    ImGui::Begin("Console");
    ImGui::Text("Mango mango");
    ImGui::End();

    ImGui::Begin("Manzana");
    ImGui::Text("aaaa");
    ImGui::End();

    ImGui::Begin("SceneTree");
    ImGui::Text("Es un arbolito");
    ImGui::End();
}
