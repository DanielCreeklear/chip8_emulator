#include <iostream>
#include "cpu.h"
#include "window.h"

using namespace std;

Cpu cpu;
Window window(800, 600, "CHIP 8 - Emulator");
char fileGame[] = {'i', 'n', 'v', 'a', 'd', 'e', 'r', 's', '.', 'c', '8'}; 

int main(int argc, char **argv)
{
    //setupGraphics();
    //setupInput();

    cpu.initialize();
    cpu.loadGame(fileGame);

    while (!window.shouldClose())
    {
        cpu.emulateCycle();

        if (cpu.drawFlag) {}//drawGraphics();
        window.update();

        cpu.setKeys();
    }

    return 0;
}