#include "Deninja.h"

Deninja::Deninja()
{
}

Deninja::~Deninja() {
    SAFE_DELETE(b);
    SAFE_DELETE(n);
    SAFE_DELETE(s);
}

void Deninja::initialize(HWND hwnd) {
	Game::initialize(hwnd);

    s = new Ship(100.0f, 100.0f, graphics);
    n = new Ninja(0.0f, 800.0f, graphics);

    Bgmanager.initialize(graphics, L"BG.png");
    Bg.initialize(graphics, 0, 0, 0, &Bgmanager);

}

void Deninja::update() {
    const float deltatime = 0.1f;

    s->Update(deltatime);

    Vec2 vel = { 0,0 };

    if (input->isKeyDown('D')) {
        vel.x += 10.0f;
    }
    else if (input->isKeyDown('A')) {
        vel.x -= 10.0f;
    }


    n->SetVelocity(vel);
    n->Update(deltatime);

    // render everything
    Deninja::render();
}

void Deninja::ai(){}
void Deninja::collisions(){
    const _Rect walls(Vec2(0, 0), GAME_WIDTH, GAME_HEIGHT);

    n->ProcessWallCollision(walls);

}
void Deninja::releaseAll()
{
    Bgmanager.onLostDevice();
    for (int x = 0; x < 11; x++) {
//        runmanager[x].onLostDevice();
    }
    Game::releaseAll();
    return;
}
void Deninja::resetAll()
{
    Bgmanager.onResetDevice();
    for (int x = 0; x < 11; x++) {
//       runmanager[x].onResetDevice();
    }
    Game::resetAll();
    return;
}

void Deninja::render()
{
    graphics->spriteBegin();
    
    Bg.draw();
    
    s->Draw();
    n->Draw();

    graphics->spriteEnd();
}