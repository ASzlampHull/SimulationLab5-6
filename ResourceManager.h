#pragma once
//Pass in the loaded model data from ModelLoader to create Model instances
#include "Model.h"
#include "ModelParserDataTypes.h"
#include "ModelLoader.h"
#include "SJGParser.h"

class ResourceManager final {
private:
	std::unordered_map<std::string, Model> models;
	ModelLoader modelLoader;
	std::unordered_map<std::string, VkSampler> textureSamplers;

	void CreateModels();
	void CreateMainTextureSampler(const CoreVulkan* coreVulkan);
public:
	ResourceManager() = default;
	~ResourceManager() = default;
	explicit ResourceManager(const ConfigData& configData) : modelLoader(configData) 
	{
		CreateModels();
	}

	void CreateTextures(const CoreVulkan* coreVulkan, const CommandPoolVulkan* commandPoolVulkan, const PipelineVulkan* pipelineVulkan, UniformVulkan& uniformBufferObject);
	void CleanupTextures(const CoreVulkan* coreVulkan);
	void CreateVertexIndexBuffers(const CoreVulkan* coreVulkan, const CommandPoolVulkan* commandPoolVulkan);
	void CleanupBuffersVI();
	void ClearModels();

	void CreateSJGModels(const std::vector<std::string>& sjgFilePaths, const std::vector<Transformations> transformations);
	void CreateNoTextureModel();

	std::unordered_map<std::string, Model>& GetModels() { return models; };
	const VkDescriptorPool GetMainDescriptorPool() const;
};