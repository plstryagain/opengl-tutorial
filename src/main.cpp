#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>

#ifdef _MSC_VER
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#define ASSERT(x) if (!(x)) __builtin_trap();
#endif

#define GLCall(x) gl_clear_error();\
    x;\
    ASSERT(gl_log_call(#x, __FILE__, __LINE__))

struct ShaderProgramSource
{
    std::string vertex_source;
    std::string fragment_source;
};

static void gl_clear_error()
{
    while (glGetError() != GL_NO_ERROR){

    }
}

static bool gl_log_call(std::string_view function, std::string_view file, int32_t line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL error] (" << error << "): " << function <<
        " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}

static ShaderProgramSource parse_shader(const std::filesystem::path& file_path)
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

static uint32_t compile_shader(uint32_t type, std::string_view source)
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

static uint32_t create_shader(std::string_view vertex_shader, std::string_view fragment_shader)
{
    uint32_t program = glCreateProgram();
    uint32_t vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    uint32_t fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    std::array<float, 8> positions{
        -0.5f, -0.5f, // 0
        0.5f, -0.5f,  // 1
        0.5f, 0.5f,   // 2
        -0.5f, 0.5f,  // 3 
    };

    std::array<uint32_t, 6> indices = {
        0, 1, 2, 
        2, 3, 0
    };

    uint32_t vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    uint32_t buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    uint32_t ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    auto source = parse_shader("res/shaders/basic.shader");
      
    uint32_t shader = create_shader(source.vertex_source, source.fragment_source);
    glUseProgram(shader);

    int32_t location = glGetUniformLocation(shader, "u_Color");
    ASSERT(location != -1)

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    float r = 0.0f;
    float inc = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f) {
            inc = -0.05f;
        } else if (r < 0.0f) {
            inc = 0.05f;
        }
        r += inc;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}