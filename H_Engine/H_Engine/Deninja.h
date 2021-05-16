#ifndef NINJA_H
#define NINJA_H
#include"game.h"
#include"image.h"
#include"textureManager.h"

#include "Bullet.h"

class Deninja :public Game
{
private:
    Bullet* b = NULL;
    
    TextureManager Bgmanager;
	Image Bg;
    TextureManager ship1Texture;
    TextureManager ship2Texture;
    TextureManager ship3Texture;
    TextureManager ship4Texture;
    TextureManager ship5Texture;
    Image ship[5];
    float shipx;
    float shipy;
    int one;
    TextureManager runmanager[11];
    Image runi[11];
    int runt;
    int forward=0;
    bool direction = false;
    int backward=0;
    float ninx = 0; 
    int jump=0;
    bool shipdir = false;
    float niny=800;
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