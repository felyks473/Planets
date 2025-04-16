#pragma once

#include <cstdint>

namespace Planets {

    class Shader
    {
    public:
        Shader();
        ~Shader();
        
        void Use();
        void Init(const char* vertexPath, const char* fragmentPath);

    private:
        std::uint32_t shaderID;
    };

}
