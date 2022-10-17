#include "animation_data.h"

#include "glad/glad.h"
#include "glfw3.h"

AnimationData::AnimationData()
{
	animate_position = false;
	offset_a = { -100, 0 };
	offset_b = { 100, 0 };

	animate_color = false;
	color_a = { 0, 0, 0 };
	color_b = { 1, 1, 1 };

	animate_scale = false;
	scale_min = 0;
	scale_max = 1;
}

glm::vec2 AnimationData::lerpPosition() const
{
	float time = glfwGetTime();
	float t = (sin(time) + 1) * 0.5f;

	glm::vec2 lerped_pos = offset_a * t + (1 - t) * offset_b;
	return lerped_pos;
}

glm::vec3 AnimationData::lerpColor() const
{
	float time = glfwGetTime();
	float t = (sin(time) + 1) * 0.5f;
	glm::vec3 color = { 0, 0, 0 };

	color.r = (1 - t) * color_a.r + t * color_b.r;
	color.g = (1 - t) * color_a.g + t * color_b.g;
	color.b = (1 - t) * color_a.b + t * color_b.b;

	return color;
}

float AnimationData::lerpScale() const
{
	if(scale_max < scale_min) return scale_min;

	float time = glfwGetTime();
	float t = (sin(time) + 1) * 0.5f;

	float dif = scale_max - scale_min;
	return scale_min + t * dif;
}
