#pragma once

#include <string>

namespace rendering
{
	class Texture
	{
	private:
		unsigned int rendererID;

	public:
		~Texture();

		void LoadTexture(const std::string& filepath);
		void Bind(unsigned int slot = 0) const;
		void Unbind() const;
	};
}
