#pragma once
#include <Unit.h>

class LeftUnit :public Unit
{
public:
	static Unit* createUnit(Factory* myFac, Factory* enemyFac, BUBBLE bubble); //유닛 생성
	void initUnit(BUBBLE bubble) override; //유닛 초기화

	void idleUnit() override; //유닛 대기
	void moveUnit() override; //유닛 이동
	void attackUnit(Unit* enemy) override; //적 유닛 공격하기
	void attackFactory() override; //적 팩토리 공격하기
	void damaged(float damage) override; //데미지 입는 함수
	void dieUnit() override; //유닛 사망
	void removeUnit() override; //유닛 제거
	void removeVector() override;

	//콜백 함수
	void callbackAttack(Unit* enemy) override; //attackUnit에서 호출하는 콜백 함수
	void callbackAttackFac() override; //공격할 때 호출

	//스케줄 함수
	void update(float f) override; //유닛 충돌 체크
};
