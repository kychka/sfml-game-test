#include "AudioManager.hpp"

namespace am
{

AudioManager::AudioManager()
{
}

void AudioManager::setGlobalVolume(float volume)
{
    sf::Listener::setGlobalVolume(volume);
}

float AudioManager::getGlobalVolume()
{
    return sf::Listener::getGlobalVolume();
}

void AudioManager::setPosition(float x, float y, float z)
{
    sf::Listener::setPosition(x,y,z);
}

void AudioManager::setPosition(const sf::Vector3f& position)
{
    sf::Listener::setPosition(position);
}

void AudioManager::setPosition(const sf::Vector2f& position, float z)
{
    sf::Listener::setPosition(position.x,position.y,z);
}

sf::Vector3f AudioManager::getPosition()
{
    return sf::Listener::getPosition();
}

void AudioManager::setDirection(float x, float y, float z)
{
    sf::Listener::setDirection(x,y,z);
}

void AudioManager::setDirection(const sf::Vector3f& direction)
{
    sf::Listener::setDirection(direction);
}

void AudioManager::setDirection(const sf::Vector2f& direction, float z)
{
    sf::Listener::setDirection(direction.x,direction.y,z);
}

sf::Vector3f AudioManager::getDirection()
{
    return sf::Listener::getDirection();
}

void AudioManager::update()
{
    updateMusicManager();
}

} // namespace am