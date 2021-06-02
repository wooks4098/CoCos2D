#pragma once
#include "cocos2d.h"
#include "Factory.h"
using namespace cocos2d;

class Unit : public cocos2d::Sprite
{
public:
	//스테이터스
	float maxHp; //최대 체력
	float hp; //현재 체력
	float speed; //이동속도
	float power; //힘

	bool isFighting = false; //싸우는 중인지
	bool isDied = false; //죽었는지
	bool isStop = false; //아군 유닛 충돌에 의해 정지했는지

	//충돌한 아군 유닛
	Unit* buddyUnit = nullptr;

	//팩토리 정보
	Factory* myFactory;
	Factory* enemyFactory;

	//HP바
	Sprite* emptyHP;
	Sprite* fullHP;


	//함수
	void initData();
	void virtual initUnit() = 0; //유닛 초기화
	void virtual idleUnit() = 0; //유닛 대기
	void virtual moveUnit() = 0; //유닛 이동
	void virtual attackUnit(Unit* enemy) = 0; //적 유닛 공격하기
	void damaged(float damage); //데미지를 입는 함수
	void virtual dieUnit() = 0; //유닛 사망

	//콜백 함수
	void virtual callbackAttack(Unit* enemy) = 0;
	void removeUnit();

	//스케줄 함수
	void virtual update(float f) = 0;
};