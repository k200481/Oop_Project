#pragma once
#include "textureManager.h"
#include "image.h"

#include "Vec2.h"
#include <vector>

class Ninja
{
private:
	enum class Direction {
		Right,
		Left
	};

public:
	// constructors
	Ninja(float initial_x, float initial_y, Graphics* graphics);
	Ninja(const Vec2<float>& initial_position, Graphics* graphics);
	// update position of ninja
	void Update(const Vec2<float>& velocity);
	// get position
	Vec2<float> GetPosition() const;
	// draw sprite
	void Draw();
private:
	// a truly horrible, list of initializations
	void InitializeTextures(Graphics* graphics);
	// move to the next frame (while skipping the idle frame)
	void AdvanceFrame();
	// updata sprite direction
	void UpdateImage();
private:
	// position and direction
	Vec2<float> position;
	Direction direction = Direction::Right;
	// width and height of the sprite
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

