#pragma once
struct BUBBLE
{
	bool iscircle;		//모양 true = 원 | false = 마름모
	float Defense;		//방어력
	float Hp;			//체력
	float SpawnSpeed;	//스폰속도
	float Damage;		//공격력
	float AttackSpeed;	//공격속도
	float MoveSpeed;	//이동속도
	int key;			//번호
};

enum Type
{
	C1_Blue, C1_Red, C1_Yellow, R1_Blue, R1_Red, R1_Yellow, C2_Blue, C2_Red, C2_Yellow, R2_Blue, R2_Red, R2_Yellow, None_Circle, None_Rhombus
};
