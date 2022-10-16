#pragma once

#include "SpriteData.h"
#include <vector>

namespace rendering
{
	class AssetRegistry
	{
	private:
		static std::vector<SpriteData> spriteRegistry;

	public:
		static void RegisterSprite(const glm::ivec2& origin, const glm::ivec2& size, const glm::ivec2& canvas_size);
		static SpriteData GetSpriteData(int id);
	};
}
