#pragma once

#include "Rectangle.h"
#include "Projectile.h"
#include "Direction.h"
#include <vector>

class Weapon : public Rectangle {
public:
    Weapon();
    virtual ~Weapon() {}

    void setActive(bool isActive);
    void update(float deltaTime);
    bool isActive() const { return m_isActive; }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // void fireProjectile(sf::Vector2f direction);
    void fireProjectile(eDirection direction);
    void setDirection(eDirection direction) { m_direction = direction; }
    // void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
    bool m_isActive = false;
    float m_timer = 0.0f;
    float m_timeSinceLastShot = 0.0f;
    float m_fireRate = 0.5f; // Adjust as needed
    eDirection m_direction = RIGHT; // Default direction
    std::vector<Projectile> m_projectiles;
};
