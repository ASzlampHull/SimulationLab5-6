#pragma once
#include "VulkanDataTypes.h"
#include "VulkanExternals.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <string>

class Renderer;

class IMGUIManager final {
private:
	const CoreVulkan* coreVulkan = nullptr;
	const SwapChainVulkan* swapChainVulkan = nullptr;
	const PipelineVulkan* pipelineVulkan = nullptr;
	const CommandPoolVulkan* commandPoolVulkan = nullptr;
	const CommandBuffersVulkan* commandBuffersVulkan = nullptr;
	VkDescriptorPool mainDescriptorPool;
	GLFWwindow* window;

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float lightColor[3] = { 1.0f, 1.0f, 1.0f};
	float darkColor[3] = { 0.0f, 0.0f, 0.0f};
	bool physicsTimeStepEnabled = true;
	float physicsTimeStep = 1.0f / 60.0f;

	void InitializeIMGUI();
	bool IsScenario(const std::string& scenarioName, Renderer* renderer);

public:
	IMGUIManager() = default;
	~IMGUIManager() = default;
	IMGUIManager(const IMGUIManager& other) = delete;
	IMGUIManager& operator=(const IMGUIManager& other)
	{
		if (this != &other) {
			this->coreVulkan = other.coreVulkan;
			this->swapChainVulkan = other.swapChainVulkan;
			this->pipelineVulkan = other.pipelineVulkan;
			this->commandPoolVulkan = other.commandPoolVulkan;
			this->commandBuffersVulkan = other.commandBuffersVulkan;
			this->mainDescriptorPool = other.mainDescriptorPool;
			this->window = other.window;
		}
		return *this;
	}

	IMGUIManager(const GLFWwindow* window, 
		const CoreVulkan* coreVulkan, 
		const SwapChainVulkan* swapChainVulkan, 
		const VkDescriptorPool descriptorVulkanPool,
		const PipelineVulkan* pipelineVulkan_,
		const CommandPoolVulkan* commandPoolVulkan_,
		const CommandBuffersVulkan* commandBuffersVulkan_ = nullptr)
		: window(const_cast<GLFWwindow*>(window)),
		coreVulkan(coreVulkan),
		swapChainVulkan(swapChainVulkan),
		mainDescriptorPool(descriptorVulkanPool),
		pipelineVulkan(pipelineVulkan_),
		commandPoolVulkan(commandPoolVulkan_),
		commandBuffersVulkan(commandBuffersVulkan_)
	{
		InitializeIMGUI();
	}

	void DisplayIMGUI(uint32_t currentFrame, float deltaTime, uint32_t vertexCount, Renderer* renderer);
	void DisplayMenus(Renderer* renderer);
	void DisplayMenusScenarioClearColor(Renderer* renderer);
	void DisplayMenusScenarioPhysicsObjects(Renderer* renderer);
	void DisplayMenusScenarios(Renderer*& renderer);
	void DisplayGraphicsDisplay(float deltaTime, uint32_t vertexCount);
	void CleanUp();
};

