#include "ObjectEditor.h"
#include "EditableViaGui.h"


ObjectEditor::ObjectEditor(const std::string& windowTitle, const ImVec2& windowMinSize, const ImVec2& windowMaxSize)
	: windowTitle(windowTitle)
	, windowMinSize(windowMinSize)
	, windowMaxSize(windowMaxSize)
{
}

ObjectEditor::~ObjectEditor()
{
}

void ObjectEditor::addObjectToEdit(EditableViaGui* editableObject)
{
	for (auto it = editableObjectsPairs.begin(); it != editableObjectsPairs.end(); ++it)
	{
		if (it->first == editableObject)
		{
			return;
		}
	}
	editableObjectsPairs.push_back({ editableObject, true });
}

void ObjectEditor::removeObjectFromEdit(EditableViaGui* editableObject)
{
	for (auto it = editableObjectsPairs.begin(); it != editableObjectsPairs.end(); ++it)
	{
		if (it->first == editableObject)
		{
			editableObjectsPairs.erase(it);
			return;
		}
	}
}

void ObjectEditor::draw()
{
	unsigned int counter = 1;
	for (auto& object : editableObjectsPairs)
	{
		begin(counter++, object);
		internalUpdate(object.first);
		if (end())
		{
			break;
		}
	}
}

void ObjectEditor::internalUpdate(EditableViaGui*)
{
}

void ObjectEditor::begin(unsigned int index, std::pair<EditableViaGui*, bool>& objectPair)
{
	ImGui::SetNextWindowSizeConstraints(windowMinSize, windowMaxSize);
	std::string indexS = index != 0 ? std::to_string(index) : "";
	std::string titleS = windowTitle + " " + indexS;
	ImGui::Begin(titleS.c_str(), &objectPair.second);
	if (objectPair.second && objectPair.first)
	{
		objectPair.first->editViaGui();
	}
}

bool ObjectEditor::end()
{
	bool removed = false;
	editableObjectsPairs.remove_if([&](const auto& el)
								   {
									   removed = true;
									   return !el.second;
								   });
	ImGui::End();
	return removed;
}
