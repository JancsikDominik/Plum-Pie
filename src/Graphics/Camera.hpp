#ifndef PLUM_CAMERA_HPP
#define PLUM_CAMERA_HPP

#include <glm/glm.hpp>

namespace Plum
{
	class Camera
	{
	public:
		Camera(float screenWidth, float screenHeight);

		void SetPosition(const glm::vec3& newPosition);
		const glm::vec3& GetPosition() const;

		void SetTarget(const glm::vec3& newTarget);
		const glm::vec3& GetTarget() const;

		void SetFOV(float newFOV);
		float GetFOV() const;

		void UpdateAspectRatio(float screenWidth, float screenHeight);

		const glm::mat4& GetViewProjection() const;
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;

		void Update();

		// TODO: base class for these events
		// TODO: OnKeyEvent, OnMouseEvent, OnResize

	protected:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

		float m_cameraSpeed{};

		glm::vec3 m_position;
		glm::vec3 m_cameraTarget;
		glm::vec3 m_up;

		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;

		glm::mat4 m_viewMatrix{1};
		glm::mat4 m_projMatrix{1};
		glm::mat4 m_viewProj{1};

		bool m_dirty = true;
	};
}

#endif
