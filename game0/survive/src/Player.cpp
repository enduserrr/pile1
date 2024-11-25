#include "Player.h"
#include "Weapon.h"
#include "InputHandler.h"
#include "Constants.h"
#include <vector>
#include "Game.h"

Player::Player(Game* pGame) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame),
    m_pWeapon(std::make_unique<Weapon>())
{
    // m_pWeapon = std::make_unique<Weapon>();
    m_pWeapon->setActive(true);
    setOrigin(sf::Vector2f(0.0f, 0.0f));
}

bool Player::initialise()
{
    m_sprite.setTexture(*m_pGame->getPlayerTexture());
    m_sprite.setScale(3.5f, 3.5f);
    setIsDead(false);
    setPosition(ScreenWidth / 2, ScreenHeight / 2);
    m_sprite.setPosition(getPosition());
    return true;
}

/**
 * @brief   Added screen wrap effect.
 */


void Player::move(InputData inputData, float deltaTime)
{
    float xSpeed = 0.0f;
    float ySpeed = 0.0f;

    // Update speed based on input
    xSpeed -= inputData.m_movingLeft * PlayerSpeed;
    xSpeed += inputData.m_movingRight * PlayerSpeed;
    ySpeed -= inputData.m_movingUp * PlayerSpeed;
    ySpeed += inputData.m_movingDown * PlayerSpeed;

    // Set direction based on input
    /* SHOULD CHANGE*/
    if (inputData.m_movingLeft && !inputData.m_movingRight)
        m_direction = LEFT;
    else if (inputData.m_movingRight && !inputData.m_movingLeft)
        m_direction = RIGHT;
    else if (inputData.m_movingUp && !inputData.m_movingDown)
        m_direction = UP;
    else if (inputData.m_movingDown && !inputData.m_movingUp)
        m_direction = DOWN;
    else if (inputData.m_movingUp && inputData.m_movingLeft)
        m_direction = UP_LEFT;
    else if (inputData.m_movingUp && inputData.m_movingRight)
        m_direction = UP_RIGHT;
    else if (inputData.m_movingDown && inputData.m_movingLeft)
        m_direction = DOWN_LEFT;
    else if (inputData.m_movingDown && inputData.m_movingRight)
        m_direction = DOWN_RIGHT;

    // Move the player
    sf::Transformable::move(sf::Vector2f(xSpeed * deltaTime, ySpeed * deltaTime));
        // Get the current position
    sf::Vector2f position = getPosition();

    // Check horizontal boundaries
    if (position.x < 0.0f) position.x = static_cast<float>(ScreenWidth);
    else if (position.x > static_cast<float>(ScreenWidth)) position.x = 0.0f;

    // Check vertical boundaries
    if (position.y < 0.0f) position.y = static_cast<float>(ScreenHeight);
    else if (position.y > static_cast<float>(ScreenHeight)) position.y = 0.0f;

    // Set the adjusted position
    setPosition(position);
    if (m_pWeapon->isActive() == false)
    {
        if (inputData.m_movingLeft && !inputData.m_movingRight) {
            m_direction = LEFT;
        } else if (!inputData.m_movingLeft && inputData.m_movingRight) {
            m_direction = RIGHT;
        }
        m_pWeapon->setDirection(m_direction);
    }
}

void Player::attack()
{
    if (m_pWeapon && m_pWeapon->isActive())
    {
        m_pWeapon->fireProjectile(m_direction);
    }
}

void Player::update(float deltaTime)
{
    sf::Vector2f weaponSize = m_pWeapon->getSize();

    m_sprite.setPosition(getPosition());
    m_pWeapon->setPosition(sf::Vector2f(
        getCenter().x - (m_direction == LEFT ? weaponSize.x : 0.0f),
        getCenter().y - weaponSize.y / 2.0f));
    m_pWeapon->update(deltaTime);
}

// void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
// {
//     Rectangle::draw(target, states);
//     m_pWeapon->draw(target, states);
// }

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the player
    Rectangle::draw(target, states);
    m_pWeapon->draw(target, states);
    // sf::RectangleShape playerRect(getSize());
    // playerRect.setFillColor(getColor());
    // playerRect.setPosition(getPosition());
    // target.draw(playerRect);

    // Draw the weapon and its projectiles
    if (m_pWeapon && m_pWeapon->isActive()) {
        m_pWeapon->draw(target, states);
    }
}

