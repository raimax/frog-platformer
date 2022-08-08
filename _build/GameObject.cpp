#include "GameObject.h"

GameObject::GameObject(Rectangle body) {
	this->body = body;
}

Rectangle GameObject::getBody() {
	return body;
}

void GameObject::draw() {
	DrawRectangle(body.x, body.y, body.width, body.height, BLACK);
}

GameObject::~GameObject() {
	
}