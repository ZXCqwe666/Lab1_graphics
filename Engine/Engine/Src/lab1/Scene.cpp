#include "Scene.h"
#include "Renderer.h"

std::vector<Triangle> Scene::trianglePool;
std::vector<Circle> Scene::circlePool;
std::vector<Quad> Scene::quadPool;

int Scene::selected_tringle_id = 0;
int Scene::selected_circle_id = 0;
int Scene::selected_quad_id = 0;

void Scene::AddTriangle(const Triangle& triangle)
{
	trianglePool.push_back(triangle);
	selected_tringle_id = trianglePool.size() - 1;
}

void Scene::AddCircle(const Circle& circle)
{
	circlePool.push_back(circle);
	selected_circle_id = circlePool.size() - 1;
}

void Scene::AddQuad(const Quad& quad)
{
	quadPool.push_back(quad);
	selected_quad_id = quadPool.size() - 1;
}

void Scene::RemoveTriangle()
{
	if (selected_tringle_id < trianglePool.size())
	{
		trianglePool[selected_tringle_id] = trianglePool[trianglePool.size() - 1];
		trianglePool.pop_back();
	}
	
	if (selected_tringle_id >= trianglePool.size()) selected_tringle_id--;
	if (selected_tringle_id < 0) selected_tringle_id = 0;
}

void Scene::RemoveCircle()
{
	if (selected_circle_id < circlePool.size())
	{
		circlePool[selected_circle_id] = circlePool[circlePool.size() - 1];
		circlePool.pop_back();
	}

	if (selected_circle_id >= circlePool.size()) selected_circle_id--;
	if (selected_circle_id < 0) selected_circle_id = 0;
}

void Scene::RemoveQuad()
{
	if (selected_quad_id < quadPool.size())
	{
		quadPool[selected_quad_id] = quadPool[quadPool.size() - 1];
		quadPool.pop_back();
	}

	if (selected_quad_id >= quadPool.size()) selected_quad_id--;
	if (selected_quad_id < 0) selected_quad_id = 0;
}

void Scene::RenderScene()
{
	for (int i = 0; i < quadPool.size(); i++) 
	{
		rendering::Renderer::DrawCircle(circlePool[i]);
	}

	for (int i = 0; i < quadPool.size(); i++)
	{
		rendering::Renderer::DrawQuad(quadPool[i]);
	}

	for (int i = 0; i < trianglePool.size(); i++)
	{
		rendering::Renderer::DrawTriangle(trianglePool[i]);
	}
}
