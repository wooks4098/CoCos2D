#pragma once
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

enum Type
{
	C1_Blue, C1_Red, C1_Yellow, R1_Blue, R1_Red, R1_Yellow, C2_Blue, C2_Red, C2_Yellow, R2_Blue, R2_Red, R2_Yellow, None_Circle, None_Rhombus
};
