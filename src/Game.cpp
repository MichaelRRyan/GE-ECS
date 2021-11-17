#include "../include/Game.h"

Game::Game() :
    m_gameIsRunning{ false },
    m_entities(MAX_ENTITIES)
{
    Coordinator & coord = *Coordinator::getInstance();

    // Registers the components.
    coord.registerComponent<ecs::component::Input>();
    coord.registerComponent<ecs::component::Health>();
    coord.registerComponent<ecs::component::Position>();

    // Registers and sets up the control system.
    m_controlSystem = coord.registerSystem<ecs::system::ControlSystem>();
    Signature signature;
    signature.set(coord.getComponentType<ecs::component::Input>());
    signature.set(coord.getComponentType<ecs::component::Position>());
    coord.setSystemSignature<ecs::system::ControlSystem>(signature);

    // Registers and sets up the health system.
    m_healthSystem = coord.registerSystem<ecs::system::HealthSystem>();
    signature.reset();
    signature.set(coord.getComponentType<ecs::component::Health>());
    coord.setSystemSignature<ecs::system::HealthSystem>(signature);

    // Registers and sets up the AI system.
    m_aiSystem = coord.registerSystem<ecs::system::AISystem>();
    signature.reset();
    signature.set(coord.getComponentType<ecs::component::Health>());
    signature.set(coord.getComponentType<ecs::component::Position>());
    coord.setSystemSignature<ecs::system::AISystem>(signature);

    // Registers and sets up the render system.
    m_renderSystem = coord.registerSystem<ecs::system::RenderSystem>();
    signature.reset();
    signature.set(coord.getComponentType<ecs::component::Position>());
    coord.setSystemSignature<ecs::system::RenderSystem>(signature);

    // Creates all the entities and adds a position component.
    float offset = 0.0f;
    for (Entity & entity : m_entities)
    {
        entity = coord.createEntity();
        coord.addComponent(entity, ecs::component::Position{ 50.0f + 50.0f * offset++, 50.0f });
    }

    // Sets up player.
    coord.addComponent(m_entities.at(0), ecs::component::Health{ 20.0f });
    coord.addComponent(m_entities.at(0), ecs::component::Input());
    
    // Sets up villain.
    coord.addComponent(m_entities.at(1), ecs::component::Health{ 50.0f });

    // Sets up Cortana.
    coord.addComponent(m_entities.at(2), ecs::component::Health{ 1000.0f });

    // Dinky Di requires no additional setup.
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