#pragma once

#include "Vec2.h"
#include "textureManager.h"
#include "image.h"

#include <vector>

class Ship
{
public:
	Ship(float initial_x, float initial_y, Graphics* graphics);
	Ship(const Vec2<float>& initial_position, Graphics* graphics);

	void Update();
	// updates the velocity of the ship
	void SetVelocity(const Vec2<float>& new_velocity);
	// updates the direction of the ship while keeping movement speed constant
	void SetDirection(const Vec2<float>& new_direction);

	// get the ship's position
	Vec2<float> GetPosition() const {
		return position;
	}
	Vec2<float> GetDirection() const {
		return direction;
	}
	float GetMovementSpeed() const {
		return movementSpeed;
	}

	// draww the ship
	void Draw();
private:
	// initalize the frames
	void InitizlizeTextures(Graphics* graphics);
	// move to the next frame
	void AdvanceFrame();

	
private:
	// position
	Vec2<float> position;
	// velocity, also tracks direction
	Vec2<float> direction = { 1.0f,0.0f };
	// movement speed, 5.0f by default
	float movementSpeed = 5.0f;

	// drawing related
	int currentFrame = 0;
	static constexpr int frameCount = 5;
	static constexpr float holdDuration = 0.1f;
	float heldFor = 0.0f;
	std::vector<TextureManager> texManager;
	std::vector<Image> image;
	const float imageScale = 2.0f;
};

