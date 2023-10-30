#pragma once

#include "imgui.h"

#include <list>
#include <string>

class EditableViaGui;

class ObjectEditor
{
public:
	ObjectEditor(const std::string& windowTitle, const ImVec2& windowMinSize, const ImVec2& windowMaxSize);
	virtual ~ObjectEditor();

	void addObjectToEdit(EditableViaGui* editableObject);
	void removeObjectFromEdit(EditableViaGui* editableObject);
	void draw();

protected:
	virtual void internalUpdate(EditableViaGui*);

	std::list<std::pair<EditableViaGui*, bool>> editableObjectsPairs;

private:
	void begin(unsigned int index, std::pair<EditableViaGui*, bool>& objectPair);
	bool end();

	std::string windowTitle;
	ImVec2 windowMinSize;
	ImVec2 windowMaxSize;
};
