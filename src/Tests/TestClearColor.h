#pragma once
#include"Test.h"
#include"imgui/imgui.h"
#include "Renderer.h"
namespace test
{
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();
		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;


	private:
		float m_Color[4] = { 0 };
		
	};

}
