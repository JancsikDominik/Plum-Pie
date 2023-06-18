#ifndef PLUM_CAMERA_HPP
#define PLUM_CAMERA_HPP

#include <glm/glm.hpp>

namespace Plum
{
	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3 eyePos, glm::vec3 upVector, float yaw, float pitch, float roll);
		~Camera() = default;

		void Update(float deltaTime);

	private:
		float m_CameraSpeed;

		glm::vec3 m_Position;
		glm::vec3 m_CameraTarget;
		glm::vec3 m_CameraDirection;
		glm::vec3 m_CameraRight;
		glm::vec3 m_CameraUp;

		float yaw, pitch, roll;

		glm::mat4 m_viewMatrix;
	};
}

#endif
