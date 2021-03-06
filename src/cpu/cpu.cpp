#include <iostream>
#include <string.h>
#include "cpu.h"

using namespace std;

Cpu::Cpu()
{

}

void Cpu::initialize(const float mhz)
{
    clock = Clock();
    audio = Audio();
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;
    delay_timer = 0;
    sound_timer = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) gfx[i] = 0;
    for (int i = 0; i < 0x1000; i++) memory[i] = 0;
    for (int i = 0; i < 16; i++)
    {
        stack[i] = 0;
        V[i] = 0;
        key[i] = 0;
    }

    clock.init(mhz);
    for (int i = 0; i < 80; i++) memory[i] = chip8_fontset[i];

    srand(time(NULL));
}

void Cpu::emulateCycle()
{

    string aux;
    jumpFlag = false;
    skipFlag = false;
    opcode = memory[pc] << 8 | memory[pc + 1];
    jump_addr = opcode & 0x0FFF;
    X = ((opcode & 0x0F00) >> 8);
    Y = ((opcode & 0x00F0) >> 4);

    //cout << "==================Cyle=================" << endl;
    //cout << "Program counter = " << dec << (int)pc << " ---- Opcode = 0x" << hex << opcode << endl;

    clock.initCycle();
    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode & 0x00FF)
            {
                case 0x00E0:
                    for (int i = 0; i < WIDTH * HEIGHT; i++) gfx[i] = 0;
                    drawFlag = true;
                break;

                case 0x00EE:
                    if (stack[sp] == 0) cout << "Invalid return from subroutine" << endl;
                    pc = stack[sp];
                    stack[sp] = 0;
                    if (sp > 0) sp--;
                break;
            
                default:
                    cout << "Unknown opcode: 0x" << hex << opcode << endl;
                    
                break;
            }
        break;

        case 0x1000:
            pc = jump_addr;
            jumpFlag = true;
        break;

        case 0x2000:
            if (stack[sp] != 0) sp++;
            stack[sp] = pc;
            pc = jump_addr;
            jumpFlag = true;
        break;

        case 0x3000:
            if (V[X] == (opcode & 0x00FF))
            {
                pc += 2;
                skipFlag = true;
            }
        break;

        case 0x4000:
            if ((V[X]) != (opcode & 0x00FF))
            {
                pc += 2;
                skipFlag = true;
            }
        break;

        case 0x5000:
            if ((V[X]) == V[Y])
            {
                pc += 2;
                skipFlag = true;
            }

        case 0x6000:
            V[X] = opcode & 0x00FF;
        break;

        case 0x7000:
            V[X] += opcode & 0x00FF;
        break;

        case 0x8000:
            switch (opcode & 0x000F)
            {
                case 0x0000:
                    V[X] = V[Y];
                break;

                case 0x0001:
                    V[X] |= V[Y];
                break;

                case 0x0002:
                    V[X] &= V[Y];
                break;

                case 0x0003:
                    V[X] ^= V[Y];
                break;

                case 0x0004:
                    if (V[Y] > 0xFF - V[X])
                    {
                        V[0xF] = 1;
                    }
                    else
                    {
                        V[0xF] = 0;
                    }
                    V[X] += V[Y];
                break;

                case 0x0005:
                    if (V[Y] > V[X])
                    {
                        V[0xF] = 0;
                    }
                    else
                    {
                        V[0xF] = 1;
                    }
                    V[X] -= V[Y];
                break;


                case 0x0006:
                    V[0xF] = V[X] & 1;
                    V[X] >>= 1;
                break;

                case 0x0007:
                    if (V[X] > V[Y])
                    {
                        V[0xF] = 0;
                    }
                    else
                    {
                        V[0xF] = 1;
                    }
                    V[Y] -= V[X];
                break;

                case 0x000E:
                    V[0xF] = V[X] >> 7;
                    V[X] <<= 1;
                break;
                
                default:
                    cout << "Unknown opcode: 0x" << hex << opcode << endl;
                    
                break;
            }
        break;

        case 0x9000:
            if ((V[X]) != V[Y])
            {
                pc += 2;
                skipFlag = true;
            }
        break;

        case 0xA000:
            I = opcode & 0x0FFF;
        break;

        case 0xB000:
            pc = jump_addr + V[0];
            jumpFlag = true;
        break;

        case 0xC000:
            V[X] = (rand() % (0xFF + 1)) & (opcode & 0x00FF);
        break;

        case 0xD000:
            drawFlag = true;
            pixelX = V[X];
            pixelY = V[Y];
            height = opcode & 0x000F;
            V[0xF] = 0;

            for (int y = 0; y < height; y++)
            {
                pixelRow = memory[I + y];
                for (int x = 0; x < 8; x++)
                {
                    if (((pixelRow >> 7) & 1) != 0)
                    {
                        if (gfx[pixelX + x + ((pixelY + y) * 64)] == 1) V[0xF] = 1;
                        gfx[pixelX + x + ((pixelY + y) * 64)] ^= 1;
                    }
                    pixelRow <<= 1;
                }
            }
        break;

        case 0xE000:
            switch (opcode & 0x00FF)
            {
                case 0x009E:
                    if (key[V[X]] == 1)
                    {
                        pc += 2;
                        skipFlag = true;
                    }
                break;

                case 0x00A1:
                    if (key[V[X]] == 0)
                    {
                        pc += 2;
                        skipFlag = true;
                    }
                break;

                default:
                    cout << "Unknown opcode: 0x" << hex << opcode << endl;
                    
                break;
            }
        break;

        case 0xF000:
            switch (opcode & 0x00FF)
            {
                case 0x0007:
                    V[X] = delay_timer;
                break;

                case 0x000A:
                    keyPressed = false;
                    for (int i = 0; i < 16; i++)
                    {
                        if (key[i])
                        {
                            keyPressed = true;
                            V[X] = i;
                        }
                    }
                    if (!keyPressed) return;
                break;

                case 0x0015:
                    delay_timer = V[X];
                break;

                case 0x0018:
                    sound_timer = V[X];
                break;

                case 0x001E:
                    I += V[X];
                break;

                case 0x0029:
                    I = V[X] * 0x5;
                break;

                case 0x0033:
                    memory[I] = V[X] / 100;
                    memory[I + 1] = (V[X] / 10) % 10;
                    memory[I + 2] = (V[X] % 100) % 10;
                break;

                case 0x0055:
                    for (int i = 0; i <= V[X]; i++) memory[I + i] = V[i];
                    I = I + X + 1;
                break;

                case 0x0065:
                    for (int i = 0; i <= V[X]; i++) V[i] = memory[I + i];
                    I = I + X + 1;
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

    if (!jumpFlag) pc += 2;

    timerCycle();
}

