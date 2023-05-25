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
	previewPlanets()
{}

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

	this->update();

	for (const auto& planet : previewPlanets) {
		this->spaceSimulation.renderObject(*planet);
	}
}

bool SpaceSimulationImGui::shouldRenderCoordinateSystemAxis()
{
	return renderCoordinateSystemAxis;
}

void SpaceSimulationImGui::createPreviewColoredPlanet()
{
	auto temp = this->spaceSimulation.createColoredPlanet(
		{ {0.0f, 0.0f, 0.0f}, 0 },
		{ {0.0f, 0.0f, 0.0f}, 0 },
		0.0f,
		1.0f,
		"Planet",
		{ 0.3f, 0.2f, 0.8f, 1.0f });

	this->previewPlanets.emplace_back(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createPreviewTexturedPlanet()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {0.0f, 0.0f, 0.0f}, 0 },
		{ {0.0f, 0.0f, 0.0f}, 0 },
		0.0f,
		1.0f,
		"Planet",
		*this->textureManager.getTexture(this->textureManager.getTexturesNames()[0]));

	this->previewPlanets.emplace_back(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::showFileMenu()
{
}


void SpaceSimulationImGui::showObjectsMenu()
{
	if (ImGui::Button("Create colored planet")) {
		this->createPreviewColoredPlanet();
	}
	if (ImGui::Button("Create textured planet")) {
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
