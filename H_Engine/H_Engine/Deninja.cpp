#include "Deninja.h"
Deninja::Deninja(){}
Deninja::~Deninja() {}
void Deninja::initialize(HWND hwnd) {
	Game::initialize(hwnd);
    Bgmanager.initialize(graphics, L"BG.png");
    Bg.initialize(graphics, 0, 0, 0, &Bgmanager);
    Bulletmanager.initialize(graphics, L"bullet.png");
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
    if (!ship[0].initialize(graphics, 0, 0, 0, &ship5Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship1Texture.initialize(graphics, L"flying-saucer-1.png");
    if (!ship[1].initialize(graphics, 0, 0, 0, &ship1Texture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    runmanager[0].initialize(graphics, L"Run__000.png");
    runi[0].initialize(graphics, 0, 0, 0, &runmanager[0]);
    runmanager[1].initialize(graphics, L"Run__001.png");
    runi[1].initialize(graphics, 0, 0, 0, &runmanager[1]);
    runmanager[2].initialize(graphics, L"Run__002.png");
    runi[2].initialize(graphics, 0, 0, 0, &runmanager[2]);
    runmanager[3].initialize(graphics, L"Run__003.png");
    runi[3].initialize(graphics, 0, 0, 0, &runmanager[3]);
    runmanager[4].initialize(graphics, L"Run__004.png");
    runi[4].initialize(graphics, 0, 0, 0, &runmanager[4]);
    runmanager[5].initialize(graphics, L"Run__005.png");
    runi[5].initialize(graphics, 0, 0, 0, &runmanager[5]);
    runmanager[6].initialize(graphics, L"Run__006.png");
    runi[6].initialize(graphics, 0, 0, 0, &runmanager[6]);
    runmanager[7].initialize(graphics, L"Run__007.png");
    runi[7].initialize(graphics, 0, 0, 0, &runmanager[7]);
    runmanager[8].initialize(graphics, L"Run__008.png");
    runi[8].initialize(graphics, 0, 0, 0, &runmanager[8]);
    runmanager[9].initialize(graphics, L"Run__009.png");
    runi[9].initialize(graphics, 0, 0, 0, &runmanager[9]);
    runmanager[10].initialize(graphics, L"Idle__000.png");
    runi[10].initialize(graphics, 0, 0, 0, &runmanager[10]);
    runt = 0;
}
void Deninja::update() {
    one = (one <= 3) ? one + 1 : 0;
    if (!bul)
        bul = true;
    if (bul) {
        if (bullet == NULL) {
            bullet = new Image;
            bullet->initialize(graphics, 0, 0, 0, &Bulletmanager);
            bullet->setX(ship[one].getCenterX());
            bullet->setY(ship[one].getY());
            bullet->setDegrees(270);
            bullet->setScale(1);
        }
        bullet->setY(bullet->getY() + 10);
        if (bullet->getCenterY() >= GAME_HEIGHT) {
            bullet->~Image();
            bul = false;
            delete bullet;
            bullet = NULL;
            score = score + 100;
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
    if (!input->isKeyDown('D')) {
        forward = 0;
    }
    if (!input->isKeyDown('A')) {
        backward = 0;
    }
    if (input->isKeyDown('D')) {
        if (forward == 10)
            forward=1;
        else
            forward++;
        direction = false;
        if(ninx<(GAME_WIDTH-60))
        ninx=ninx+3;
    }
    if (input->isKeyDown('A')) {
        if (backward == 10)
            backward = 1;
        else
            backward++;
        direction = true;
        if (ninx >0)
        ninx = ninx - 3;
    }
    if (input->isKeyDown('W')) {
    }
    if (input->isKeyDown('S')) {
    }
    Deninja::render();

}
void Deninja::ai(){}
void Deninja::collisions(){
    if (bullet)
        if (bullet->getCenterX() >= runi[runt].getCenterX()-30 &&
            bullet->getCenterX() <= runi[runt].getCenterX() +30
            && bullet->getY() <= runi[runt].getY() + 100
            && bullet->getY() >= runi[runt].getY() - 100) {
            wchar_t buffer[256];
            wsprintfW(buffer, L"Your Score is %d", score);
            MessageBox(NULL, L"You lost", buffer, MB_ICONERROR);
            PostQuitMessage(1);
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
    if(bullet)
    bullet->draw();
    ship[one].setScale(2);
    ship[one].draw();
        if (forward == 0 && backward == 0) {
            runi[10].flipHorizontal(direction);
            runi[10].setX(ninx);
            runi[10].setY(niny);
            runi[10].setScale(.2);
            runi[10].draw();
        }
        else if (forward != 0) {
            runi[forward - 1].setX(ninx);
            runi[forward - 1].setY(niny);
            runi[forward - 1].flipHorizontal(false);
            runi[forward - 1].setScale(.2);
            runi[forward - 1].draw();
        }
        else {
            runi[backward - 1].setX(ninx);
            runi[backward - 1].setY(niny);
            runi[backward - 1].flipHorizontal(true);
            runi[backward - 1].setScale(.2);
            runi[backward - 1].draw();
        }
    
    graphics->spriteEnd();
}