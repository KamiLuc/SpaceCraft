#pragma once

#include <string>

#include "ImGuiEditableObjectsHandler.h"

class ImGuiEditableObjectsHandler;

class EditableViaImGui {
public:
	virtual void editViaImGui(ImGuiEditableObjectsHandler* objectHandler, unsigned int windowID) = 0;

private:
};

