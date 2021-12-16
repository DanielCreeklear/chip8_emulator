#include <iostream>
#include <string.h>
#include "cpu.h"

using namespace std;

Cpu::Cpu()
{

}

void Cpu::initialize()
{
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;

    for (int i = 0; i < 80; i++) memory[i] = chip8_fontset[i];
}

void Cpu::emulateCycle()
{
    opcode = memory[pc] << 8 | memory[pc + 1];

    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode & 0x000F)
            {
                case 0x0000:
                    //
                break;

                case 0x000E:
                    //
                break;
            
                default:
                    cout << "Unknown opcode: 0x" << hex << opcode << endl;
                break;
            }
        break;

        case 0x2000:
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
        break;

        case 0x8000:
            switch (opcode & 0x000F)
            {
                case 0x0004:
                    if (V[(opcode & 0x00F0) >> 4] > 0xFF - V[(opcode & 0x0F00) >> 8])
                    {
                        V[0xF] = 1;
                    }
                    else
                    {
                        V[0xF] = 0;
                    }
                    V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
                break;
                
                default:
                    cout << "Unknown opcode: 0x" << hex << opcode << endl;
                break;
            }
        break;

        case 0xA000:
            I = opcode & 0x0FFF;
            pc += 2;
        break;

        case 0xF000:
            switch (opcode & 0x00FF)
            {
                case 0x0033:
                    memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
                    memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
                    memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
                    pc += 2;
                break;
            
                default:
                    cout << "Unknown opcode: 0x" << hex << opcode << endl;
                break;
            }
        break;

        default:
            cout << "Unknown opcode: 0x" << hex << opcode << endl;
        break;
    }

    if (delay_timer > 0) --delay_timer;

    if (sound_timer > 0)
    {
        if (sound_timer == 1)
        {
            cout << "BEEP!" << endl;
            --sound_timer;
        }
    }

}

bool Cpu::loadGame(char* gameName)
{
    cout << "Loading: [" << gameName << "]. " << endl;
    FILE* fileGame;
    fopen_s(&fileGame, gameName, "rb");

	if (fileGame == NULL)
	{
		fputs ("File error", stderr); 
		return false;
	}

    fseek(fileGame , 0 , SEEK_END);
	long sizeFileGame = ftell(fileGame);
	rewind(fileGame);
    cout << "File size: [" << sizeFileGame << " bytes]." << endl;

    char* buffer = (char*) malloc(sizeof(char) * sizeFileGame);
    size_t result = fread(buffer, 1, sizeFileGame, fileGame);
    if (result != sizeFileGame) 
	{
		fputs("Reading error", stderr); 
		return false;
	}

    if (0x1000 - 0x200 > sizeFileGame)
    {
        for (int i = 0; i < sizeFileGame; i++) memory[i + 512] = buffer[i];
    }
    else
    {
        cout << "Error! ROM is bigger than available memory." << endl;
    }


    fclose(fileGame);
	free(buffer);
    cout << "Successfuly loaded!" << endl;
    return true;
}

void Cpu::setKeys()
{
    
}