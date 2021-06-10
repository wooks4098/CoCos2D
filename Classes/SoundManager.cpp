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
	case Bubble_Creat:
		experimental::AudioEngine::play2d("Sound/B_Create.wav", false, 1.0f);
		break;
	case Bubble_Mix:
		experimental::AudioEngine::play2d("Sound/B_Mix.wav", false, 1.0f);
		break;
	case Bubble_Select:
		experimental::AudioEngine::play2d("Sound/B_Select.wav", false, 1.0f);
		break;
	case Bubble_Sell:
		experimental::AudioEngine::play2d("Sound/B_Sell.wav", false, 1.0f);
		break;
	case BackGround_0:
		experimental::AudioEngine::play2d("Sound/BG00.wav", true, 1.0f);
		break;
	case BackGround_1:
		experimental::AudioEngine::play2d("Sound/BG01.wav", false, 1.0f);
		break;
	case Bubble_Out:
		experimental::AudioEngine::play2d("Sound/F_Bubbleout.wav", false, 1.0f);
		break;
	case Bubble_Set:
		experimental::AudioEngine::play2d("Sound/F_Bubbleset.wav", false, 1.0f);
		break;
	case Factory_Damage:
		experimental::AudioEngine::play2d("Sounds/BG00.mp3", false, 1.0f);
		break;
	case Unit_Attack_0:
		experimental::AudioEngine::play2d("Sound/U_Attack00.wav", false, 1.0f);
		break;
	case Unit_Attack_1:
		experimental::AudioEngine::play2d("Sound/U_Attack01.wav", false, 1.0f);
		break;
	case Unit_Attack_2:
		experimental::AudioEngine::play2d("Sound/U_Attack02.wav", false, 1.0f);
		break;
	case Unit_Creat:
		experimental::AudioEngine::play2d("Sound/U_Create.wav", false, 1.0f);
		break;
	case Unit_Dead_0:
		experimental::AudioEngine::play2d("Sound/U_Dead00.wav", false, 1.0f);
		break;
	case Unit_Dead_1:
		experimental::AudioEngine::play2d("Sound/U_Dead01.wav", false, 1.0f);
		break;
	case Unit_Dead_2:
		experimental::AudioEngine::play2d("Sound/U_Dead02.wav", false, 1.0f);
		break;
	case Unit_Upgrade:
		experimental::AudioEngine::play2d("Sound/U_Upgrade.wav", false, 1.0f);
		break;
	case UI_Click:
		experimental::AudioEngine::play2d("Sound/UI_Click.wav", false, 1.0f);
		break;
	case UI_End:
		experimental::AudioEngine::play2d("Sound/UI_End.wav", false, 1.0f);
		break;

	default:
		break;
	}
}