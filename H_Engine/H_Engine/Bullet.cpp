#include "Bullet.h"

bool Bullet::animationsInitialized = false;
const wchar_t* Bullet::file = L"bullet.png";
TextureManager Bullet::texManager;
Image Bullet::img;

void Bullet::InitBulletAnimation(Graphics* graphics) {
	// initialize the texture manager
	if (!texManager.initialize(graphics, file)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	}
	// initialize basic info for the bullet img
	img.initialize(graphics, 0, 0, 0, &texManager);
	img.setDegrees(270.0f);
	img.setScale(1.0f);

	animationsInitialized = true;
}

Bullet::Bullet(float center_x, float center_y)
	:
	x(center_x),
	y(center_y)
{
	if (!animationsInitialized) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bullet image not initialized"));
	}
}

void Bullet::UpdatePosition(float delta_x, float delta_y) {
	// update x and y
	x += delta_x;
	y += delta_y;

	// will automatically be destroyed on reaching game height
	if (y >= GAME_HEIGHT) {
		isDestroyed = true;
	}
}

float Bullet::GetX() {
	return x;
}

float Bullet::GetY() {
	return y;
}

void Bullet::BulletDestroyed() {
	isDestroyed = true;
}

bool Bullet::IsDestroyed() {
	return isDestroyed;
}

void Bullet::Draw() {
	// make sure bullet isn't already destroyed
	if (!IsDestroyed()) {
		// update the x and y of image before rendering
		img.setX(x);
		img.setY(y);
		// draw
		img.draw();
	}
}
