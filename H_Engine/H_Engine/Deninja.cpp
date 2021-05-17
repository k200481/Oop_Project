#include "Deninja.h"

Deninja::Deninja()
{
}

Deninja::~Deninja() {
    SAFE_DELETE(b);
    SAFE_DELETE(ninja);
    SAFE_DELETE(ship);
}

void Deninja::initialize(HWND hwnd) {
	Game::initialize(hwnd);

    ship = new Ship(100.0f, 100.0f, graphics);
    ninja = new Ninja(0.0f, 800.0f, graphics);

    ninja->Jump();

    Bgmanager.initialize(graphics, L"BG.png");
    Bg.initialize(graphics, 0, 0, 0, &Bgmanager);

}

void Deninja::update() {
    const float deltatime = 1 / 60.0f;

    ship->Update(deltatime);

    if (b == NULL) {
        b = new Bullet(ship->GetPosition(), { 0.0f, 10.0f }, graphics);
    }
    else if (b->IsDestroyed()) {
        delete b;
        b = NULL;
        b = new Bullet(ship->GetPosition(), { 0.0f, 10.0f }, graphics);
    }
    else {
        b->Update(deltatime);
    }

    Vec2 vel = { 0,0 };
    const float movementSpeed = 100.0f;

    if (input->isKeyDown('D')) {
        vel.x += movementSpeed;
    }
    else if (input->isKeyDown('A')) {
        vel.x -= movementSpeed;
    }
    if (input->wasKeyPressed('W')) {
        if (!ninja->IsInAir()) {
            vel.y = -500.0f;
        }
    }

    if (ninja->IsInAir()) {
        vel.x /= 100.0f;
        vel.y += 10.0f;
        ninja->UpdateVelocity(vel);
    }
    else {
        ninja->SetVelocity(vel);
    }
    ninja->Update(deltatime);

    // render everything
    Deninja::render();
}

void Deninja::ai(){}
void Deninja::collisions()
{
    const _Rect walls(Vec2(0, 0), GAME_WIDTH, GAME_HEIGHT-100u);

    if (ninja->DetectEntityCollision(*b)) {
        b->BulletDestroyed();
    }

    ninja->ProcessWallCollision(walls);
    b->ProcessWallCollision(walls);

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
    
    ship->Draw();
    ninja->Draw();
    b->Draw();

    graphics->spriteEnd();
}