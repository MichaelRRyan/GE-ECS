#include <SDL.h>
#include <iostream>
#include <string>

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