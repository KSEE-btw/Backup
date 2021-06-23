
#include "TestTexture.h"
#include"imgui/imgui.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"


namespace test
{
    TestTexture::TestTexture()
        :m_Pos1(0.0f, 0.0f, 0.0f), m_Pos2(300.0, 100.0f, 0.0f),
        m_CamPos(glm::vec3(0.0f, 100.0f, 0.0f)),
        m_Width(960.0f),
        m_Height(540.0f),
        m_Proj(glm::perspective(glm::radians(100.0f), 16.0f / 9.0f, 0.1f, 1200.0f)),
        m_View (GetViewMatrix()
            /*glm::lookAt(
            glm::vec3(0, 0, 500), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0),// and looks at the origin
            glm::vec3(0,1, -1)  // Head is up (set to 0,-1,0 to look upside-down)*/
        )
    {
        
       
        float position[] = {
          -500.0f, -500.0f, 0.0f, 0.0f,//0
           500.0f, -500.0f, 1.0f, 0.0f,//1
           500.0f,  500.0f, 1.0f, 1.0f,//2
          -500.0f,  500.0f, 0.0f, 1.0f, //3
           700.0f, -900.0f, 0.0f, 0.0f,//4
           900.0f, -900.0f, 1.0f, 0.0f,
           900.0f, -700.0f, 1.0f, 1.1f,
           700.0f, -700.0f, 0.0f, 1.1f
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4
        };
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
        //glBlendEquation();
        m_VAO = std::make_unique<VertexArray>();
        m_Vb = std::make_unique<VertexBuffer>(position, 4 * 8 * sizeof(float));
      
        VertextBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_Vb, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
        m_Shader = std::make_unique<ShaderParser>("res/shaders/Basic.shader");
        m_Shader->Bind();
        
        m_Texture = std::make_unique<Texture>("res/textures/aayush_template.png");
        m_Shader->SetUnifrom1i("u_Texture", 0);
	}
	TestTexture::~TestTexture()
	{
	}
	void TestTexture::OnUpdate(float DeltaTime)
	{
	}
	void TestTexture::OnRender()
	{
        Renderer Renderer;
        m_Texture->Bind();
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        {
            glm::mat4 Model = glm::translate(glm::mat4(1.0f), m_Pos1);
            glm::mat4 mvp = m_Proj * m_View * Model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            Renderer.Draw(*m_Shader, *m_VAO, *m_IndexBuffer);
        }
        /*{
            glm::mat4 Model = glm::translate(glm::mat4(1.0f), m_Pos2);
            glm::mat4 mvp = m_Proj * m_View * Model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            Renderer.Draw(*m_Shader,*m_VAO,*m_IndexBuffer);
        }*/
       
	}
	void TestTexture::OnImGuiRender()
	{
        ImGui::SliderFloat("object A translate x", &m_Pos1.x, -1920.0f, 1920.0f);
        ImGui::SliderFloat("object A translate y", &m_Pos1.y, -1080.0f, 1080.0f);
        ImGui::SliderFloat("object A translate z", &m_Pos1.z, -540.0f, 540.0f);

        //ImGui::SliderFloat3("object B translate", &m_Pos2.x, 0.0f, 960.0f);
	}

}


