#include <iostream>
#include "cpu.h"

using namespace std;

Cpu cpu;
char fileGame[] = {'i', 'n', 'v', 'a', 'd', 'e', 'r', 's', '.', 'c', '8'}; 

int main(int argc, char **argv)
{
    //setupGraphics();
    //setupInput();

    cpu.initialize();
    cpu.loadGame(fileGame);

    for (;;)
    {
        cpu.emulateCycle();

        if (cpu.drawFlag) {}//drawGraphics();

        cpu.setKeys();
    }

    return 0;
}