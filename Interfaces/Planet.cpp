#include "Planet.h"

Planet::Planet()
{
}

void Planet::update(float timeInSec)
{
	if (canMove)
	{
		position += velocity * timeInSec;
	}
}

void Planet::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui)
{
	std::array<const char*, 3> xyz { "X", "Y", "Z" };
	std::array<const char*, 3> vxyz { "vX", "vY", "vZ" };

	if (beginImGui)
	{
		ImGui::Begin(("Edit planet " + std::to_string(windowID)).c_str());
	}

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

	if (beginImGui)
	{
		ImGui::End();
	}
}