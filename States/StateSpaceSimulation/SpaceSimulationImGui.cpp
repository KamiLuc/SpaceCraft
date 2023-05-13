#include "SpaceSimulationImGui.h"
#include <imgui.h>

SpaceSimulationImGui::SpaceSimulationImGui(CameraSettings* arcBallCameraSettings, CameraSettings* fpsCameraSettings, LightSettings* mainLightSettings)
	: fpsCameraSettings(fpsCameraSettings), arcBallCameraSettings(arcBallCameraSettings), mainLightSettings(mainLightSettings), renderCoordinateSystemAxis(false)
{
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
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

bool SpaceSimulationImGui::shouldRenderCoordinateSystemAxis()
{
	return renderCoordinateSystemAxis;
}

void SpaceSimulationImGui::showFileMenu()
{
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

void SpaceSimulationImGui::showObjectsMenu()
{
}
