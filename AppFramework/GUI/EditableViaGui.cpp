#include "EditableViaGui.h"
#include "ObjectEditor.h"

EditableViaGui::~EditableViaGui()
{
}

void EditableViaGui::startEditing()
{
	if (editor)
	{
		editor->addObjectToEdit(this);
	}
}

void EditableViaGui::unregisterEditor()
{
	if (editor)
	{
		editor->removeObjectFromEdit(this);
		this->editor = nullptr;
	}
}

bool EditableViaGui::isBeingEdited() const
{
	if (editor)
	{
		return editor->isBeingEdited(this);
	}

	return false;
}
