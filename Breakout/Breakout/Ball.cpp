#pragma once
#include "Ball.h"
//#include "VectorCalculation.h"
using namespace sf;

extern float Magnitude(Vector2f v);
extern Vector2f Normalize(Vector2f v);
extern Vector2f Lerp(Vector2f v1, Vector2f v2, float t);
extern float Dot(Vector2f v1, Vector2f v2);
extern float deltaTime;
extern RenderWindow window;

//Vector2f position, direction;
//float speed, radius;
//CircleShape ball;

Ball::Ball(Vector2f position, Vector2f direction, float radius, float velocity) {
	this->position = position;
	this->direction = Normalize(direction);
	this->radius = radius;
	this->originRadius = radius;
	this->velocity = velocity;
	ball.setOrigin(radius, radius);
	texture.loadFromFile("Ball_Texture.png");
	sprite.setTexture(texture);
	sprite.setOrigin(30, 30);
	isContinuousCollided = false;
}

void Ball::Update() {
	if (isContinuousCollided) {
		isContinuousCollided = false;
		return;
	}
	position = position + velocity * direction * deltaTime;
}


bool Ball::Collision(Paddle p) {
	//4 vertex of paddle
	Vector2f p1(p.position.x - p.size.x / 2, p.position.y - p.size.y / 2),
		p2(p.position.x + p.size.x / 2, p.position.y - p.size.y / 2),
		p3(p.position.x - p.size.x / 2, p.position.y + p.size.y / 2),
		p4(p.position.x + p.size.x / 2, p.position.y + p.size.y / 2);
	//ball hit top or bottom edge of paddle
	if (abs(position.y - p.position.y) < radius + p.size.y / 2
		&& abs(position.x - p.position.x) < p.size.x / 2) {
		if (position.y > p.position.y) {
			position.y = p.position.y + p.size.y / 2 + radius;
		}
		else {
			position.y = p.position.y - p.size.y / 2 - radius;
		}
		//change direction by position
		direction = Normalize(Lerp(Normalize(position - p.position), Vector2f(direction.x, -direction.y), 0.4));
		return true;
	}
	//ball hit left or right edge
	else if (abs(position.x - p.position.x) < radius + p.size.x / 2
		&& abs(position.y - p.position.y) < p.size.y / 2) {
		if (position.x > p.position.x) {
			position.x = p.position.x + p.size.x / 2 + radius;
		}
		else {
			position.x = p.position.x - p.size.x / 2 - radius;
		}
		//speed += 10.0f;
		direction.x *= -1;
		return true;
	}
	//ball hit 4 vertex of paddle
	else if (Magnitude(position - p1) < radius) {
		position = p1 + Normalize(position - p1) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p1)) * Normalize(position - p1);
		return true;
	}
	else if (Magnitude(position - p2) < radius) {
		position = p2 + Normalize(position - p2) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p2)) * Normalize(position - p2);
		return true;
	}
	else if (Magnitude(position - p3) < radius) {
		position = p3 + Normalize(position - p3) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p3)) * Normalize(position - p3);
		return true;
	}
	else if (Magnitude(position - p4) < radius) {
		position = p4 + Normalize(position - p4) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p4)) * Normalize(position - p4);
		return true;
	}
	return false;
}

