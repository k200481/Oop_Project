#include "Kunai.h"
#include <assert.h>

// using the bullet image for now, until I can find something else
const std::vector<LPCWSTR> Kunai::file = {
	L"Bullet.png"
};

// copied over from bullet
// which tells me there was still room for at least one other general class

Kunai::Kunai(const Vec2& position, const Vec2& velocity, Graphics* graphics)
	:
	Projectile(position, velocity),
	animation(graphics, file, imageScale, degrees)
{
	// flipped because the image is horizontal but the bullet falls vertically
	SetWidth(animation.GetHeight());
	SetHeight(animation.GetWidth());
}

void Kunai::Update(float deltatime)
{
	UpdatePosition(deltatime);

	// advancing animations is unnecessary with only one frame
	// but it can be called in case more frames are ever added
	animation.Advance(deltatime);
}

bool Kunai::ProcessWallCollision(const _Rect& walls)
{
	// kunai can rebound off of all walls except the bottom wall, should make it interesting...
	_Rect rect = GetRect();
	if (rect.bottom >= walls.bottom) {
		SetDestroyed();
	}
	return Projectile::ProcessWallCollision(walls);
}

Vec2 Kunai::GetPosition() const
{
	return BasicEntity::GetPosition();
}

void Kunai::OnResetDevice()
{
	animation.OnResetDevice();
}

void Kunai::OnLostDevice()
{
	animation.OnLostDevice();
}

void Kunai::SetDestroyed()
{
	isDestroyed = true;
}

bool Kunai::IsDestroyed() const
{
	return isDestroyed;
}

void Kunai::Draw()
{
	assert(!IsDestroyed());
	animation.Draw(GetPosition());
}