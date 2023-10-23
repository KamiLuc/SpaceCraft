#pragma once

#include "AppFramework/GUI/EditableViaImGui.h"
#include "Light.h"

#include <glm/gtc/type_ptr.hpp>

class OmnipresentLight : public Light, public EditableViaImGui
{
public:
	OmnipresentLight(const glm::vec3& color, GLfloat ambientIntenisty);
	virtual ~OmnipresentLight();

	void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui) override;

private:
};

