#include "SphereComponent.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"

namespace Planets {

    SphereComponent::SphereComponent()
    {
        Texture texture;
        const int latitudeCount = 100;
        const int longitudeCount = 100;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texCoords;

        const float PI = 3.1415926535f;
        float r = 1.5f;
        for (int lat = 0; lat <= latitudeCount; ++lat) {
            
            float theta = lat * PI / latitudeCount;
            
            for (int lon = 0; lon <= longitudeCount; ++lon) {
                
                float phi = lon * 2 * PI / longitudeCount;
                float x = r * sin(theta) * cos(phi);
                float y = r * cos(theta);
                float z = r * sin(theta) * sin(phi);

                vertices.push_back(glm::vec3(x, y, z));
                
                float s = 1.0f - float(lon) / longitudeCount;
                float t = 1.0f - float(lat) / latitudeCount;
                
                texCoords.push_back(glm::vec2(s, t));
            }
        }

        for (int lat = 0; lat < latitudeCount; ++lat) {
            
            for (int lon = 0; lon < longitudeCount; ++lon) {
            
                int first = (lat * (longitudeCount + 1)) + lon;
                int second = first + longitudeCount + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        GLuint VBO, EBO, VBO_TEX;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &VBO_TEX);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size()*sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(std::uint32_t), indices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST);

        texture.Init("../Engine/src/assets/8k_earth_daymap.jpg"); 
    }

    SphereComponent::~SphereComponent() {}

    void SphereComponent::update() {}
    
    std::uint32_t SphereComponent::getVAO() const
    {
        return VAO;
    }

    std::vector<std::uint32_t>& SphereComponent::getIndices()
    {
        return indices;
    }

}
