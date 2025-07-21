#pragma once

#include <cstdint>

#include <vector>

namespace Planets {

    class Texture
    {
    public:
        Texture(const char* path);
        Texture(const char* path1, const char* path2);
        ~Texture() = default;
        void bindTexture(std::uint32_t);
        std::vector<std::uint32_t> getID() const;
    private:
        std::vector<std::uint32_t> textureID;
    };

}
