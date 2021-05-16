#pragma once
#include "textureManager.h"
#include "image.h"
#include "Constant.h"

class Bullet
{
public:
	static void InitBulletAnimation(Graphics* graphics) {
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

	Bullet(float center_x, float center_y) 
		:
		x(center_x),
		y(center_y)
	{
		if (!animationsInitialized) {
			throw(GameError(gameErrorNS::FATAL_ERROR, "Bullet image not initialized"));
		}
	}

	void UpdatePosition(float delta_x, float delta_y) {
		// update x and y
		x += delta_x;
		y += delta_y;	

		// will automatically be destroyed on reaching game height
		if (y >= GAME_HEIGHT) {
			isDestroyed = true;
		}
	}

	float GetX() {
		return x;
	}
	float GetY() {
		return y;
	}

	void BulletDestroyed() {
		isDestroyed = true;
	}
	bool IsDestroyed() {
		return isDestroyed;
	}

	void Draw() {
		// make sure bullet isn't already destroyed
		if (!IsDestroyed()) {
			// update the x and y of image before rendering
			img.setX(x);
			img.setY(y);
			// draw
			img.draw();
		}
	}

private:
	static bool animationsInitialized;
	
	// center of the bulet
	float x;
	float y;
	// width and height of bullet, will be used to create rect for collision detection
	const float width = 58.0f;
	const float height = 36.0f;
	// delete the bullet when this becomes true
	bool isDestroyed = false;
	// static pointers for bullet rendering
	static const wchar_t* file;
	static TextureManager texManager;
	static Image img;
};