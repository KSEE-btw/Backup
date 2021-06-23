#pragma once
#include"Test.h"
#include"imgui/imgui.h"
#include"Renderer.h"
#include"VertetxBufferLayout.h"
#include"Texture.h"
#include"memory"
#include"ControllerSandBox/CameraController.h"
namespace test
{
	class TestTexture :public Test,public cont::CameraController
	{
	public:
		TestTexture();
		~TestTexture();
		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;


	private:
		Renderer m_Renderer;
		std::unique_ptr<ShaderParser> m_Shader;
		std::unique_ptr<IndexBuffer>m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_Vb;
		std::unique_ptr<Texture> m_Texture;
		glm::mat4 m_Proj, m_View;
		float m_Height, m_Width;
		glm::vec3 m_Pos1, m_Pos2,m_CamPos;
		
	};

}
