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

#include <vector>

class Deninja :public Game
{
private:
    // the timers for the entire game
    Timer timer;
    
    //
    Ninja* ninja = NULL;
    Ship* ship = NULL;
    std::vector<Bullet*> bullets;

    // isn't really animated, but there's room for it to be
    // could also make a new class to handle 'scenes' with several animations
    // has to be a pointer because a graphics pointer is needed to construct it
    Animation* background = NULL;

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