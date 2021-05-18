#include "Ninja.h"

const std::vector<LPCWSTR> Ninja::run_files = {
	L"Run__000.png",
	L"Run__001.png",
	L"Run__002.png",
	L"Run__003.png",
	L"Run__004.png",
	L"Run__005.png",
	L"Run__006.png",
	L"Run__007.png",
	L"Run__008.png",
	L"Run__009.png"
};
const std::vector<LPCWSTR> Ninja::idle_files = { 
	L"Idle__000.png" 
};

Ninja::Ninja(float initial_x, float initial_y, Graphics* graphics)
	:
	Ninja(Vec2(initial_x, initial_y), graphics)
{
}

Ninja::Ninja(const Vec2& initial_position, Graphics* graphics)
	:
	BasicEntity(initial_position)
{
	// running
	animations.push_back( Animation( graphics, run_files, imageScale ) );
	// jumping
	animations.push_back( Animation( graphics, run_files, imageScale ) );
	// idle
	animations.push_back( Animation(graphics, idle_files, imageScale ) );

	// get width and height of sprite (assume all sprites have the same dimensions... which they should)
	SetWidth(animations[0].GetWidth());
	SetHeight(animations[0].GetHeight());
}

void Ninja::Update(float deltatime)
{
	BasicEntity::UpdatePosition(deltatime);
	animations[int(state)].Advance(deltatime);
}

void Ninja::UpdateVelocity(const Vec2& delta_velocity)
{
	// update velocity
	SetVelocity(GetVelocity() + delta_velocity);
	UpdateStateAndDirection(delta_velocity);
}

bool Ninja::ProcessWallCollision(const _Rect& walls)
{
	const _Rect& rect = GetRect();

	if (int(rect.bottom) >= int(walls.bottom)) {
		Vec2 vel = GetVelocity();
		vel.y = 0.0f;
		SetVelocity(vel);
	}

	return BasicEntity::ProcessWallCollision(walls);
}

void Ninja::Jump()
{
	if (!IsInAir()) {
		SetVelocity(Vec2(0.0f, -400.0f));
	}
}

void Ninja::Draw()
{
	animations[int(state)].Draw(GetPosition(), direction);
}

Vec2 Ninja::GetPosition() const
{
	return BasicEntity::GetPosition();
}

Vec2 Ninja::GetVelocity() const
{
	return BasicEntity::GetVelocity();
}

void Ninja::SetVelocity(const Vec2& new_velocity)
{
	BasicEntity::SetVelocity(new_velocity);
	UpdateStateAndDirection(new_velocity);
}

void Ninja::OnResetDevice()
{
	for (Animation& a : animations) {
		a.OnResetDevice();
	}
}

void Ninja::OnLostDevice()
{
	for (Animation& a : animations) {
		a.OnLostDevice();
	}
}

void Ninja::UpdateStateAndDirection(const Vec2& v)
{
	if (v.y != 0) {
		// jumping
		state = State::Jumping;
	}
	else if (v.x != 0.0f) {
		// running
		state = State::Running;
	}
	else {
		// idle
		state = State::Idle;
	}

	if (v.x > 0) {
		direction = Animation::Direction::Right;
	}
	else if (v.x < 0) {
		direction = Animation::Direction::Left;
	}
	// else retain previous direction
}
