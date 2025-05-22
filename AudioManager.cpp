#include "AudioManager.h"

using namespace std;



AudioManager::AudioManager() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

AudioManager::~AudioManager() {
	clean();
	Mix_CloseAudio();
}

bool AudioManager::loadAudio(const string& path) {
	bgMusic = Mix_LoadMUS(path.c_str());
	return bgMusic != nullptr;
}

bool AudioManager::loadEffect(const string& path) {
	effect = Mix_LoadWAV(path.c_str());
	return effect != nullptr;
}

void AudioManager::playMusic(int loops) {
	if (bgMusic) {
		Mix_PlayMusic(bgMusic, loops);
	}
}

void AudioManager::playEffect() {
	if (effect) {
		Mix_PlayChannel(-1, effect, 0);
	}
}

void AudioManager::stopMusic() {
	Mix_HaltMusic();
}

void AudioManager::clean() {
	if (bgMusic) {
		Mix_FreeMusic(bgMusic);
		bgMusic = nullptr;
	}
	if (effect) {
		Mix_FreeChunk(effect);
		effect = nullptr;
	}
}

void AudioManager::setMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}
