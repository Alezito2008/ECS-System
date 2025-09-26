#pragma once

#include "imgui.h"

class Themes {
public:
    static void SetDefaultColors();
    static void SetBessDarkColors();
    static void SetCatpuccinMochaColors();
    static void SetModernDarkColors();
    static void SetDarkThemeColors();
    static void SetFluentUIColors();
private:
    static inline bool m_SavedDefaultColors = false;
    static void SaveDefaultColors();

    static inline ImGuiStyle m_DefaultStyle;
    static inline ImVec4 m_DefaultColors[ImGuiCol_COUNT];
};
