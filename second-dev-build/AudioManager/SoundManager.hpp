#ifndef AM_SOUNDMANAGER_HPP
#define AM_SOUNDMANAGER_HPP

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <random>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace am
{

class SoundManager
{
    public:
        SoundManager();
        ~SoundManager();

        std::shared_ptr<sf::Sound> prepareSound(std::string const& filename);
        bool playSound(std::string const& filename);
		bool playRandSound(std::string const& filename);

    protected:
        std::map<std::string,sf::SoundBuffer> mBuffers;
        std::vector<std::shared_ptr<sf::Sound>> mSounds;
};

} // namespace am

#endif // AM_SOUNDMANAGER_HPP