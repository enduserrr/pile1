#include "Weapon.h"
#include "Constants.h"
#include "Direction.h"
#include "Projectile.h"

/*// Weapon::Weapon() : Rectangle(sf::Vector2f(0, 0))
// {
//     setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
//     setOrigin(sf::Vector2f(0.0f, 0.0f));
//     setColor(sf::Color::Blue);
// }

// void Weapon::setActive(bool isActive)
// {
//     m_isActive = isActive;
//     if (isActive)
//     {
//         setSize(sf::Vector2f(WeaponWidth, WeaponHeight));
//         m_timer = WeaponActiveTime;
//     }
//     else
//     {
//         setSize(sf::Vector2f(0.0f, 0.0f));
//         m_timer = 0.0f;
//     }
// }

// void Weapon::update(float deltaTime)
// {
//     if (m_isActive)
//     {
//         m_timer -= deltaTime;
//         if (m_timer <= 0.0f)
//         {
//             setActive(false);
//         }
//     }
// }

// void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
// {
//     sf::RectangleShape graphicsRect(getSize());
//     graphicsRect.setFillColor(getColor());
//     graphicsRect.setPosition(getPosition());
//     target.draw(graphicsRect);
// }*/

Weapon::Weapon() : Rectangle(sf::Vector2f(0, 0)) {
    setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f));
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setColor(sf::Color::Blue);
}

void Weapon::setActive(bool isActive) {
    m_isActive = isActive;
    if (isActive) {
        setSize(sf::Vector2f(WeaponWidth, WeaponHeight));
        m_timer = WeaponActiveTime;
    } else {
        setSize(sf::Vector2f(0.0f, 0.0f));
        m_timer = 0.0f;
        m_projectiles.clear();
    }
}

void Weapon::update(float deltaTime) {
    if (m_isActive) {
        m_timer -= deltaTime;
        m_timeSinceLastShot += deltaTime;

        if (m_timeSinceLastShot >= m_fireRate) {
            fireProjectile(m_direction);
            m_timeSinceLastShot = 0.0f;
        }

        if (m_timer <= 0.0f) {
            setActive(false);
        }

        for (auto& projectile : m_projectiles) {
            projectile.update(deltaTime);
        }
    }
}

void Weapon::fireProjectile(eDirection direction)
{
    sf::Vector2f dirVector;

    // Convert eDirection to an sf::Vector2f direction vector
    switch (direction)
    {
        case LEFT:       dirVector = sf::Vector2f(-1.0f, 0.0f); break;
        case RIGHT:      dirVector = sf::Vector2f(1.0f, 0.0f); break;
        case UP:         dirVector = sf::Vector2f(0.0f, -1.0f); break;
        case DOWN:       dirVector = sf::Vector2f(0.0f, 1.0f); break;
        case UP_LEFT:    dirVector = sf::Vector2f(-0.707f, -0.707f); break;
        case UP_RIGHT:   dirVector = sf::Vector2f(0.707f, -0.707f); break;
        case DOWN_LEFT:  dirVector = sf::Vector2f(-0.707f, 0.707f); break;
        case DOWN_RIGHT: dirVector = sf::Vector2f(0.707f, 0.707f); break;
    }

    // Projectile speed
    dirVector *= (PlayerSpeed * 1.5f);

    // Create a new projectile with the calculated direction and speed
    m_projectiles.emplace_back(getPosition(), dirVector, PlayerSpeed * 1.5f);
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Draw the L shape by drawing two rectangles
    sf::RectangleShape verticalPart(sf::Vector2f(10.0f, 30.0f));
    sf::RectangleShape horizontalPart(sf::Vector2f(30.0f, 10.0f));

    verticalPart.setFillColor(sf::Color::Blue);
    horizontalPart.setFillColor(sf::Color::Blue);

    verticalPart.setPosition(getPosition());
    horizontalPart.setPosition(getPosition().x + 10.0f, getPosition().y);

    target.draw(verticalPart);
    target.draw(horizontalPart);
        // Draw the weapon itself (if needed)
    sf::RectangleShape graphicsRect(getSize());
    graphicsRect.setFillColor(getColor());
    graphicsRect.setPosition(getPosition());
    target.draw(graphicsRect);

    // Draw each projectile in m_projectiles
    for (const auto& projectile : m_projectiles) {
        target.draw(projectile); // Projectile should be drawable as it inherits from sf::RectangleShape
    }

    for (const auto& projectile : m_projectiles) {
        target.draw(projectile);
    }
}

