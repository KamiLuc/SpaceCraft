#include "RenderablePlanet.h"

RenderablePlanet::RenderablePlanet() : RenderablePlanet({}, {}, {}, {}, 1.0f, "")
{
}

RenderablePlanet::RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
								   const PhysicalUnit& radius, float scale, const std::string& identifier, unsigned int sectors, unsigned int stacks)
	: PhysicalObject(position, velocity, mass, scale)
	, Sphere(radius, stacks, sectors)
	, lastRealOrbitUpdate(0.0f)
	, renderOrbit(false)
	, orbitDataUpdateIntervalInSec(0.1f)
	, worldScale({ 1.495978707f, 10 })
	, orbitInWorldSpace(150, { 1.0f, 1.0f, 1.0f })
	, identifier(identifier)
{
}

glm::mat4 RenderablePlanet::getModelMatrix() const
{
	glm::mat4 model(1.0f);

	auto pos = position / worldScale;
	auto sc = (radius / worldScale) * scale;

	model = glm::translate(model, pos.getGlmVec());
	model = glm::scale(model, glm::vec3(sc, sc, sc));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	return model;
}

void RenderablePlanet::update(float simInSec)
{
	if (canMove)
	{
		position += velocity * simInSec;
	}
}

void RenderablePlanet::updateOrbit(float realTimeInSec)
{
	if (canMove)
	{
		if (lastRealOrbitUpdate >= orbitDataUpdateIntervalInSec && canMove)
		{
			orbitInWorldSpace.addPoint(getPositionInWorldSpace());
			lastRealOrbitUpdate = 0.0f;
		}
		else
		{
			lastRealOrbitUpdate += realTimeInSec;
		}
	}
}

float RenderablePlanet::getRadiusInWorldSpace() const
{
	return (radius / worldScale).getValue() * scale;
}

glm::vec3 RenderablePlanet::getPositionInWorldSpace() const
{
	return (position / worldScale).getGlmVec();
}

void RenderablePlanet::beginOutlineRender() const
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
}

void RenderablePlanet::endOutlineRender(const SceneContext& sceneContext, const BasicMesh& mesh) const
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);

	auto outlineShader = sceneContext.shaderManager->useShader("outlineShader");
	outlineShader->useCamera(*sceneContext.cameraManager->getCurrentCamera());
	outlineShader->useModel(getModelMatrix());
	mesh.useMesh();

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void RenderablePlanet::editViaGui()
{
	std::array<const char*, 3> xyz { "X", "Y", "Z" };
	std::array<const char*, 3> vxyz { "vX", "vY", "vZ" };

	ImGui::PushItemWidth(100.0f);
	ImGui::InputText("Identifier", const_cast<char*>(identifier.c_str()), sizeof(const_cast<char*>(identifier.c_str())));
	ImGui::SameLine();
	ImGui::Checkbox("Can move", &canMove);

	if (ImGui::CollapsingHeader("Position"))
	{
		for (size_t i = 0; i < xyz.size(); ++i)
		{
			ImGui::DragFloat(xyz[i], position.getData()[i].getBasePtr(), 0.01f);
			ImGui::SameLine();
			std::string exponentLabel { xyz[i] };
			exponentLabel += " Exponent";
			ImGui::InputInt(exponentLabel.c_str(), position.getData()[i].getExponentPtr());
		}
	}

	if (ImGui::CollapsingHeader("Velocity"))
	{
		for (size_t i = 0; i < vxyz.size(); ++i)
		{
			ImGui::DragFloat(vxyz[i], velocity.getData()[i].getBasePtr(), 0.01f);
			ImGui::SameLine();
			std::string exponentLabel { vxyz[i] };
			exponentLabel += " Exponent";
			ImGui::InputInt(exponentLabel.c_str(), velocity.getData()[i].getExponentPtr());
		}
	}

	if (ImGui::CollapsingHeader("Mass, Radius, Scale"))
	{
		ImGui::DragFloat("Mass", mass.getBasePtr(), 0.01f, 0.0f, 1000.0f);
		ImGui::SameLine();
		ImGui::InputInt("Mass Exponent", mass.getExponentPtr());
		ImGui::DragFloat("Radius", radius.getBasePtr(), 0.01f, 0.0f, 1000.0f);
		ImGui::SameLine();
		ImGui::InputInt("Radius Exponent", radius.getExponentPtr());
		ImGui::DragFloat("Scale", &scale, 0.1f, 1.0f, 10000.0f);
	}

	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::Separator();
		ImGui::Text("Material settings");
		ImGui::DragFloat("Specular intensity", material.getSpecularIntensityPtr(), 0.01f, 0.0f, 1024.0f);
		ImGui::DragFloat("Shininess", material.getShininessPtr(), 0.01f, 0.0f, 1024.0f);
	}

	ImGui::PopItemWidth();

	if (ImGui::CollapsingHeader("Orbit"))
	{
		ImGui::Checkbox("Render orbit", &renderOrbit);

		ImGui::PushItemWidth(291.0f);
		glm::vec3 color = orbitInWorldSpace.getColor();
		if (ImGui::ColorEdit3("Color", glm::value_ptr(color)))
		{
			orbitInWorldSpace.setColor(color);
		}
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(100.0f);
		int orbitMaxSize = static_cast<int>(orbitInWorldSpace.getMaxSize());
		if (ImGui::InputInt("Max size", &orbitMaxSize))
		{
			if (orbitMaxSize > 0)
			{
				orbitInWorldSpace.setMaxSize(orbitMaxSize);
			}
		}

		ImGui::DragFloat("Update interval", &orbitDataUpdateIntervalInSec, 0.01f, 0.01f, 100.0f);
		ImGui::PopItemWidth();
	}
}

void RenderablePlanet::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	outputArchive & canMove;
	outputArchive & identifier;
	outputArchive & mass;
	outputArchive & material;
	outputArchive & position;
	outputArchive & radius;
	outputArchive & scale;
	outputArchive & velocity;
}

void RenderablePlanet::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	inputArchive & canMove;
	inputArchive & identifier;
	inputArchive & mass;
	inputArchive & material;
	inputArchive & position;
	inputArchive & radius;
	inputArchive & scale;
	inputArchive & velocity;
}

void RenderablePlanet::setIdentifier(const std::string& identifier)
{
	this->identifier = identifier;
}

std::string RenderablePlanet::getIdentifier() const
{
	return identifier;
}
