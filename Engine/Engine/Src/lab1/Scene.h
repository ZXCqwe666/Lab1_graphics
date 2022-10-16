#pragma once

#include "objects.h"
#include <vector>

class Scene
{
public:
	Scene() {};
	~Scene() {};

	static void AddTriangle(const Triangle& triangle);
	static void AddCircle(const Circle& circle);
	static void AddQuad(const Quad& quad);

	static void RemoveTriangle();
	static void RemoveCircle();
	static void RemoveQuad();

public:
	static std::vector<Triangle> trianglePool;
	static std::vector<Circle> circlePool;
	static std::vector<Quad> quadPool;

	static int selected_tringle_id;
	static int selected_circle_id;
	static int selected_quad_id;
};
