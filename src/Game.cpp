#include "../include/Game.h"

Game::Game() :
    m_gameIsRunning{ false }
{

}
    
Game::~Game()
{
    cleanUp();
}
    
void Game::run()
{
    m_gameIsRunning = true;
    while (m_gameIsRunning)
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    std::cout << "Processing Events" << std::endl;
}

void Game::update()
{
    std::cout << "Updating" << std::endl;
}

void Game::render()
{
    std::cout << "Rendering" << std::endl;
}

void Game::cleanUp()
{
    std::cout << "Cleaning up" << std::endl;
}