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
	Ninja(float initial_x, float initial_y, Graphics* graphics)
		:
		x(initial_x),
		y(initial_y)
	{
		// initialize all the runs frames
		wchar_t str[] = L"Run__000.png";
		for (int i = 0; i <= runFrameCount; i++) {
			str[7] = '0' + i;
			texManager.emplace_back();
		}

		InitializeTextures(graphics);

		// initialize images
		for (int i = 0; i <= runFrameCount; i++) {
			image.emplace_back();
			image[i].initialize(graphics, 0, 0, 0, &texManager[i]);
			image[i].setScale(imageScale);
		}

		width = image[0].getWidth() * imageScale;
		height = image[0].getHeight() * imageScale;
	}

	void Update(float delta_x, float delta_y) {
		// update position
		x += delta_x;
		y += delta_y;

		if (delta_x == 0.0f) {
			currentFrame = 10;
		}
		else {
			// turn ninja in the correct direction
			if (delta_x > 0) { // moving right
				direction = Direction::Right;
			}
			else {			   // moving left
				direction = Direction::Left;
			}
			// move to the next frame before updating the image
			AdvanceFrame();
		}
		// update the image
		UpdateImage();
	}

	void AdvanceFrame() {
		heldFor += 0.01f;
		if (heldFor < holdDuration) {
			return;
		}
		heldFor = 0.0f;
		
		currentFrame++;
		if (currentFrame >= runFrameCount) { // wrap around to beginning
			currentFrame = 0;
		}
	}

	void UpdateImage() {
		const bool horizontalFlip = image[currentFrame].getSpriteInfo().flipHorizontal;
		const float scaling = image[currentFrame].getSpriteInfo().scale;
		if (direction == Direction::Right) {
			image[currentFrame].flipHorizontal(false);
		}
		else {
			image[currentFrame].flipHorizontal(true);
		}

		image[currentFrame].setX(x);
		image[currentFrame].setY(y);
	}

	void Draw() {
		image[currentFrame].draw();
	}
private:
	void InitializeTextures(Graphics* graphics) {
		if (!texManager[0].initialize(graphics, L"Run__000.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[1].initialize(graphics, L"Run__001.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[2].initialize(graphics, L"Run__002.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[3].initialize(graphics, L"Run__003.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[4].initialize(graphics, L"Run__004.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[5].initialize(graphics, L"Run__005.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[6].initialize(graphics, L"Run__006.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[7].initialize(graphics, L"Run__007.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[8].initialize(graphics, L"Run__008.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[9].initialize(graphics, L"Run__009.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
		if (!texManager[10].initialize(graphics, L"idle__000.png")) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Error Initialising Ninja");
		}
	}

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

