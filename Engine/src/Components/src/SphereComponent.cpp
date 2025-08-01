#include "SphereComponent.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Planets {

    SphereComponent::SphereComponent(float r)
    {
        constexpr int latitudeCount = 100;
        constexpr int longitudeCount = 100;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;

        constexpr float PI = 3.1415926535f;
        for (int lat = 0; lat <= latitudeCount; ++lat) {
            
            float theta = lat * PI / latitudeCount;
            
            for (int lon = 0; lon <= longitudeCount; ++lon) {
                
                float phi = lon * 2 * PI / longitudeCount;
                float x = r * sin(theta) * cos(phi);
                float y = r * cos(theta);
                float z = r * sin(theta) * sin(phi);

                vertices.push_back(glm::vec3(x, y, z));

                float n_x = x / r;
                float n_y = y / r;
                float n_z = z / r;

                normals.push_back(glm::vec3(n_x, n_y, n_z));
                
                float s = 1.0f - static_cast<float>(lon) / longitudeCount;
                float t = 1.0f - static_cast<float>(lat) / latitudeCount;
                
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_TEX);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(0));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        glEnable(GL_DEPTH_TEST); 
    }

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
