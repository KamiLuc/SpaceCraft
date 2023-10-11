#pragma once

#include "3DRenderer/Texture/Texture.h"

#include <memory>

class Textured {
public:
	Textured() : texture(nullptr) {}
	Textured(std::shared_ptr<Texture> texture) : texture(texture) {}
	virtual ~Textured() {}

	void setTexture(std::shared_ptr<Texture> texture) { this->texture = texture; }
	const std::shared_ptr<const Texture> getTexture() const { return texture; }

protected:
	std::shared_ptr<const Texture> texture;
};