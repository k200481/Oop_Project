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

    Bgmanager.initialize(graphics, L"BG.png");
    Bg.initialize(graphics, 0, 0, 0, &Bgmanager);

}

void Deninja::update() {
    
    s->Update();
    // render everything
    Deninja::render();
}

void Deninja::ai(){}
void Deninja::collisions(){
    if (b != NULL) {


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
    
    s->Draw();

    graphics->spriteEnd();
}