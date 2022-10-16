#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct VertexColored
{
	glm::vec2 position;
	glm::vec3 color;
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
	glm::vec3 color = { 0.0f, 0.0f, 0.0f };
	glm::vec2 verts[4];
};

struct Circle
{
public:
	glm::vec2 origin = { 0.0f, 0.0f };
	glm::vec3 color = { 0.0f, 0.0f, 0.0f };
	float radius = 1.0f;
};
