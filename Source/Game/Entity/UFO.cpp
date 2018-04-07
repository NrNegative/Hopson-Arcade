#include "UFO.h"

#include "../../DisplayInfo.h"

namespace {
    constexpr float WIDTH = 50;
    constexpr float HEIGHT = 25;
    constexpr float Y_POS = 50;
}

UFO::UFO(Random<>& rand)
: Collidable    (WIDTH, HEIGHT)
, m_rng         (rand)
{
    m_sprite.setSize({ WIDTH, HEIGHT });
    m_sprite.setPosition((float)Display::WIDTH, Y_POS);
}

UFO::State UFO::getState() const
{
    return m_state;
}

void UFO::update(float dt)
{
    switch (m_state) {
        case State::Destroyed:
            m_state = State::Waiting;
            break;

        case State::Flying:
            m_sprite.move(m_vx * dt, 0);
            if (getPosition().x <= -WIDTH || getPosition().x >= Display::WIDTH + WIDTH) {
                m_state = State::Waiting;
            }
            break;

        case State::Waiting:
            if (m_rng.getIntInRange(1, 250) == 100) {
                m_state = State::Flying;
                m_vx = (float)m_rng.getIntInRange(-1, 1) * 200.0f;
                float xPos;
                if (m_vx >= 0) {
                    xPos = -WIDTH;
                }
                else {
                    xPos = Display::WIDTH;
                }
                m_sprite.setPosition(xPos, Y_POS);
            }
            break;
        }
}

void UFO::draw(sf::RenderTarget & window)
{
    if (m_state == State::Flying) {
        window.draw(m_sprite);
    }
}

const sf::Vector2f & UFO::getPosition() const
{
    return m_sprite.getPosition();
}

void UFO::onCollide(Collidable & other)
{
    m_state = State::Destroyed;
}
