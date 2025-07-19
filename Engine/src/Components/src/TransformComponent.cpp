#include "TransformComponent.h"

#include <glm/glm.hpp>

namespace Planets {

    TransformComponent::TransformComponent()
    : earthPosition(glm::vec3(0.0f, 0.0f, 0.0f)), moonPosition(glm::vec3(0.0f, 0.0f, 0.0f)), angleDegree(23.5f)
    {
        earthOrbitSpeed = 360.0f / (365.25f * 24.0f * 60.0f * 60.0f); // 365.25 days is  earth's orbital period 
        
        /* 1e7f is a scale factor */
        distanceFromEarthX = 149.6e6f / 1e7f;
        distanceFromEarthZ = 149.2e6f / 1e7f;
        distanceFromMoonX = 0.384f * 10.f;
        distanceFromMoonZ = 0.384f * 10.f;
        angleRadians = glm::radians(angleDegree);
        

        /*               Earth's rotation period - 23h 56m 4s         */
        /*               We get this number by doing this:            */
        /* 23 / 24 [h] + 56 / (24 * 60) [m] + 4 / (24 * 60 * 60) [s]  */
        
        days = (0.95833f + 0.03889f + 0.00004629f);

        earthAxis = glm::normalize(glm::vec3(sin(angleRadians), cos(angleRadians), 0.0f));
        sunAxis = glm::normalize(glm::vec3(sin(glm::radians(7.25f)), cos(glm::radians(7.25f)), 0.0f));
        moonAxis = glm::normalize(glm::vec3(sin(glm::radians(5.14f)), cos(glm::radians(5.14f)), 0.0f));
    }

    void TransformComponent::Update(int windowWidth, int windowHeight, std::shared_ptr<Shader> shader, int shader_flag, CameraSystem &camera, std::vector<bool*>& stop, std::vector<float*>& slider_value)
    {
        shader->Use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 tilt = glm::mat4(1.0f);

        /* I believe that for the true tidal lock of a moon the scale factor below has to be the same as the scale factor of the distance from earth */
        /* That's either going to make the moon's distance too large or make the spinning of the moon too slow                                       */
        /* At one point I'll try to get them in sync but for now let them be slightly inaccurate                                                     */

        float time = glfwGetTime();
        float earthSpinningSpeed = 360.0f / (days * 24.0f * 60.0f * 60.0f) * static_cast<float>(time) * 1e4f;
        float moonSpinningSpeed = 360.0f / (27.321661f * 24.0f * 60.0f * 60.0f) * static_cast<float>(time) * 1e4f; //27.321661 days
    
        float sunSpinningSpeed = 360.0f / (25.0f * 24.0f * 60.0f * 60.0f) * static_cast<float>(time) * 1e4f; // approx. 25 days

        if (shader_flag == 0) // Earth
        {
            tilt = glm::rotate(tilt, glm::radians(23.5f), glm::vec3(1.0f, 0.0f, 0.0f));
            
            /* 1e5f is a scale factor */
            earthPosition.x = distanceFromEarthX * cos(earthOrbitSpeed * 1e5f * glfwGetTime());
            earthPosition.z = distanceFromEarthZ * sin(earthOrbitSpeed * 1e5f * glfwGetTime());
            
            if (*stop[0])
            {
                earthPosition.x = *slider_value[2] * cos(*slider_value[0] * 1e5f * earthOrbitSpeed);
                earthPosition.z = (*slider_value[2] - 0.4e6f / 1e7f) * sin(*slider_value[0] * 1e5f * earthOrbitSpeed);
            }

            model = glm::translate(model, earthPosition);

            model = model * tilt;

            if (*stop[0])
                model = glm::rotate(model, glm::radians(earthSpinningSpeed / time), earthAxis);
            else 
                model = glm::rotate(model, glm::radians(earthSpinningSpeed), earthAxis);

        }
        if (shader_flag == 1) // Sun
        {
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
            tilt = glm::rotate(tilt, glm::radians(7.25f), glm::vec3(1.0f, 0.0f, 0.0f));
        
            model = glm::rotate(model, glm::radians(sunSpinningSpeed), sunAxis);
            
            model = model * tilt;
        }
        if (shader_flag == 2) // Moon
        {
            glm::mat4 moon_model = glm::mat4(1.0f);
            glm::mat4 earth_model = glm::mat4(1.0f);
            
            /* 1e5f is a scale factor */
            earthPosition.x = distanceFromEarthX * cos(earthOrbitSpeed * 1e5f * glfwGetTime());
            earthPosition.z = distanceFromEarthZ * sin(earthOrbitSpeed * 1e5f * glfwGetTime());

            moonPosition.x = distanceFromMoonX * cos(moonSpinningSpeed);
            moonPosition.z = distanceFromMoonZ * sin(moonSpinningSpeed);

            if (*stop[0])
            {
                earthPosition.x = *slider_value[2] * cos(*slider_value[0] * 1e5f * earthOrbitSpeed);
                earthPosition.z = (*slider_value[2] - 0.4e6f / 1e7f) * sin(*slider_value[0] * 1e5f * earthOrbitSpeed);
                
                moonPosition.x = *slider_value[3] * cos(*slider_value[1] * 1e4f * 360.0f / (27.321661f * 24.0f * 60.0f * 60.0f));
                moonPosition.z = *slider_value[3] * sin(*slider_value[1] * 1e4f * 360.0f / (27.321661f * 24.0f * 60.0f * 60.0f));    
            }

            earth_model = glm::translate(earth_model, earthPosition);         

            moon_model = glm::translate(moon_model, moonPosition);
            moon_model = glm::rotate(moon_model, glm::radians(5.14f), glm::vec3(1.0f, 0.0f, 0.0f));
            
            if (*stop[0])
                moon_model = glm::rotate(moon_model, glm::radians(moonSpinningSpeed / time), moonAxis);
            else 
                moon_model = glm::rotate(moon_model, glm::radians(moonSpinningSpeed), moonAxis);

            moon_model = glm::scale(moon_model, glm::vec3(0.25f, 0.25f, 0.25f));

            model = earth_model * moon_model;
        }
        if (shader_flag == 3)
        {
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
        }
        view = camera.GetViewMatrix();
        
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0f);

        glm::mat4 mvp = projection * view * model;

        shader->setMat4("mvp", mvp);
    }

}
