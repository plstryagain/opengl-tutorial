#pragma once

#include <filesystem>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string vertex_source;
    std::string fragment_source;
};

class Shader
{
public:
    Shader(const std::filesystem::path& file_path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(std::string_view name, int32_t v);
    void SetUniform1f(std::string_view name, float v);
    void SetUniform4f(std::string_view name, float v0, float v1, float v2, float v3);

private:
    int32_t GetUniformLocation(std::string_view name);
    uint32_t CreateShader(std::string_view vertex_shader, std::string_view fragment_shader);
    ShaderProgramSource ParseShader(const std::filesystem::path& file_path);
    uint32_t CompileShader(uint32_t type, std::string_view source);

private:
    uint32_t renderer_id_;
    std::filesystem::path file_path_;
    std::unordered_map<std::string_view, int32_t> uniform_location_cache_;
};