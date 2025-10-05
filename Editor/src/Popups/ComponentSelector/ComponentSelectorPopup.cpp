#include "ComponentSelector/ComponentSelectorPopup.h"
#include "imgui.h"
#include "ComponentRegistry.h"
#include "Themes.h"
#include "GameObject.h"

static bool isOpen = false;

void ComponentSelectorPopup::Open() {
    isOpen = true;
    ImGui::OpenPopup("###component-selector");
}

void ComponentSelectorPopup::Render() {
    using namespace ImGui;

    if (!isOpen) return;

    if (BeginPopup("Select Component ###component-selector")) {
        PushFont(Fonts::MainFontBold, 16.0f);
        Text("Select Component");
        PopFont();
        Separator();
        
        Spacing();
        
        const auto& components = ComponentRegistry::GetComponents();

        static float lineHeight = GetTextLineHeightWithSpacing();
        static float maxHeight = 300.0f;

        float childHeight = lineHeight * components.size();

        childHeight = std::min(childHeight, maxHeight) + 10.0f;

        BeginChild("components-view", ImVec2(0, childHeight));

        for (const auto& [name, create] : components) {
            if (Button(name.c_str(), ImVec2(-FLT_MIN, 0))) {
                std::unique_ptr<Component> comp = create(Selection::selected);
                Selection::selected->AddComponent(std::move(comp));
                CloseCurrentPopup();
                isOpen = false;
            };
        }

        EndChild();

        EndPopup();
    };
    
}
