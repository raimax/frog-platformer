#include "GameObject.h"

GameObject::GameObject(Rectangle body) {
	this->body = body;
}

Rectangle GameObject::getBody() {
	return body;
}

void GameObject::draw() {
	DrawRectangle((int)body.x, (int)body.y, (int)body.width, (int)body.height, BLACK);
}

GameObject::~GameObject() {
	
}