#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <string>
#include "Coordinator.h"

#include "components/Position.h"
#include "components/Health.h"
#include "components/Input.h"
#include "components/Name.h"

#include "systems/ControlSystem.h"
#include "systems/HealthSystem.h"
#include "systems/AISystem.h"
#include "systems/RenderSystem.h"

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

    void registerComponents(Coordinator & t_coord);
    void setupSystems(Coordinator & t_coord);
    void setupEntities(Coordinator & t_coord);

    bool m_gameIsRunning;

    std::shared_ptr<ecs::system::ControlSystem> m_controlSystem;
    std::shared_ptr<ecs::system::HealthSystem> m_healthSystem;
    std::shared_ptr<ecs::system::AISystem> m_aiSystem;
    std::shared_ptr<ecs::system::RenderSystem> m_renderSystem;

    std::vector<Entity> m_entities;
};

#endif // !GAME_H