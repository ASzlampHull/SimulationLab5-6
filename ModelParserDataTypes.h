#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using IndicesVector = std::vector<uint32_t>;

struct ModelOBJ {
	std::string configName;
	std::string name; // o
	std::vector<glm::vec3> vertices; // v
	std::vector<glm::vec3> normals; // vn
	std::vector<glm::vec2> texCoords; // vt
	IndicesVector vertexIndices; // f
	IndicesVector normalIndices; // f
	IndicesVector texCoordIndices; // f
	std::string materialName; // usemtl
};

struct ModelMTL {
	std::string name;           // newmtl
	std::string texturePath;    // map_Kd

	glm::vec3 ambientColor;     // Ka
	glm::vec3 diffuseColor;     // Kd
	glm::vec3 specularColor;    // Ks
	glm::vec3 emissionColor;    // Ke

	float shininess;            // Ns
	float refractionIndex;      // Ni
	float transparency;         // d

	unsigned int illuminationModel; // illum
};

struct ModelData {
	std::string name;
	ModelOBJ objData;
	ModelMTL mtlData;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct VertexSJG {
	float x, y, z;
	float nx, ny, nz;
};

struct MeshDataSJG {
	std::vector<VertexSJG> vertices;
	IndicesVector indices;
};

struct Transformations {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

using ModelVector = std::vector<ModelData>;