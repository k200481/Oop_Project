#include "Deninja.h"
Deninja::Deninja(){}
Deninja::~Deninja() {
    SAFE_DELETE(b);
    SAFE_DELETE(n);
}
void Deninja::initialize(HWND hwnd) {
	Game::initialize(hwnd);

    Bullet::InitBulletAnimation(graphics);

    Bgmanager.initialize(graphics, L"BG.png");
    
    Bg.initialize(graphics, 0, 0, 0, &Bgmanager);
    
    if (!ship[0].initialize(graphics, 0, 0, 0, &ship5Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship1Texture.initialize(graphics, L"flying-saucer-1.png");
    if (!ship[1].initialize(graphics, 0, 0, 0, &ship1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship2Texture.initialize(graphics, L"flying-saucer-2.png");
    if (!ship[2].initialize(graphics, 0, 0, 0, &ship2Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship3Texture.initialize(graphics, L"flying-saucer-3.png");
    if (!ship[3].initialize(graphics, 0, 0, 0, &ship3Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship4Texture.initialize(graphics, L"flying-saucer-4.png");
    if (!ship[4].initialize(graphics, 0, 0, 0, &ship4Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship5Texture.initialize(graphics, L"flying-saucer-5.png");
    
    n = new Ninja(0.0f, 800.0f, graphics);
}
void Deninja::update() {
    one = (one <= 3) ? one + 1 : 0;
    
    if (b == NULL) {
        // create a new bullet if there is none
        const Vec2<float> shipPosition(ship[one].getCenterX(), ship[one].getCenterY());
        b = new Bullet(shipPosition);
    }
    else {
        // update the bullet's current position
        const Vec2<float> bulletVelocity(0.0f, 10.0f);
        b->UpdatePosition(bulletVelocity);
        // check if the new position caused the bullet to reach game height and get destroyed
        if (b->IsDestroyed()) {
            delete b;
            b = NULL;

            // update score
            score += 100;
        }
    }

    if (!shipdir)
        if (ship[one].getX() < GAME_WIDTH - ship[one].getWidth()-20)
            shipx = shipx + 10;
        else
            shipdir = !shipdir;
    if(shipdir)
        if(ship[one].getX() > 0)
        shipx = shipx - 10;
    else
        shipdir = !shipdir;
    ship[one].setX(shipx);

    // update player's position
    Vec2<float> playerVelocity(0.0f,0.0f);
    if (input->isKeyDown('A')) {
        playerVelocity.x += -10.0f;
    }
    else if (input->isKeyDown('D')) {
        playerVelocity.x += +1.0f;
    }

    if (n->GetPosition().y >= 800.0f) {
        if (input->wasKeyPressed(VK_SPACE)) {
            input->clearKeyPress(VK_SPACE);
            playerVelocity.y += -100.0f;
        }
    }
    else {
        playerVelocity.y += +10.0f;
    }

    n->Update(playerVelocity);
    
    // render everything
    Deninja::render();
}
void Deninja::ai(){}
void Deninja::collisions(){
    if (b != NULL) {
        const float bulletCenterX = b->GetX();
        const float bulletCenterY = b->GetY();

        const float playerLeft = runi[runt].getCenterX() - 30;
        const float playerRight = runi[runt].getCenterX() + 30;
        const float playerTop = runi[runt].getY() - 100;
        const float playerBottom = runi[runt].getY() + 100;

        //if ( bulletCenterX >= playerLeft && bulletCenterX <= playerRight
        //    && bulletCenterY >= playerTop && bulletCenterY <= playerBottom )
        //{
        //    wchar_t buffer[256];
        //    wsprintfW(buffer, L"Your Score is %d", score);
        //    MessageBox(NULL, L"You lost", buffer, MB_ICONERROR);
        //    PostQuitMessage(1);
        //}
    }
}
void Deninja::releaseAll()
{
    Bgmanager.onLostDevice();
    for (int x = 0; x < 11; x++) {
        runmanager[x].onLostDevice();
    }
    Game::releaseAll();
    return;
}
void Deninja::resetAll()
{
    Bgmanager.onResetDevice();
    for (int x = 0; x < 11; x++) {
        runmanager[x].onResetDevice();
    }
    Game::resetAll();
    return;
}
void Deninja::render()
{
    graphics->spriteBegin();
    
    Bg.draw();

    if ( b != NULL ) {
        b->Draw();
    }

    ship[one].setScale(2);
    ship[one].draw();

    n->Draw();

    graphics->spriteEnd();
}