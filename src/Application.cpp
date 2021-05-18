#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ShaderParser.h"
#include"VertetxBufferLayout.h"
#include"Texture.h"
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(888, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(4);
    if (glewInit() != GLEW_OK)
        std::cout << "error" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float position[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,//0
             0.5f, -0.5f, 1.0f, 0.0f,//1
             0.5f,  0.5f, 1.0f, 1.0f,//2
            -0.5f,  0.5f, 0.0f, 1.0f //3
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
       
        VertexArray vao;
        VertexBuffer vb(position, 4 * 4 * sizeof(float));//VertextBuffer generation
        VertextBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        vao.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6); //IndexBuffer generation
        ShaderParser shader("res/shaders/Basic.shader");
        shader.Bind();
        vb.Bind();
        Texture texture("res/textures/aayush_template.png");
        texture.Bind();
        shader.SetUnifrom1i("u_Texture", 0);
        float red = 0.5f;
        float increment = 0.5f;
        Renderer renderer;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            
            renderer.Clear();
            //glClearError();
            
            renderer.Draw(shader, vao, ib);
            shader.SetUnifrom4f("u_Color", red, 0.0f, 1.0f, 0.8f);
           

            
            /* Swap front and back buffers */
            if (red < 0.0f)
            {
                increment = 0.5f;
            }
            if ((red > 1.0f))
                increment = -0.5f;
            red += increment;
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        shader.Unbind();
    }
    glfwTerminate();
    return 0;
}