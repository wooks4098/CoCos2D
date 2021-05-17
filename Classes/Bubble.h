#pragma once
#include "cocos2d.h"

class Bubble : public cocos2d::Sprite
{
public:
	static Bubble* create(const std::string& filename);
	void setPr(int fixedPr);
	void setP1r(int fixedPr);
	void setPrWiththis(bool useNodePr);
	void onEnter();
	void onExit();
	bool isMove();
	bool _isMove = false;

private:
	cocos2d::EventListener* _listener;
	int _fixedPr;
	bool _useNodePr;
};