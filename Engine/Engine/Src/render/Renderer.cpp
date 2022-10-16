#include "Renderer.h"

#include "glad/glad.h"
#include "GLErrorHandler.h"

#include "AssetRegistry.h"
#include "Camera.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

namespace rendering
{
	int Renderer::quadsDrawn;
	int Renderer::drawCalls;
	int Renderer::quadCount = 0;

	Vertex Renderer::vertices[max_verts];
	Texture Renderer::texture;
	Shader Renderer::shader;

	uint32_t Renderer::vertexArrayID;
	uint32_t Renderer::vertexBufferID;
	uint32_t Renderer::indexBufferID;

	void Renderer::Init(const glm::vec3& clearColor)
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f));

		texture.LoadTexture(".\\Resources\\Textures\\Atlas.png");
		shader.LoadShader(".\\Resources\\Shaders\\Quad.shader");

		GLCall(glGenVertexArrays(1, &vertexArrayID));
		GLCall(glBindVertexArray(vertexArrayID));

		GLCall(glGenBuffers(1, &vertexBufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, max_verts * sizeof(Vertex), nullptr, GL_STATIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position)));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv)));

		uint32_t offset = 0;
		uint32_t* indices = new uint32_t[max_indices];

		for (int i = 0; i < max_indices; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		GLCall(glGenBuffers(1, &indexBufferID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_indices * sizeof(uint32_t), indices, GL_STATIC_DRAW));

		delete[] indices;
	}

	void Renderer::Shutdown()
	{
		GLCall(glDeleteVertexArrays(1, &vertexArrayID));
		GLCall(glDeleteBuffers(1, &vertexBufferID));
		GLCall(glDeleteBuffers(1, &indexBufferID));
	}

	void Renderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		quadsDrawn = 0;
		drawCalls = 0;
	}

	void Renderer::SubmitQuad(float x, float y, int id)
	{
		SpriteData data = AssetRegistry::GetSpriteData(id);
		glm::vec2 position = {x, y};

		int index_vert = quadCount * 4;

		vertices[index_vert + 0].position = position;
		vertices[index_vert + 1].position = position + data.pixel_size * vertexOffsets[1];
		vertices[index_vert + 2].position = position + data.pixel_size * vertexOffsets[2];
		vertices[index_vert + 3].position = position + data.pixel_size * vertexOffsets[3];

		vertices[index_vert + 0].uv = data.uv_origin;
		vertices[index_vert + 1].uv = data.uv_origin + data.uv_size * vertexOffsets[1];
		vertices[index_vert + 2].uv = data.uv_origin + data.uv_size * vertexOffsets[2];
		vertices[index_vert + 3].uv = data.uv_origin + data.uv_size * vertexOffsets[3];

		quadCount++;

		if (quadCount >= max_quads)
		{
			DrawBatch();
		}
	}

	void Renderer::DrawBatch()
	{
		if(quadCount == 0) return;

		shader.Bind();
		shader.Set_Mat4_Float("u_MVP", Camera::Get_ProjectionView_Matrix());

		uint32_t size = 4 * quadCount * sizeof(rendering::Vertex);
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices));
		GLCall(glDrawElements(GL_TRIANGLES, 6 * quadCount, GL_UNSIGNED_INT, nullptr));

		quadsDrawn += quadCount;
		drawCalls++;
		quadCount = 0;
	}
}
