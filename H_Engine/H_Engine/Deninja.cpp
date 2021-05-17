#include "Deninja.h"
Deninja::Deninja(){}
Deninja::~Deninja() {
    SAFE_DELETE(b);
    SAFE_DELETE(n);
    SAFE_DELETE(s);
}
void Deninja::initialize(HWND hwnd) {
	Game::initialize(hwnd);

    Bullet::InitBulletAnimation(graphics);

    Bgmanager.initialize(graphics, L"BG.png");
    
    Bg.initialize(graphics, 0, 0, 0, &Bgmanager);
    
    n = new Ninja(0.0f, 800.0f, graphics);
    s = new Ship(0.0f, 10.0f, graphics);
}
void Deninja::update() {
    
    if (b == NULL) {
        // create a new bullet if there is none
        const Vec2<float> shipPosition(s->GetPosition());
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

    if (s->GetPosition().x <= 10.0f && s->GetDirection().x < 0) {
        s->SetDirection(Vec2<float>(1, 0));
    }
    else if (s->GetPosition().x >= GAME_WIDTH && s->GetDirection().x > 0) {
        s->SetDirection(Vec2<float>(-1, 0));
    }
    s->Update();

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

        /*const float playerLeft = runi[runt].getCenterX() - 30;
        const float playerRight = runi[runt].getCenterX() + 30;
        const float playerTop = runi[runt].getY() - 100;
        const float playerBottom = runi[runt].getY() + 100;*/

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

    if ( b != NULL ) {
        b->Draw();
    }

    s->Draw();

    n->Draw();

    graphics->spriteEnd();
}