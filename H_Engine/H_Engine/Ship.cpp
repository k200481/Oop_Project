#include "Ship.h"

const std::vector<LPCWSTR> Ship::files = {
		L"flying-saucer-1.png",
		L"flying-saucer-2.png",
		L"flying-saucer-3.png",
		L"flying-saucer-4.png",
		L"flying-saucer-5.png"
};

Ship::Ship(float initial_x, float initial_y, Graphics* graphics)
	:
	Ship(Vec2<float>(initial_x, initial_y), graphics)
{
}

Ship::Ship(const Vec2<float>& initial_position, Graphics* graphics)
	:
	position(initial_position),
	animation(graphics, files, 2.0f)
{
}

void Ship::Update()
{
	// update position
	position += direction * movementSpeed;
	// pass deltatime to animation
	animation.Advance(0.01f);
}

void Ship::Draw()
{
	animation.Draw(position);
}

void Ship::SetVelocity(const Vec2<float>& new_velocity)
{
	direction = new_velocity.UnitVector();
	movementSpeed = float(new_velocity.Magnitude());
}

void Ship::SetDirection(const Vec2<float>& new_direction)
{
	direction = new_direction.UnitVector();
}

Vec2<float> Ship::GetPosition() const
{
	return position;
}

Vec2<float> Ship::GetDirection() const
{
	return direction;
}

float Ship::GetMovementSpeed() const
{
	return movementSpeed;
}

