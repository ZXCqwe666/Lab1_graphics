#pragma once

#include <unordered_map>
#include <string>
#include "glm/mat4x4.hpp"

namespace rendering
{
	struct ShaderProgramSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};

	class Shader
	{
	private:
		unsigned int rendererID;
		std::string filePath;
		mutable std::unordered_map<std::string, int> uniformLocationCache;
	
	public:
		~Shader();

		void LoadShader(const std::string& filename);
		void Bind() const;
		void Unbind() const;

		void Set_Mat4_Float(const std::string& name, const glm::mat4& matrix);

	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const ShaderProgramSource& source);

		int GetUniformLocation(const std::string& name) const;
	};
}
