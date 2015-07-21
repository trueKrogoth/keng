#include <keng/keng.hpp>
#include <time.h>

using namespace Keng;

TFrame* Frame;
TWorld* World;

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    Prog::init(_T("Game"), _T("Game"), 15, 32, 16);
    return Prog::main(hThisInstance,
                      hPrevInstance,
                      lpszArgument,
                      nCmdShow);
}

void Prog::onTimer() {
    Frame->updateAll();
}

void Prog::onMouseMove() {
}

void Prog::onRButtonDown(WPARAM button) {
}

void Prog::onRButtonUp(WPARAM button) {
}

void Prog::onKeyDown(WPARAM key) {
}

void Prog::onKeyUp(WPARAM key) {
    PostQuitMessage(1);
}

void Prog::onCreate() {
    srand(time(0));

    Frame = new TFrame();
    World = new TWorld(new TBackground(Frame));
    new TCursor(Frame);
    World->setTilebox(new TTilebox(World));
    new TAllroundScroller(World);
}

void Prog::onClose() {
}
