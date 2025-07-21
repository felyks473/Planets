#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <string>

namespace Planets {

    class Shader
    {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader() = default;
        
        void Use();
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void setInt(const std::string &name, int n) const;
        void cleanup();
        
    private:
        std::uint32_t shaderID;
    };

}
