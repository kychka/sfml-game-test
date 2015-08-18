#include "SoundManager.hpp"

std::random_device rd;
std::mt19937 gen(rd());

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
	std::uniform_int_distribution<int> uid(1, maxNumberOfSounds);
	i = uid(gen);
	std::string fullPath = "resources/sounds/" + filename + "/" + std::to_string(i) + ".wav";
	auto s = prepareSound(fullPath);
	if (s != nullptr)
	{
		s->play();
		return true;
	}
	return false;
}

} // namespace am