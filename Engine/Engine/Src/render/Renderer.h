#pragma once

#include "RenderConstants.h"
#include "Texture.h"
#include "Shader.h"
#include "Vertex.h"

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
		static Shader shader;

		static uint32_t vertexArrayID;
		static uint32_t vertexBufferID;
		static uint32_t indexBufferID;

	public:
		static void Init(const glm::vec3& clearColor);
		static void Shutdown();

		static void Clear();
		static void SubmitQuad(float x, float y, int id);
		static void DrawBatch();
	};
}
