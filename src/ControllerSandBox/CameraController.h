#pragma once
#include"ControllerSandBox.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
namespace cont
{
	class CameraController : ControllerSandBox
	{
	public:
		CameraController();
		~CameraController();
		glm::mat4 GetViewMatrix();
		MouseAxis GetMouseAxis() override;
		void RotateRight();
		void RotateLeft();
		void RotateDown();
		void RotateUp();
		void KeyPressEvent(GLenum key) override;
	private:
		cont::ControllerSandBox* Controller;
		float horizontalAngle = 3.14f;
		float verticalAngle = 0.0f;
		float m_CursorSpeed = 0.005f;
		float m_Speed = 3.0f;
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 500.0f)
			, m_Direction = glm::vec3(0.0f, 0.0f, 0.0f),
			m_Up = glm::vec3(0.0f, 0.0f, 0.0f),
			m_Right = glm::vec3(0.0f, 0.0f, 0.0f);
			
	};
}