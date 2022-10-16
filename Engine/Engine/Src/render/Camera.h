#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

namespace rendering
{
	class Camera
	{
	public:
		static void Init(int screenSize_x, int screenSize_y);
		static void Move(float x, float y, float speed);
		static void SetPosition(float x, float y);

		static glm::mat4 Get_ProjectionView_Matrix();

	private:
		static void UpdateMatrix();

		static glm::mat4 projection_view;
		static glm::mat4 proj_matrix;
		static glm::mat4 view_matrix;

		static glm::vec3 position;
		static glm::vec2 viewSize;
	};
}
