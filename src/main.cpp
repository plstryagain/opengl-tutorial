#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

#include <string>

#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <vector>


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

    {
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


        VertexArray va{};
        VertexBuffer vb{positions.data(), positions.size() * sizeof(float)};
        VertexBufferLayout layout{};
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib{indices.data(), indices.size()};
        Shader shader{"res/shaders/basic.shader"};
        shader.Bind();

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        float r = 0.0f;
        float inc = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Bind();
            shader.SetUnifrom4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            va.Bind();
            ib.Bind();

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
    }
    glfwTerminate();
    return 0;
}