#include "ImGuiEditableObjectsHandler.h"

#include "EditableViaImGui.h"

void ImGuiEditableObjectsHandler::addObjectToEdit(std::shared_ptr<EditableViaImGui> object)
{
	addObjectToEdit(object.get());
}

void ImGuiEditableObjectsHandler::addObjectToEdit(EditableViaImGui* object)
{
	if (std::find(objectsToEdit.begin(), objectsToEdit.end(), object) == objectsToEdit.end()) {
		objectsToEdit.push_back(object);
	}
}

void ImGuiEditableObjectsHandler::removeObjectFromEdit(std::shared_ptr<EditableViaImGui> object)
{
	removeObjectFromEdit(object.get());
}

void ImGuiEditableObjectsHandler::removeObjectFromEdit(EditableViaImGui* object)
{
	auto f = std::find(objectsToEdit.begin(), objectsToEdit.end(), object);
	if (f != objectsToEdit.end()) {
		objectsToEdit.erase(f);
	}
}

void ImGuiEditableObjectsHandler::update()
{
	for (unsigned int i = 0; i < objectsToEdit.size(); i++) {
		objectsToEdit[i]->editViaImGui(*this, i);
	}
}