#include "SJGParser.h"

MeshDataSJG SJGParser::ParseSJGFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file) throw std::runtime_error("Failed to open file: " + filePath);

    std::string line;
    MeshDataSJG mesh;

    // Parse Vertex Format header
    std::getline(file, line);
    // Remove BOM if present
    if (!line.empty() && line[0] == '\xEF' && line[1] == '\xBB' && line[2] == '\xBF') {
        line = line.substr(3);
    }
    if (line.find("Vertex Format") != 0)
        throw std::runtime_error("Expected 'Vertex Format' header");

    // Parse vertex count
    std::getline(file, line);
    int vertexCount = std::stoi(line);

    // Parse vertices
    for (int i = 0; i < vertexCount; ++i) {
        std::getline(file, line);
        std::istringstream ss(line);
        VertexSJG v;
        char comma;
        ss >> v.x >> comma >> v.y >> comma >> v.z >> comma
            >> v.nx >> comma >> v.ny >> comma >> v.nz;
        mesh.vertices.push_back(v);
    }

    // Parse Index Format header
    std::getline(file, line);
    if (line.find("Index Format") != 0)
        throw std::runtime_error("Expected 'Index Format' header");

    // Parse index count
    std::getline(file, line);
    int indexCount = std::stoi(line);

    // Parse indices
    for (int i = 0; i < indexCount; ++i) {
        std::getline(file, line);
        std::istringstream ss(line);
        uint32_t v1, v2, v3;
        char comma;
        ss >> v1 >> comma >> v2 >> comma >> v3;
        mesh.indices.push_back(v1);
        mesh.indices.push_back(v2);
        mesh.indices.push_back(v3);
    }

    return mesh;
}
