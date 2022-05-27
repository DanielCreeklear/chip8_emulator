# CHIP-8 emulator
![GitHub repo size](https://img.shields.io/github/repo-size/danielcreeklear/chip8_emulator?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/danielcreeklear/chip8_emulator?style=for-the-badge)
![GitHub last commit](https://img.shields.io/github/last-commit/danielcreeklear/chip8_emulator?style=for-the-badge)
![GitHub Release Date](https://img.shields.io/github/release-date/danielcreeklear/chip8_emulator?style=for-the-badge)
![GitHub license](https://img.shields.io/github/license/danielcreeklear/chip8_emulator?style=for-the-badge)
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/54/Space_intercept.png/220px-Space_intercept.png"/>
<p>An emulator of CHIP-8, written in C++.</p>
<p>"CHIP-8 is an interpreted programming language, developed by Joseph Weisbecker. It was initially used on the COSMAC VIP and Telmac 1800 8-bit microcomputers in the mid-1970s. CHIP-8 programs are run on a CHIP-8 virtual machine. It was made to allow video games to be more easily programmed for these computers, but CHIP 8 is still used today, due to its simplicity, and consequently on any platform and its teaching of programming Binary numbers."</p>
<p><a href="https://en.wikipedia.org/wiki/CHIP-8" target="_blank">Wikipedia about CHIP-8</a></p>

# About the project
<p>The project was built with this <a href="http://devernay.free.fr/hacks/chip8/C8TECH10.HTM" target="_blank">documentation</a>.
This documentation it's required for build the cpu, inputs and outputs of CHIP-8.</p>
<p>The language chosen it's C++, there are plans to use this solution in a microcontroller, so
the language can help to speed up future development, where i'll just need to rewrite a few things.</p>

## Graphics
<img src="https://www.opengl.org/img/opengl_logo.jpg"/>
<p>To render graphics of the emulator, <a href="https://www.opengl.org/" target="_blank">OpenGL</a> is used.</p>

## Sound
<img src="https://www.libsdl.org/media/SDL_logo.png"/>
<p>To created sound of the emulator, <ahref="https://www.libsdl.org/" target="_blank">SDL2</a> is used.</p>

# Version history

## 1.0.0
### First version of emulator
- Compatibility with some games;
- Full screen support;

# Getting Started

## Running
```
chip8 [Path to file with code]
```
