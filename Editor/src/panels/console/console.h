#include <string>

enum class LOGTYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

namespace Console {
    void Render();
    void AddLog(LOGTYPE type, const std::string& text);
}