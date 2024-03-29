#pragma once

#include "Brick.h"

extern RenderWindow window;

Brick::Brick(Vector2f position, Vector2f size) {
	this->position = position;
	this->size = size;
	sprite.setTexture(textureN);
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(this->size.x / textureN.getSize().x,
		this->size.y / textureN.getSize().y);
	sprite.setColor(Color(255, 255, 255, 255));
	type = normal;
}
Brick::Brick(Vector2f position) {
	this->position = position;
	size = (Vector2f)textureN.getSize();
	sprite.setTexture(textureN);
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(this->size.x / textureN.getSize().x,
		this->size.y / textureN.getSize().y);
	sprite.setColor(Color(255, 255, 255, 255));
	type = normal;
}
Brick::Brick() {
	size = (Vector2f)textureN.getSize();
	position = Vector2f(size.x / 2, size.y / 2);
	sprite.setTexture(textureN);
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setScale(this->size.x / textureN.getSize().x,
		this->size.y / textureN.getSize().y);
	sprite.setColor(Color(255, 255, 255, 255));
	type = normal;
}

void Brick::Draw() {
	switch (type)
	{
	case Brick::normal:
		sprite.setTexture(textureN);
		break;
	case Brick::strong:
		sprite.setTexture(hitPoint <= 0 ? textureB : textureS);
		break;
	case Brick::invincible:
		sprite.setTexture(textureI);
		break;
	case Brick::accelerate:
		sprite.setTexture(textureA);
		break;
	default:
		break;
	}
	sprite.setPosition(position);
	window.draw(sprite);
}

//Brick::~Brick() {
//
//}