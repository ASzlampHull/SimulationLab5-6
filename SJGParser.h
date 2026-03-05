#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <stdexcept>
#include "ModelParserDataTypes.h"

class SJGParser final {
private:

public:
	SJGParser() = default;
	~SJGParser() = default;
	MeshDataSJG ParseSJGFile(const std::string& filePath);
};