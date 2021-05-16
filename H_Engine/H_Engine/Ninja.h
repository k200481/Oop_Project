#pragma once
#include "textureManager.h"
#include "image.h"
#include <vector>

class Ninja
{
private:
	enum class Direction {
		Right,
		Left
	};

public:
	// constructor
	Ninja(float initial_x, float initial_y, Graphics* graphics);
	// update position of ninja
	void Update(float delta_x, float delta_y);
	// move to the next frame (while skipping the idle frame)
	void AdvanceFrame();
	// updata sprite direction
	void UpdateImage();
	// draw sprite
	void Draw() {
		image[currentFrame].draw();
	}
private:
	// a truly horrible, list of initializations
	void InitializeTextures(Graphics* graphics);
private:
	// position and direction
	float x;
	float y;
	Direction direction = Direction::Right;

	float width;
	float height;

	// animation management
	int currentFrame = 0;
	static constexpr int runFrameCount = 10;
	static constexpr int idleFrameIndex = runFrameCount; // basically at the end of the vector
	static constexpr float holdDuration = 0.1f;
	float heldFor = 0.0f;
	std::vector<TextureManager> texManager;
	std::vector<Image> image;
	const float imageScale = 0.2f;
};

