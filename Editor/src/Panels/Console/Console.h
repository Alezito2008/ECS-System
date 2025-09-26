#pragma once

#include <string>

enum class LOGTYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

namespace ConsolePanel {
    void Render();
    void AddLog(LOGTYPE type, const std::string& text);
}