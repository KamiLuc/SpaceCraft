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

	void draw();
	void addObjectToEdit(EditableViaGui* editableObject);
	void removeObjectFromEdit(EditableViaGui* editableObject);
	bool isBeingEdited(const EditableViaGui* editableObject) const;
	bool shouldDraw();

protected:
	virtual void internalUpdate(EditableViaGui*);

	std::list<std::pair<EditableViaGui*, bool>> editableObjectsPairs;

private:
	void begin(unsigned int index, std::pair<EditableViaGui*, bool>& objectPair);
	void end();

	std::string windowTitle;
	ImVec2 windowMinSize;
	ImVec2 windowMaxSize;
	bool breakDrawLoop;
};
