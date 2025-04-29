#pragma once

#include <cstdint>

namespace Planets {

    class Texture
    {
    public:
        Texture();
        ~Texture();
        void Init(const char* path);
    private:
        std::uint32_t textureID;
    };

}
