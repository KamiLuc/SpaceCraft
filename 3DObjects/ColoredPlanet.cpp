#include "ColoredPlanet.h"

ColoredPlanet::ColoredPlanet()
	: ColoredPlanet({}, {}, {}, {}, 1.0f, {}, glm::vec4(1.0f))
{
}

ColoredPlanet::ColoredPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
							 float scale, const std::string& identifier, const glm::vec4& color)
	: RenderablePlanet(position, velocity, mass, radius, scale, identifier)
	, Colored(color)
{
	setUpMesh();
}

void ColoredPlanet::render(SceneContext& sceneContext) const
{
	auto shader = sceneContext.shaderManager->useShader("coloredObjectShader");

	shader->useCamera(*sceneContext.cameraManager->getCurrentCamera());
	shader->useOmnipresentLight(*sceneContext.mainLight);
	shader->usePointLights(sceneContext.pointLights);
	shader->useMaterial(material);
	shader->useModel(getModelMatrix());

	mesh.useMesh();

	if (renderOrbit)
	{
		orbitInWorldSpace.render(sceneContext);
	}
}

SerializableObjectId ColoredPlanet::getSerializabledId() const
{
	return SerializableObjectId::COLORED_PLANET;
}

void ColoredPlanet::serializeFromBase(boost::archive::text_oarchive & outputArchive, std::shared_ptr<Serializable> obj)
{
	outputArchive & *std::dynamic_pointer_cast<ColoredPlanet>(obj);
}

void ColoredPlanet::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	RenderablePlanet::serialize(outputArchive, version);
	outputArchive & color[0] & color[1] & color[2] & color[3];
}

void ColoredPlanet::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	RenderablePlanet::serialize(inputArchive, version);
	glm::vec4 serializedColor {};
	inputArchive& serializedColor[0] & serializedColor[1] & serializedColor[2] & serializedColor[3];
	setColor(serializedColor);
}

void ColoredPlanet::setColor(const glm::vec4 & color)
{
	this->color = color;
	mesh.bindSingleColor(color);
}

void ColoredPlanet::setUpMesh()
{
	std::vector<GLfloat> vertices {};
	std::vector<GLfloat> normals {};
	std::vector<unsigned int> indices {};
	std::vector<GLfloat> colors((stacks + 1) * (sectors + 1) * 4);

	for (size_t i = 0; i < colors.size() / 4; i += 1)
	{
		colors[i * 4] = color[0];
		colors[i * 4 + 1] = color[1];
		colors[i * 4 + 2] = color[2];
		colors[i * 4 + 3] = color[3];
	}

	Sphere::createSphere(vertices, normals, indices);
	mesh.createMesh(vertices, indices, normals, colors);
}

void ColoredPlanet::editViaGui()
{
	RenderablePlanet::editViaGui();

	ImGui::Separator();
	if (ImGui::ColorEdit4("Planet color", glm::value_ptr(color), ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar))
	{
		mesh.bindSingleColor(color);
	}
}
