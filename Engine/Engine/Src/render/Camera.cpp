#include "RenderConstants.h"
#include "Camera.h"

namespace rendering
{
	glm::mat4 Camera::projection_view;
	glm::mat4 Camera::proj_matrix;
	glm::mat4 Camera::view_matrix;

	glm::vec3 Camera::position = { 0, 0, 0 };
	glm::vec2 Camera::viewSize;

	void Camera::Init(int screenSize_x, int screenSize_y)
	{
		viewSize = { screenSize_x, screenSize_y};
		UpdateMatrix();
	}

	void Camera::SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
		UpdateMatrix();
	}

	void Camera::Move(float x, float y, float speed)
	{
		position.x += x * speed;
		position.y += y * speed;
		UpdateMatrix();
	}

	void Camera::UpdateMatrix()
	{
		float half_x = viewSize.x / 2.0f;
		float half_y = viewSize.y / 2.0f;

		proj_matrix = glm::ortho(-half_x, half_x, -half_y, half_y, -1.0f, 1.0f);
		view_matrix = glm::translate(glm::mat4(1.0f), -position);
		projection_view = proj_matrix * view_matrix;
	}

	glm::mat4 Camera::Get_ProjectionView_Matrix()
	{
		return projection_view;
	}
}
