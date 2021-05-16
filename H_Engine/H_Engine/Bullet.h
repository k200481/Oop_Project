#pragma once
#include "textureManager.h"
#include "image.h"
#include "Constant.h"

class Bullet
{
public:
	// load bullet image into program
	static void InitBulletAnimation(Graphics* graphics);
	//constructor
	Bullet(float center_x, float center_y);
	void UpdatePosition(float delta_x, float delta_y);
	// position getters
	float GetX();
	float GetY();
	// used to destroy bullet
	void BulletDestroyed();
	// returns true if bullet has been destroyed
	bool IsDestroyed();
	// draws bullet depending on its position
	void Draw();

private:
	// used to make sure if the bullet image has been loaded before anything is one with bullet
	static bool animationsInitialized;
	// center of the bulet
	float x;
	float y;
	// width and height of bullet, will be used to create rect for collision detection
	const float width = 58.0f;
	const float height = 36.0f;
	// delete the bullet when this becomes true
	bool isDestroyed = false;
	// static pointers for bullet rendering
	static const wchar_t* file;
	static TextureManager texManager;
	static Image img;
};