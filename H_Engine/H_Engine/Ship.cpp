#include "Ship.h"

Ship::Ship(float initial_x, float initial_y, Graphics* graphics)
	:Ship(Vec2<float>(initial_x, initial_y), graphics)
{
}

Ship::Ship(const Vec2<float>& initial_position, Graphics* graphics)
	:
	position(initial_position)
{
	// default construct textures
	for (int i = 0; i < frameCount; i++) {
		texManager.emplace_back();
	}
	// initialize default constructed textures
	InitizlizeTextures(graphics);
	// initialize images
	for (int i = 0; i < frameCount; i++) {
		image.emplace_back();
		image[i].initialize(graphics, 0, 0, 0, &texManager[i]);
		image[i].setScale(imageScale);
	}
}

void Ship::Update()
{
	position += direction * movementSpeed;
	AdvanceFrame();
}

void Ship::SetVelocity(const Vec2<float>& new_velocity)
{
	direction = new_velocity.UnitVector();
	movementSpeed = new_velocity.Magnitude();
}

void Ship::SetDirection(const Vec2<float>& new_direction)
{
	direction = new_direction.UnitVector();
}

void Ship::Draw()
{
	image[currentFrame].setX(position.x);
	image[currentFrame].setY(position.y);
	image[currentFrame].draw();
}

void Ship::InitizlizeTextures(Graphics* graphics)
{
	if (!texManager[0].initialize(graphics, L"flying-saucer-1.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	if (!texManager[1].initialize(graphics, L"flying-saucer-2.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	if (!texManager[2].initialize(graphics, L"flying-saucer-3.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	if (!texManager[3].initialize(graphics, L"flying-saucer-4.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	if (!texManager[4].initialize(graphics, L"flying-saucer-5.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
}

void Ship::AdvanceFrame()
{
	heldFor += 0.01f;
	if (heldFor < holdDuration) {
		return;
	}
	heldFor -= holdDuration;

	currentFrame++;
	if (currentFrame >= frameCount) {
		currentFrame = 0;
	}
}
