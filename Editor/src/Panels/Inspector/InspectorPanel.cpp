#include "Inspector/InspectorPanel.h"
#include "IconFont/IconsFontAwesome7.h"
#include "imgui.h"

#include "GameObject.h"

void RenderComponent() {
    using namespace ImGui;

    LabelText("Manzana", "Manzana");
}

void InspectorPanel::Render() {
    ImGui::Begin( ICON_FA_CIRCLE_INFO " Inspector ###Inspector");
    RenderComponent();
    ImGui::End();
}
