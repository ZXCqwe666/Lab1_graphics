#include "AssetRegistry.h"

namespace rendering
{
	std::vector<rendering::SpriteData> AssetRegistry::spriteRegistry;

	void AssetRegistry::RegisterSprite(const glm::ivec2& origin, const glm::ivec2& size, const glm::ivec2& canvas_size)
	{
		glm::vec2 pixelRatio = glm::vec2(1.0f, 1.0f) / (glm::vec2)canvas_size;

		rendering::SpriteData data
		{
			(glm::vec2)size,
			pixelRatio * (glm::vec2)origin,
			pixelRatio * (glm::vec2)size,
		};

		spriteRegistry.push_back(data);
	}

	rendering::SpriteData AssetRegistry::GetSpriteData(int id)
	{
		return spriteRegistry[id];
	}
}
