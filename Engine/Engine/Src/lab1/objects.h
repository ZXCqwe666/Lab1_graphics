#pragma once

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct VertexColored
{
	glm::vec2 position = glm::vec2 { 0.0f, 0.0f };
	glm::vec3 color = glm::vec3 { 1.0f, 1.0f, 1.0f };
};

struct Triangle
{
public:
	glm::vec2 origin = { 0.0f, 0.0f };
	VertexColored verts[3];
};

struct Quad
{
public:
	glm::vec2 origin = { 0.0f, 0.0f };
	glm::vec3 color = { 1.0f, 1.0f, 1.0f };
	float size = 100.0f;
};

struct Circle
{
public:
	glm::vec2 origin = { 0.0f, 0.0f };
	glm::vec3 color = { 1.0f, 1.0f, 1.0f };
	float radius = 50.0f;
};
