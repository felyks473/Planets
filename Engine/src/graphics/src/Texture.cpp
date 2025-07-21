#include "Texture.h"
#include "Log.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Planets {

    Texture::Texture(const char* path)
    {
        textureID.push_back(1);
        glGenTextures(1, &textureID[0]);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width;
        int height;
        int nrChannels;

        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            EH_CORE_INFO("Texture loaded successfully\n");
        }
        else 
        {
            EH_CORE_ERROR("Failed to load the texture\n");
        }
        
        stbi_image_free(data);
    }

   Texture::Texture(const char* path1, const char* path2)
    {
        textureID.push_back(1);
        textureID.push_back(2);

        glGenTextures(1, &textureID[0]);
        glBindTexture(GL_TEXTURE_2D, textureID[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width1;
        int height1;
        int nrChannels1;

        stbi_set_flip_vertically_on_load(true);
        unsigned char *data1 = stbi_load(path1, &width1, &height1, &nrChannels1, 0);
        if (data1)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
            glGenerateMipmap(GL_TEXTURE_2D);
            EH_CORE_INFO("Texture loaded successfully\n");
        }
        else 
        {
            EH_CORE_ERROR("Failed to load the texture\n");
        }
        
        stbi_image_free(data1);

        glGenTextures(1, &textureID[1]);
        glBindTexture(GL_TEXTURE_2D, textureID[1]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width2;
        int height2;
        int nrChannels2;

        stbi_set_flip_vertically_on_load(true);
        unsigned char *data2 = stbi_load(path2, &width2, &height2, &nrChannels2, 0);
        if (data2)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
            glGenerateMipmap(GL_TEXTURE_2D);
            EH_CORE_INFO("Texture loaded successfully\n");
        }
        else 
        {
            EH_CORE_ERROR("Failed to load the texture\n");
        }
        
        stbi_image_free(data1);   
    }

    void Texture::bindTexture(std::uint32_t id)
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    std::vector<std::uint32_t> Texture::getID() const
    {
        return textureID;
    }
}
