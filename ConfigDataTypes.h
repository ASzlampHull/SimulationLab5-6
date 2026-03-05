#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Resolution {
	int width;
	int height;
};

struct ModelStats {
	std::string name;
	std::string modelPath;
	std::string materialPath;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct DirectionalLight {
	glm::vec3 direction;
	glm::vec3 color;
	float intensity;
};

struct SunMoonDirections {
	glm::vec3 sunDirection;
	glm::vec3 moonDirection;
};

struct SeasonalTimings {
	float dayDuration;
	float nightDuration;
	float drySeasonDuration;
	float snowSeasonDuration;
	float wetSeasonDuration;
};

struct ConfigData {
	std::unordered_map<std::string, ModelStats> models; // Key: model name
	DirectionalLight directionalLight;
	SunMoonDirections sunMoonDirections;
	SeasonalTimings seasonalTimings;
	Resolution resolution;
	std::string title;
};
