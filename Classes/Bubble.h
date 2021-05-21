#pragma once
#include "cocos2d.h"
#include "mecro.h"

class Bubble : public cocos2d::Sprite
{
public:
	static Bubble* create(const std::string& filename);// , BUBBLE b_slot);
	Bubble* BubbleCreate(BUBBLE info);
	void setPr(int fixedPr);
	void setP1r(int fixedPr);
	void setPrWiththis(bool useNodePr);
	void onEnter();
	void onExit();
	bool isMove();
	bool _isMove = false;
	//void DimuTick(float t);
	Bubble* Bubble_rt() { return pBub; }
	BUBBLE BubbleStat_rt() { return b_stat; }
private:
	cocos2d::EventListener* _listener;
	Sprite* bubble_s;
	BUBBLE b_stat;
	Bubble* pBub;
	int _fixedPr;
	bool _useNodePr;
};