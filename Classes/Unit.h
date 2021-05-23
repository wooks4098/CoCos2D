#pragma once
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#endif

#include "cocos2d.h"
using namespace cocos2d;

class TestScene1;

class Unit : public cocos2d::Sprite
{
private:
	//�������ͽ�
	float hp;
	float speed;
	float power;
	
	//���丮 ����
	Vec2 myFactory;
	Vec2 enemyFactory;


	MoveTo* move;

public:
	static Unit* createUnit(Vec2 v); //���� ����
	void moveUnit(float speed); //���� �̵�
	void stopUnit(); //���� �̵� ����
	void collision(float f); //���� �浹
	void hit(float f); //�������� �����ϴ� �Լ�
	void damaged(); //�����ֿ��� ���� �޴� �Լ�
	void die(); //���� ���

	float getHp() { return hp; }
	Vec2 getMyFac() { return myFactory; }

	Unit* enemy;

};