bool Ball::Collision(Brick b) {
	//4 vertex of brick
	Vector2f p1(b.position.x - b.size.x / 2, b.position.y - b.size.y / 2),
		p2(b.position.x + b.size.x / 2, b.position.y - b.size.y / 2),
		p3(b.position.x - b.size.x / 2, b.position.y + b.size.y / 2),
		p4(b.position.x + b.size.x / 2, b.position.y + b.size.y / 2);
	//ball hit top or bottom edge of brick
	if (abs(position.y - b.position.y) < radius + b.size.y / 2
		&& abs(position.x - b.position.x) < b.size.x / 2) {
		if (position.y > b.position.y) {
			position.y = b.position.y + b.size.y / 2 + radius;
		}
		else {
			position.y = b.position.y - b.size.y / 2 - radius;
		}
		direction = Vector2f(direction.x, -direction.y);
		return true;
	}
	//ball hit left or right edge
	else if (abs(position.x - b.position.x) < radius + b.size.x / 2
		&& abs(position.y - b.position.y) < b.size.y / 2) {
		if (position.x > b.position.x) {
			position.x = b.position.x + b.size.x / 2 + radius;
		}
		else {
			position.x = b.position.x - b.size.x / 2 - radius;
		}
		//speed += 10.0f;
		direction.x *= -1;
		return true;
	}
	//ball hit 4 vertex of paddle
	else if (Magnitude(position - p1) < radius) {
		position = p1 + Normalize(position - p1) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p1)) * Normalize(position - p1);
		return true;
	}
	else if (Magnitude(position - p2) < radius) {
		position = p2 + Normalize(position - p2) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p2)) * Normalize(position - p2);
		return true;
	}
	else if (Magnitude(position - p3) < radius) {
		position = p3 + Normalize(position - p3) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p3)) * Normalize(position - p3);
		return true;
	}
	else if (Magnitude(position - p4) < radius) {
		position = p4 + Normalize(position - p4) * radius;
		direction = direction - 2 * Dot(direction, Normalize(position - p4)) * Normalize(position - p4);
		return true;
	}
	return false;
}

bool Ball::ContinuousCollision(Paddle p) {
	Vector2f hitPoint = position + direction * radius;
	//4 vertex of paddle
	Vector2f p1(p.position.x - p.size.x / 2, p.position.y - p.size.y / 2),
		p2(p.position.x + p.size.x / 2, p.position.y - p.size.y / 2),
		p3(p.position.x - p.size.x / 2, p.position.y + p.size.y / 2),
		p4(p.position.x + p.size.x / 2, p.position.y + p.size.y / 2);
	//ball hit top 
	if (0 < direction.y && hitPoint.y < p1.y	//ball comes from above
		&& p1.x < hitPoint.x + -direction.x / -direction.y * (p1.y - hitPoint.y)	//detect if ball will hit the paddle
		&& hitPoint.x + -direction.x / -direction.y * (p1.y - hitPoint.y) < p2.x) {
		if (Magnitude(Vector2f(-direction.x / -direction.y * (p1.y - hitPoint.y), p1.y - hitPoint.y)) < Magnitude(-direction * deltaTime * velocity)) {	//dectect if ball pass through the paddle
			position += direction * Magnitude(Vector2f(-direction.x / -direction.y * (p1.y - hitPoint.y), p1.y - hitPoint.y));
			direction = Normalize(Lerp(Normalize(position - p.position), Vector2f(direction.x, -direction.y), 0.3));
			isContinuousCollided = true;
			return true;
		}
	}
	//ball hit bottom
	if (direction.y < 0 && p3.y < hitPoint.y 	//ball comes from below
		&& p3.x < hitPoint.x + direction.x / direction.y * (p3.y - hitPoint.y)	//detect if ball will hit the paddle
		&& hitPoint.x + direction.x / direction.y * (p3.y - hitPoint.y) < p4.x) {
		if (Magnitude(Vector2f(-direction.x / -direction.y * (p3.y - hitPoint.y), p3.y - hitPoint.y)) < Magnitude(-direction * deltaTime * velocity)) {	//dectect if ball pass through the paddle
			position += direction * Magnitude(Vector2f(-direction.x / -direction.y * (p3.y - hitPoint.y), p3.y - hitPoint.y));
			direction = Normalize(Lerp(Normalize(position - p.position), Vector2f(direction.x, -direction.y), 0.3));
			isContinuousCollided = true;
			return true;
		}
	}
	isContinuousCollided = false;
	return false;
}


void Ball::Draw() {
	ball.setRadius(radius);
	ball.setPosition(position);
	sprite.setPosition(position);
	sprite.setScale(radius / 25, radius / 25);
	//win.draw(ball);
	window.draw(sprite);
}

