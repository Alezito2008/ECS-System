#include "TreePanel.h"
#include "IconFont/IconsFontAwesome7.h"

#include <format>

#include "imgui.h"

static const ImU32 SCENE_COLOR = IM_COL32(45, 43, 74, 255);

void RenderGameObject(const GameObject* obj) {
    using namespace ImGui;

    const char* name = obj->GetName().c_str();
    const auto& children = obj->GetChilds();

    char nameIcon[128];
    snprintf(nameIcon, sizeof(nameIcon), "%s %s", ICON_FA_CUBE, name);

    if (children.empty()) {
        if (TreeNodeEx(nameIcon, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen));
    } else {
        if (TreeNode(nameIcon)) {
            for (const auto& child : children) {
                RenderGameObject(child);
            }

            TreePop();
        }
    }

}

void RenderScene(const Scene* scene) {
    using namespace ImGui;

    const char* sceneName = scene->GetName().c_str();
    char sceneNameIcon[128];
    snprintf(sceneNameIcon, sizeof(sceneNameIcon), "%s %s", ICON_FA_FILM, sceneName);
    

    Separator();

    ImVec2 pos = GetCursorScreenPos();
    ImVec2 size = ImVec2(GetContentRegionAvail().x, GetTextLineHeight());

    GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), SCENE_COLOR);

    PushStyleColor(ImGuiCol_Header, ImVec4(0.573, 0.467, 0.922, 1));
    PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.573, 0.467, 0.922, 1));
    PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.573, 0.467, 0.922, 1));

    if (TreeNodeEx(sceneNameIcon, ImGuiTreeNodeFlags_DefaultOpen)) {
        for (const auto& obj : scene->GetGameObjects()) {
            if (obj->GetParent()) continue;
            RenderGameObject(obj.get());
        }
        TreePop();
    }

    PopStyleColor(3);
}

void TreePanel::Render(std::vector<std::unique_ptr<Scene>>& scenes) {
    ImGui::Begin( ICON_FA_CODE_BRANCH " Tree ###Tree");

    for (const auto& scene : scenes) {
        RenderScene(scene.get());
    }

    ImGui::End();
}
