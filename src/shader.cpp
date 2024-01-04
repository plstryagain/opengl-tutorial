#include "shader.h"
#include "renderer.h"

#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>


Shader::Shader(const std::filesystem::path& file_path)
    : file_path_(file_path), renderer_id_(0)
{
    auto source = ParseShader(file_path);
    renderer_id_ = CreateShader(source.vertex_source, source.fragment_source);
}

Shader::~Shader()
{
    glDeleteProgram(renderer_id_);
}

void Shader::Bind() const
{
    glUseProgram(renderer_id_);
}
void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUnifrom1f(std::string_view name, float v)
{
    glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetUnifrom4f(std::string_view name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int32_t Shader::GetUniformLocation(std::string_view name)
{
    if (uniform_location_cache_.find(name) != uniform_location_cache_.end()) {
        return uniform_location_cache_[name];
    }
    int32_t location = glGetUniformLocation(renderer_id_, name.data());
    uniform_location_cache_[name] = location;
    return location;
}

uint32_t Shader::CompileShader(uint32_t type, std::string_view source)
{
    uint32_t id = glCreateShader(type);
    const char* src = source.data();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    // TODO: Error handling
    int32_t result = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == 0) {
        int32_t length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> message(length);
        glGetShaderInfoLog(id, length, &length, message.data());
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
                    << " shader" << std::endl;
        std::cout << message.data() << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

uint32_t Shader::CreateShader(std::string_view vertex_shader, std::string_view fragment_shader)
{
    uint32_t program = glCreateProgram();
    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShaderProgramSource Shader::ParseShader(const std::filesystem::path& file_path)
{
    std::ifstream stream{file_path};
    if (!stream.is_open()) {
        std::cout << "File not open!" << std::endl;
        return {};
    }

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }
    return { 
        ss[static_cast<int>(ShaderType::VERTEX)].str(), 
        ss[static_cast<int>(ShaderType::FRAGMENT)].str() 
    };
}

