#include "Deninja.h"

#include <algorithm>

Deninja::Deninja()
{
}

Deninja::~Deninja()
{
    SAFE_DELETE(ninja);
    SAFE_DELETE(ship);
    SAFE_DELETE(background);

    for (Projectile* b : bullets) {
        delete b;
    }
    for (Projectile* k : kunai) {
        delete k;
    }
}

void Deninja::initialize(HWND hwnd) 
{
	Game::initialize(hwnd);

    ship = new Ship(100.0f, 100.0f, graphics);
    ninja = new Ninja(0.0f, 800.0f, graphics);
    // just making a vector on the go
    background = new Animation(graphics, std::vector<LPCWSTR>({L"BG.png"}), 1.0f);

    ship->SetVelocity(Vec2(400.0f, 0.0f));
}

void Deninja::update() 
{
    // get the time that has passed since the previous frame
    const float deltatime = timer.Mark();

    // update ship's position
    ship->Update(deltatime);

    // see if ship can fire a new bullet and do so if it can
    if (ship->CanFire()) {
        bullets.push_back(ship->Fire());
    }

    // update the positions of all the bullets
    for (Projectile* b : bullets) {
        b->Update(deltatime);
    }
    for (Projectile* k : kunai) {
        k->Update(deltatime);
    }

    // calculate the player's velocity based on user input
    Vec2 vel = { 0,0 };
    // maxumum human running speed = 12.5 ms-1
    const float movementSpeed = 572.5f;
    // human juming initial velocity = 2.7 ms-1
    // this guy is superhuman, so... 10 ms-1
    const float jumpSpeed = 458.0f;
    // see projectile.h for details

    if (input->isKeyDown('D')) {
        vel.x += movementSpeed;
    }
    else if (input->isKeyDown('A')) {
        vel.x -= movementSpeed;
    }

    if (input->isKeyDown('W')) {
        if (!ninja->IsInAir()) {
            ninja->Jump(jumpSpeed);
        }
    }

    if (!ninja->IsInAir()) {
        ninja->SetVelocity(vel);
    }

    if (input->getMouseLButton()) {
        if (ninja->CanFire()) {
            const float targetX = input->getMouseX();
            const float targetY = input->getMouseY();
            kunai.push_back(ninja->Fire(Vec2{targetX, targetY}));
        }
    }

    ninja->Update(deltatime);
}

void Deninja::ai()
{
}

void Deninja::collisions()
{
    const _Rect walls(Vec2(0, 0), GAME_WIDTH, GAME_HEIGHT-100u);

    ninja->ProcessWallCollision(walls);
    ship->ProcessWallCollision(walls);
    
    // process all wall collisions
    for (Projectile* b : bullets) {
        b->ProcessWallCollision(walls);
    }
    // process all bullet collisions with ninja
    for (Projectile* b : bullets) {
        if (b->DetectEntityCollision(*ninja)) {
            b->SetDestroyed();
        }
    }

    // remove any bullets that were destroyed from collisions
    const std::vector<Projectile*>::const_iterator newEnd = std::remove_if(
        // begin and end points
        bullets.begin(), bullets.end(),
        // lambda function to remove destroyed bullets
        [](Projectile* b) {
            if (b->IsDestroyed()) {
                delete b;
                b = NULL;
                return true;
            }
            return false;
        }
    );
    // clear out the freed up space in the vector
    bullets.erase(newEnd, bullets.end());

    // process all wall collisions
    for (Projectile* k : kunai) {
        k->ProcessWallCollision(walls);
    }
    // process all kunai collisions with ship
    for (Projectile* k : kunai) {
        if (k->DetectEntityCollision(*ship)) {
            k->SetDestroyed();
        }
    }

    // remove any bullets that were destroyed from collisions
    const std::vector<Projectile*>::const_iterator newEnd2 = std::remove_if(
        // begin and end points
        kunai.begin(), kunai.end(),
        // lambda function to remove destroyed bullets
        [](Projectile* k) {
            if (k->IsDestroyed()) {
                delete k;
                k = NULL;
                return true;
            }
            return false;
        }
    );
    // clear out the freed up space in the vector
    kunai.erase(newEnd2, kunai.end());
}

void Deninja::releaseAll()
{
    background->OnLostDevice();
    ship->OnLostDevice();
    ninja->OnLostDevice();
    Game::releaseAll();
    return;
}

void Deninja::resetAll()
{
    background->OnResetDevice();
    ship->OnResetDevice();
    ninja->OnResetDevice();
    Game::resetAll();
    return;
}

void Deninja::render()
{
    graphics->spriteBegin();

    background->Draw(Vec2(0.0f, 0.0f));
    
    ship->Draw();
    ninja->Draw();

    // render all bullets
    for (Projectile* b : bullets) {
        b->Draw();
    }

    // render all bullets
    for (Projectile* k : kunai) {
        k->Draw();
    }

    graphics->spriteEnd();
}