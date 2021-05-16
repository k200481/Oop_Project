#include "Ninja.h"

Ninja::Ninja(float initial_x, float initial_y, Graphics* graphics)
	:
	Ninja(Vec2<float>(initial_x, initial_y), graphics)
{
}

Ninja::Ninja(const Vec2<float>& initial_position, Graphics* graphics)
	:
	position(initial_position)
{
	// initialize all the runs frames
	for (int i = 0; i <= runFrameCount; i++) {
		texManager.emplace_back();
	}

	// initialize all the frames in the animation, gonna make a frame class to deal with this later, probably
	// initialize textures
	InitializeTextures(graphics);
	// initialize images
	for (int i = 0; i <= runFrameCount; i++) {
		image.emplace_back();
		image[i].initialize(graphics, 0, 0, 0, &texManager[i]);
		image[i].setScale(imageScale);
	}
	// get width and height of sprite (assume all sprites have the same dimensions... which they should)
	width = image[0].getWidth() * imageScale;
	height = image[0].getHeight() * imageScale;
}

void Ninja::Update(const Vec2<float>& velocity)
{
	// update position
	position += velocity;

	if (velocity.x == 0.0f) {
		currentFrame = idleFrameIndex;
	}
	else {
		// turn ninja in the correct direction
		if (velocity.x > 0) { // moving right
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

Vec2<float> Ninja::GetPosition() const
{
	return position;
}

void Ninja::Draw()
{
	image[currentFrame].draw();
}

void Ninja::AdvanceFrame()
{
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

void Ninja::UpdateImage()
{
	const bool horizontalFlip = image[currentFrame].getSpriteInfo().flipHorizontal;
	const float scaling = image[currentFrame].getSpriteInfo().scale;
	if (direction == Direction::Right) {
		image[currentFrame].flipHorizontal(false);
	}
	else {
		image[currentFrame].flipHorizontal(true);
	}

	image[currentFrame].setX(position.x);
	image[currentFrame].setY(position.y);
}

void Ninja::InitializeTextures(Graphics* graphics) {
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
