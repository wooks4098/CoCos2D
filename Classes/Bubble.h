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
	BUBBLE b_stat;
	Sprite* Bubble_rt() { return bubble_s; }
private:
	cocos2d::EventListener* _listener;
	Sprite* bubble_s;
	Bubble* pBub;
	int _fixedPr;
	bool _useNodePr;
};