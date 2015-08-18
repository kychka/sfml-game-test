#ifndef AM_MUSICMANAGER_HPP
#define AM_MUSICMANAGER_HPP

#include <memory>
#include <string>
#include <SFML/Audio/Music.hpp>

namespace am
{
	class MusicManager
	{
		public:
			MusicManager();
			~MusicManager();
			std::shared_ptr<sf::Music> playMusic(std::string const& filename);
			std::shared_ptr<sf::Music> playList();
			void setPlaylist(std::vector<std::string> playlist);
			std::vector<std::string>& getPlaylist();
		protected:
			void updateMusicManager();
		protected:
			std::shared_ptr<sf::Music> mMusic;
			std::vector<std::string> mPlaylist;
			unsigned int mPlaylistIndex;
			bool mLoopMode;
	};
} // namespace am

#endif // AM_MUSICMANAGER_HPP