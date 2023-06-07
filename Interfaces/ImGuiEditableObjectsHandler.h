#pragma once

#include "EditableViaImGui.h"

#include <vector>
#include <algorithm>
#include <imgui.h>

class EditableViaImGui;

class ImGuiEditableObjectsHandler {
public:
	ImGuiEditableObjectsHandler() {}
	virtual ~ImGuiEditableObjectsHandler() {}

	void addObjectToEdit(EditableViaImGui* object);
	void removeObjectFromEdit(EditableViaImGui* object);
	void update();

protected:
	std::vector<EditableViaImGui*> objectsToEdit;
};

