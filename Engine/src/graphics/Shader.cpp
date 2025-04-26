#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"
#include <fstream>
#include <sstream>

namespace Planets {

    Shader::Shader() { }
    
    Shader::~Shader()
    {
        glDeleteProgram(shaderID);
    }

    void Shader::Use()
    {
        glUseProgram(shaderID);
    }

    void Shader::Init(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode, fragmentCode;
        std::ifstream vertexShaderFile, fragmentShaderFile;

        vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vertexShaderFile.open(vertexPath);
            fragmentShaderFile.open(fragmentPath);
            std::stringstream vertexShaderStream, fragmentShaderStream;

            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();

            vertexCode = vertexShaderStream.str();
            fragmentCode = fragmentShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            EH_CORE_ERROR("SHADER::FILE_NOT_SUCCESSFULLY_READ\n {0}", e.what());
        }

        EH_CORE_INFO("SHADER::FILE_SUCCESSFULLY_READ\n");

        const char* vertexShaderCode = vertexCode.c_str();
        const char* fragmentShaderCode = fragmentCode.c_str();

        std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);

        glCompileShader(vertexShader);
        
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            EH_CORE_ERROR("VERTEX::SHADER::COMPILATION_FAILED\n {0}", infoLog);
        }
        
        EH_CORE_INFO("VERTEX::SHADER::COMPILATION_SUCCESSFULL\n");

        glCompileShader(fragmentShader);
        
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            EH_CORE_ERROR("FRAGMENT::SHADER::COMPILATION_FAILED\n {0}", infoLog);
        }

        EH_CORE_INFO("FRAGMENT::SHADER::COMPILATION_SUCCESSFULL\n");

        shaderID = glCreateProgram();
        glAttachShader(shaderID, vertexShader);
        glAttachShader(shaderID, fragmentShader);
        glLinkProgram(shaderID);

        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
            EH_CORE_ERROR("SHADER::PROGRAM::LINKING_FAILED\n {0}", infoLog);
        }

        EH_CORE_INFO("SHADER::PROGRAM::LINKING_SUCCESSFULL\n");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
    }
    
    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}
