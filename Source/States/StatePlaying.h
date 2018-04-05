#pragma once

#include "StateBase.h"
#include "../Game/InvaderManager.h"
#include "../Game/Player.h"
#include "../Game/Projectile.h"
#include "../Game/AnimationRenderer.h"

class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleInput    ()                              override;
        void update         (sf::Time deltaTime)            override;
        void fixedUpdate    (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
        InvaderManager m_invaders;
        Player m_player;


        sf::Clock m_invaderShotDelayTimer;
        sf::Clock m_shootDelayTimer;
        std::vector<Projectile> m_projectiles;
        AnimationRenderer m_projectileRenderer;

        Random<> m_rng;
        sf::Clock animTimer;
};
