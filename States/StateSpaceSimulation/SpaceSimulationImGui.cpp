#include "SpaceSimulationImGui.h"
#include <imgui.h>
#include <vector>

SpaceSimulationImGui::SpaceSimulationImGui(StateSpaceSimulation& spaceSimulation, CameraSettings* arcBallCameraSettings, CameraSettings* fpsCameraSettings,
	LightSettings* mainLightSettings, TextureManager& textureManager)
	:
	spaceSimulation(spaceSimulation),
	fpsCameraSettings(fpsCameraSettings),
	arcBallCameraSettings(arcBallCameraSettings),
	mainLightSettings(mainLightSettings),
	textureManager(textureManager),
	renderCoordinateSystemAxis(false),
	newObjectPosition{ 0.0f, 0.0f, 0.0f },
	newObjectPositionExponent(1),
	newObjectVelocity{ 0.0f, 0.0f, 0.0f },
	newObjectVelocityExponent(1),
	newObjectMass(1.0f),
	newObjectMassExponent(1),
	newObjectScale(1.0f),
	newObjectIdentifier{ "planet" },
	newObjectTexture{ "" },
	newObjectTextureIndex(0),
	objectToEditIndex(0),
	newObjectColor{ 0.2f, 0.8f, 0.4f, 1.0f },
	b_showCreateTexturedPlanetWindow(false),
	b_showCreateColoredPlanetWindow(false),
	previewPlanet(nullptr)
{
	this->textures = textureManager.getTexturesNames();
}

void SpaceSimulationImGui::draw()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			showFileMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings")) {
			showSettingsMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Objects")) {
			showObjectsMenu();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (b_showCreateColoredPlanetWindow) {
		showCreateColoredPlanetWindow();
	}

	if (b_showCreateTexturedPlanetWindow) {
		showCreateTexturedPlanetWindow();
	}

	if (previewPlanet) {
		this->spaceSimulation.renderObject(*previewPlanet);
	}
}

bool SpaceSimulationImGui::shouldRenderCoordinateSystemAxis()
{
	return renderCoordinateSystemAxis;
}

void SpaceSimulationImGui::createPreviewColoredPlanet()
{
	this->previewPlanet = this->spaceSimulation.createColoredPlanet(
		glm::vec<3, Measure>({ newObjectPosition[0], newObjectPositionExponent }, { newObjectPosition[1], newObjectPositionExponent }, { newObjectPosition[2], newObjectPositionExponent }),
		glm::vec<3, Measure>({ newObjectVelocity[0],  newObjectVelocityExponent }, { newObjectVelocity[1],  newObjectVelocityExponent }, { newObjectVelocity[2],  newObjectVelocityExponent }),
		{ newObjectMass, newObjectMassExponent },
		newObjectScale,
		newObjectIdentifier,
		glm::vec4(newObjectColor[0], newObjectColor[1], newObjectColor[2], newObjectColor[3])
	);
}

void SpaceSimulationImGui::createPreviewTexturedPlanet()
{
	this->previewPlanet = this->spaceSimulation.createTexturedPlanet(
		glm::vec<3, Measure>({ newObjectPosition[0], newObjectPositionExponent }, { newObjectPosition[1], newObjectPositionExponent }, { newObjectPosition[2], newObjectPositionExponent }),
		glm::vec<3, Measure>({ newObjectVelocity[0],  newObjectVelocityExponent }, { newObjectVelocity[1],  newObjectVelocityExponent }, { newObjectVelocity[2],  newObjectVelocityExponent }),
		{ newObjectMass, newObjectMassExponent },
		newObjectScale,
		newObjectIdentifier,
		*textureManager.getTexture(this->textures[this->newObjectTextureIndex])
	);
}

void SpaceSimulationImGui::showFileMenu()
{
}

void SpaceSimulationImGui::showBaseCreatePlanet()
{
	ImGui::InputText("Identifier", newObjectIdentifier, sizeof(newObjectIdentifier));
	previewPlanet->setIdentifier(std::string(newObjectIdentifier));
	ImGui::Separator();

	ImGui::InputFloat3("Position", newObjectPosition);
	ImGui::InputInt("Position", &newObjectPositionExponent);
	previewPlanet->setPosition(glm::vec3(newObjectPosition[0], newObjectPosition[1], newObjectPosition[2]), newObjectPositionExponent);
	ImGui::Separator();

	ImGui::InputFloat3("Velocity", newObjectVelocity);
	ImGui::InputInt("Velocity", &newObjectVelocityExponent);
	ImGui::Separator();

	ImGui::InputFloat("Mass", &newObjectMass);
	ImGui::InputInt("Mass", &newObjectMassExponent);
	previewPlanet->setMass({ newObjectMass, newObjectMassExponent });
	ImGui::Separator();

	ImGui::SliderFloat("Scale", &newObjectScale, 0.01f, 10.0f);
	previewPlanet->setScale(newObjectScale);
	ImGui::Separator();
}

