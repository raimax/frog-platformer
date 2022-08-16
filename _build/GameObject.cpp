#include "GameObject.h"

GameObject::GameObject(Rectangle body) {
	this->position.x = body.x;
	this->position.y = body.y;
	this->hitBox = body;
}

Rectangle* GameObject::getHitBox() {
	return &hitBox;
}

void GameObject::update() {

}

void GameObject::draw() {
	//DrawRectanglePro(hitBox, Vector2{0, 0}, 0.0f, BLACK);
}

GameObject::~GameObject() {
	
}