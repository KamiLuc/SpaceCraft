#include "Functions.h"

void calculateAverageNormals(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals)
{
	normals.clear();
	normals.resize(vertices.size(), 0.0f);

	for (size_t i = 0; i < indices.size(); i += 3)
	{
		glm::vec3 v1(vertices[3 * indices[i]], vertices[3 * indices[i] + 1], vertices[3 * indices[i] + 2]);
		glm::vec3 v2(vertices[3 * indices[i + 1]], vertices[3 * indices[i + 1] + 1], vertices[3 * indices[i + 1] + 2]);
		glm::vec3 v3(vertices[3 * indices[i + 2]], vertices[3 * indices[i + 2] + 1], vertices[3 * indices[i + 2] + 2]);
		glm::vec3 faceNormal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

		normals[3 * indices[i]] += faceNormal.x;
		normals[3 * indices[i] + 1] += faceNormal.y;
		normals[3 * indices[i] + 2] += faceNormal.z;
		normals[3 * indices[i + 1]] += faceNormal.x;
		normals[3 * indices[i + 1] + 1] += faceNormal.y;
		normals[3 * indices[i + 1] + 2] += faceNormal.z;
		normals[3 * indices[i + 2]] += faceNormal.x;
		normals[3 * indices[i + 2] + 1] += faceNormal.y;
		normals[3 * indices[i + 2] + 2] += faceNormal.z;
	}

	for (size_t i = 0; i < normals.size(); i += 3)
	{
		glm::vec3 normal(normals[i], normals[i + 1], normals[i + 2]);
		normal = glm::normalize(normal);
		normals[i] = normal.x;
		normals[i + 1] = normal.y;
		normals[i + 2] = normal.z;
	}

}
