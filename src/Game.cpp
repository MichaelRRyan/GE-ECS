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

float getCurrentSeconds()
{
    return static_cast<float>(SDL_GetTicks()) / 1000.0f;
}

void Game::run()
{
    float lastUpdateTime = getCurrentSeconds();
    const float FPS{ 60.0f };
    float timePerFrame = 1.0f / FPS;
    while (!m_controlSystem->isExiting())
    {
        processEvents();
        float now = getCurrentSeconds();
        if (now >= lastUpdateTime + timePerFrame)
        {
            float dt = now - lastUpdateTime;
            processEvents();
            update(dt);
            lastUpdateTime = now;
        }
        render();
    }
}

void Game::processEvents()
{
    //std::cout << "Processing Events" << std::endl;
    m_controlSystem->processEvents();
}

void Game::update(float t_delta)
{
    //std::cout << "Updating" << std::endl;
    m_aiSystem->update(t_delta);
    m_controlSystem->update(t_delta);
}

void Game::render()
{
    //std::cout << "Rendering" << std::endl;
    m_renderSystem->render();
    m_healthSystem->render();
    m_renderSystem->display();
}

void Game::cleanUp()
{
    //std::cout << "Cleaning up" << std::endl;
}

void Game::registerComponents(Coordinator & t_coord)
{
    t_coord.registerComponent<ecs::component::Name>();
    t_coord.registerComponent<ecs::component::Health>();
    t_coord.registerComponent<ecs::component::Input>();
    t_coord.registerComponent<ecs::component::Position>();
    t_coord.registerComponent<ecs::component::AI>();
}

void Game::setupSystems(Coordinator & t_coord)
{
    // Registers and sets up the control system.
    m_controlSystem = t_coord.registerSystem<ecs::system::ControlSystem>();
    Signature signature;
    signature.set(t_coord.getComponentType<ecs::component::Input>());
    signature.set(t_coord.getComponentType<ecs::component::Position>());
    t_coord.setSystemSignature<ecs::system::ControlSystem>(signature);

    // Registers and sets up the render system.
    m_renderSystem = t_coord.registerSystem<ecs::system::RenderSystem>();
    signature.reset();
    signature.set(t_coord.getComponentType<ecs::component::Position>());
    signature.set(t_coord.getComponentType<ecs::component::Name>());
    t_coord.setSystemSignature<ecs::system::RenderSystem>(signature);

    // Registers and sets up the health system.
    m_healthSystem = t_coord.registerSystem<ecs::system::HealthSystem>();
    signature.reset();
    signature.set(t_coord.getComponentType<ecs::component::Health>());
    signature.set(t_coord.getComponentType<ecs::component::Name>());
    t_coord.setSystemSignature<ecs::system::HealthSystem>(signature);
    
    m_healthSystem->setRenderer(m_renderSystem->getRenderer());

    // Registers and sets up the AI system.
    m_aiSystem = t_coord.registerSystem<ecs::system::AISystem>();
    signature.reset();
    signature.set(t_coord.getComponentType<ecs::component::Health>());
    signature.set(t_coord.getComponentType<ecs::component::Position>());
    signature.set(t_coord.getComponentType<ecs::component::AI>());
    t_coord.setSystemSignature<ecs::system::AISystem>(signature);
}

void Game::setupEntities(Coordinator & t_coord)
{
    std::string names[]{ "Player", "Villain", "Cortana", "Dinki Di" };

    // Creates all the entities and adds a name component.
    int i = 0;
    for (Entity & entity : m_entities)
    {
        entity = t_coord.createEntity();
        t_coord.addComponent(entity, ecs::component::Name{ names[i++] });
    }

    // Sets up player.
    t_coord.addComponent(m_entities.at(0), ecs::component::Health{ 20.0f });
    t_coord.addComponent(m_entities.at(0), ecs::component::Position{ 50.0f, 50.0f });
    t_coord.addComponent(m_entities.at(0), ecs::component::Input());
    
    // Sets up villain.
    t_coord.addComponent(m_entities.at(1), ecs::component::Health{ 50.0f });
    t_coord.addComponent(m_entities.at(1), ecs::component::Position{ 150.0f, 50.0f });
    t_coord.addComponent(m_entities.at(1), ecs::component::AI{ 0.0f, 0.0f, 10.0f });

    // Sets up Cortana.
    t_coord.addComponent(m_entities.at(2), ecs::component::Health{ 1000.0f });
    t_coord.addComponent(m_entities.at(2), ecs::component::Position{ 250.0f, 50.0f });
    t_coord.addComponent(m_entities.at(2), ecs::component::AI{ 0.0f, 0.0f, 20.0f });

    // Sets up Dinky Di.
    t_coord.addComponent(m_entities.at(3), ecs::component::Position{ 350.0f, 50.0f });
}