#pragma once

#include "imgui.h"

class ObjectEditor;

class EditableViaGui
{
public:
	EditableViaGui() : editor(nullptr) {};
	virtual ~EditableViaGui();

	void startEditing();
	void registerEditor(ObjectEditor* editor) { this->editor = editor; }
	void unregisterEditor();
	bool isBeingEdited() const;

	virtual void editViaGui() = 0;

protected:
	ObjectEditor* editor;
};
