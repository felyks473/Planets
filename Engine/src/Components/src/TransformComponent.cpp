#include "TransformComponent.h"

#include <glm/glm.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Planets {

    TransformComponent::TransformComponent()
    : earthPosition(glm::vec3(0.0f, 0.0f, 0.0f)), moonPosition(glm::vec3(0.0f, 0.0f, 0.0f)), angleDegree(23.5f)
    {
        earth_timer.start();
        moon_timer.start();
        sun_timer.start();
        earthOrbitSpeed = 360.0f / (365.25f * 24.0f * 60.0f * 60.0f); // 365.25 days is  earth's orbital period 
        
        /* 1e7f is a scale factor */
        distanceFromEarthX = 149.6e6f / 1e7f;
        distanceFromEarthZ = 149.2e6f / 1e7f;
        distanceFromMoon = 0.384f * 10.0f;
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

        float time_earth = earth_timer.getTime();
        float time_moon = moon_timer.getTime();
        float time_sun = sun_timer.getTime();

        float earthSpinningSpeed = 360.0f / (days * 24.0f * 60.0f * 60.0f) * time_earth * 1e4f;
        float moonSpinningSpeed = 360.0f / (27.321661f * 24.0f * 60.0f * 60.0f) * 1e4f; //27.321661 days
    
        float sunSpinningSpeed = 360.0f / (25.0f * 24.0f * 60.0f * 60.0f) * time_sun * 1e4f; // approx. 25 days

        static float earthManualSlider = 0.0f;
        static float moonManualSlider = 0.0f;
        static float moonDistanceManualSlider = 0.0f;
        static float earthDistanceManualSlider = 0.0f;
        
        static bool lastStop = false;
        static bool moonLastStop = false;
        static float lastSet = distanceFromMoon;
        static float earthLastSet = distanceFromEarthX;
        static glm::vec3 localEarthPosition;

        if (shader_flag == 0) // Earth
        {
            tilt = glm::rotate(tilt, glm::radians(23.5f), glm::vec3(1.0f, 0.0f, 0.0f));

            if (*stop[0])
            {
                earth_timer.pause();

                if (ImGui::SliderFloat("Earth orbit", &earthManualSlider, 0.0f, 5.51f))
                {
                    *slider_value[0] = earthManualSlider;
                    earth_timer.setTime(earthManualSlider);
                }

                if (ImGui::SliderFloat("Earth distance (from Sun)", &earthDistanceManualSlider, 0.0f, 100.0f))
                {
                    *slider_value[2] = earthDistanceManualSlider;
                    earthLastSet = *slider_value[2];
                }
                earthPosition.x = *slider_value[2] * cos(*slider_value[0] * 1e5f * earthOrbitSpeed);
                earthPosition.z = (*slider_value[2] - 0.4e6f / 1e7f) * sin(*slider_value[0] * 1e5f * earthOrbitSpeed);
            
                localEarthPosition = earthPosition;
            }
            else 
            {
                if (lastStop)
                {
                    earth_timer.resume();
                }

                float time_earth = earth_timer.getTime();
                *slider_value[0] = time_earth;
                distanceFromEarthX = earthLastSet;
                distanceFromEarthZ = earthLastSet - 0.4e6f / 1e7f;

                earthPosition.z = distanceFromEarthZ * sin(earthOrbitSpeed * 1e5f * time_earth);
                earthPosition.x = distanceFromEarthX * cos(earthOrbitSpeed * 1e5f * time_earth);
                
                localEarthPosition = earthPosition;
            }
            lastStop = *stop[0];

            model = glm::translate(model, earthPosition);

            model = model * tilt;

            model = glm::rotate(model, glm::radians(earthSpinningSpeed), earthAxis);

        }
        if (shader_flag == 1) // Sun
        {
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
            tilt = glm::rotate(tilt, glm::radians(7.25f), glm::vec3(1.0f, 0.0f, 0.0f));

            if (*stop[0])
            {
                sun_timer.pause();
            }
            else 
            {
                sun_timer.resume();
            }
        
            model = glm::rotate(model, glm::radians(sunSpinningSpeed), sunAxis);

            model = model * tilt;
        }
        if (shader_flag == 2) // Moon
        {   
            if (*stop[0])
            {
                moon_timer.pause();
                /* Without this there's the sudden movement towards Earth followed by the sudden stop */
                static bool firstTime = true;
                if (firstTime)
                {
                    *slider_value[3] = 3.84f; // Distance between Earth and Moon
                    firstTime = false; // Do that only the first time
                }

                if (ImGui::SliderFloat("Moon orbit", &moonManualSlider, 0.0f, 4.12f))
                {
                    *slider_value[1] = moonManualSlider;
                    moon_timer.setTime(moonManualSlider);
                }
                
                if (ImGui::SliderFloat("Moon distance (from Earth)", &moonDistanceManualSlider, 0.0f, 100.0f))
                {
                    *slider_value[3] = moonDistanceManualSlider;
                    lastSet = *slider_value[3];
                }
                
                moonPosition.x = localEarthPosition.x + *slider_value[3] * cos(*slider_value[1] * moonSpinningSpeed);
                moonPosition.z = localEarthPosition.z + *slider_value[3] * sin(*slider_value[1] * moonSpinningSpeed);
            }
            else 
            {
                moon_timer.resume();

                if (moonLastStop)
                {
                    moon_timer.resume();
                }

                float time_moon = moon_timer.getTime();
                *slider_value[1] = time_moon;
                distanceFromMoon = lastSet;
                                
                moonPosition.x = localEarthPosition.x + distanceFromMoon * cos(moonSpinningSpeed * time_moon);
                moonPosition.z = localEarthPosition.z + distanceFromMoon * sin(moonSpinningSpeed * time_moon);
            }
            moonLastStop = *stop[0];

            model = glm::translate(model, moonPosition);
            model = glm::rotate(model, glm::radians(5.14f), glm::vec3(1.0f, 0.0f, 0.0f));
            
            model = glm::rotate(model, glm::radians(moonSpinningSpeed * time_moon), moonAxis);

            model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
        }
        if (shader_flag == 3) // Stars
        {
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        }
        view = camera.GetViewMatrix();
        
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0f);

        glm::mat4 mvp = projection * view * model;

        shader->setMat4("mvp", mvp);
    }

}
