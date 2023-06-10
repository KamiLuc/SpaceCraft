#pragma once

#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"

void calculateAverageNormals(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals);