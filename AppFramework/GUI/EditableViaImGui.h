#pragma once

#include <string>

#include "ImGuiEditableObjectsHandler.h"
#include "imgui.h"

class ImGuiEditableObjectsHandler;

class EditableViaImGui {
public:
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui) = 0;
	virtual ~EditableViaImGui() {}

private:
};

