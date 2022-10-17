#include "Renderer.h"

#include "glad/glad.h"
#include "GLErrorHandler.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Camera.h"
#include "Window.h"

namespace rendering
{
	Shader Renderer::shader_vcolor;
	Shader Renderer::shader_circle;

	void Renderer::Init(const glm::vec3& clearColor)
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f));

		shader_vcolor.LoadShader(".\\Resources\\Shaders\\VertColor.shader");
		shader_circle.LoadShader(".\\Resources\\Shaders\\Circle.shader");
	}

	void Renderer::Shutdown()
	{
		
	}

	void Renderer::DrawTriangle(const Triangle& triangle)
	{
		VertexColored verts_copy[3] = {triangle.verts[0], triangle.verts[1], triangle.verts[2]};
		float scale = triangle.anim.animate_scale ? triangle.anim.lerpScale() : 1.0f;
		glm::vec2 origin = triangle.anim.animate_position ? triangle.origin + triangle.anim.lerpPosition() : triangle.origin;

		if (triangle.anim.animate_color)
		{
			glm::vec3 color = triangle.anim.lerpColor();
			verts_copy[0].color = color;
			verts_copy[1].color = color;
			verts_copy[2].color = color;
		}

		verts_copy[0].position *= scale;
		verts_copy[1].position *= scale;
		verts_copy[2].position *= scale;

		uint32_t va_id = 0;
		GLCall(glGenVertexArrays(1, &va_id));
		GLCall(glBindVertexArray(va_id));

		uint32_t vb_id = 0;
		GLCall(glGenBuffers(1, &vb_id));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb_id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(VertexColored), verts_copy, GL_STATIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexColored), (const void*)offsetof(VertexColored, position)));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColored), (const void*)offsetof(VertexColored, color)));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3{origin.x, origin.y, 0});
		shader_vcolor.Bind();
		shader_vcolor.Set_Mat4_Float("u_MVP", Camera::Get_ProjectionView_Matrix() * model);

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		GLCall(glDeleteVertexArrays(1, &va_id));
		GLCall(glDeleteBuffers(1, &vb_id));
	}

	void Renderer::DrawQuad(const Quad& quad)
	{
		const glm::vec2 vertex_offsets[4] = {{-0.5f, -0.5}, {0.5f, -0.5}, {-0.5f, 0.5}, {0.5f, 0.5}};

		Triangle triangle0;
		triangle0.anim = quad.anim;
		triangle0.origin = quad.origin;
		triangle0.verts[0] = { vertex_offsets[0] * quad.size, quad.color };
		triangle0.verts[1] = { vertex_offsets[1] * quad.size, quad.color };
		triangle0.verts[2] = { vertex_offsets[2] * quad.size, quad.color };

		Renderer::DrawTriangle(triangle0);
		triangle0.verts[0] = { vertex_offsets[3] * quad.size, quad.color };
		Renderer::DrawTriangle(triangle0);
	}

	void Renderer::DrawCircle(const Circle& circle)
	{
		glm::vec3 color = circle.anim.animate_color ? circle.anim.lerpColor() : circle.color;
		float radius = circle.anim.animate_scale ? circle.radius * circle.anim.lerpScale() : circle.radius;
		glm::vec2 origin = circle.anim.animate_position ? circle.origin + circle.anim.lerpPosition() : circle.origin;

		const glm::vec2 vertex_offsets[4] = { {-0.5f, -0.5}, {0.5f, -0.5}, {-0.5f, 0.5}, {0.5f, 0.5} };

		glm::vec2 verts[6]{};
		verts[0] = 2.0f * vertex_offsets[0] * circle.radius;
		verts[1] = 2.0f * vertex_offsets[1] * circle.radius;
		verts[2] = 2.0f * vertex_offsets[2] * circle.radius;
		verts[3] = 2.0f * vertex_offsets[2] * circle.radius;
		verts[4] = 2.0f * vertex_offsets[1] * circle.radius;
		verts[5] = 2.0f * vertex_offsets[3] * circle.radius;

		uint32_t va_id = 0;
		GLCall(glGenVertexArrays(1, &va_id));
		GLCall(glBindVertexArray(va_id));

		uint32_t vb_id = 0;
		GLCall(glGenBuffers(1, &vb_id));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb_id));
		GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), verts, GL_STATIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (const void*)0));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3{ origin.x, origin.y, 0 });
		shader_circle.Bind();
		shader_circle.Set_Float2("u_origin", origin);
		shader_circle.Set_Float("u_radius", 2.0f * radius);
		shader_circle.Set_Float("u_fade", circle.fade);
		shader_circle.Set_Float3("u_circleColor", color);
		shader_circle.Set_Float2("u_resolution", {Window::width, Window::height});
		shader_circle.Set_Mat4_Float("u_MVP", Camera::Get_ProjectionView_Matrix() * model);

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

		GLCall(glDeleteVertexArrays(1, &va_id));
		GLCall(glDeleteBuffers(1, &vb_id));
	}

	void Renderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
}
