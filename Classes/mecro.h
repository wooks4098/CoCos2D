#pragma once
#pragma once
#define FACTORY_RIGHT 0
#define FACTORY_LEFT 1
struct BUBBLE
{
	bool iscircle;		//��� true = �� | false = ������
	float Defense;		//����
	float Hp;			//ü��
	float SpawnSpeed;	//�����ӵ�
	float Damage;		//���ݷ�
	float AttackSpeed;	//���ݼӵ�
	float MoveSpeed;	//�̵��ӵ�
	int key;			//��ȣ
};

struct INVENPOS
{
	int x;
	int y;
	bool isFull;
};

enum Type
{
	C1_Blue, C1_Red, C1_Yellow, R1_Blue, R1_Red, R1_Yellow, C2_Blue, C2_Red, C2_Yellow, R2_Blue, R2_Red, R2_Yellow, None_Circle, None_Rhombus
};

enum Sound
{
	Bubble_Creat = 0, 
	Bubble_Mix, 
	Bubble_Select , 
	Bubble_Sell, 
	BackGround_0, 
	BackGround_1, 
	Bubble_Out, 
	Bubble_Set,
	Factory_Damage,
	Unit_Attack_0,
	Unit_Attack_1,
	Unit_Attack_2,
	Unit_Create,
	Unit_Dead_0,
	Unit_Dead_1,
	Unit_Dead_2,
	Unit_Upgrade,
	UI_Click,
	UI_End
};

class mecro
{
};

