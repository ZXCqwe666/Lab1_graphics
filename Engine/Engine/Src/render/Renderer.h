#pragma once

#include "Shader.h"
#include "objects.h"

namespace rendering
{
	class Renderer
	{
	private:
		static Shader shader_vcolor;
		static Shader shader_circle;

	public:
		static void Init(const glm::vec3& clearColor);
		static void Shutdown();

		static void DrawTriangle(const Triangle& triangle);
		static void DrawQuad(const Quad& quad);
		static void DrawCircle(const Circle& triangle);
		static void Clear();
	};
}
