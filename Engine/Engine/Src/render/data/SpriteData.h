#pragma once

#include "glm/vec2.hpp"

namespace rendering
{
	struct SpriteData
	{
		glm::vec2 pixel_size;
		glm::vec2 uv_origin;
		glm::vec2 uv_size;
	};
}
