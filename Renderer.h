#pragma once
#include "ResourceManager.h"
#include "WindowManager.h"
#include "Camera.h"
#include "DayNightSeasonal.h"
#include "VulkanCore.h"
#include "VulkanSwapChain.h"
#include "VulkanPipeline.h"
#include "VulkanFramebuffers.h"
#include "VulkanBuffers.h"
#include "VulkanCommandBuffers.h"
#include "VulkanFrameSync.h"
#include "IMGUIManager.h"
#include <chrono>
#include <array>
#include <GLFW/glfw3.h>

#include "Scenario.h"
#include "ScenarioDefault.h"
#include "ScenarioClearColor.h"
#include "ScenarioPhysicsObjects.h"


class Renderer final {
private:
    ResourceManager resourceManager;
	IMGUIManager imguiManager;
    DayNightSeasonal dayNightSeasonal;
	std::unique_ptr<Scenario> currentScenario;

    VulkanCore vulkanCore;
    VulkanSwapChain vulkanSwapChain;
    VulkanPipeline vulkanPipeline;
    VulkanFramebuffers vulkanFramebuffers;
    VulkanCommandBuffers vulkanCommandBuffers;
    VulkanFrameSync vulkanFrameSync;

    UniformVulkan uniformBufferObject;
    CameraSettings currentCamera;

    GLFWwindow* window;
    const CoreVulkan* coreVulkan;
    const SwapChainVulkan* swapChainVulkan;
    const PipelineVulkan* pipelineVulkan;
    const CommandPoolVulkan* commandPoolVulkan;
    const CommandBuffersVulkan* commandBuffersVulkan;
    const FrameSyncVulkan* frameSyncVulkan;
    bool* framebufferResized;

    uint32_t currentFrame = 0;
    float deltaTime = 0.0f;
    float physicsAccumulator = 0.0f;
    float fixedPhysicsTimeStep = 1.0f / 60.0f; // 60 Hz physics
	bool enablePhysicsTimeStep = true;
    std::array<VkClearValue, 2> clearValues{};
	std::pair<glm::vec3, glm::vec3> lightDarkColor = { glm::vec3(1.0f), glm::vec3(0.0f) };

	void InitVulkan();
	void InitIMGUI();
	void CreateUniformBuffers();
	void RecreateSwapChain();
	void CleanupSwapChain();
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void UpdateUniformBuffer(uint32_t currentImage);
public:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer& other) = default;
    Renderer& operator=(const Renderer& other)
    {
        if (this != &other) {
            resourceManager = other.resourceManager;
            dayNightSeasonal = other.dayNightSeasonal;
            vulkanCore = other.vulkanCore;
            vulkanSwapChain = other.vulkanSwapChain;
            vulkanPipeline = other.vulkanPipeline;
            vulkanFramebuffers = other.vulkanFramebuffers;
            vulkanCommandBuffers = other.vulkanCommandBuffers;
            vulkanFrameSync = other.vulkanFrameSync;
            uniformBufferObject = other.uniformBufferObject;
            currentCamera = other.currentCamera;
            window = other.window;
            coreVulkan = other.coreVulkan;
            swapChainVulkan = other.swapChainVulkan;
            pipelineVulkan = other.pipelineVulkan;
            commandPoolVulkan = other.commandPoolVulkan;
            commandBuffersVulkan = other.commandBuffersVulkan;
            frameSyncVulkan = other.frameSyncVulkan;
            framebufferResized = other.framebufferResized;
            currentFrame = other.currentFrame;
            deltaTime = other.deltaTime;
			clearValues = other.clearValues;
			lightDarkColor = other.lightDarkColor;
            physicsAccumulator = other.physicsAccumulator;
			fixedPhysicsTimeStep = other.fixedPhysicsTimeStep;
        }
        return *this;
    }

	ResourceManager& GetResourceManager() { return resourceManager; };
	DayNightSeasonal& GetDayNightSeasonal() { return dayNightSeasonal; };
	Scenario* GetCurrentScenario() const { return currentScenario.get(); };
	const CoreVulkan& GetCoreVulkan() const { return *coreVulkan; };

    const CoreVulkan* GetCoreVulkanPtr() const { return coreVulkan; };
    const CommandPoolVulkan* GetCommandPoolVulkanPtr() const { return commandPoolVulkan; };
	const PipelineVulkan* GetPipelineVulkanPtr() const { return pipelineVulkan; };
	UniformVulkan& GetUniformBufferObject() { return uniformBufferObject; };

	float GetPhysicsTimeStep() const { return fixedPhysicsTimeStep; }
	float GetPhysicsAccumulator() const { return physicsAccumulator; }

    void SetScenario(std::unique_ptr<Scenario> scenario);
    void SetClearColor(float r, float g, float b, float a);
    void SetLightDarkColor(float lightColor[3], float darkColor[3]);
	void SetNoTextureModels();
    void UpdatePhysicsTime();
    void SetPhysicsTimeStep(float timeStep, bool enabled);

	void InitRenderer(const ConfigData& configData, GLFWwindow* window_, const CameraSettings& currentCamera_);
	void Update(const InputManager& input, const CameraSettings& currentCamera_, float deltaTime_, bool* framebufferResized_);
    void DrawFrame();
	void Cleanup();
};