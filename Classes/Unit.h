#pragma once
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#endif

#include "cocos2d.h"

using namespace cocos2d;

class TestScene1;

class Unit : public cocos2d::Sprite
{
public:
	//�������ͽ�
	float maxHp;
	float hp;
	float speed;
	float power;
	float delay = 1.0f;
	float time = 0;
	
	//������ ���
	Unit* enemy;

	//���丮 ����
	Vec2 myFactory;
	Vec2 enemyFactory;

	static Unit* createUnitL(); //���� ����
	static Unit* createUnitR(); //���� ����
	void initUnit(); //���� �ʱ�ȭ
	void initAni(); //���� �ִϸ��̼�



	//�׼� & �ִϸ��̼�
	MoveTo* move;

	Animation* moveAni;
	Animation* attackAni;
	Animation* dieAni;

	Animate* moveAct;
	Animate* attackAct;
	Animate* dieAct;

	//������ �Լ�
	void moveUnit(); //���� �̵�
	void attack();
	/*
	
	void damaged(); //�����ֿ��� ���� �޴� �Լ�
	void die(); //���� ���

	//get
	float getHp() { return hp; }
	Vec2 getMyFac() { return myFactory; }


	//�ִϸ��̼�

	





	//������ �Լ�
	void actionMove(float f);
	void actionAttack(float f);
	void actionDie(float f);
	
	void update(float f) override;

	//HP��
	Sprite* emptyHP;
	Sprite* fullHP;
	*/
};