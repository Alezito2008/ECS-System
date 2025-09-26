#include "MenuBar.h"
#include "imgui.h"
#include "Themes.h"

static void Preferences_Theme() {
    using namespace ImGui;

    static std::vector<ThemeEntry> themes = Themes::GetThemes();
    ImVec2 fullWidth(GetContentRegionAvail().x, 0);

    for (const auto& theme : themes) {
        if (Button(theme.name, fullWidth)) theme.apply();
    }
}

void MenuBar::Render() {
    using namespace ImGui;

    if (BeginMainMenuBar()) {
        if (BeginMenu("File")) {
            EndMenu();
        }

        if (BeginMenu("Preferences")) {
            if (BeginMenu("Theme")) {
                Preferences_Theme();
                EndMenu();
            }
            EndMenu();
        }

        EndMainMenuBar();
    }
}
