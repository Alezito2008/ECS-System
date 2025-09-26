#include "MenuBar.h"
#include "imgui.h"
#include "Themes.h"


static void Preferences_Theme() {
    using namespace ImGui;

    if (Button("Bess Dark")) Themes::SetBessDarkColors();
    else if (Button("Catpuccin Mocha")) Themes::SetCatpuccinMochaColors();
    else if (Button("Dark")) Themes::SetDarkThemeColors();
    else if (Button("ImGui")) Themes::SetDefaultColors();
    else if (Button("Fluent UI")) Themes::SetFluentUIColors();
    else if (Button("Modern Dark")) Themes::SetModernDarkColors();
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
