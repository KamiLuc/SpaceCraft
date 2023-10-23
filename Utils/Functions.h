#pragma once

#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"

void calculateAverageNormals(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals);
glm::vec2 getObjectPositionOnScreen(const glm::vec3& objectPositionIn3dSpace, const glm::mat4& viewMatrix,
									const glm::mat4& projectionMatrix, const glm::vec2& screenSize);
