#include "Deninja.h"

Deninja::Deninja()
{
}

Deninja::~Deninja() {
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
    // get the time that has passed since the previous frame
    const float deltatime = timer.Mark();

    // update Ship's position
    ship->Update(deltatime);

    // see if ship can fire a new bullet and do so if it can


    // calculate the player's velocity based on user input
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
}

void Deninja::ai(){}
void Deninja::collisions()
{
    const _Rect walls(Vec2(0, 0), GAME_WIDTH, GAME_HEIGHT-100u);

    ninja->ProcessWallCollision(walls);

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

    graphics->spriteEnd();
}