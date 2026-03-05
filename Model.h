#pragma once
#include "ModelParserDataTypes.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderDataTypes.h"
#include "VulkanDataTypes.h"
#include "VulkanBuffers.h"


class Model final {
private:
	Mesh mesh;
	Material material;
	VulkanBuffers vulkanBuffers;
	Transformations transformations = {};
	std::string name = "";
	bool hasNoTexture = false;
	const ModelBuffersVulkan* modelBuffersVulkan = nullptr;

public:
	Model() = default;
	~Model() = default;
	explicit Model(const ModelData& modelData)
		: mesh(modelData.objData, modelData.mtlData), material(modelData.mtlData),
		transformations{ modelData.position, modelData.rotation, modelData.scale }, name(modelData.name) { }
	Model(const Model& other) = default;
	Model& operator=(const Model& other)
	{
		if (this != &other) {
			mesh = other.mesh;
			material = other.material;
			transformations = other.transformations;
			vulkanBuffers = other.vulkanBuffers;
			modelBuffersVulkan = other.modelBuffersVulkan;
			name = other.name;
		}
		return *this;
	}

	void UpdatePushConstants(VkCommandBuffer commandBuffer, const PipelineVulkan* pipelineVulkan, std::pair<glm::vec3, glm::vec3> lightDarkColor_) const;
	void CreateVertexIndexBuffers(const CoreVulkan* coreVulkan, const CommandPoolVulkan* commandPoolVulkan);
	const void CleanupBuffersVI() const { vulkanBuffers.CleanupBuffersVI(); };

	void SetHasNoTexture(bool hasNoTexture_) { hasNoTexture = hasNoTexture_; }
	const Mesh& GetMesh() const { return mesh; };
	const Material& GetMaterial() const { return material; };
	Mesh& GetMeshRef() { return mesh; };
	Material& GetMaterialRef() { return material; };
	const ModelBuffersVulkan* GetModelBuffersVulkan() const { return modelBuffersVulkan; };
	const Transformations& GetTransformations() const { return transformations; };
	void SetTransformations(const Transformations& transformations_) { transformations = transformations_; }
};