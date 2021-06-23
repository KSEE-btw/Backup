#include "TestClearColor.h"
namespace test
{
	TestClearColor::TestClearColor()
	{
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float DeltaTime)
	{
	}

	void TestClearColor::OnRender()
	{

	}
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("clear color", m_Color);
		GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
	}
}


