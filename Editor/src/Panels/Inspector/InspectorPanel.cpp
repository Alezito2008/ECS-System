#include "Inspector/InspectorPanel.h"
#include "IconFont/IconsFontAwesome7.h"
#include "imgui.h"
#include "Colors.h"
#include "Themes.h"
#include "GameObject.h"

#include <iostream>

void RenderObjectInfo(GameObject* obj) {
    using namespace ImGui;

    const std::string name = ' ' + obj->GetName();

    PushFont(Fonts::MainFontBold);
    Checkbox(name.c_str(), obj->GetActivePtr());
    PopFont();
}

void RenderComponent() {
    using namespace ImGui;

}

void InspectorPanel::Render() {
    ImGui::Begin( ICON_FA_CIRCLE_INFO " Inspector ###Inspector");

    ImGui::PushTextWrapPos(0.0f);

    GameObject* obj = Selection::selected;

    if (obj) {
        RenderObjectInfo(obj);
        RenderComponent();
    } else {
        ImGui::PushStyleColor(ImGuiCol_Text, Color::SecondaryText);
        ImGui::Text("No Game Object selected");
        ImGui::PopStyleColor();
    }

    ImGui::PopTextWrapPos();

    ImGui::End();
}
