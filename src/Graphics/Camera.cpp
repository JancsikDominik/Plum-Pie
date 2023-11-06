#include "Camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Plum
{
	Camera::Camera(float screenWidth, float screenHeight) :
		m_position(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_cameraTarget(glm::vec3(0.0f, 0.0f, -1.0f)),
		m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
		m_fov(60.f),
		m_aspectRatio(screenWidth / screenHeight),
		m_nearPlane(0.1f),
		m_farPlane(100.0f)
	{
		UpdateProjectionMatrix();
		UpdateViewMatrix();
	}

	void Camera::SetPosition(const glm::vec3& newPosition)
	{
		m_position = newPosition;
		m_dirty = true;
	}

	const glm::vec3& Camera::GetPosition() const
	{
		return m_position;
	}

	void Camera::SetTarget(const glm::vec3& newTarget)
	{
		m_cameraTarget = newTarget;
		m_dirty = true;
	}

	const glm::vec3& Camera::GetTarget() const
	{
		return m_cameraTarget;
	}

	void Camera::SetFOV(float newFOV)
	{
		m_fov = newFOV;
		m_dirty = true;
	}

	float Camera::GetFOV() const
	{
		return m_fov;
	}

	void Camera::UpdateAspectRatio(float screenWidth, float screenHeight)
	{
		m_aspectRatio = screenWidth / screenHeight;
		m_dirty = true;
	}

	const glm::mat4& Camera::GetViewProjection() const
	{
		return m_viewProj;
	}

	const glm::mat4& Camera::GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	const glm::mat4& Camera::GetProjectionMatrix() const
	{
		return m_projMatrix;
	}

	void Camera::Update()
	{
		if (m_dirty)
		{
			UpdateProjectionMatrix();
			UpdateViewMatrix();
			m_viewProj = m_projMatrix * m_viewMatrix;
			m_dirty = false;
		}
	}

	void Camera::UpdateViewMatrix()
	{
		m_viewMatrix = glm::lookAt(m_position, m_cameraTarget, m_up);
	}

	void Camera::UpdateProjectionMatrix()
	{
		m_projMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
	}
}
