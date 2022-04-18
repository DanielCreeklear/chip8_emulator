#include "Emulator.h"

Emulator::Emulator(int width, int height, char *game, Cpu *cpu, std::unordered_map<char, int> *keysMap)
{
	keysMapEmulator = keysMap;
	cpu = cpu;

	//setkeysMapEmulator();

	cpu->initialize(2.0f);
	cpu->loadGame(game);

	glutMainLoop();
}

void Emulator::setkeysMapEmulator()
{
	std::vector<Key> keys;

	// Read config.txt
	keys.push_back({'1', 1});
	keys.push_back({'2', 2});
	keys.push_back({'3', 3});
	keys.push_back({'q', 4});
	keys.push_back({'w', 5});
	keys.push_back({'e', 6});
	keys.push_back({'a', 7});
	keys.push_back({'s', 8});
	keys.push_back({'d', 9});
	keys.push_back({'z', 10});
	keys.push_back({'c', 11});
	keys.push_back({'v', 12});
	keys.push_back({'f', 13});
	keys.push_back({'r', 14});
	keys.push_back({'4', 15});
	keys.push_back({'x', 0});;

	for (Key key : keys) setKeyMap(key);
}

void Emulator::setKeyMap(Key key)
{
	keysMapEmulator->insert(std::make_pair(key.key, key.index));
}