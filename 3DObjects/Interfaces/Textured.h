#pragma once

#include "../../3DRenderer/Texture/Texture.h"

class Textured {
public:
	Textured(const Texture& texture) : texture(&texture) {};
	virtual ~Textured() {}

	void setTexture(const Texture& texture) { this->texture = &texture; }
	const Texture& getTexture() const { return *texture; }

protected:
	const Texture* texture;
};