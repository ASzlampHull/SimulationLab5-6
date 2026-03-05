#include "ResourceManager.h"

void ResourceManager::CreateModels() {
	models.clear();
	for (const auto& modelData : modelLoader.GetLoadedModels()) {
		const Model model(modelData);
		models[modelData.name] = model;
	}
}

void ResourceManager::CreateMainTextureSampler(const CoreVulkan* coreVulkan)
{
	VkPhysicalDeviceProperties properties{};
	vkGetPhysicalDeviceProperties(coreVulkan->physicalDevice, &properties);

	VkSamplerCreateInfo samplerInfo{};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

	if (vkCreateSampler(coreVulkan->device, &samplerInfo, nullptr, &textureSamplers["Main"]) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}
}

void ResourceManager::CreateTextures(const CoreVulkan* coreVulkan, 
	const CommandPoolVulkan* commandPoolVulkan,
	const PipelineVulkan* pipelineVulkan,
	UniformVulkan& uniformBufferObject)
{
	CreateMainTextureSampler(coreVulkan);
	for (auto& pair : models) {
		auto& model = pair.second;
		auto& material = model.GetMaterialRef();
		material.CreateMaterialResources(coreVulkan, commandPoolVulkan, model.GetModelBuffersVulkan(), pipelineVulkan, &textureSamplers["Main"], uniformBufferObject);
	}
}

void ResourceManager::CleanupTextures(const CoreVulkan* coreVulkan)
{
	for (auto& samplerPair : textureSamplers) {
		vkDestroySampler(coreVulkan->device, samplerPair.second, nullptr);
	}

	for (auto& pair : models) {
		auto& model = pair.second;
		auto& material = model.GetMaterialRef();
		material.CleanupMaterialResources();
	}
}

void ResourceManager::CreateVertexIndexBuffers(const CoreVulkan* coreVulkan, const CommandPoolVulkan* commandPoolVulkan)
{
	for (auto& pair : models) {
		auto& model = pair.second;
		model.CreateVertexIndexBuffers(coreVulkan, commandPoolVulkan);
	}
}

void ResourceManager::CleanupBuffersVI()
{
	for (const auto& pair : models) {
		const auto& model = pair.second;
		model.CleanupBuffersVI();
	}
}

void ResourceManager::ClearModels()
{
	models.clear();
}

// Make quickly and dirty way for testing purposes.
void ResourceManager::CreateSJGModels(const std::vector<std::string>& sjgFilePaths, const std::vector<Transformations> transformations)
{
	SJGParser sjgParser;
	size_t count = sjgFilePaths.size();
	for (size_t i = 0; i < count; ++i) {
		const auto& filePath = sjgFilePaths[i];
		const auto& transform = transformations[i];

		MeshDataSJG meshDataSJG = sjgParser.ParseSJGFile(filePath);
		ModelData modelData;
		// Use file path as name for simplicity
		modelData.name = filePath + std::to_string(i);
		modelData.objData.name = filePath + std::to_string(i);
		modelData.objData.configName = filePath + std::to_string(i);
		for (const auto& vertex : meshDataSJG.vertices) {
			glm::vec3 vertexPos(vertex.x, vertex.y, vertex.z);
			glm::vec3 vertexNormal(vertex.nx, vertex.ny, vertex.nz);
			glm::vec2 vertexTexCoord(0.0f, 0.0f); // No texture coordinates in SJG format, set to default
			modelData.objData.vertices.push_back(vertexPos);
			modelData.objData.normals.push_back(vertexNormal);
			modelData.objData.texCoords.push_back(vertexTexCoord);
		}
		modelData.objData.vertexIndices = meshDataSJG.indices;
		modelData.objData.normalIndices = meshDataSJG.indices;
		modelData.objData.texCoordIndices = meshDataSJG.indices;

		modelData.mtlData.name = "DefaultMaterial";
		modelData.mtlData.texturePath = "textures/dummyTexture.png";
		modelData.mtlData.ambientColor = glm::vec3(0.1f);
		modelData.mtlData.diffuseColor = glm::vec3(0.5f);
		modelData.mtlData.specularColor = glm::vec3(1.0f);
		modelData.mtlData.emissionColor = glm::vec3(0.0f);
		modelData.mtlData.shininess = 32.0f;
		modelData.mtlData.refractionIndex = 1.0f;
		modelData.mtlData.transparency = 1.0f;
		modelData.mtlData.illuminationModel = 2; // Use a common illumination model

		models[modelData.name] = Model(modelData);
		models[modelData.name].SetTransformations(transform);
		models[modelData.name].SetHasNoTexture(true);
	}
}

void ResourceManager::CreateNoTextureModel()
{
	for (auto& pair : models) {
		auto& model = pair.second;
		model.SetHasNoTexture(true);
	}
}

const VkDescriptorPool ResourceManager::GetMainDescriptorPool() const
{
	const auto& pair = models.begin();
	const auto& model = pair->second;
	const auto& material = model.GetMaterial();
	if (material.GetDescriptorVulkan() != nullptr) {
		return material.GetDescriptorVulkan()->descriptorPool;
	}

	__debugbreak(); // No models / materials available to get descriptor pool from
	return VkDescriptorPool();
}
