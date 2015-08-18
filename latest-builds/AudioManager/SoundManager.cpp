#include "SoundManager.hpp"

namespace am
{

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
    mSounds.clear();
    mBuffers.clear();
}

std::shared_ptr<sf::Sound> SoundManager::prepareSound(std::string const& filename)
{
    mSounds.push_back(std::make_shared<sf::Sound>());
    if (mBuffers.find(filename) == mBuffers.end())
    {
        assert(mBuffers[filename].loadFromFile(filename));
    }
    mSounds.back()->setBuffer(mBuffers.at(filename));
    return mSounds.back();
}

bool SoundManager::playSound(std::string const& filename)
{
	std::string fullPath = "resources/sounds/" + filename;
    auto s = prepareSound(fullPath);
    if (s != nullptr)
    {
        s->play();
        return true;
    }
    return false;
}

bool SoundManager::playRandSound(std::string const& filename)
{
	short maxNumberOfSounds = 0;
	if (filename == "sword/swipe") maxNumberOfSounds = 13;
	/*
		more
	*/

	short i = 0;
	srand(time(0));
	i = rand() % maxNumberOfSounds + 1;

	std::ostringstream numb;
	numb << i;
	std::string fullPath = "resources/sounds/" + filename + "/" + numb.str() + ".wav";
	auto s = prepareSound(fullPath);
	if (s != nullptr)
	{
		s->play();
		return true;
	}
	return false;
}

} // namespace am