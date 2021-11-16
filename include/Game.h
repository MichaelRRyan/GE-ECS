#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <string>
#include "Coordinator.h"

class Game
{
public:

    Game();
    ~Game();
    void run();

private:

    void processEvents();
    void update();
    void render();

    void cleanUp();

    bool m_gameIsRunning;

};

#endif // !GAME_H