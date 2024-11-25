#pragma once

#include <SFML/Graphics.hpp>

class Projectile : public sf::RectangleShape {
public:
    Projectile(sf::Vector2f position, sf::Vector2f direction, float speed)
        : m_direction(direction), m_speed(speed) {
        setPosition(position);
        setSize(sf::Vector2f(5.0f, 5.0f));  // Small square shape for the projectile
        setFillColor(sf::Color::White);
    }

    void update(float deltaTime) {
        move(m_direction * m_speed * deltaTime);
    }

private:
    sf::Vector2f m_direction;
    float m_speed;
};
