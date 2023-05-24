#pragma once

class EditableViaImGui {
public:

	//when edit finished, return false
	virtual bool editViaImGui() = 0;

private:
};