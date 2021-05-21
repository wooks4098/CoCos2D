#pragma once
#include "cocos2d.h"

class Bubble
{
public:
	static Bubble* create(const std::string& filename, bool iscc, float hp, float dmg, float def, float speed, float spawntime);
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