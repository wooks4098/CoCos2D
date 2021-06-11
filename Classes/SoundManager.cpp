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
		experimental::AudioEngine::play2d("Sound/B_Create.ogg", false, 1.0f);
		break;
	case Bubble_Mix:
		experimental::AudioEngine::play2d("Sound/B_Mix.ogg", false, 1.0f);
		break;
	case Bubble_Select:
		experimental::AudioEngine::play2d("Sound/B_Select.ogg", false, 1.0f);
		break;
	case Bubble_Sell:
		experimental::AudioEngine::play2d("Sound/B_Sell.ogg", false, 1.0f);
		break;
	case BackGround_0:
		experimental::AudioEngine::play2d("Sound/BG00.ogg", true, 1.0f);
		break;
	case BackGround_1:
		experimental::AudioEngine::play2d("Sound/BG01.ogg", false, 1.0f);
		break;
	case Bubble_Out:
		experimental::AudioEngine::play2d("Sound/F_Bubbleout.ogg", false, 1.0f);
		break;
	case Bubble_Set:
		experimental::AudioEngine::play2d("Sound/F_Bubbleset.ogg", false, 1.0f);
		break;
	case Factory_Damage:
		experimental::AudioEngine::play2d("Sound/F_Damaged.ogg", false, 1.0f);
		break;
	case Unit_Attack_0:
		experimental::AudioEngine::play2d("Sound/U_Attack00.ogg", false, 1.0f);
		break;
	case Unit_Attack_1:
		experimental::AudioEngine::play2d("Sound/U_Attack01.ogg", false, 1.0f);
		break;
	case Unit_Attack_2:
		experimental::AudioEngine::play2d("Sound/U_Attack02.ogg", false, 1.0f);
		break;
	case Unit_Create:
		experimental::AudioEngine::play2d("Sound/U_Create.ogg", false, 1.0f);
		break;
	case Unit_Dead_0:
		experimental::AudioEngine::play2d("Sound/U_Dead00.ogg", false, 1.0f);
		break;
	case Unit_Dead_1:
		experimental::AudioEngine::play2d("Sound/U_Dead01.ogg", false, 1.0f);
		break;
	case Unit_Dead_2:
		experimental::AudioEngine::play2d("Sound/U_Dead02.ogg", false, 1.0f);
		break;
	case Unit_Upgrade:
		experimental::AudioEngine::play2d("Sound/U_Upgrade.ogg", false, 1.0f);
		break;
	case UI_Click:
		experimental::AudioEngine::play2d("Sound/UI_Click.ogg", false, 1.0f);
		break;
	case UI_End:
		experimental::AudioEngine::play2d("Sound/UI_End.ogg", false, 1.0f);
		break;

	default:
		break;
	}
}