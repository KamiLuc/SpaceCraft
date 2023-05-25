#pragma once

#include "EditableViaImGui.h"

#include <vector>
#include <algorithm>

class EditableViaImGui;

class ImGuiEditableObjectsHandler {
public:
	ImGuiEditableObjectsHandler() {}

	void addObjectToEdit(EditableViaImGui* object);
	void removeObjectFromEdit(EditableViaImGui* object);
	void update();

protected:
	std::vector<EditableViaImGui*> objectsToEdit;
};

