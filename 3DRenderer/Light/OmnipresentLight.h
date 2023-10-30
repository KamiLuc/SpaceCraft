#pragma once

#include "Light.h"
#include "AppFramework/GUI/EditableViaGui.h"

#include <glm/gtc/type_ptr.hpp>

class OmnipresentLight : public Light, public EditableViaGui
{
public:
	OmnipresentLight(const glm::vec3& color, GLfloat ambientIntenisty);

private:
	void editViaGui() override;
};