bool Cpu::loadGame(string *gameName)
{
    cout << "Loading: " << *gameName << endl;
    stringstream fileGame;
    if (!loadFile(gameName, fileGame)) return false;

    string fileData = fileGame.str();
    cout << "File size: " << fileData.length() << " bytes." << endl;

    if (0x1000 - 0x200 > fileData.length())
    {
        for (int i = 0; i < fileData.length(); i++)
        {
            memory[i + 512] = fileData[i];
        }
    }
    else
    {
        cout << "Error! ROM is bigger than available memory." << endl;
        return false;
    }

    cout << "Successfuly loaded!" << "\n";
    return true;
}

void Cpu::setKeys()
{
    
}

void Cpu::timerCycle()
{
    if (!clock.isCpuClockCompleted())
    {
        if (skipFlag)
        {
            unsigned int timeRemain = clock.getTimeRemain();
            std::this_thread::sleep_for(std::chrono::nanoseconds(timeRemain + 3 * clock.CPU_PERIOD_NS));
        }
        else if (!jumpFlag)
        {
            unsigned int timeRemain = clock.getTimeRemain();
            std::this_thread::sleep_for(std::chrono::nanoseconds(timeRemain + clock.CPU_PERIOD_NS));
        }
        else
        {
            unsigned int timeRemain = clock.getTimeRemain();
            std::this_thread::sleep_for(std::chrono::nanoseconds(timeRemain));
        }
        
    }
    
    if (delay_timer > 0)
    {
        if (clock.isTimerRunning())
        {
            if (clock.getTimerRemain() == 0)
            {
                delay_timer--;
                clock.resetTimer();
            }

            if (delay_timer == 0)
            {
                clock.stopTimer();
            }
            
        }
        else
        {
            clock.initTimer();
        }
    }
    
    if (sound_timer > 0)
    {
        sound_timer--;
        audio.play();
    }
}