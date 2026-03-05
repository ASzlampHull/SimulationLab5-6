#include "IMGUIManager.h"
#include "Renderer.h"

static void check_vk_result(VkResult err)
{
	if (err == VK_SUCCESS)
		return;
	fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
	if (err < 0)
		abort();
}

void IMGUIManager::InitializeIMGUI()
{
	//IMGUI Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	// Setup Platform/Renderer backends
	uint32_t graphicsQueueFamily = ImGui_ImplVulkanH_SelectQueueFamilyIndex(coreVulkan->physicalDevice);
	IM_ASSERT(graphicsQueueFamily != (uint32_t)-1);
	VkPipelineCache pipelineCache = VK_NULL_HANDLE;

	ImGui_ImplGlfw_InitForVulkan(window, true);
	ImGui_ImplVulkan_InitInfo init_info = {};
	init_info.Instance = coreVulkan->instance;
	init_info.PhysicalDevice = coreVulkan->physicalDevice;
	init_info.Device = coreVulkan->device;
	init_info.QueueFamily = graphicsQueueFamily;
	init_info.Queue = coreVulkan->graphicsQueue;
	init_info.PipelineCache = pipelineCache;
	init_info.DescriptorPool = mainDescriptorPool;
	init_info.MinImageCount = swapChainVulkan->imageCountMin;
	init_info.ImageCount = swapChainVulkan->imageCount;
	init_info.Allocator = nullptr;
	init_info.PipelineInfoMain.RenderPass = pipelineVulkan->renderPass;
	init_info.PipelineInfoMain.Subpass = 0;
	init_info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
	init_info.CheckVkResultFn = check_vk_result;

	ImGui_ImplVulkan_Init(&init_info);
}

bool IMGUIManager::IsScenario(const std::string& scenarioName_, Renderer* renderer)
{
	auto scenarioName = renderer->GetCurrentScenario()->GetName();

	if (scenarioName == scenarioName_) {
		return true;
	}
	else
		return false;
}

void IMGUIManager::DisplayIMGUI(uint32_t currentFrame, float deltaTime, uint32_t vertexCount, Renderer* renderer)
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (IsScenario("Default Scenario", renderer)) {
		DisplayGraphicsDisplay(deltaTime, vertexCount);
	}
	DisplayMenus(renderer);

	ImGui::Render();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffersVulkan->commandBuffers[currentFrame]);
}

void IMGUIManager::DisplayMenus(Renderer* renderer)
{
	if (ImGui::BeginMainMenuBar())
	{
		DisplayMenusScenarios(renderer);
		DisplayMenusScenarioClearColor(renderer);
		DisplayMenusScenarioPhysicsObjects(renderer);
		ImGui::EndMainMenuBar();
	}
}

void IMGUIManager::DisplayMenusScenarioClearColor(Renderer* renderer)
{
	if (IsScenario("Clear Color Scenario", renderer)) {
		if (ImGui::BeginMenu("Colour"))
		{
			ImGui::ColorPicker4("Colour", clearColor);
			ImGui::EndMenu();
		}
		renderer->SetClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	}
}

void IMGUIManager::DisplayMenusScenarioPhysicsObjects(Renderer* renderer)
{
	if (IsScenario("Physics Objects Scenario", renderer)) {
		if (ImGui::BeginMenu("Material Light"))
		{
			ImGui::ColorPicker3("Colour", lightColor);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Material Dark"))
		{
			ImGui::ColorPicker3("Colour", darkColor);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Simulation"))
		{
			if (ImGui::Button("Start")) {
				physicsTimeStepEnabled = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Stop")) {
				physicsTimeStepEnabled = false;
			}

			ImGui::SliderFloat("Slider", &physicsTimeStep, 0.0f, 1.0f);

			ImGui::EndMenu();
		}
		renderer->SetLightDarkColor(lightColor, darkColor);
		renderer->SetPhysicsTimeStep(physicsTimeStep, physicsTimeStepEnabled);
	}
}

void IMGUIManager::DisplayMenusScenarios(Renderer*& renderer)
{
	if (ImGui::BeginMenu("Scenario"))
	{
		if (ImGui::MenuItem("Default Scenario")) {
			renderer->SetScenario(std::make_unique<ScenarioDefault>(renderer));
		}
		if (ImGui::MenuItem("Clear Color Scenario")) {
			renderer->SetScenario(std::make_unique<ScenarioClearColor>(renderer));
		}
		if (ImGui::MenuItem("Physics Objects Scenario")) {
			renderer->SetScenario(std::make_unique<ScenarioPhysicsObjects>(renderer));
		}
		ImGui::EndMenu();
	}
}

void IMGUIManager::DisplayGraphicsDisplay(float deltaTime, uint32_t vertexCount)
{
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Once);

	ImGui::Begin("Graphics Statistics");
	ImGui::Text("Frame Time: %.3f ms", deltaTime * 1000.0f);
	ImGui::Text("FPS: %.1f", 1.0f / deltaTime);
	ImGui::Text("Vertices Rendered: %u", vertexCount);
	ImGui::End();
}

void IMGUIManager::CleanUp()
{
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}