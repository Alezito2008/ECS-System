#include "Tree.h"

#include "imgui.h"

static const ImU32 SCENE_COLOR = IM_COL32(45, 43, 74, 255);

void RenderGameObject(const GameObject* obj) {
    using namespace ImGui;

    const char* name = obj->GetName().c_str();
    const auto& children = obj->GetChilds();

    if (children.empty()) {
        if (TreeNodeEx(name, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen));
    } else {
        if (TreeNode(name)) {
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

    Separator();

    ImVec2 pos = GetCursorScreenPos();
    ImVec2 size = ImVec2(GetContentRegionAvail().x, GetTextLineHeight());

    GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), SCENE_COLOR);

    PushStyleColor(ImGuiCol_Header, ImVec4(0.573, 0.467, 0.922, 1));
    PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.573, 0.467, 0.922, 1));
    PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.573, 0.467, 0.922, 1));

    if (TreeNodeEx(sceneName, ImGuiTreeNodeFlags_DefaultOpen)) {
        for (const auto& obj : scene->GetGameObjects()) {
            if (obj->GetParent()) continue;
            RenderGameObject(obj.get());
        }
        TreePop();
    }

    PopStyleColor(3);
}

void TreePanel::Render(std::vector<std::unique_ptr<Scene>>& scenes) {
    ImGui::Begin("Tree");

    for (const auto& scene : scenes) {
        RenderScene(scene.get());
    }

    ImGui::End();
}
