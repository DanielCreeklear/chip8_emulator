#pragma once
#include <random>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "utils.h"
#include "clock.h"
#include "audio.h"

using namespace std;

const int MAX_ADDRESS_MEMORY = 0x1000;
const int MAX_REGISTERS = 16;
const int WIDTH = 64;
const int HEIGHT = 32;

class Cpu
{
    private:
        unsigned short opcode, jump_addr;
        unsigned char V[MAX_REGISTERS];
        unsigned short I;
        
        unsigned char delay_timer;
        unsigned char sound_timer;

        unsigned short stack[0x10];
        unsigned short sp;

        bool jumpFlag, skipFlag;

        unsigned short pixelX;
        unsigned short pixelY;
        unsigned short height;
        unsigned short pixelRow;
        bool keyPressed;

        unsigned short X, Y;

        unsigned char chip8_fontset[80] =
        { 
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };
        Clock clock;
        Audio audio;

        void timerCycle();
    public:
        Cpu();

        bool drawFlag;
        unsigned short pc;
        unsigned char gfx[WIDTH * HEIGHT];
        unsigned key[0x10];
        unsigned char memory[MAX_ADDRESS_MEMORY];

        void initialize(const float mhz);
        void emulateCycle();
        bool loadGame(string* gameName);
        void setKeys();
};