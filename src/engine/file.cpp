#include "engine/file.hpp"

std::string readFile(const char* filePath) {
    std::string code;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << filePath << std::endl;
        return code;
    }

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    code = stream.str();

    return code;
}