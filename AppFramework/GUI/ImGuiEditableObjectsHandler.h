#pragma once

#include "EditableViaImGui.h"
#include "EditableViaImGui.h"

#include <vector>
#include <algorithm>
#include <imgui.h>
#include <memory>

class EditableViaImGui;

class ImGuiEditableObjectsHandler {
public:
	ImGuiEditableObjectsHandler() {}
	virtual ~ImGuiEditableObjectsHandler() {}

	virtual void deleteObject(std::shared_ptr<EditableViaImGui> object) = 0;
	virtual void deleteObject(EditableViaImGui* object) = 0;

	void addObjectToEdit(std::shared_ptr<EditableViaImGui> object);
	void addObjectToEdit(EditableViaImGui* object);
	void removeObjectFromEdit(std::shared_ptr<EditableViaImGui> object);
	void removeObjectFromEdit(EditableViaImGui* object);
	void update();

protected:
	std::vector<EditableViaImGui*> objectsToEdit;
};

