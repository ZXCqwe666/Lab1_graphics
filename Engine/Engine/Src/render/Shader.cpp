#include "Shader.h"

#include "glad/glad.h"
#include "GLErrorHandler.h"

#include<iostream>
#include<fstream>
#include<sstream>

namespace rendering
{
    void Shader::LoadShader(const std::string& filepath)
    {
        filePath = filepath;
        rendererID = 0;

        ShaderProgramSource source = ParseShader(filepath);
        rendererID = CreateShader(source);

        Bind();
    }

    Shader::~Shader()
    {
        GLCall(glDeleteProgram(rendererID));
    }

    ShaderProgramSource Shader::ParseShader(const std::string& filepath)
    {
        ShaderType type = ShaderType::NONE;

        std::ifstream stream(filepath);
        std::stringstream ss[2];
        std::string line;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos) type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos) type = ShaderType::FRAGMENT;
            }
            else ss[(int)type] << line << '\n';
        }

        return { ss[0].str(), ss[1].str() };
    }

    unsigned int Shader::CreateShader(const ShaderProgramSource& source)
    {
        GLCall(unsigned int program = glCreateProgram());
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.vertexSource);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.fragmentSource);

        GLCall(glAttachShader(program, vs));
        GLCall(glAttachShader(program, fs));

        GLCall(glLinkProgram(program));
        GLCall(glValidateProgram(program));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return program;
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        GLCall(unsigned int id = glCreateShader(type));
        const char* src = source.c_str();

        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

        if (result == GL_FALSE)
        {
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

            char* message = (char*)alloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(id, length, &length, message));

            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << message << std::endl;
            return 0;
        }

        return id;
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(rendererID));
    }

    void Shader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    int Shader::GetUniformLocation(const std::string& name) const
    {
        if(uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

        int location = glGetUniformLocation(rendererID, name.c_str());

        if(location == -1) std::cout << "Warning: uniform " << name << " doesnt exist!" << std::endl;
        else uniformLocationCache[name] = location;

        return location;
    }

    void Shader::Set_Mat4_Float(const std::string& name, const glm::mat4& matrix)
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }
}
