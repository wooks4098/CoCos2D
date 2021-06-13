#pragma once
#include "mecro.h"
#include "AudioEngine.h"
using namespace cocos2d;


class SoundManager
{
#pragma region ΩÃ±€≈Ê
	static SoundManager* m_hThis;
public:
	static SoundManager* GetInstance()
	{
		if (m_hThis == nullptr)
			m_hThis = new SoundManager;

		return m_hThis;
	}

#pragma endregion

private:
	//experimental::AudioEngine* test;

public:
	void CreatAudio();
	void Play(int _SoundNum);
	

};