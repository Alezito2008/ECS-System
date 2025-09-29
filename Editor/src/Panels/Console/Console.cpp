#include "Console.h"
#include "IconFont/IconsFontAwesome7.h"

#include "imgui.h"

#include <ctime>

static char inputBuffer[512];
static ImGuiTextBuffer logBuffer;
static ImGuiTextFilter filter;
static bool autoScroll = true;
static bool scrollToBottom = false;

static std::string LogTypeToString(LOGTYPE type) {
    switch (type) {
        case LOGTYPE::DEBUG:    return "DEBUG";
        case LOGTYPE::INFO:     return "INFO";
        case LOGTYPE::WARNING:  return "WARNING";
        case LOGTYPE::ERROR:    return "ERROR";
    }
    return "NULL";
}

static std::string GetCurrentTimeString() {
    std::time_t now = std::time(nullptr);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", std::localtime(&now));
    return std::string(buffer);
}

void ConsolePanel::AddLog(LOGTYPE type, const std::string& text) {
    logBuffer.appendf("[%s] [%s] %s\n", GetCurrentTimeString().c_str(), LogTypeToString(type).c_str(), text.c_str());
    scrollToBottom = autoScroll;
}

void ConsolePanel::Render() {
    using namespace ImGui;
    Begin(ICON_FA_TERMINAL " Console ###Console");

    if (BeginTable("ConsoleTable", 2, ImGuiTableFlags_SizingStretchProp)) {
        TableNextColumn();

        if (BeginPopup("Console Options")) {
            Checkbox( "AutoScroll", &autoScroll);
            EndPopup();
        }

        SetNextItemWidth(GetContentRegionAvail().x);
        filter.Draw("##filter");
        
        TableNextColumn();
        if (Button( ICON_FA_BROOM " Clear")) {
            logBuffer.clear();
        };
        if (IsItemHovered()) {
            SetTooltip("Clear all logs");
        };
        SameLine();
        if (Button( ICON_FA_COPY " Copy")) {
            LogToClipboard();
            TextUnformatted(logBuffer.begin(),logBuffer.end());
            LogFinish();
        };
        if (IsItemHovered()) {
            SetTooltip("Copy all logs");
        };
        SameLine();
        if (Button(ICON_FA_GEAR " Options")) {
            OpenPopup("Console Options");
        };
        if (IsItemHovered()) {
            SetTooltip("Display options");
        };
        EndTable();
    }

    BeginChild("LogRegion", ImVec2(0,0), true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
    const char* text = logBuffer.begin();
    const char* line_start = text;

    for (const char* p = text; *p; p++) {
        if (*p == '\n') {
            std::string line(line_start, p - line_start);
            if (filter.PassFilter(line.c_str())) {
                TextUnformatted(line.c_str());
            }
            line_start = p + 1;
        }
    }

    if (scrollToBottom) {
        SetScrollHereY(1.0f);
        scrollToBottom = false;
    }

    EndChild();

    End();
}