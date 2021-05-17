#include "Bullet.h"

const std::vector<LPCWSTR> Bullet::file = {
	L"bullet.png"
};

Bullet::Bullet(const Vec2& position, const Vec2& velocity, Graphics* graphics)
	:
	BasicEntity(position, velocity),
	animation(graphics, file, imageScale, degrees)
{
	// flipped because the image is horizontal but the bullet falls vertically
	SetWidth(animation.GetHeight());
	SetHeight(animation.GetWidth());
}

void Bullet::Update(float deltatime) 
{
	BasicEntity::UpdatePosition(deltatime);

	// advancing animations is unnecessary with only one frame
	// but it can be called in case more frames are ever added
	animation.Advance(deltatime);
}

bool Bullet::ProcessWallCollision(const _Rect& walls)
{
	if (BasicEntity::ProcessWallCollision(walls)) {
		BulletDestroyed();
	}
	return true;
}

Vec2 Bullet::GetPosition() const 
{
	return BasicEntity::GetPosition();
}

void Bullet::BulletDestroyed() 
{
	isDestroyed = true;
}

bool Bullet::IsDestroyed() const 
{
	return isDestroyed;
}

void Bullet::Draw()
{
	if (!IsDestroyed()) {
		animation.Draw(GetPosition());
	}
}