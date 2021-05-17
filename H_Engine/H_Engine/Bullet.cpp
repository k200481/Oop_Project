#include "Bullet.h"

bool Bullet::animationsInitialized = false;
const wchar_t* Bullet::file = L"bullet.png";
TextureManager Bullet::texManager;
Image Bullet::img;

void Bullet::InitBulletAnimation(Graphics* graphics) {
	// initialize the texture manager
	if (!texManager.initialize(graphics, file)) {
		throw GameError(gameErrorNS::FATAL_ERROR, L"Error initializing bullet");
	}
	// initialize basic info for the bullet img
	img.initialize(graphics, 0, 0, 0, &texManager);
	img.setDegrees(270.0f);
	img.setScale(1.0f);

	animationsInitialized = true;
}

Bullet::Bullet(const Vec2& position)
	:
	position(position)
{
	if (!animationsInitialized) {
		throw GameError(gameErrorNS::FATAL_ERROR, L"Bullet image not initialized");
	}
}

void Bullet::UpdatePosition(const Vec2& velocity) {
	// update position
	position += velocity;

	// will automatically be destroyed on reaching game height
	if (int(position.y) >= GAME_HEIGHT) {
		isDestroyed = true;
	}
}

float Bullet::GetX() const {
	return position.x;
}

float Bullet::GetY() const {
	return position.y;
}

Vec2 Bullet::GetPosition() const {
	return position;
}

void Bullet::BulletDestroyed() {
	isDestroyed = true;
}

bool Bullet::IsDestroyed() const {
	return isDestroyed;
}

void Bullet::Draw() {
	// make sure bullet isn't already destroyed
	if (!IsDestroyed()) {
		// update the x and y of image before rendering
		img.setX(position.x);
		img.setY(position.y);
		// draw
		img.draw();
	}
}
