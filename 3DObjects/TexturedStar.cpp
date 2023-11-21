#include "TexturedStar.h"

#include "Utils/Functions.h"

TexturedStar::TexturedStar()
{
}

TexturedStar::TexturedStar(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit & mass,
						   const PhysicalUnit & radius, float scale, const std::string & identifier, std::shared_ptr<Texture> texture)
	: TexturedPlanet(position, velocity, mass, radius, scale, identifier, texture)
	, PointLight({ 1.0f, 1.0f, 1.0f }, 0.0f, TexturedPlanet::getPositionInWorldSpace(), 1.0f,
				 std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min())
{
}

void TexturedStar::render(SceneContext& sceneContext) const
{
	bool drawOutline = this->isBeingEdited();
	if (drawOutline)
	{
		beginOutlineRender();
	}

	auto shader = sceneContext.shaderManager->useShader("texturedStarShader");
	shader->useCamera(*sceneContext.cameraManager->getCurrentCamera());
	shader->useOmnipresentLight(*sceneContext.mainLight);
	shader->usePointLights(sceneContext.pointLights);
	shader->useMaterial(material);
	shader->useModel(getModelMatrix());
	glUniform1f(shader->getUniformLocations().timePassed, sceneContext.lifeTimeInSec);
	texture->useTexture();
	mesh.useMesh();

	if (drawOutline)
	{
		endOutlineRender(sceneContext, mesh);
	}

	if (renderOrbit)
	{
		orbitInWorldSpace.render(sceneContext);
	}
}

SerializableObjectId TexturedStar::getSerializabledId() const
{
	return SerializableObjectId::TEXTURED_STAR;
}

void TexturedStar::serializeFromBase(boost::archive::text_oarchive & outputArchive, std::shared_ptr<Serializable> obj)
{
	outputArchive & *std::dynamic_pointer_cast<TexturedStar>(obj);
}

void TexturedStar::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	TexturedPlanet::serialize(outputArchive, version);

	outputArchive & diffuseIntensity;
	outputArchive & ambientIntensity;
	outputArchive & exponent;
	outputArchive & linear;
	outputArchive & constant;
	outputArchive & color[0] & color[1] & color[2];
}

void TexturedStar::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	TexturedPlanet::serialize(inputArchive, version);

	inputArchive & diffuseIntensity;
	inputArchive & ambientIntensity;
	inputArchive & exponent;
	inputArchive & linear;
	inputArchive & constant;

	glm::vec3 serializedColor {};
	inputArchive& serializedColor[0] & serializedColor[1] & serializedColor[2];
	color = serializedColor;
	PointLight::position = getPositionInWorldSpace();
}

void TexturedStar::editViaGui()
{
	TexturedPlanet::editViaGui();

	if (ImGui::CollapsingHeader("Emited light"))
	{
		ImGui::PushItemWidth(291.0f);
		glm::vec3 color = PointLight::color;
		if (ImGui::ColorEdit3("Color", glm::value_ptr(color)))
		{
			PointLight::color = color;
		}
		ImGui::PopItemWidth();

		auto di = static_cast<float>(PointLight::diffuseIntensity);

		ImGui::PushItemWidth(100.0f);
		ImGui::DragFloat("Diffuse intensity", &di, 0.01f, 0.01f, 100.0f);
		ImGui::PopItemWidth();

		PointLight::diffuseIntensity = di;
	}

	PointLight::position = getPositionInWorldSpace();
}
