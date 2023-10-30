#include "TexturedPlanet.h"

TexturedPlanet::TexturedPlanet()
	: TexturedPlanet({}, {}, {}, {}, 1.0f, {}, nullptr)
{
}

TexturedPlanet::TexturedPlanet(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
	const PhysicalUnit& radius, float scale, const std::string& identifier, std::shared_ptr<Texture> texture)
	: RenderablePlanet(position, velocity, mass, radius, scale, identifier)
	, Textured(texture)
{
	setUpMesh();
}

std::string TexturedPlanet::getSerializedTextureName() const
{
	return serializedTextureName;
}

void TexturedPlanet::render(SceneContext& sceneContext) const
{
	auto shader = sceneContext.shaderManager->useShader("texturedObjectShader");

	shader->useCamera(*sceneContext.cameraManager->getCurrentCamera());
	shader->useOmnipresentLight(*sceneContext.mainLight);
	shader->usePointLights(sceneContext.pointLights);
	shader->useMaterial(material);
	shader->useModel(getModelMatrix());

	texture->useTexture();
	mesh.useMesh();

	if (renderOrbit)
	{
		orbitInWorldSpace.render(sceneContext);
	}
}

SerializableObjectId TexturedPlanet::getSerializabledId() const
{
	return SerializableObjectId::TEXTURED_PLANET;
}

void TexturedPlanet::serializeFromBase(boost::archive::text_oarchive & outputArchive, std::shared_ptr<Serializable> obj)
{
	outputArchive & *std::dynamic_pointer_cast<TexturedPlanet>(obj);
}

void TexturedPlanet::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	RenderablePlanet::serialize(outputArchive, version);
	outputArchive& texture->getName();
}

void TexturedPlanet::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	RenderablePlanet::serialize(inputArchive, version);
	inputArchive& serializedTextureName;
}

void TexturedPlanet::setUpMesh()
{
	std::vector<GLfloat> vertices {};
	std::vector<GLfloat> normals {};
	std::vector<GLfloat> textureCoordinates {};
	std::vector<unsigned int> indices {};

	for (GLuint i = 0; i <= stacks; ++i)
	{
		for (GLuint j = 0; j <= sectors; ++j)
		{
			textureCoordinates.emplace_back(static_cast<GLfloat>(j) / sectors);
			textureCoordinates.emplace_back(static_cast<GLfloat>(i) / stacks);
		}
	}

	Sphere::createSphere(vertices, normals, indices);
	mesh.createMesh(vertices, indices, normals, textureCoordinates);
}

void TexturedPlanet::editViaGui()
{
	RenderablePlanet::editViaGui();
}
