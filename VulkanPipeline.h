#pragma once
#include "VulkanDataTypes.h"
#include "VulkanExternals.h"
#include "RenderDataTypes.h"
#include <string>
#include <fstream>


class VulkanPipeline final {
private:
	PipelineVulkan pipelineVulkan;
	ShaderVulkan shaderVulkan;
	const SwapChainVulkan* swapChainVulkan;
	const CoreVulkan* coreVulkan;

	void InitialisePipeline();
	void CreateRenderPass();
	void CreateDescriptorSetLayout();
	void CreateGraphicsPipeline();

	const void ReadFile(const std::string& filename, std::vector<char>& buffer_) const;
	const VkShaderModule CreateShaderModule(const std::vector<char>& code) const;
public:
	VulkanPipeline() = default;
	~VulkanPipeline() = default;
	explicit VulkanPipeline(const CoreVulkan* coreVulkan_, const SwapChainVulkan* swapChainVulkan_)
		: pipelineVulkan(),
		shaderVulkan(),
		swapChainVulkan(swapChainVulkan_),
		coreVulkan(coreVulkan_)
	{
		InitialisePipeline();
	}
	VulkanPipeline(const VulkanPipeline& other) = default;
	VulkanPipeline& operator=(const VulkanPipeline& rhs)
	{
		if (this != &rhs) {
			this->coreVulkan = rhs.coreVulkan;
			this->swapChainVulkan = rhs.swapChainVulkan;
			this->pipelineVulkan = rhs.pipelineVulkan;
			this->shaderVulkan = rhs.shaderVulkan;
		}
		return *this;
	}

	const PipelineVulkan& GetPipelineVulkan() const { return pipelineVulkan; };

	const void Cleanup() const;
	const void CleanupDescriptorSetLayout() const { vkDestroyDescriptorSetLayout(coreVulkan->device, pipelineVulkan.descriptorSetLayout, nullptr); };
};