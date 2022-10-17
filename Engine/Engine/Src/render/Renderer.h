#pragma once

#include "RenderConstants.h"
#include "Texture.h"
#include "Shader.h"
#include "Vertex.h"

#include "objects.h"

namespace rendering
{
	class Renderer
	{
	public:
		static int quadsDrawn;
		static int drawCalls;

	private:
		static int quadCount;

		static Vertex vertices[max_verts];
		static Texture texture;
		static Shader shader_tex_quad;
		static Shader shader_vcolor;
		static Shader shader_circle;

		static uint32_t vertexArrayID;
		static uint32_t vertexBufferID;
		static uint32_t indexBufferID;

	public:
		static void Init(const glm::vec3& clearColor);
		static void Shutdown();

		static void DrawTriangle(const Triangle& triangle);
		static void DrawQuad(const Quad& quad);
		static void DrawCircle(const Circle& triangle);

		static void Clear();
		static void SubmitQuad(float x, float y, int id);
		static void DrawBatch();
	};
}
