#include "../include/Game.h"

Game::Game() :
    m_gameIsRunning{ false },
    m_entities(MAX_ENTITIES)
{
    Coordinator & coord = *Coordinator::getInstance();

    registerComponents(coord);
    setupSystems(coord);
    setupEntities(coord);
}
    
Game::~Game()
{
    cleanUp();
}
    
void Game::run()
{
    while (m_renderSystem->isWindowOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    //std::cout << "Processing Events" << std::endl;
    m_renderSystem->processEvents();
}

void Game::update()
{
    //std::cout << "Updating" << std::endl;
}

void Game::render()
{
    //std::cout << "Rendering" << std::endl;
    m_renderSystem->render();
}

void Game::cleanUp()
{
    //std::cout << "Cleaning up" << std::endl;
}

void Game::registerComponents(Coordinator & t_coord)
{
    t_coord.registerComponent<ecs::component::Input>();
    t_coord.registerComponent<ecs::component::Health>();
    t_coord.registerComponent<ecs::component::Position>();
    t_coord.registerComponent<ecs::component::Name>();
}

void Game::setupSystems(Coordinator & t_coord)
{
    // Registers and sets up the control system.
    m_controlSystem = t_coord.registerSystem<ecs::system::ControlSystem>();
    Signature signature;
    signature.set(t_coord.getComponentType<ecs::component::Input>());
    signature.set(t_coord.getComponentType<ecs::component::Position>());
    t_coord.setSystemSignature<ecs::system::ControlSystem>(signature);

    // Registers and sets up the health system.
    m_healthSystem = t_coord.registerSystem<ecs::system::HealthSystem>();
    signature.reset();
    signature.set(t_coord.getComponentType<ecs::component::Health>());
    t_coord.setSystemSignature<ecs::system::HealthSystem>(signature);

    // Registers and sets up the AI system.
    m_aiSystem = t_coord.registerSystem<ecs::system::AISystem>();
    signature.reset();
    signature.set(t_coord.getComponentType<ecs::component::Health>());
    signature.set(t_coord.getComponentType<ecs::component::Position>());
    t_coord.setSystemSignature<ecs::system::AISystem>(signature);

    // Registers and sets up the render system.
    m_renderSystem = t_coord.registerSystem<ecs::system::RenderSystem>();
    signature.reset();
    signature.set(t_coord.getComponentType<ecs::component::Position>());
    signature.set(t_coord.getComponentType<ecs::component::Name>());

//#define RENDER_HEALTH
#ifdef RENDER_HEALTH
    signature.set(t_coord.getComponentType<ecs::component::Health>());
#endif

    t_coord.setSystemSignature<ecs::system::RenderSystem>(signature);
}

void Game::setupEntities(Coordinator & t_coord)
{
    // Creates all the entities and adds a position component.
    float offset = 0.0f;
    for (Entity & entity : m_entities)
    {
        entity = t_coord.createEntity();
        t_coord.addComponent(entity, ecs::component::Position{ 50.0f + 50.0f * offset++, 50.0f });
    }

    // Sets up player.
    t_coord.addComponent(m_entities.at(0), ecs::component::Name{ "Player" });
    t_coord.addComponent(m_entities.at(0), ecs::component::Health{ 20.0f });
    t_coord.addComponent(m_entities.at(0), ecs::component::Input());
    
    // Sets up villain.
    t_coord.addComponent(m_entities.at(1), ecs::component::Name{ "Villain" });
    t_coord.addComponent(m_entities.at(1), ecs::component::Health{ 50.0f });

    // Sets up Cortana.
    t_coord.addComponent(m_entities.at(2), ecs::component::Name{ "Cortana" });
    t_coord.addComponent(m_entities.at(2), ecs::component::Health{ 1000.0f });

    // Sets up Dinky Di.
    t_coord.addComponent(m_entities.at(3), ecs::component::Name{ "Dinki Di" });
}