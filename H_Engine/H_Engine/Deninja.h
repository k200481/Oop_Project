#ifndef NINJA_H
#define NINJA_H
#include"game.h"
#include"image.h"
#include"textureManager.h"

#include "Vec2.h"
#include "_Rect.h"
#include "Ninja.h"
#include "Ship.h"
#include "Bullet.h"
#include "Timer.h"

class Deninja :public Game
{
private:
    Timer timer;
    
    Ninja* ninja = NULL;
    Ship* ship = NULL;

    TextureManager Bgmanager;
	Image Bg;

    int score = 0;
public:
    Deninja();
    virtual ~Deninja();
    void initialize(HWND hwnd);
    void update();
    void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();

};

#endif