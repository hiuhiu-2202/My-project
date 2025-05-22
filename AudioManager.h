#pragma once
#include <SDL_mixer.h>
#include <string>

using namespace std;

class AudioManager {
public:
	AudioManager();
	~AudioManager();

	bool loadAudio(const string& path);
	bool loadEffect(const string& path);
	void playMusic(int loops = -1);
	void playEffect();
	void stopMusic();
	void clean();
	void setMusicVolume(int volume);

private:
	Mix_Music* bgMusic = nullptr;
	Mix_Chunk* effect = nullptr;
};
