#pragma once

#include <glm/vec2.hpp>

namespace rendering
{
	const int max_quads = 1000;
	const int max_verts = max_quads * 4;
	const int max_indices = max_quads * 6;
	const glm::vec2 vertexOffsets[4] { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
}
