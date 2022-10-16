#include "Texture.h"

#include "glad/glad.h"
#include "GLErrorHandler.h"
#include "stb_image/stb_image.h"

namespace rendering
{
	void Texture::LoadTexture(const std::string& filepath)
	{
		int width = 0;
		int height = 0;
		int BPP = 0;

		stbi_set_flip_vertically_on_load(1);
		uint8_t* m_LocalBuffer = stbi_load(filepath.c_str(), &width, &height, &BPP, 4);

		GLCall(glGenTextures(1, &rendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		Bind();

		if(m_LocalBuffer) 
		stbi_image_free(m_LocalBuffer);
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &rendererID));
	}

	void Texture::Bind(unsigned int slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}
