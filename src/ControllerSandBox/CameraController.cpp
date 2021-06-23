#include "CameraController.h"
namespace cont
{
	CameraController::CameraController()
	{
	}

	glm::mat4 CameraController::GetViewMatrix()
	{

		horizontalAngle += m_Speed * float(1920 / 2 - GetMouseAxis().Xaxis);
		verticalAngle += m_Speed * float(1080 / 2 - GetMouseAxis().Yaxis);
		return glm::mat4();
		m_Direction = glm::vec3(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * sin(horizontalAngle)
		);
		m_Right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);
		m_Up = glm::cross(m_Right,m_Direction);
		Event event_;
		event_.RegisterKey<CameraController>(GLFW_KEY_UP, &CameraController::RotateUp);
		event_.RegisterKey<CameraController>(GLFW_KEY_DOWN, &CameraController::RotateDown);
		event_.RegisterKey<CameraController>(GLFW_KEY_LEFT, &CameraController::RotateLeft);
		event_.RegisterKey<CameraController>(GLFW_KEY_RIGHT, &CameraController::RotateRight);
		if (GetKeyPress(GLFW_KEY_UP))
		{
			KeyPressEvent(GLFW_KEY_UP);
		}
		if (GLFW_KEY_DOWN)
		{
			KeyPressEvent(GLFW_KEY_DOWN);
		}
		if (GLFW_KEY_LEFT)
		{
			KeyPressEvent(GLFW_KEY_LEFT);
		}
		if(GLFW_KEY_RIGHT)
		{
			KeyPressEvent(GLFW_KEY_RIGHT);
		}
		return glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
	}

	MouseAxis CameraController::GetMouseAxis()
	{
		return __super::GetMouseAxis();	
	}

	void CameraController::RotateRight()
	{
		m_Position += m_Right* m_Speed;
	}

	void CameraController::RotateLeft()
	{
		m_Position -= m_Right * m_Speed;
	}

	void CameraController::RotateUp()
	{
		m_Position += m_Direction * m_Speed;
	}

	void CameraController::KeyPressEvent(GLenum key)
	{
		KeyBindings[key]();
	}

	void CameraController::RotateDown()
	{
		m_Position -= m_Direction * m_Speed;
	}
	
	

}
