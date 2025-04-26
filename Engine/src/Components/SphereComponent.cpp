#include "SphereComponent.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Planets {

    SphereComponent::SphereComponent()
    {
        const int latitudeCount = 20;
        const int longitudeCount = 20;

        std::vector<glm::vec3> vertices;

        float r = 1.0f;
        for (int lat = 0; lat <= latitudeCount; ++lat) {
            
            float theta = lat * M_PI / latitudeCount;
            
            for (int lon = 0; lon <= longitudeCount; ++lon) {
                
                float phi = lon * 2 * M_PI / longitudeCount;
                float x = r * sin(theta) * cos(phi);
                float y = r * cos(theta);
                float z = r * sin(theta) * sin(phi);
            
                vertices.push_back(glm::vec3(x, y, z));
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

        GLuint VBO, EBO;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(std::uint32_t), indices.data(), GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glEnable(GL_DEPTH_TEST);
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
