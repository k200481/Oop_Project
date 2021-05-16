#include "Bullet.h"


bool Bullet::animationsInitialized = false;
const wchar_t* Bullet::file = L"bullet.png";
TextureManager Bullet::texManager;
Image Bullet::img;