#pragma once

#include <cstdint>

namespace Planets {

    class Texture
    {
    public:
        Texture(const char* path);
        ~Texture() = default;
    private:
        std::uint32_t textureID;
    };

}
