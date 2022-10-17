#pragma once

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct AnimationData
{
	bool animate_position;
	glm::vec2 offset_a;
	glm::vec2 offset_b;

	bool animate_color;
	glm::vec3 color_a;
	glm::vec3 color_b;

	bool animate_scale;
	float scale_min;
	float scale_max;

	AnimationData();

public:
	glm::vec2 lerpPosition() const;
	glm::vec3 lerpColor() const;
	float lerpScale() const;
};
