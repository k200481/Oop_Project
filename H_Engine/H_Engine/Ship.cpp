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
	Ship(Vec2(initial_x, initial_y), graphics)
{
}

Ship::Ship(const Vec2& initial_position, Graphics* graphics)
	:
	BasicEntity(initial_position),
	graphics(graphics),
	animation(graphics, files, imageScale)
{
	SetWidth(animation.GetWidth());
	SetHeight(animation.GetHeight());
}

void Ship::Update(float deltatime)
{
	// update position
	BasicEntity::UpdatePosition(deltatime);
	// pass deltatime to animation
	animation.Advance(deltatime);
	// update time since last fire
	fireTimePassed += deltatime;
}

bool Ship::CanFire()
{
	return fireTimePassed >= firePeriod;
}

Bullet* Ship::Fire()
{
	// does not check for 'can fire'
	// so the 'can fire' attriibute may be ignored, up to the field to decide
	
	// reset time
	fireTimePassed = 0.0f;
	// return pointer to new bullet
	return new Bullet(GetCenter(), {0.0f, 0.0f}, graphics);
}

void Ship::Draw()
{
	animation.Draw(GetPosition());
}

bool Ship::ProcessWallCollision(const _Rect& walls)
{
	_Rect rect = GetRect();
	if (rect.right >= walls.right || rect.left <= walls.left) {
		if (!isCollidingWithWall) {
			Vec2 vel = GetVelocity();
			SetVelocity({-vel.x, vel.y});
			isCollidingWithWall = true;
		}
	}
	else {
		isCollidingWithWall = false;
	}
	return BasicEntity::ProcessWallCollision(walls);
}

void Ship::SetVelocity(const Vec2& new_velocity)
{
	BasicEntity::SetVelocity(new_velocity);
}

Vec2 Ship::GetPosition() const
{
	return BasicEntity::GetPosition();
}

void Ship::OnResetDevice()
{
	animation.OnResetDevice();
}

void Ship::OnLostDevice()
{
	animation.OnLostDevice();
}

