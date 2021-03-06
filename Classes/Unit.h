#pragma once
#include "SoundManager.h"
#include "cocos2d.h"
#include "Factory.h"
#include "mecro.h"
#include <algorithm>

using namespace cocos2d;

class Unit : public cocos2d::Sprite
{
public:
	int unitNumber; //유닛의 번호

	//스테이터스
	float startHp; //초기 체력
	float startSpeed; //초기 이속
	float startPower; //초기 힘
	float hp; //현재 체력
	float speed; //이동속도
	float damage; //공격력
	float attackSpeed; //공격 속도
	float defense; //방어력

	bool isStop = false; //아군 유닛 충돌에 의해 정지한 상태인지
	//bool isFight = false; //싸우는 중인지 (유닛 or 팩토리)
	bool isAttackUnit = false; //유닛을 공격했는지
	bool isAttackFac = false; //팩토리를 공격했는지
	bool isDied = false; //죽었는지
	bool isDieAct = false; //죽는 애니메이션 한번만 하기 위해서

	//충돌한 아군 유닛
	Unit* buddyUnit = nullptr;
	Unit* backBuddyUnit = nullptr;

	//팩토리 정보
	Factory* myFactory;
	Factory* enemyFactory;
	Vec2 myFactoryPos;
	Vec2 enemyFactoryPos;

	//HP바
	Sprite* emptyHP;
	Sprite* fullHP;

	//함수
	void initData();
	void virtual initUnit(BUBBLE bubble) = 0; //유닛 초기화
	void virtual idleUnit() = 0; //유닛 대기
	void virtual moveUnit() = 0; //유닛 이동
	void virtual attackUnit(Unit* enemy) = 0; //적 유닛 공격하기
	void virtual attackFactory() = 0; //적 팩토리 공격하기
	void virtual dieUnit() = 0; //유닛 사망
	void virtual damaged(float damage) = 0; //데미지 입는 함수
	void died(); //데미지 입은 후에 사망하기 위한 함수

	//HP바 관련 함수
	void callbackHpBarAni(); //HP바 애니메이션
	void createHpBar();

	//콜백 함수
	void virtual callbackAttack(Unit* enemy) = 0; //공격할 때 호출
	void virtual callbackAttackFac() = 0; //공격할 때 호출
	void virtual removeUnit() = 0; //사망할 때 호출
	void virtual removeVector() = 0;

	//스케줄 함수
	void virtual update(float f) = 0;

	//사운드 함수
	void sound_create();
	void sound_attack();
	void sound_attackFac();
	void sound_upgrade();
	void sound_dead();
};