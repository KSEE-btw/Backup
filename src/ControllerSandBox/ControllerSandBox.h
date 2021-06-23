#pragma once
#include"GLFW/glfw3.h"
#include<vector>
#include<unordered_map>
#include<functional>
namespace cont
{
	
	struct MouseAxis
	{
		double Xaxis;
		double Yaxis;
	};
	class ControllerSandBox
	{
	public:
		
		std::unordered_map<GLenum,void(*)()> KeyBindings;
		ControllerSandBox();
		~ControllerSandBox();
		bool GetKeyPress(GLenum Key);
		bool GetMouseKeyPress(unsigned int Key);
		virtual MouseAxis GetMouseAxis()
		{
				glfwGetCursorPos(m_Window, &m_Maxis.Xaxis, &m_Maxis.Yaxis);
				return m_Maxis;	
		}
		void JoypadBindings() {};

		virtual void KeyPressEvent(GLenum Key) {}
		
	private:
		static MouseAxis m_Maxis;
		static GLFWwindow* m_Window;
	};

	GLFWwindow* ControllerSandBox::m_Window = glfwGetCurrentContext();
	ControllerSandBox::~ControllerSandBox()
	{
	}
	inline bool ControllerSandBox::GetKeyPress(unsigned int Key)
	{
		int state = glfwGetKey(m_Window, Key);
		return state == GLFW_PRESS;
	}

	inline bool ControllerSandBox::GetMouseKeyPress(unsigned int Key)
	{
		int state = glfwGetKey(m_Window,Key);
		return state == GLFW_PRESS;
	}
	class Event : public ControllerSandBox
	{
	public:
		template<typename TMyclass >
		inline void RegisterKey(GLenum Key, void(TMyclass::*f)())
		{
			KeyBindings[Key] = f;
		}
		// Inherited via ControllerSandBox
	};
}