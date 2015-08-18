#include "MusicManager.hpp"

namespace am
{

MusicManager::MusicManager() : mLoopMode(true)
{
    mMusic = std::make_shared<sf::Music>();
}

MusicManager::~MusicManager()
{
    mMusic = nullptr;
}

std::shared_ptr<sf::Music> MusicManager::playMusic(std::string const& filename)
{
	std::string fullPath = "resources/music/" + filename;
    mLoopMode = true;
    mMusic->setLoop(true);
    mMusic->stop();
    if (mMusic->openFromFile(fullPath))
    {
        mMusic->play();
    }
    return mMusic;
}

std::shared_ptr<sf::Music> MusicManager::playList()
{
    mLoopMode = false;
    mMusic->setLoop(false);
    mMusic->stop();
    mPlaylistIndex = 0;
    MusicManager::updateMusicManager();
    return mMusic;
}

void MusicManager::setPlaylist(std::vector<std::string> playlist)
{
    mPlaylist = playlist;
    mPlaylistIndex = 0;
}

std::vector<std::string>& MusicManager::getPlaylist()
{
    return mPlaylist;
}

void MusicManager::updateMusicManager()
{
    if (!mLoopMode && mMusic->getStatus() == sf::Music::Status::Stopped)
    {
        mPlaylistIndex++;
        if (mPlaylistIndex == mPlaylist.size())
        {
            mPlaylistIndex = 0;
        }
        if (mPlaylistIndex < mPlaylist.size() && mPlaylistIndex >= 0)
        {
            if (mMusic->openFromFile(mPlaylist.at(mPlaylistIndex)))
            {
                mMusic->play();
            }
        }
    }
}

} // namespace am