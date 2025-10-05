#include "Inspector/InspectorPanel.h"
#include "IconFont/IconsFontAwesome7.h"
#include "imgui.h"
#include "Colors.h"
#include "Themes.h"
#include "GameObject.h"
#include "GameObject.inl"
#include "SerializedField.h"

const std::string ToTag(const std::string& name) {
    return "###" + name + "_field";
} 

static void DrawSerializedField(ISerializedField* field) {
    using namespace ImGui;
    const char* name = field->GetName();

    if (field->GetType() == typeid(int)) {
        int* value = static_cast<int*>(field->GetPtr());
        Text("%s:", name);
        SameLine();
        SetNextItemWidth(100);
        InputInt(ToTag(name).c_str(), value);
    }
}

void RenderObjectInfo(GameObject* obj) {
    using namespace ImGui;

    const std::string name = " " + obj->GetName();

    PushFont(Fonts::MainFontBold, 16.0f);
    Checkbox(name.c_str(), obj->GetActivePtr());
    PopFont();

    SeparatorText("Properties");

    PushFont(Fonts::ConsoleFont, 14.0f);

    Dummy(ImVec2(0, 5.0f));

    GameObject* parent = obj->GetParent();

    Text("ID: %d", obj->GetID());
    Text("Childs: %d", obj->GetChilds().size());
    Text("Components: %d", obj->GetComponents().size());
    Text("Parent: %s", parent ? parent->GetName().c_str() : "null");

    Dummy(ImVec2(0, 5.0f));

    PopFont();

    SeparatorText("Components");
}

void RenderComponent(Component* comp) {
    using namespace ImGui;

    PushFont(Fonts::MainFontBold, 16.0f);
    Text(comp->GetName().c_str());
    Dummy(ImVec2(0, 5.0f));
    Separator();
    PopFont();
    PushFont(Fonts::ConsoleFont, 16.0f);
    for (ISerializedField* field : comp->GetSerializedFields()) {
        Dummy(ImVec2(0, 5.0f));
        DrawSerializedField(field);
    }
    PopFont();
}

void InspectorPanel::Render() {
    ImGui::Begin( ICON_FA_CIRCLE_INFO " Inspector ###Inspector");

    ImGui::PushTextWrapPos(0.0f);

    GameObject* obj = Selection::selected;

    if (obj) {
        RenderObjectInfo(obj);
        
        for (auto& comp : obj->GetComponents()) {
            RenderComponent(comp);
        }
    } else {
        // Cuando no hay nada seleccionado
        constexpr const char* text = "No Game Object selected";

        const ImVec2 spaceSize = ImGui::GetWindowSize();
        const ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, false, 0.0f);
        float cursorX = (spaceSize.x - textSize.x) * 0.5f;
        const float cursorY = (spaceSize.y - textSize.y) * 0.5f;

        if (cursorX <= 15.0f) cursorX = 15.0f;

        ImGui::SetCursorPos(ImVec2(cursorX, cursorY));
        
        ImGui::PushStyleColor(ImGuiCol_Text, Color::SecondaryText);
        ImGui::TextUnformatted(text);
        ImGui::PopStyleColor();
    }

    ImGui::PopTextWrapPos();

    ImGui::End();
}
