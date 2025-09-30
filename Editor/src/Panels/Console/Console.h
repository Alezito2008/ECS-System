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
    void AddLog(const std::string& text, LOGTYPE type = LOGTYPE::INFO);
}