#ifndef AM_AUDIOMANAGER_HPP
#define AM_AUDIOMANAGER_HPP

#include <SFML/Audio/Listener.hpp>
#include <SFML/System/Vector2.hpp>

#include "MusicManager.hpp"
#include "SoundManager.hpp"

namespace am
{

class AudioManager : public MusicManager, public SoundManager
{
    public:
        AudioManager();

        static void setGlobalVolume(float volume);
        static float getGlobalVolume();

        static void setPosition(float x, float y, float z = 0);
        static void setPosition(const sf::Vector3f& position);
        static void setPosition(const sf::Vector2f& position, float z = 0);
        static sf::Vector3f getPosition();

        static void setDirection(float x, float y, float z = 0);
        static void setDirection(const sf::Vector3f& direction);
        static void setDirection(const sf::Vector2f& direction, float z = 0);
        static sf::Vector3f getDirection();

        void update();

};

} // namespace am

#endif // AM_AUDIOMANAGER_HPP