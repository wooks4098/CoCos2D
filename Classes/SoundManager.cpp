#include "SoundManager.h"
SoundManager* SoundManager::m_hThis = nullptr;


void SoundManager::CreatAudio()
{
	experimental::AudioEngine::preload("Sounds/Test.ogg");
}

void SoundManager::Play(int _SoundNum)
{
	switch (_SoundNum)
	{
	case 0:
		experimental::AudioEngine::play2d("Sounds/Test.ogg", false, 1.0f);

	default:
		break;
	}
}