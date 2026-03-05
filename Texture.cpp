#include "Texture.h"

void Texture::CreateTexture(const CoreVulkan* coreVulkan, const CommandPoolVulkan* commandPoolVulkan, const VkSampler* texSampler)
{
	vulkanTexture = VulkanTexture(coreVulkan, commandPoolVulkan, texturePath, texSampler);
	textureVulkan = &vulkanTexture.GetTextureVulkan();
}