void SpaceSimulationImGui::showCreateTexturedPlanetWindow()
{
	ImGui::Begin("Textured planet");
	this->showBaseCreatePlanet();

	if (ImGui::BeginCombo("Texture", textures[newObjectTextureIndex].c_str()))
	{
		for (int i = 0; i < textures.size(); i++)
		{
			const bool isSelected = (newObjectTextureIndex == i);
			if (ImGui::Selectable(textures[i].c_str(), isSelected))
			{
				newObjectTextureIndex = i;
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	ImGui::Separator();
	if (ImGui::Button("Create", { ImGui::GetWindowWidth(), 20 })) {
		//createPreviewTexturedPlanet();
	}
	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		b_showCreateTexturedPlanetWindow = false;
	}

	ImGui::End();
}

void SpaceSimulationImGui::showCreateColoredPlanetWindow()
{
	this->previewPlanet->editViaImGui();
	/*
	ImGui::Begin("Colored planet");
	this->showBaseCreatePlanet();

	ImGui::ColorPicker4("Planet color", newObjectColor, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar);

	ImGui::Separator();
	if (ImGui::Button("Create", { ImGui::GetWindowWidth(), 20 })) {
		//createPreviewColoredPlanet();
	}
	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		b_showCreateColoredPlanetWindow = false;
	}

	ImGui::End();
	*/
}

void SpaceSimulationImGui::showObjectsMenu()
{
	if (ImGui::Button("Create colored planet")) {
		b_showCreateColoredPlanetWindow = true;
		b_showCreateTexturedPlanetWindow = false;
		this->createPreviewColoredPlanet();
	}
	if (ImGui::Button("Create textured planet")) {
		b_showCreateTexturedPlanetWindow = true;
		b_showCreateColoredPlanetWindow = false;
		this->createPreviewTexturedPlanet();
	}

	ImGui::Separator();
}

void SpaceSimulationImGui::showSettingsMenu()
{
	ImGui::Checkbox("Render coordinate system axis", &renderCoordinateSystemAxis);
	ImGui::Separator();
	if (arcBallCameraSettings != nullptr) {
		if (ImGui::BeginMenu(arcBallCameraSettings->cameraName.c_str())) {
			ImGui::SliderFloat("Move speed", &arcBallCameraSettings->moveSpeed, 0.0f, 10.0f);
			ImGui::SliderFloat("Turn speed", &arcBallCameraSettings->turnSpeed, 0.0f, 3.0f);
			ImGui::EndMenu();
		}
	}
	if (fpsCameraSettings != nullptr) {
		if (ImGui::BeginMenu(fpsCameraSettings->cameraName.c_str())) {
			ImGui::SliderFloat("Move speed", &fpsCameraSettings->moveSpeed, 0.0f, 30.0f);
			ImGui::SliderFloat("Turn speed", &fpsCameraSettings->turnSpeed, 0.0f, 1.5f);
			ImGui::EndMenu();
		}
	}
	ImGui::Separator();
	if (mainLightSettings != nullptr) {
		if (ImGui::BeginMenu("Main Light")) {
			ImGui::SliderFloat("Intensity", &mainLightSettings->ambientIntensity, 0.0f, 1.0f);
			float color[] = { mainLightSettings->color.r, mainLightSettings->color.g, mainLightSettings->color.b };
			ImGui::ColorEdit3("Color", color, ImGuiColorEditFlags_Float);
			mainLightSettings->color.r = color[0];
			mainLightSettings->color.g = color[1];
			mainLightSettings->color.b = color[2];
			ImGui::Separator();
			ImGui::SliderFloat("Diffuse intensity", &mainLightSettings->diffuseIntensity, 0.0f, 1.0f);
			ImGui::SliderFloat("X direction", &mainLightSettings->direction.x, -1.0f, 1.0f);
			ImGui::SliderFloat("Y direction", &mainLightSettings->direction.y, -1.0f, 1.0f);
			ImGui::SliderFloat("Z direction", &mainLightSettings->direction.z, -1.0f, 1.0f);
			ImGui::EndMenu();
		}
	}
}
